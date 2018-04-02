#include "cmsis_os.h"
#include "task_dma_parser.h"

#include "uart_dma_callback_parser.h"


static void dma_uart_string_parser(const void *argument)
{
	struct uart_api *uart6 = (struct uart_api *)argument;
	
	uart6->receive_dma(&uart_dma2_callback_string_byte, 1);
	
	uint8_t dma_string_checkout[dma2_string_out_buffer_length];
	while(1) {
		if(uart_dma2_callback_string_out(dma_string_checkout) != NULL) {
			printf("%s\r\n", dma_string_checkout);
		}
	}
}

void task_dma_parser(struct uart_api *uart)
{
	osThreadDef(dma_parser_id, dma_uart_string_parser, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(dma_parser_id), uart);
}
