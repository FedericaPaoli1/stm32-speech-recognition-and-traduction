/**
 *******************************************************************************
 * @file           : commands.c
 * @brief          : This file contains the definition of the neural network
 * 					 dictionary and the helper functions.
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "ai_platform.h"

/* Variables -----------------------------------------------------------------*/

const char _BACKGROUND_NOISE_[] = "_background_noise_";
const char _SILENCE_[] = "_silence_";
const char _UNKNOWN_[] = "_unknown_";
const char BACKWARD[] = "backward";
const char BED[] = "bed";
const char BIRD[] = "bird";
const char CAT[] = "cat";
const char DOG[] = "dog";
const char DOWN[] = "down";
const char EIGHT[] = "eight";
const char FIVE[] = "five";
const char FOLLOW[] = "follow";
const char FORWARD[] = "forward";
const char FOUR[] = "four";
const char GO[] = "go";
const char HAPPY[] = "happy";
const char HOUSE[] = "house";
const char LEARN[] = "learn";
const char LEFT[] = "left";
const char MARVIN[] = "marvin";
const char NINE[] = "nine";
const char NO[] = "no";
const char OFF[] = "off";
const char ON[] = "on";
const char ONE[] = "one";
const char RIGHT[] = "right";
const char SEVEN[] = "seven";
const char SHEILA[] = "sheila";
const char SIX[] = "six";
const char STOP[] = "stop";
const char THREE[] = "three";
const char TREE[] = "tree";
const char TWO[] = "two";
const char UP[] = "up";
const char VISUAL[] = "visual";
const char WOW[] = "wow";
const char YES[] = "yes";
const char ZERO[] = "zero";

/* Dictionary that the neural network recognizes.
 * This array must be kept in this order, otherwise the neural network is not
 * able to correctly classify the spoken words.
 */
static const char *dictionary[DICTIONARY_SIZE] = { _BACKGROUND_NOISE_,
		_SILENCE_, _UNKNOWN_, BACKWARD, BED, BIRD, CAT, DOG, DOWN, EIGHT, FIVE,
		FOLLOW, FORWARD, FOUR, GO, HAPPY, HOUSE, LEARN, LEFT, MARVIN, NINE, NO,
		OFF, ON, ONE, RIGHT, SEVEN, SHEILA, SIX, STOP, THREE, TREE, TWO, UP,
		VISUAL, WOW, YES, ZERO };


/**
 * @brief Find the index of the maximum value in the array.
 *   This function must be called after the neural network inference to find
 *   index of the predicted word.
 *
 * @param  arr   output array of neural network predictions
 * @param  size  arr size. It must be positive and less than `DICTIONARY_SIZE`
 *
 * @retval idx:  arr maximum value index
 */
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

/**
 * @brief Get the word from the dictionary corresponding to the input index.
 *   This function must have the output of the `argmax` function as input.
 *
 * @param  idx   word index. It must be less than `DICTIONARY_SIZE`
 *
 * @retval       the dictionary word corresponding to the input index
 */
char* get_word(uint8_t idx) {
	assert(idx < DICTIONARY_SIZE);
	return dictionary[idx];
}

