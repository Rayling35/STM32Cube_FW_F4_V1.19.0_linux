#include "spi5.h"
#include "spi5_cs1.h"
#include "api_define.h"


extern SPI_HandleTypeDef SpiHandle5;

static void spi5_cs1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	SPI5C1_OUTPUT_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = SPI5C1_OUTPUT_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	
	HAL_GPIO_Init(SPI5C1_OUTPUT_PORT, &GPIO_InitStruct);
	spi5_init();
}

static void spi5_cs1_error(void)
{
	SPI5C1_OUTPUT_CLK_DISABLE();
	_SPI5_MspDeInit();
	spi5_cs1_init();
}

static int spi5_cs1_transmit(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_Transmit(&SpiHandle5, data, length, timeout);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

static int spi5_cs1_receive(uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_Receive(&SpiHandle5, data, length, timeout);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

static int spi5_cs1_transmit_receive(uint8_t *tx_data, uint8_t *rx_data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_TransmitReceive(&SpiHandle5, tx_data, rx_data, length, timeout);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

#ifdef SPI5C1_IT
static int spi5_cs1_transmit_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_Transmit_IT(&SpiHandle5, data, length);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

static int spi5_cs1_receive_it(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_Receive_IT(&SpiHandle5, data, length);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

static int spi5_cs1_transmit_receive_it(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_TransmitReceive_IT(&SpiHandle5, tx_data, rx_data, length);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

#ifdef SPI5C1_DMA
static int spi5_cs1_transmit_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_Transmit_DMA(&SpiHandle5, data, length);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

static int spi5_cs1_receive_dma(uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_Receive_DMA(&SpiHandle5, data, length);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}

static int spi5_cs1_transmit_receive_dma(uint8_t *tx_data, uint8_t *rx_data, uint16_t length)
{
	HAL_StatusTypeDef status = HAL_OK;
	SPI5C1_LOW();
	status = HAL_SPI_TransmitReceive_DMA(&SpiHandle5, tx_data, rx_data, length);
	SPI5C1_HIGH();
	if(status != HAL_OK) {
		spi5_cs1_error();
	}
	return status;
}
#endif
#endif

static struct spi_api spi5_cs1_api = {
	.init                 = spi5_cs1_init,
	.transmit             = spi5_cs1_transmit,
	.receive              = spi5_cs1_receive,
	.transmit_receive     = spi5_cs1_transmit_receive,
	#ifdef SPI5C1_IT
	.transmit_it          = spi5_cs1_transmit_it,
	.receive_it           = spi5_cs1_receive_it,
	.transmit_receive_it  = spi5_cs1_transmit_receive_it,
	#ifdef SPI5C1_DMA
	.transmit_dma         = spi5_cs1_transmit_dma,
	.receive_dma          = spi5_cs1_receive_dma,
	.transmit_receive_dma = spi5_cs1_transmit_receive_dma,
	#endif
	#endif
};

struct spi_api* spi5_cs1_binding(void)
{
	return &spi5_cs1_api; //¶Ç»¼¦ì¸m
}
