/**
 *******************************************************************************
 * @file           : execution_time.h
 * @brief          : Header for execution_time.c file.
 *					 This file contains the defines to compute the execution
 *					 time of a code block.
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
 *******************************************************************************
 */

#ifndef INC_EXECUTION_TIME_H_
#define INC_EXECUTION_TIME_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

/* Maximum number of code blocks to monitor */
#define  EXECUTION_TIME_MAX_SECTIONS  3

/* Typedefs ------------------------------------------------------------------*/

typedef struct time_statistics {
	uint32_t start;
	uint32_t elapsed;
	uint32_t max;
	uint32_t min;
} Time_Statistics;

/* Variables -----------------------------------------------------------------*/

extern Time_Statistics time_statistics_blocks[EXECUTION_TIME_MAX_SECTIONS];

/* Functions -----------------------------------------------------------------*/

void execution_time_clear(uint32_t i);
void execution_time_init(void);
void execution_time_start(uint32_t i);
void execution_time_stop(uint32_t i);

#endif /* INC_EXECUTION_TIME_H_ */
