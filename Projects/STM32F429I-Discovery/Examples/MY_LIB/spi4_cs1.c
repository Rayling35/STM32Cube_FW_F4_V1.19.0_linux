#include "spi4.h"
#include "spi4_cs1.h"

#include "api_define.h"


extern SPI_HandleTypeDef SpiHandle4;

void spi4_cs1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SPI4C1_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = SPI4C1_OUTPUT_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	
	HAL_GPIO_Init(SPI4C1_OUTPUT_PORT, &GPIO_InitStruct);
	spi4_init();
}

static void spi4_cs1_error(void)
{
	SPI4C1_OUTPUT_CLK_DISABLE();
	spi4_error();
	spi4_cs1_init();
}

int spi4_cs1_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_Transmit(&SpiHandle4, data, length, timeout);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

int spi4_cs1_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_Receive(&SpiHandle4, data, length, timeout);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

int spi4_cs1_transmit_receive(uint8_t *tx_data, uint8_t *rx_data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_TransmitReceive(&SpiHandle4, tx_data, rx_data, length, timeout);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

#ifdef SPI4C1_IT
int spi4_cs1_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_Transmit_IT(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

int spi4_cs1_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_Receive_IT(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

int spi4_cs1_transmit_receive_it(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_TransmitReceive_IT(&SpiHandle4, tx_data, rx_data, length);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

#ifdef SPI4C1_DMA
int spi4_cs1_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_Transmit_DMA(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

int spi4_cs1_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_Receive_DMA(&SpiHandle4, data, length);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}

int spi4_cs1_transmit_receive_dma(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI4C1_LOW();
	status = HAL_SPI_TransmitReceive_DMA(&SpiHandle4, tx_data, rx_data, length);
	SPI4C1_HIGH();
	if(status != HAL_OK) {
		spi4_cs1_error();
	}
	return status;
}
#endif
#endif

struct spi_api spi4_cs1_api = {
	.init                 = spi4_cs1_init,
	.transmit             = spi4_cs1_transmit,
	.receive              = spi4_cs1_receive,
	.transmit_receive     = spi4_cs1_transmit_receive,
	#ifdef SPI4C1_IT
	.transmit_it          = spi4_cs1_transmit_it,
	.receive_it           = spi4_cs1_receive_it,
	.transmit_receive_it  = spi4_cs1_transmit_receive_it,
	#ifdef SPI4C1_DMA
	.transmit_dma         = spi4_cs1_transmit_dma,
	.receive_dma          = spi4_cs1_receive_dma,
	.transmit_receive_dma = spi4_cs1_transmit_receive_dma,
	#endif
	#endif
};

struct spi_api* spi4_cs1_binding(void)
{
	return &spi4_cs1_api; //¶Ç»¼¦ì¸m
}
