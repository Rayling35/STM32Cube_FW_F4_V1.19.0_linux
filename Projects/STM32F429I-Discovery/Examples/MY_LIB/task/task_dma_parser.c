#include "cmsis_os.h"
#include "task_dma_parser.h"

#include "uart_dma_callback_parser.h"


static void dma_uart_string_parser(const void *argument)
{
	struct uart_api *uart6 = (struct uart_api *)argument;
	uint8_t *dma_string_checkout;
	
	uart6->receive_dma(&uart_dma1_callback_string_byte, 1);
	while(1) {
		do {
			dma_string_checkout = uart_dma1_callback_string_out();
		} while(dma_string_checkout == NULL);
		uart6->transmit(dma_string_checkout, 1, 1);
	}
}

void task_dma_parser(struct uart_api *uart)
{
	osThreadDef(dma_parser_id, dma_uart_string_parser, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(dma_parser_id), uart);
}
