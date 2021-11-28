/*
 * lookup.h
 *
 *  Created on: Nov 19, 2021
 *      Author: federica
 */

#ifndef __LOOKUP_H
#define __LOOKUP_H

extern const float LPF_precalc[256][16];
extern const float hamming_window_400[400];
extern const float mel_filterbank_257x26_div400[6682];
extern const float dct_table_26x12[312];
extern const int frame_base[32];
extern const float mfcc_templates[24][312];

#endif /* __LOOKUP_H */
