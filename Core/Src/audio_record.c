/**
 *******************************************************************************
 * @file           : audio_record.c
 * @brief          : This file contains the functions to acquire and process
 * 					 input MEMS microphone audio.
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>
#include "audio_record.h"

/* Variables -----------------------------------------------------------------*/

/* PCM data of input audio signal */
uint16_t pcm_buffer[PCM_BUFFER_SIZE];

/* PDM to PCM conversion data of input audio signal */
static uint16_t pdmtopcm_buffer[PCM_OUT_SIZE];

/* Input audio signal in PDM form */
static uint16_t pdm_buffer[PDM_BUFFER_SIZE];

/* Offset to copy `pdmtopcm_buffer` into `pcm_buffer` */
__IO uint32_t pcm_offset = 0;

/* Indicates the transfer of PDM data from microphone into `pdm_buffer` */
DMA_Buffer_State dma_transfer_state;

/* Indicates the end of the PCM data acquisition */
__IO uint32_t data_ready = 0;

/* Functions -----------------------------------------------------------------*/

/**
 * @brief Record audio signal.
 *   This function acquires the input audio signal from the audio peripheral
 *   through I2S2 in PDM form and transforms it into PCM signal.
 *
 * @param  None
 *
 * @retval None
 */
void audio_record(void) {
	dma_transfer_state = OFFSET_NONE;

	/* Initialize audio peripheral */
	if (BSP_AUDIO_IN_Init(DEFAULT_AUDIO_IN_FREQ,
	DEFAULT_AUDIO_IN_BIT_RESOLUTION,
	DEFAULT_AUDIO_IN_CHANNEL_NBR) != AUDIO_OK) {
		Error_Handler();
	}

	/* Start the audio input record */
	if (BSP_AUDIO_IN_Record((uint16_t*) &pdm_buffer[0],
	PDM_BUFFER_SIZE) != AUDIO_OK) {
		Error_Handler();
	}

	data_ready = 0;

	/* Wait for the data to be ready in the PCM form */
	while (data_ready != 1) {
		if (dma_transfer_state == OFFSET_HALF) {
			/* PDM to PCM data conversion */
			BSP_AUDIO_IN_PDMToPCM((uint16_t*) &pdm_buffer[0],
					(uint16_t*) &pdmtopcm_buffer[0]);

			/* Copy of PCM data into the final buffer. It copies PCM_OUT_SIZE * 2
			 * because they are uint16_t, which are 2 bytes long and memcpy
			 * expects a size in bytes.
			 */
			memcpy((uint16_t*) &pcm_buffer[pcm_offset * PCM_OUT_SIZE],
					pdmtopcm_buffer,
					PCM_OUT_SIZE * 2);

			dma_transfer_state = OFFSET_NONE;

			/* if the buffer is full, audio acquisition is done */
			if (pcm_offset == (PCM_BUFFER_SIZE / (PCM_OUT_SIZE)) - 1) {
				data_ready = 1;
				pcm_offset = 0;
			} else {
				pcm_offset++;
			}

		}

		if (dma_transfer_state == OFFSET_FULL) {
			/* PDM to PCM data convert */
			BSP_AUDIO_IN_PDMToPCM((uint16_t*) &pdm_buffer[PDM_BUFFER_SIZE / 2],
					(uint16_t*) &pdmtopcm_buffer[0]);

			/* Copy of PCM data into the final buffer. It copies PCM_OUT_SIZE * 2
			 * because they are uint16_t, which are 2 bytes long and memcpy
			 * expects a size in bytes.
			 */
			memcpy((uint16_t*) &pcm_buffer[pcm_offset * (PCM_OUT_SIZE)],
					pdmtopcm_buffer,
					PCM_OUT_SIZE * 2);

			dma_transfer_state = OFFSET_NONE;

			/* if the buffer is full, audio acquisition is done */
			if (pcm_offset == (PCM_BUFFER_SIZE / (PCM_OUT_SIZE)) - 1) {
				data_ready = 1;
				pcm_offset = 0;
			} else {
				pcm_offset++;
			}
		}
	}

	/* Stop audio record */
	if (BSP_AUDIO_IN_Stop() != AUDIO_OK) {
		Error_Handler();
	}
}

/**
 * @brief Manages the DMA Transfer complete interrupt
 * @param  None
 * @retval None
 */
void BSP_AUDIO_IN_TransferComplete_CallBack(void) {
	dma_transfer_state = OFFSET_FULL;
}

/**
 * @brief  Manages the DMA Half Transfer complete interrupt
 * @param  None
 * @retval None
 */
void BSP_AUDIO_IN_HalfTransfer_CallBack(void) {
	dma_transfer_state = OFFSET_HALF;
}

/**
 * @brief  Audio IN Error callback function
 * @param  pData
 * @retval None
 */
void BSP_AUDIO_IN_Error_Callback(void) {
	Error_Handler();
}
