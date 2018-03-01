#include "uart_string_receive_parser.h"

static uint16_t uart_string_out(UART_HandleTypeDef *huart, uint8_t first_char, uint8_t *buffer, uint16_t length, uint32_t timeout)
{
	uint32_t tickstart = 0U;
	
	memset((char*)buffer, '\0', length);
	while(1) {
		HAL_UART_Receive(huart, &buffer[0], 1, 1);
		if(buffer[0] == first_char) {
			HAL_UART_Receive(huart, &buffer[1], length, timeout);
			return 0;
		}
		tickstart++;
		if(tickstart > timeout) {
			return 1;
		}
	}
}

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

/*---------------------------------------------------------------------------------------------------*/
static void a_init(struct receive_table_a *fmt)
{
	*fmt->o1 = '\0'; *fmt->o2 = '\0'; *fmt->o3 = '\0'; *fmt->o4 = '\0';
	*fmt->o5 = '\0'; *fmt->o6 = '\0'; *fmt->o7 = '\0'; *fmt->o8 = '\0';
	*fmt->o9 = '\0'; *fmt->o10 = '\0'; *fmt->o11 = '\0'; *fmt->o12 = '\0';
	*fmt->o13 = '\0'; *fmt->o14 = '\0'; *fmt->o15 = '\0';
}
uint16_t receive_cmd_a(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t length)
{
	char *name = "$ABCDE";
	uint32_t tickstart = 0U;
	
	while(1) {
		if(uart_string_out(huart, '$', buffer, length, 1000)) {
			printf("Timeout!\n");
			tickstart++;
			if(tickstart > 5) {
				return 1;
			}
			continue;
		}
		if(buffer_cmp((uint8_t*)name, buffer, strlen(name))) {
			printf("No compare!\n");
			continue;
		}
		a_init((struct receive_table_a*)buffer);
		return 0;
	}
}

/*---------------------------------------------------------------------------------------------------*/
static void version_init(struct receive_table_version *fmt)
{
	*fmt->o1 = '\0';
	*fmt->o2 = '\0';
	*fmt->o3 = '\0';
}
uint16_t receive_cmd_version(UART_HandleTypeDef *huart, uint8_t *buffer, uint16_t length)
{
	char name[] = {0x0A,0x56};
	uint32_t tickstart = 0U;
	
	while(1) {
		if(uart_string_out(huart, 0x0A, buffer, length, 1000)) {
			printf("Timeout!\n");
			tickstart++;
			if(tickstart > 5) {
				return 1;
			}
			continue;
		}
		if(buffer_cmp((uint8_t*)name, buffer, strlen(name))) {
			printf("No compare!\n");
			continue;
		}
		version_init((struct receive_table_version*)buffer);
		return 0;
	}
}

/*---------------------------------------------------------------------------------------------------*/
