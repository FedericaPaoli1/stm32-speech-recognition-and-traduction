/*
 * commands.c
 *
 *  Created on: Dec 4, 2021
 *      Author: federica
 */

#include "commands.h"
#include "ai_platform.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

const char UP[] = "up";
const char YES[] = "yes";
const char NO[] = "no";
const char OFF[] = "off";
const char RIGHT[] = "right";
const char DOWN[] = "down";
const char LEFT[] = "left";
const char ON[] = "on";

static const char * dictionary[DICTIONARY_SIZE] = { UP, YES, NO, OFF, RIGHT, DOWN, LEFT, ON };

uint8_t argmax(const ai_float arr[], uint8_t size) {
	assert(size > 0 && size <= DICTIONARY_SIZE);
	uint8_t idx = 0;
	ai_float max = arr[0];
	ai_float tmp;

	for (uint8_t i = 1; i < size; i++) {
		tmp = arr[i];
		if (tmp > max) {
			max = tmp;
			idx = i;
		}
	}

	return idx;
}

char* get_word(uint8_t idx) {
	assert(idx < DICTIONARY_SIZE);
	return dictionary[idx];
}

