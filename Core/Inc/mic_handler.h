/*
 * mic_handler.h
 *
 *  Created on: Oct 27, 2021
 *      Author: federica
 */

#ifndef INC_MIC_HANDLER_H_
#define INC_MIC_HANDLER_H_

#define PCM_BUF_SIZE 48
#define PDM_BUF_SIZE (PCM_BUF_SIZE*4)

void mic_init(void *i2s_instance);
int mic_start_recording(void);
void mic_stop_recording(void);
int mic_monitor(void);
int16_t* get_pcm(void);

#endif /* INC_MIC_HANDLER_H_ */
