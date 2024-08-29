/*
 * ring_buffer.h
 *
 *  Created on: Aug 15, 2024
 *      Author: torre
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_
#include <stdint.h>

typedef struct ring_buffer_ {

	uint8_t *buffer;
	uint8_t head;
	uint8_t tail;
	uint8_t is_full;
	uint8_t capacity;

} ring_buffer_t;

void ring_buffer_reset(void);//ok
uint8_t ring_buffer_size(void);//ok
uint8_t ring_buffer_is_full(void);//ok
uint8_t ring_buffer_is_empty(void);//ok

uint8_t check_sequence(uint8_t byte);

void ring_buffer_write(uint8_t data);
uint8_t ring_buffer_read(uint8_t *byte);


#endif /* INC_RING_BUFFER_H_ */
