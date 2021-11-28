/*
 * dsp.c
 *
 *  Created on: Nov 19, 2021
 *      Author: federica
 */

#include "dsp.h"
//#include "main.h"
//#include "lookup.h"

//#define ARM_MATH_CM4
//#include <arm_math.h>
//#include "arm_const_structs.h"
//#include "fft.h"

//void clear_mfcc(void);
//uint32_t calc_dtw(const float *s, const float *t);

/*
 mfcc_templates for
 4play
 4stop
 4red
 4blue
 4green
 4orange
 */

/*#if RECORDING
 float mfcc_templates[40][NUMBER_OF_FRAMES*12];
 static int boom;
 #endif
 */

/*const float LPF_precalc[256][16];
const float hamming_window_400[400];
const float mel_filterbank_257x26_div400[6682];
const float dct_table_26x12[312];
const int frame_base[32];
const float mfcc_templates[24][312];

static float mfcc[NUMBER_OF_FRAMES * 12];

arm_matrix_instance_f32 power_frame_struct;
arm_matrix_instance_f32 mel_filterbank_struct;
arm_matrix_instance_f32 mel_26_struct;

arm_matrix_instance_f32 log_26_struct;
arm_matrix_instance_f32 dct_table_struct;
arm_matrix_instance_f32 dct_12_struct;

float frame[FRAME_SIZE];
float hamming_frame[FRAME_SIZE];
float fft_frame[514];
float power_frame[257];
float mel_26[26];
float log_26[26];

//static uint8_t PDM_temp[992];

/*void cost_calc(float* PCM_buff, uint32_t* count) {
 float cost = 0, temp;
 if (*count == 512) {
 for (int i = 0; i < 512; i++) {
 abzf(temp, PCM_buff[i]);
 cost += temp;
 }
 if (cost < 20) {
 *count = 0;
 }
 } else if (*count == 1024) {
 for (int i = 512; i < 1024; i++) {
 abzf(temp, PCM_buff[i]);
 cost += temp;
 }
 if (cost < 50) {
 if (cost > 20) {
 memcpy(PCM_buff, &PCM_buff[512], 2048);
 *count = 512;
 } else {
 *count = 0;
 }
 }
 }
 }

 void PDM_to_PCM(uint16_t *PDMBuf, float *PCMBuf) {
 int i = 0, j, k, l, m;
 uint8_t* var;
 float temp, temp1, temp2, temp3, temp4;

 var = &PDM_temp[480];
 while (i < 512) {
 *var++ = (uint8_t)((PDMBuf[i >> 2] & 0xF000) >> 12);
 *var++ = (uint8_t)((PDMBuf[i >> 2] & 0x0F00) >> 8);
 *var++ = (uint8_t)((PDMBuf[i >> 2] & 0x00F0) >> 4);
 *var++ = (uint8_t)(PDMBuf[i >> 2] & 0x000F);
 i += 4;
 }
 i = 0;
 while (i < 16) {
 var = &PDM_temp[i * 32];
 temp = -4;	//-4 is to remove dc
 j = 0;
 k = 1;
 l = 2;
 m = 3;
 while (j < 256) {
 temp1 = LPF_precalc[j][var[j]];
 temp2 = LPF_precalc[k][var[k]];
 temp3 = LPF_precalc[l][var[l]];
 temp4 = LPF_precalc[m][var[m]];
 j += 4;
 k = j + 1;
 l = j + 2;
 m = j + 3;
 temp = temp + temp1 + temp2 + temp3 + temp4;
 }
 PCMBuf[i] = temp;
 i++;
 }
 memcpy(&PDM_temp[0], &PDM_temp[512], 480);
 }*/

