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

#define DICTIONARY_SIZE 8
#define MAX_STR_LEN 5

extern const char UP[];
extern const char YES[];
extern const char NO[];
extern const char OFF[];
extern const char RIGHT[];
extern const char DOWN[];
extern const char LEFT[];
extern const char ON[];

uint8_t argmax(const ai_float arr[], uint8_t size);

char* get_word(uint8_t idx);

#endif /* INC_COMMANDS_H_ */
