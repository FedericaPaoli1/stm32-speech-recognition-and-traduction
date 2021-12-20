/**
 *******************************************************************************
 * @file           : audio_record.h
 * @brief          : Header for audio_record.c file.
 *					 This file contains the defines to manage audio acquisition.
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
 *******************************************************************************
 */

#ifndef INC_AUDIO_RECORD_H_
#define INC_AUDIO_RECORD_H_

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc/pdm2pcm_glo.h"

/* Typedefs ------------------------------------------------------------------*/

typedef enum {
	OFFSET_NONE = 0, OFFSET_HALF, OFFSET_FULL,
} DMA_Buffer_State;

/* Variables -----------------------------------------------------------------*/

extern uint16_t pcm_buffer[PCM_BUFFER_SIZE];

/* Functions -----------------------------------------------------------------*/

void audio_record(void);

#endif /* INC_AUDIO_RECORD_H_ */
