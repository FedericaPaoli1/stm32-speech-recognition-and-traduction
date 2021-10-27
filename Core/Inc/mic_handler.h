/*
 * mic_handler.h
 *
 *  Created on: Oct 27, 2021
 *      Author: federica
 */

#ifndef INC_MIC_HANDLER_H_
#define INC_MIC_HANDLER_H_

void mic_init(void *i2s_instance);
int mic_start_recording(void);
void mic_stop_recording(void);
int mic_monitor(void);

#endif /* INC_MIC_HANDLER_H_ */
