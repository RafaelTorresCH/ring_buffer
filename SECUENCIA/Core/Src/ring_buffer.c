/*
 * ring_buffer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: torre
 */

#include "ring_buffer.h"
#define capacity (8)//capacidad del buffe
uint8_t ring_buffer[capacity];//buffer
uint8_t head_ptr;//cabeza buffer
uint8_t tail_ptr;//cola buffer
uint8_t is_full;
uint8_t seq_index;
uint8_t sequence_size = 10;
/**
 * @brief: esta funcion se encarga de escribir un dato en el buffer
 *
 * @param data: indica el dato que se va a escribir
 *
 * retval ninguno
 * */
void ring_buffer_write(uint8_t data) {
    ring_buffer[head_ptr] = data;
    head_ptr++;

    if (head_ptr >= capacity) {
        head_ptr = 0;
    }
    //cuando la cabeza es mayor que la capacidad, se resetea la cabeza
    if (head_ptr == tail_ptr) {
        is_full = 1;//indica que ya esta lelno el buffer, y que la cola esta lista para avanzar
    }

    if (is_full != 0) {
        tail_ptr++;//la cola aumenta
    }
    if (tail_ptr >= capacity) {
        tail_ptr = 0;//reseteo de la cola
    }
}
/**
 * @brief: esta funcion se encarga de escribir un dato en el buffer
 *
 * @param data: indica el dato que se va a escribir
 *
 * retval ninguno
 * */
uint8_t ring_buffer_read (uint8_t *byte) {
    if ((is_full != 0) || (head_ptr != tail_ptr)) {
        *byte = ring_buffer[tail_ptr];
        tail_ptr++;
        if (tail_ptr >= capacity) {
            tail_ptr = 0;
        }
        is_full = 0;
        return 1; // Buffer tenía datos y se leyó un byte
    }
    return 0; // Buffer está vacío
}


uint8_t ring_buffer_size(void){
	if(head_ptr > tail_ptr){
		return head_ptr - tail_ptr;

	}else{

		return capacity - tail_ptr + head_ptr;// esta formula indica el numero de elemntos presentes en el buffer, ha ocurrido un wrap-around
	}

}
void ring_buffer_reset(void){
	for(uint8_t i = 0; i < 8; i++){
		ring_buffer[0] = 0;//reset buffer
	}
}
/**
 * @brief:revisa si el buffer esta lleno
 * @param void
 *
 * retval 0:buffer no full, 1: buffer full
 * */
uint8_t ring_buffer_is_full(void){
	if(is_full != 0){
		return 1;// buffer full
	}else{
		return 0; //buffer no full
	}
}
/**
 * @brief: esta funcion se encarga de revisar si el buffer esta vacio
 *
 * @param void
 *
 * retval 0:buffer empty, 1: buffer no empty
 * */
uint8_t ring_buffer_is_empty(void){
	for(uint8_t i = 0; i < 8; i++){
			if(ring_buffer[i] != '0'){
				return 1;//buffer no empty
			}
	}
	return 0;
	//buffer empty
}

/**
 * @brief: esta funcion se encarga de encontrar una secuencia de numeros, a traves de la lectura del buffer
 *
 * @param byte: indica el byte entrante, para hacer la correspondiente comprobacion
 *
 * retval 0: no se ha encontrado la secuencia, 1: se encontro la secuencia
 * */
uint8_t check_sequence(uint8_t byte) {

    uint8_t sequence[10] =  {'1', '0', '0', '7', '2', '4', '6', '6', '0', '6'};

        if (byte == sequence[seq_index]) {
            seq_index++;
            if (seq_index == sequence_size) {
                // se encontro la secuencia

                seq_index = 0; // Reiniciar secuencia para encontrar la proxima
                return 1;
            }
        } else {
            seq_index = 0; // reinicia el contador
        }

    return 0;
}

