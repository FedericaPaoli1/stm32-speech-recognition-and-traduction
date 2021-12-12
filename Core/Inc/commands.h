/*
 * commands.h
 *
 *  Created on: Dec 4, 2021
 *      Author: federica
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include <inttypes.h>
#include "ai_platform.h"

#define DICTIONARY_SIZE 37

extern const char FIVE[];
extern const char LEFT[];
extern const char SIX[];
extern const char FOLLOW[];
extern const char _SILENCE_[];
extern const char NINE[];
extern const char UP[];
extern const char OFF[];
extern const char CAT[];
extern const char TREE[];
extern const char _UNKNOWN_[];
extern const char ON[];
extern const char ZERO[];
extern const char ONE[];
extern const char EIGHT[];
extern const char BIRD[];
extern const char HOUSE[];
extern const char MARVIN[];
extern const char THREE[];
extern const char LEARN[];
extern const char RIGHT[];
extern const char GO[];
extern const char FOUR[];
extern const char DOG[];
extern const char SHEILA[];
extern const char NO[];
extern const char DOWN[];
extern const char TWO[];
extern const char HAPPY[];
extern const char YES[];
extern const char BED[];
extern const char BACKWARD[];
extern const char WOW[];
extern const char FORWARD[];
extern const char STOP[];
extern const char SEVEN[];
extern const char VISUAL[];

uint8_t argmax(const ai_float arr[], uint8_t size);

char* get_word(uint8_t idx);

#endif /* INC_COMMANDS_H_ */
