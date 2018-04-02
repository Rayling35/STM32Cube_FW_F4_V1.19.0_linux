#include <string.h>
#include "uart_dma_callback_parser.h"


uint8_t uart_dma1_callback_string_byte; //extern data

static uint8_t string1_out[dma1_string_out_buffer_length];
static uint8_t buffer1_flag = 0;

void uart_dma1_callback_parser(void)
{
	static uint8_t buffer[dma1_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_dma1_callback_string_byte;
	i++;
	if(uart_dma1_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string1_out, '\0', dma1_string_out_buffer_length);
		memcpy((char *)string1_out, buffer, i-1);
		buffer1_flag = 1;
		i = 0;
	}
}

int uart_dma1_callback_string_out(uint8_t *out)
{
	if(buffer1_flag) {
		buffer1_flag = 0;
		memcpy((char *)out, string1_out, dma1_string_out_buffer_length);
		if(buffer1_flag) {
			return 1;
		}else {
			return 0;
		}
	}
	return NULL;
}


uint8_t uart_dma2_callback_string_byte; //extern data

static uint8_t string2_out[dma2_string_out_buffer_length];
static uint8_t buffer2_flag = 0;

void uart_dma2_callback_parser(void)
{
	static uint8_t buffer[dma2_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_dma2_callback_string_byte;
	i++;
	if(uart_dma2_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string2_out, '\0', dma2_string_out_buffer_length);
		memcpy((char *)string2_out, buffer, i-1);
		buffer2_flag = 1;
		i = 0;
	}
}

int uart_dma2_callback_string_out(uint8_t *out)
{
	if(buffer2_flag) {
		buffer2_flag = 0;
		memcpy((char *)out, string2_out, dma2_string_out_buffer_length);
		if(buffer2_flag) {
			return 1;
		}else {
			return 0;
		}
	}
	return NULL;
}


uint8_t uart_dma3_callback_string_byte; //extern data

static uint8_t string3_out[dma3_string_out_buffer_length];
static uint8_t buffer3_flag = 0;

void uart_dma3_callback_parser(void)
{
	static uint8_t buffer[dma3_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_dma3_callback_string_byte;
	i++;
	if(uart_dma3_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string3_out, '\0', dma3_string_out_buffer_length);
		memcpy((char *)string3_out, buffer, i-1);
		buffer3_flag = 1;
		i = 0;
	}
}

int uart_dma3_callback_string_out(uint8_t *out)
{
	if(buffer3_flag) {
		buffer3_flag = 0;
		memcpy((char *)out, string3_out, dma3_string_out_buffer_length);
		if(buffer3_flag) {
			return 1;
		}else {
			return 0;
		}
	}
	return NULL;
}
