#include <string.h>
#include "uart_string_receive_parser.h"


static uint16_t buffer_cmp(uint8_t *buffer1, uint8_t *buffer2, uint16_t length)
{
	while(length--) {
		if(*buffer1 != *buffer2) {
			return 1;
		}
		buffer1++;
		buffer2++;
	}
	return 0;
}

static uint16_t uart_string_out(struct uart_api *huart, char *name, uint8_t *buffer, uint16_t length, uint32_t timeout)
{
	uint32_t tickstart = 0U;
	
	memset((char *)buffer, '\0', length);
	while(1) {
		huart->receive(&buffer[0], 1, 1);
		if(buffer[0] == name[0]) {
			huart->receive(&buffer[1], length, timeout);
			return 0;
		}
		tickstart++;
		if(tickstart > timeout) {
			return 1;
		}
	}
}

uint16_t head_checkout(struct uart_api *huart, char *name, uint8_t *buffer, uint16_t length)
{
	uint16_t tickstart = 0U;
	
	while(1) {
		if(uart_string_out(huart, name, buffer, length, 100)) {
			printf("Timeout!\r\n");
			tickstart++;
			if(tickstart > 5) {
				return 1;
			}
			continue;
		}
		if(buffer_cmp((uint8_t *)name, buffer, strlen(name))) {
			printf("No compare!\r\n");
			continue;
		}
		return 0;
	}
}


gps_data_t* a_parser(uint8_t *buffer)
{
	uint16_t length = strlen((char *)buffer);
	gps_data_t *fmt = (gps_data_t *)buffer;
	
	*fmt->o1 = '\0'; *fmt->o2 = '\0'; *fmt->o3 = '\0'; *fmt->o4 = '\0';
	*fmt->o5 = '\0'; *fmt->o6 = '\0'; *fmt->o7 = '\0'; *fmt->o8 = '\0';
	printf("START = %s\r\n", fmt->start);
	printf("Data1 = %s\r\n", fmt->data1);
	printf("Data2 = %s\r\n", fmt->data2);
	printf("Data3 = %s\r\n", fmt->data3);
	printf("Data4 = %s\r\n", fmt->data4);
	printf("Data5 = %s\r\n", fmt->data5);
	printf("Data6 = %s\r\n", fmt->data6);
	printf("END = %s\r\n", fmt->end);	
	
	return (gps_data_t *)buffer;
}

version_data_t* version_parser(uint8_t *buffer)
{
	uint16_t length = strlen((char *)buffer);
	version_data_t *fmt = (version_data_t *)buffer;
	
	printf("START = %02X\r\n", *fmt->start);
	printf("CMD = 0x%02x\r\n", *fmt->cmd);
	printf("VER1 = %.4s\r\n", fmt->ver1);
	printf("ID = %.16s\r\n", fmt->id);
	printf("VER2 = %.3s\r\n", fmt->ver2);
	printf("Region = %.5s\r\n", fmt->region);
	printf("END = %02X %02X\r\n", *fmt->end, *(fmt->end+1));
	
	return (version_data_t *)buffer;
}