void PCM_post_processing(float *PCM_buff, uint16_t size) {
	float avg = 0, max = 0, temp;
	for (int i = 0; i < size; i++) {
		avg += PCM_buff[i];
	}
	avg /= size;
	for (int i = 0; i < size; i++) {
		PCM_buff[i] = PCM_buff[i] - avg;
		abzf(temp, PCM_buff[i]);
		if (max < temp) {
			max = temp;
		}
	}
	max /= 0.95f;
	for (int i = 0; i < size; i++) {
		PCM_buff[i] = PCM_buff[i] / max;
	}
}
/*void init_mfcc(void) {
	power_frame_struct.numRows = 1;
	power_frame_struct.numCols = 257;
	power_frame_struct.pData = power_frame;

	mel_filterbank_struct.numRows = 257;
	mel_filterbank_struct.numCols = 26;
	mel_filterbank_struct.pData = (float*) mel_filterbank_257x26_div400;

	mel_26_struct.numRows = 1;
	mel_26_struct.numCols = 26;
	mel_26_struct.pData = mel_26;

	log_26_struct.numRows = 1;
	log_26_struct.numCols = 26;
	log_26_struct.pData = log_26;

	dct_table_struct.numRows = 26;
	dct_table_struct.numCols = 12;
	dct_table_struct.pData = (float*) dct_table_26x12;

	dct_12_struct.numRows = 1;
	dct_12_struct.numCols = 12;
}

arm_matrix_instance_f32 *calc_mfcc(const float *buffer_float) {
	int op_status;
	arm_rfft_fast_instance_f32 S;

	for (int i = 0; i < NUMBER_OF_FRAMES; i++) {
		arm_mult_f32((float*) &buffer_float[frame_base[i]],
				(float*) hamming_window_400, hamming_frame, FRAME_SIZE); //&buffer_float[frame_base[i]]

		op_status = arm_rfft_fast_init_f32(&S, 512);
		if (op_status != 0) {
			Error_Handler();
		}
		memset(fft_frame, 0, sizeof(fft_frame));

		arm_rfft_fast_f32(&S, hamming_frame, fft_frame, 0);
		fft_frame[512] = fft_frame[1];	//rearranging for power calc
		fft_frame[513] = 0;
		fft_frame[1] = 0;

		arm_cmplx_mag_squared_f32(fft_frame, power_frame, 257);		//pow calc

		op_status = arm_mat_mult_f32(&power_frame_struct,
				&mel_filterbank_struct, &mel_26_struct);
		if (op_status != 0) {
			Error_Handler();
		}

		for (int j = 0; j < 26; j++) {
			log_26[j] = log10f(mel_26[j]);		//log calc
		}

		//dct_12_struct.pData = &mfcc[i * 12];			//store mfcc
		op_status = arm_mat_mult_f32(&log_26_struct, &dct_table_struct,
				&dct_12_struct);		//dct calc
		if (op_status != 0) {
			Error_Handler();
		}

//		clear_mfcc();
	}
	return &dct_12_struct;
}
/*#if RECORDING
 for(int i=0;i<NUMBER_OF_FRAMES*12;i++)
 {
 mfcc_templates[boom][i]=mfcc[i];
 }
 boom++;
 #endif
 }

 uint32_t result_mfcc(void) {
 uint32_t similarity[WORDS], similarity2[WORDS * 4];
 int32_t temp = 0;
 uint32_t out;
 memset(similarity, 0, sizeof(similarity));
 for (int i = 0; i < WORDS; i++) {
 for (int j = 0; j < ACCURACY; j++) {
 similarity2[j + temp] = calc_dtw(&mfcc[0],
 &mfcc_templates[j + temp][0]);
 similarity[i] += similarity2[j + temp];
 }
 temp += 4;
 }
 //	arm_min_q31((int32_t*)similarity,WORDS,&temp,&out);	//sum of 4 differences
 arm_min_q31((int32_t*) similarity2, WORDS * ACCURACY, &temp, &out);
 out /= ACCURACY;

 return out;
 }

 // calc_dtw : array s with size N and array t with size M(here M,N=12*NUMBER_OF_FRAMES)
 uint32_t calc_dtw(const float* s, const float* t) {
 int start, end, window;
 float *x, *y, *temp, result;

 float buf1[12 * NUMBER_OF_FRAMES], buf2[12 * NUMBER_OF_FRAMES];
 x = &buf1[0];
 y = &buf2[0];

 uint32_t M = 12 * NUMBER_OF_FRAMES;
 uint32_t N = 12 * NUMBER_OF_FRAMES;
 window = N / 4;

 memset(buf1, 0x5F, N * 4);
 memset(buf2, 0x5F, N * 4);
 d(result, s[1], t[1])
 x[1] = result;		//x[1]=d(s[1],t[1]);
 for (int i = 2; i < window; i++) {
 d(result, s[i], t[1])
 x[i] = result + x[i - 1];		//x[i] = d(s[i],t[1]) + x[i-1];
 }
 for (int m = 2; m < M; m++) {
 start = max2(1, m - window);
 end = min2(N, m + window);
 for (int n = start; n < end; n++) {
 if (n == 1) {
 d(result, s[1], t[m])
 y[1] = result + x[1];		//y[1] = d(s[1],t[m]) + x[1];
 }
 d(result, s[n], t[m])
 y[n] = result + min3(y[n - 1], x[n - 1], x[n]);	//y[n] = d(s[n],t[m]) + min3(y[n-1],x[n-1],x[n]);
 }
 temp = x;
 x = y;
 y = temp;
 }
 return (uint32_t) x[N - 1];
 }
 */
