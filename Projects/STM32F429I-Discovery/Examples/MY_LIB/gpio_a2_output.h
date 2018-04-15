#ifndef __GPIO_A2_OUTPUT_H
#define __GPIO_A2_OUTPUT_H


#define PA2_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA2_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA2_OUTPUT_PIN                 GPIO_PIN_2
#define PA2_OUTPUT_PORT                GPIOA


#define PA2_OUTPUT_HIGH()      HAL_GPIO_WritePin(PA2_OUTPUT_PORT, PA2_OUTPUT_PIN, 1)
#define PA2_OUTPUT_LOW()       HAL_GPIO_WritePin(PA2_OUTPUT_PORT, PA2_OUTPUT_PIN, 0)

void gpio_a2_output_init(void);


#endif
