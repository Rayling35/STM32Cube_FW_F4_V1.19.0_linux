#include <string.h>
#include "uart_it_callback_parser.h"


uint8_t uart_it1_callback_string_byte; //extern data

static uint8_t string1_out[it1_string_out_buffer_length];
static uint8_t buffer1_flag = 0;

void uart_it1_callback_parser(struct uart_api *uart)
{
	static uint8_t buffer[it1_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_it1_callback_string_byte;
	i++;
	if(uart_it1_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string1_out, '\0', it1_string_out_buffer_length);
		memcpy((char *)string1_out, buffer, i-1);
		buffer1_flag = 1;
		i = 0;
	}
	uart->receive_it(&uart_it1_callback_string_byte, 1);
}

uint8_t* uart_it1_callback_string_out(void)
{
	if(buffer1_flag) {
		buffer1_flag = 0;
		return string1_out;
	}
	return NULL;
}


uint8_t uart_it2_callback_string_byte; //extern data

static uint8_t string2_out[it2_string_out_buffer_length];
static uint8_t buffer2_flag = 0;

void uart_it2_callback_parser(struct uart_api *uart)
{
	static uint8_t buffer[it2_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_it2_callback_string_byte;
	i++;
	if(uart_it2_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		memset((char *)string2_out, '\0', it2_string_out_buffer_length);
		memcpy((char *)string2_out, buffer, i-1);
		buffer2_flag = 1;
		i = 0;
	}
	uart->receive_it(&uart_it2_callback_string_byte, 1);
}

uint8_t* uart_it2_callback_string_out(void)
{
	if(buffer2_flag) {
		buffer2_flag = 0;
		return string2_out;
	}
	return NULL;
}


uint8_t uart_it3_callback_string_byte; //extern data

static uint8_t string3_out[4][it3_string_out_buffer_length];
static uint8_t buffer3_flag1 = 0;
static uint8_t buffer3_flag2 = 0;
static uint8_t buffer3_flag3 = 0;
static uint8_t buffer3_flag4 = 0;

void uart_it3_callback_parser(struct uart_api *uart)
{
	static uint8_t buffer[it3_string_out_buffer_length];
	static uint16_t i = 0;
	
	buffer[i] = uart_it3_callback_string_byte;
	i++;
	if(uart_it3_callback_string_byte == 0x0A  &&  buffer[i-2] == 0x0D) {
		static uint16_t count = 0;
		switch(count) {
			case 0:
				buffer3_flag1 = 0;
				memset((char *)*(string3_out+0), '\0', it3_string_out_buffer_length);
				memcpy((char *)*(string3_out+0), buffer, i-1);
				buffer3_flag1 = 1;
				i = 0;
				break;
			case 1:
				buffer3_flag2 = 0;
				memset((char *)*(string3_out+1), '\0', it3_string_out_buffer_length);
				memcpy((char *)*(string3_out+1), buffer, i-1);
				buffer3_flag2 = 1;
				i = 0;
				break;
			case 2:
				buffer3_flag3 = 0;
				memset((char *)*(string3_out+2), '\0', it3_string_out_buffer_length);
				memcpy((char *)*(string3_out+2), buffer, i-1);
				buffer3_flag3 = 1;
				i = 0;
				break;
			case 3:
				buffer3_flag4 = 0;
				memset((char *)*(string3_out+3), '\0', it3_string_out_buffer_length);
				memcpy((char *)*(string3_out+3), buffer, i-1);
				buffer3_flag4 = 1;
				i = 0;
				break;
		}
		count++;
		if(count >= 4){
			count = 0;
		}
	}
	uart->receive_it(&uart_it3_callback_string_byte, 1);
}

uint8_t* uart_it3_callback_string_out(void)
{
	if(buffer3_flag1) {
		buffer3_flag1 = 0;
		return *(string3_out+0);
	}else if(buffer3_flag2) {
		buffer3_flag2 = 0;
		return *(string3_out+1);
	}else if(buffer3_flag3) {
		buffer3_flag3 = 0;
		return *(string3_out+2);
	}else if(buffer3_flag4) {
		buffer3_flag4 = 0;
		return *(string3_out+3);
	}
	return NULL;
}
