#include <string.h>
#include "uart_string_transmit_parser.h"


struct transmit_table_pzem004t {
	uint8_t head;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
	uint8_t data4;
	uint8_t data5;
	uint8_t sum;
};

static void pzem_voltage_fill(struct transmit_table_pzem004t *fill)
{
	fill->head = 0xB0;
	fill->data1 = 0xC0;
	fill->data2 = 0xA8;
	fill->data3 = 0x01;
	fill->data4 = 0x01;
	fill->data5 = 0x00;
	fill->sum = (fill->head + fill->data1 + fill->data2 + fill->data3 + fill->data4 + fill->data5) & 0xFF;
}
uint16_t transmit_pzem_voltage(struct uart_api *huart)
{
	uint8_t buffer[7];
	
	pzem_voltage_fill((struct transmit_table_pzem004t*)buffer);
	huart->transmit(buffer, 7, 1000);
	return 0;
}

/*---------------------------------------------------------------------------------------------------*/
struct transmit_table_at_uart {
	char *command;
	char *device;
	int data1;
	int data2;
	int data3;
};

static void at_uart_fill(struct transmit_table_at_uart *fill)
{
	fill->command = "AT";
	fill->device = "UART";
	fill->data1 = 115200;
	fill->data2 = 0;
	fill->data3 = 1;
}
uint16_t transmit_at_uart(struct uart_api *huart)
{
	struct transmit_table_at_uart at;
	char buffer[] = "\0";
	
	at_uart_fill(&at);
	sprintf(buffer, "%s+%s=%d,%d,%d", at.command, at.device, at.data1, at.data2, at.data3);
	huart->transmit((uint8_t*)buffer, strlen(buffer), 1000);
	return 0;
}

/*---------------------------------------------------------------------------------------------------*/
