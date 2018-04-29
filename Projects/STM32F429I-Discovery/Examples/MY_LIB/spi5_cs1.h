#ifndef __SPI5_CS1_H
#define __SPI5_CS1_H


#define SPI5C1_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPI5C1_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOC_CLK_DISABLE()

#define SPI5C1_OUTPUT_PIN                 GPIO_PIN_1
#define SPI5C1_OUTPUT_PORT                GPIOC


#define SPI5C1_HIGH()      HAL_GPIO_WritePin(SPI5C1_OUTPUT_PORT, SPI5C1_OUTPUT_PIN, GPIO_PIN_SET)
#define SPI5C1_LOW()       HAL_GPIO_WritePin(SPI5C1_OUTPUT_PORT, SPI5C1_OUTPUT_PIN, GPIO_PIN_RESET)
#define SPI5C1_Toggle()    HAL_GPIO_TogglePin(SPI5C1_OUTPUT_PORT, SPI5C1_OUTPUT_PIN)

struct spi_api* spi5_cs1_binding(void);


#endif
