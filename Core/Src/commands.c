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

const char FIVE[] = "five";
const char LEFT[] = "left";
const char SIX[] = "six";
const char FOLLOW[] = "follow";
const char _SILENCE_[] = "_silence_";
const char NINE[] = "nine";
const char UP[] = "up";
const char OFF[] = "off";
const char CAT[] = "cat";
const char TREE[] = "tree";
const char _UNKNOWN_[] = "_unknown_";
const char ON[] = "on";
const char ZERO[] = "zero";
const char ONE[] = "one";
const char EIGHT[] = "eight";
const char BIRD[] = "bird";
const char HOUSE[] = "house";
const char MARVIN[] = "marvin";
const char THREE[] = "three";
const char LEARN[] = "learn";
const char RIGHT[] = "right";
const char GO[] = "go";
const char FOUR[] = "four";
const char DOG[] = "dog";
const char SHEILA[] = "sheila";
const char NO[] = "no";
const char DOWN[] = "down";
const char TWO[] = "two";
const char HAPPY[] = "happy";
const char YES[] = "yes";
const char BED[] = "bed";
const char BACKWARD[] = "backward";
const char WOW[] = "wow";
const char FORWARD[] = "forward";
const char STOP[] = "stop";
const char SEVEN[] = "seven";
const char VISUAL[] = "visual";

static const char *dictionary[DICTIONARY_SIZE] =
		{ FIVE, LEFT, SIX, FOLLOW, _SILENCE_, NINE, UP, OFF, CAT, TREE,
				_UNKNOWN_, ON, ZERO, ONE, EIGHT, BIRD, HOUSE, MARVIN, THREE,
				LEARN, RIGHT, GO, FOUR, DOG, SHEILA, NO, DOWN, TWO, HAPPY, YES,
				BED, BACKWARD, WOW, FORWARD, STOP, SEVEN, VISUAL};

// TODO: document me!
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

// TODO: document me!
char* get_word(uint8_t idx) {
	assert(idx < DICTIONARY_SIZE);
	return dictionary[idx];
}

