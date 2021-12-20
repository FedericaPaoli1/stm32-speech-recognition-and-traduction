/**
 *******************************************************************************
 * @file           : commands.h
 * @brief          : Header for commands.c file.
 *					 This file contains the defines to manage the neural
 *					 network output.
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
 *******************************************************************************
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

/* Includes ------------------------------------------------------------------*/

#include <inttypes.h>
#include "ai_platform.h"

/* Defines -------------------------------------------------------------------*/

/* Number of words that the neural network can recognize */
#define DICTIONARY_SIZE 38

/* Variables -----------------------------------------------------------------*/

/* Words that the neural network can recognize */
extern const char _BACKGROUND_NOISE_[];
extern const char _SILENCE_[];
extern const char _UNKNOWN_[];
extern const char BACKWARD[];
extern const char BED[];
extern const char BIRD[];
extern const char CAT[];
extern const char DOG[];
extern const char DOWN[];
extern const char EIGHT[];
extern const char FIVE[];
extern const char FOLLOW[];
extern const char FORWARD[];
extern const char FOUR[];
extern const char GO[];
extern const char HAPPY[];
extern const char HOUSE[];
extern const char LEARN[];
extern const char LEFT[];
extern const char MARVIN[];
extern const char NINE[];
extern const char NO[];
extern const char OFF[];
extern const char ON[];
extern const char ONE[];
extern const char RIGHT[];
extern const char SEVEN[];
extern const char SHEILA[];
extern const char SIX[];
extern const char STOP[];
extern const char THREE[];
extern const char TREE[];
extern const char TWO[];
extern const char UP[];
extern const char VISUAL[];
extern const char WOW[];
extern const char YES[];
extern const char ZERO[];

/* Functions -----------------------------------------------------------------*/

uint8_t argmax(const ai_float arr[], uint8_t size);

char* get_word(uint8_t idx);

#endif /* INC_COMMANDS_H_ */
