/*
 * elapsed_time.h
 *
 *  Created on: 19 dic 2021
 *      Author: federica
 */

#ifndef INC_ELAPSED_TIME_H_
#define INC_ELAPSED_TIME_H_
#include <stdint.h>
/*
 ********************************************************************************
 *                             Data Structure
 ********************************************************************************
 */

typedef struct elapsed_time {
	uint32_t start;
	uint32_t current;
	uint32_t max;
	uint32_t min;
} ELAPSED_TIME;
/*
 ********************************************************************************
 *                MAXIMUM NUMBER OF ELAPSED TIME MEASUREMENT SECTIONS
 ********************************************************************************
 */

#define  ELAPSED_TIME_MAX_SECTIONS  3

extern ELAPSED_TIME elapsed_time_tbl[ELAPSED_TIME_MAX_SECTIONS];

/*
 ********************************************************************************
 *                             FUNCTION PROTOTYPES
 ********************************************************************************
 */

void elapsed_time_clr(uint32_t i);      // Clear measured values
void elapsed_time_init(void);             // Module initialization
void elapsed_time_start(uint32_t i);      // Start measurement
void elapsed_time_stop(uint32_t i);      // Stop  measurement

#endif /* INC_ELAPSED_TIME_H_ */
