/**
 *******************************************************************************
 * @file           : execution_time.c
 * @brief          : This file contains the facilities to compute the execution
 * 					 time of different code blocks.
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "execution_time.h"

/* Defines -------------------------------------------------------------------*/

/* Debug Exception and Monitor Control Register content */
#define  ARM_CM_DEMCR      (*(uint32_t *)0xE000EDFC)

/* DWT Control Register content */
#define  ARM_CM_DWT_CTRL   (*(uint32_t *)0xE0001000)

/* DWT Current PC Sampler Cycle Count Register content */
#define  ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)

/* Variables -----------------------------------------------------------------*/

/* Execution time measurements of different code blocks */
Time_Statistics time_statistics_blocks[EXECUTION_TIME_MAX_SECTIONS];

/* Functions -----------------------------------------------------------------*/

/**
 * @brief Initialize the execution time module.
 *   This function must be called before any of the other functions of the module.
 *
 * @param  None
 *
 * @retval None
 */
void execution_time_init(void) {
	uint32_t i;

	if (ARM_CM_DWT_CTRL != 0) {
		ARM_CM_DEMCR |= 1 << 24; /* enable DWT and set bit 24 */
		ARM_CM_DWT_CYCCNT = 0; /* clear DWT cycle counter   */
		ARM_CM_DWT_CTRL |= 1; /* enable DWT cycle counter  */
	}

	for (i = 0; i < EXECUTION_TIME_MAX_SECTIONS; i++) {
		execution_time_clear(i);
	}
}

/**
 * @brief Start the execution time measurement of the input code block.
 *
 * @param  i   number of the code block to measure. It must be less than
 * 			   `EXECUTION_TIME_MAX_SECTIONS`.
 *
 * @retval None
 */
void execution_time_start(uint32_t i) {
	if (i < EXECUTION_TIME_MAX_SECTIONS)
		time_statistics_blocks[i].start = ARM_CM_DWT_CYCCNT;
}

/**
 * @brief Stop the execution time measurement of the input code block and
 *        compute statistics.
 *
 * @param  i   number of the code block to measure. It must be less than
 * 			   `EXECUTION_TIME_MAX_SECTIONS`.
 *
 * @retval None
 */
void execution_time_stop(uint32_t i) {
	if (i < EXECUTION_TIME_MAX_SECTIONS) {
		uint32_t stop;
		Time_Statistics *p_tbl;

		stop = ARM_CM_DWT_CYCCNT;
		p_tbl = &time_statistics_blocks[i];
		p_tbl->elapsed = stop - p_tbl->start;
		if (p_tbl->max < p_tbl->elapsed) {
			p_tbl->max = p_tbl->elapsed;
		}
		if (p_tbl->min > p_tbl->elapsed) {
			p_tbl->min = p_tbl->elapsed;
		}
	}
}

/**
 * @brief Reset the time measurement of the input code block.
 *
 * @param  i   number of the code block to measure. It must be less than
 * 			   `EXECUTION_TIME_MAX_SECTIONS`.
 *
 * @retval None
 */
void execution_time_clear(uint32_t i) {
	if (i < EXECUTION_TIME_MAX_SECTIONS) {
		Time_Statistics *p_tbl;

		p_tbl = &time_statistics_blocks[i];
		p_tbl->start = 0;
		p_tbl->elapsed = 0;
		p_tbl->min = 0xFFFFFFFF;
		p_tbl->max = 0;
	}
}
