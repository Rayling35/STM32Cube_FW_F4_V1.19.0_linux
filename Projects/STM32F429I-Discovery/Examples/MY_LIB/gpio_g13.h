#ifndef __GPIO_G13_H
#define __GPIO_G13_H


#define PG13_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG13_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG13_PIN                   GPIO_PIN_13
#define PG13_PORT                  GPIOG


#define PG13_OUTPUT_HIGH()         HAL_GPIO_WritePin(PG13_PORT, PG13_PIN, GPIO_PIN_SET)
#define PG13_OUTPUT_LOW()          HAL_GPIO_WritePin(PG13_PORT, PG13_PIN, GPIO_PIN_RESET)
#define PG13_OUTPUT_Toggle()       HAL_GPIO_TogglePin(PG13_PORT, PG13_PIN)
#define PG13_GET_STATE()           HAL_GPIO_ReadPin(PG13_PORT, PG13_PIN)

void gpio_g13_output_init(void);
void gpio_g13_input_init(void);
#ifdef G13_EXIT
void gpio_g13_exit_init(void);
#endif


#endif
