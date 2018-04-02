#include "cmsis_os.h"
#include "task_test.h"

#include "uart_dma_callback_parser.h"


static void uart_test(const void *argument)
{
	struct uart_api *uart7 = (struct uart_api *)argument;
	
	uart7->receive_dma(&uart_dma3_callback_string_byte, 1);
	
	uint8_t dma_string_checkout[dma3_string_out_buffer_length];
	while(1) {
		if(uart_dma3_callback_string_out(dma_string_checkout) != NULL) {
			printf("%s\r\n", dma_string_checkout);
		}
	}
}

void task_test(struct uart_api *uart)
{
	osThreadDef(test_id, uart_test, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(test_id), uart);
}
