/**
 ******************************************************************************
 * @file    feature_extraction.c
 * @author  MCD Application Team
 * @brief   Spectral feature extraction functions
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Software License Agreement
 * SLA0055, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *        www.st.com/resource/en/license_agreement/dm00251784.pdf
 *
 ******************************************************************************
 */
#include "feature_extraction.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288 /*!< pi */
#endif

/**
 * @defgroup groupFeature Feature Extraction
 * @brief Spectral feature extraction functions
 * @{
 */

/**
 * @brief      Convert 16-bit PCM into floating point values
 *
 * @param      *pInSignal  points to input signal buffer
 * @param      *pOutSignal points to output signal buffer
 * @param      len         signal length
 */
void buf_to_float(int16_t *pInSignal, float32_t *pOutSignal, uint32_t len)
{
  for (uint32_t i = 0; i < len; i++)
  {
    pOutSignal[i] = (float32_t) pInSignal[i];
  }
}

/**
 * @brief      Convert 16-bit PCM into normalized floating point values
 *
 * @param      *pInSignal   points to input signal buffer
 * @param      *pOutSignal  points to output signal buffer
 * @param      len          signal length
 */
void buf_to_float_normed(int16_t *pInSignal, float32_t *pOutSignal, uint32_t len)
{
  for (uint32_t i = 0; i < len; i++)
  {
    pOutSignal[i] = (float32_t) pInSignal[i] / (1 << 15);
  }
}

/**
 * @brief      Power Spectrogram column
 *
 * @param      *S          points to an instance of the floating-point Spectrogram structure.
 * @param      *pInSignal  points to the in-place input signal frame of length FFTLen.
 * @param      *pOutCol    points to  output Spectrogram column.
 * @return     None
 */
void SpectrogramColumn(SpectrogramTypeDef *S, float32_t *pInSignal, float32_t *pOutCol)
{
  uint32_t frame_len = S->FrameLen;
  uint32_t n_fft = S->FFTLen;
  float32_t *scratch_buffer = S->pScratch;

  float32_t first_energy;
  float32_t last_energy;

  /* In-place window application (on signal length, not entire n_fft) */
  /* @note: OK to typecast because hannWin content is not modified */
  arm_mult_f32(pInSignal, S->pWindow, pInSignal, frame_len);

  /* Zero pad if signal frame length is shorter than n_fft */
  memset(&pInSignal[frame_len], 0, n_fft - frame_len);

  /* FFT */
  arm_rfft_fast_f32(S->pRfft, pInSignal, scratch_buffer, 0);

  /* Power spectrum */
  first_energy = scratch_buffer[0] * scratch_buffer[0];
  last_energy = scratch_buffer[1] * scratch_buffer[1];
  pOutCol[0] = first_energy;
  arm_cmplx_mag_squared_f32(&scratch_buffer[2], &pOutCol[1], (n_fft / 2) - 1);
  pOutCol[n_fft / 2] = last_energy;

  /* Magnitude spectrum */
  if (S->Type == SPECTRUM_TYPE_MAGNITUDE)
  {
    for (uint32_t i = 0; i < (n_fft / 2) + 1; i++)
    {
      arm_sqrt_f32(pOutCol[i], &pOutCol[i]);
    }
  }
}

/**
 * @brief      Mel Spectrogram column
 *
 * @param      *S          points to an instance of the floating-point Mel structure.
 * @param      *pInSignal  points to input signal frame of length FFTLen.
 * @param      *pOutCol    points to  output Mel Spectrogram column.
 * @return     None
 */
void MelSpectrogramColumn(MelSpectrogramTypeDef *S, float32_t *pInSignal, float32_t *pOutCol)
{
  float32_t *tmp_buffer = S->SpectrogramConf->pScratch;

  /* Power Spectrogram */
  SpectrogramColumn(S->SpectrogramConf, pInSignal, tmp_buffer);

  /* Mel Filter Banks Application */
  MelFilterbank(S->MelFilter, tmp_buffer, pOutCol);
}

/**
 * @brief      Log-Mel Spectrogram column
 *
 * @param      *S          points to an instance of the floating-point Log-Mel structure.
 * @param      *pInSignal  points to input signal frame of length FFTLen.
 * @param      *pOutCol    points to  output Log-Mel Spectrogram column.
 * @return     None
 */
void LogMelSpectrogramColumn(LogMelSpectrogramTypeDef *S, float32_t *pInSignal, float32_t *pOutCol)
{
  uint32_t n_mels = S->MelSpectrogramConf->MelFilter->NumMels;
  float32_t top_dB = S->TopdB;
  float32_t ref = S->Ref;
  float32_t *tmp_buffer = S->MelSpectrogramConf->SpectrogramConf->pScratch;

  SpectrogramColumn(S->MelSpectrogramConf->SpectrogramConf, pInSignal, tmp_buffer);

  /* Mel Filter Banks Application to power spectrum column */
  MelFilterbank(S->MelSpectrogramConf->MelFilter, tmp_buffer, pOutCol);

  /* Scaling */
  for (uint32_t i = 0; i < n_mels; i++) {
    pOutCol[i] /= ref;
  }

  /* Avoid log of zero or a negative number */
  for (uint32_t i = 0; i < n_mels; i++) {
    if (pOutCol[i] <= 0.0f) {
      pOutCol[i] = FLT_MIN;
    }
  }

  if (S->LogFormula == LOGMELSPECTROGRAM_SCALE_DB)
  {
    /* Convert power spectrogram to decibel */
    for (uint32_t i = 0; i < n_mels; i++) {
      pOutCol[i] = 10.0f * log10f(pOutCol[i]);
    }

    /* Threshold output to -top_dB dB */
    for (uint32_t i = 0; i < n_mels; i++) {
      pOutCol[i] = (pOutCol[i] < -top_dB) ? (-top_dB) : (pOutCol[i]);
    }
  }
  else
  {
    /* Convert power spectrogram to log scale */
    for (uint32_t i = 0; i < n_mels; i++) {
      pOutCol[i] = logf(pOutCol[i]);
    }
  }

}

/**
 * @brief      Mel-Frequency Cepstral Coefficients (MFCCs) column
 *
 * @param      *S          points to an instance of the floating-point MFCC structure.
 * @param      *pInSignal  points to input signal frame of length FFTLen.
 * @param      *pOutCol    points to  output MFCC spectrogram column.
 * @return     None
 */
void MfccColumn(MfccTypeDef *S, float32_t *pInSignal, float32_t *pOutCol)
{
  float32_t *tmp_buffer = S->pScratch;

  LogMelSpectrogramColumn(S->LogMelConf, pInSignal, tmp_buffer);

  /* DCT for computing MFCCs from spectrogram slice. */
  DCT(S->pDCT, tmp_buffer, pOutCol);
}

/**
 * @} end of groupFeature
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
