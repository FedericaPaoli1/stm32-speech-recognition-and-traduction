/*
 * mic_handler.c
 *
 *  Created on: Oct 27, 2021
 *      Author: federica
 */

#include <stdio.h>
#include "stm32f4xx_hal.h"

#include "pdm2pcm.h"
#include <stdlib.h>

/**
 * Note: if the decimation factor or number of output samples
 * per conversion is changed, these buffer sizes will
 * need to be changed!
 */
#define PCM_BUF_SIZE 48
// For a decimation factor of 64 and 16-bit wordlength ...
#define PDM_BUF_SIZE (PCM_BUF_SIZE*4)

static I2S_HandleTypeDef *i2s;

static int16_t pcm[PCM_BUF_SIZE];

static uint16_t rxbufs[2][PDM_BUF_SIZE];
static uint16_t *rxbuf;
static uint32_t sample_count;

static volatile __IO uint8_t new_data;

static int convert_audio_to_pcm(void);

void mic_init(void *instance) {
	i2s = instance;
	MX_PDM2PCM_Init();
}

int mic_start_recording(void) {
	memset(pcm, 0, PCM_BUF_SIZE);
	memset(rxbufs[0], 0, PDM_BUF_SIZE);
	memset(rxbufs[1], 0, PDM_BUF_SIZE);
	rxbuf = 0;
	unsigned transfer_len = PDM_BUF_SIZE;
	HAL_StatusTypeDef status = HAL_I2S_Receive_DMA(i2s, rxbufs[0],
			transfer_len);
	if (status != HAL_OK) {
		//Failed to start I2S transmission
		return 1;
	}
	sample_count = 0;

	return 0;
}

void mic_stop_recording(void) {
	HAL_I2S_DMAStop(i2s);
}

int mic_monitor(void) {
	if (new_data) {
		new_data = 0;
		return convert_audio_to_pcm();
	}
	return 0;
}

static int convert_audio_to_pcm(void) {
	uint32_t rc = PDM_Filter(rxbuf, pcm, &PDM1_filter_handler);
	if (rc != 0) {
		//Error in PDM to PCM conversion
		return -1;
	}
	return 1;
}

int16_t* get_pcm(void) {
	return pcm;
}

/*
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
	if (hi2s != i2s) {
		return;
	}
	rxbuf = rxbufs[0];
	new_data = 1;
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
	if (hi2s != i2s) {
		return;
	}
	rxbuf = rxbufs[1];
	new_data = 1;
}*/
