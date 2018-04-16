#ifndef __GPIO_PG13_OUTPUT_H
#define __GPIO_PG13_OUTPUT_H


#define PG13_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG13_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG13_OUTPUT_PIN                 GPIO_PIN_13
#define PG13_OUTPUT_PORT                GPIOG


#define PG13_OUTPUT_HIGH()      HAL_GPIO_WritePin(PG13_OUTPUT_PORT, PG13_OUTPUT_PIN, GPIO_PIN_SET)
#define PG13_OUTPUT_LOW()       HAL_GPIO_WritePin(PG13_OUTPUT_PORT, PG13_OUTPUT_PIN, GPIO_PIN_RESET)
#define PG13_OUTPUT_Toggle()    HAL_GPIO_TogglePin(PG13_OUTPUT_PORT, PG13_OUTPUT_PIN)

void gpio_g13_output_init(void);


#endif
