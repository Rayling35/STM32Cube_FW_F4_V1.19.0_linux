#ifndef __GPIO_A0_H
#define __GPIO_A0_H


#define PA0_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA0_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA0_PIN                   GPIO_PIN_0
#define PA0_PORT                  GPIOA


#define PA0_OUTPUT_HIGH()         HAL_GPIO_WritePin(PA0_PORT, PA0_PIN, GPIO_PIN_SET)
#define PA0_OUTPUT_LOW()          HAL_GPIO_WritePin(PA0_PORT, PA0_PIN, GPIO_PIN_RESET)
#define PA0_OUTPUT_Toggle()       HAL_GPIO_TogglePin(PA0_PORT, PA0_PIN)
#define PA0_GET_STATE()           HAL_GPIO_ReadPin(PA0_PORT, PA0_PIN)

void gpio_a0_output_init(void);
void gpio_a0_input_init(void);
#ifdef A0_EXIT
void gpio_a0_exit_init(void);
#endif


#endif
