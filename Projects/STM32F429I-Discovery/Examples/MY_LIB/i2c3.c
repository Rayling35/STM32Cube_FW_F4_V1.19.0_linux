#include "i2c3.h"
#include "api_define.h"


I2C_HandleTypeDef I2cHandle3;

void _I2C3_MspInit(I2C_HandleTypeDef *I2cHandle)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	#ifdef I2C3_DMA
	static DMA_HandleTypeDef HdmaHandle_i2c3_tx;
	static DMA_HandleTypeDef HdmaHandle_i2c3_rx;
	
	I2C_HandleTypeDef *pI2cHandle3;
	pI2cHandle3 = &I2cHandle3;
	#endif
	
	if(I2cHandle->Instance == I2C3)
	{
		I2C3_SCL_GPIO_CLK_ENABLE();
		I2C3_SDA_GPIO_CLK_ENABLE();
		
		GPIO_InitStruct.Pin       = I2C3_SCL_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull      = GPIO_NOPULL;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = I2C3_SCL_AF;
		HAL_GPIO_Init(I2C3_SCL_GPIO_PORT, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin       = I2C3_SDA_PIN;
		GPIO_InitStruct.Alternate = I2C3_SDA_AF;
		HAL_GPIO_Init(I2C3_SDA_GPIO_PORT, &GPIO_InitStruct);
		
		I2C3_CLK_ENABLE();
		I2C3_FORCE_RESET();
		I2C3_RELEASE_RESET();
		
		#ifdef I2C3_IT
		HAL_NVIC_SetPriority(I2C3_ER_IRQn, 0x0F, 0);
		HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
		
		HAL_NVIC_SetPriority(I2C3_EV_IRQn, 0x0F, 0);
		HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
		
		#ifdef I2C3_DMA
		DMA_I2C3_CLK_ENABLE();
		
		HdmaHandle_i2c3_tx.Instance                 = DMA_I2C3_TX_STREAM;
		HdmaHandle_i2c3_tx.Init.Channel             = DMA_I2C3_TX_CHANNEL;
		HdmaHandle_i2c3_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
		HdmaHandle_i2c3_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
		HdmaHandle_i2c3_tx.Init.MemInc              = DMA_MINC_ENABLE;
		HdmaHandle_i2c3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HdmaHandle_i2c3_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
		HdmaHandle_i2c3_tx.Init.Mode                = DMA_NORMAL;
		HdmaHandle_i2c3_tx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
		HdmaHandle_i2c3_tx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
		HdmaHandle_i2c3_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
		HdmaHandle_i2c3_tx.Init.MemBurst            = DMA_MBURST_SINGLE;
		HdmaHandle_i2c3_tx.Init.PeriphBurst         = DMA_PBURST_SINGLE;
		
		__HAL_LINKDMA(pI2cHandle3, hdmatx, HdmaHandle_i2c3_tx);
		HAL_DMA_Init(&HdmaHandle_i2c3_tx);
		
		HAL_NVIC_SetPriority(DMA_I2C3_TX_IRQn, DMA_I2C3_PREPRIO, 0);
		HAL_NVIC_EnableIRQ(DMA_I2C3_TX_IRQn);
		
		HdmaHandle_i2c3_rx.Instance                 = DMA_I2C3_RX_STREAM;
		HdmaHandle_i2c3_rx.Init.Channel             = DMA_I2C3_RX_CHANNEL;
		HdmaHandle_i2c3_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
		HdmaHandle_i2c3_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
		HdmaHandle_i2c3_rx.Init.MemInc              = DMA_MINC_ENABLE;
		HdmaHandle_i2c3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		HdmaHandle_i2c3_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
		HdmaHandle_i2c3_rx.Init.Mode                = DMA_NORMAL;
		HdmaHandle_i2c3_rx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
		HdmaHandle_i2c3_rx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
		HdmaHandle_i2c3_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
		HdmaHandle_i2c3_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
		HdmaHandle_i2c3_rx.Init.PeriphBurst         = DMA_PBURST_SINGLE;
		
		__HAL_LINKDMA(pI2cHandle3, hdmarx, HdmaHandle_i2c3_rx);
		HAL_DMA_Init(&HdmaHandle_i2c3_rx);
		
		HAL_NVIC_SetPriority(DMA_I2C3_RX_IRQn, DMA_I2C3_PREPRIO, 0);
		HAL_NVIC_EnableIRQ(DMA_I2C3_RX_IRQn);
		#endif
		#endif
	}
}

void i2c3_init(void)
{
	if(HAL_I2C_GetState(&I2cHandle3) == HAL_I2C_STATE_RESET)
	{
		I2cHandle3.Instance             = I2C3;
		I2cHandle3.Init.ClockSpeed      = I2C3_CLOCKSPEED;
		I2cHandle3.Init.DutyCycle       = I2C_DUTYCYCLE_2;
		I2cHandle3.Init.OwnAddress1     = 0;
		I2cHandle3.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
		I2cHandle3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		I2cHandle3.Init.OwnAddress2     = 0;
		I2cHandle3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		I2cHandle3.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
		
		_I2C3_MspInit(&I2cHandle3);
		HAL_I2C_Init(&I2cHandle3);
	}
}

void _I2C3_MspDeInit(void)
{
	HAL_GPIO_DeInit(I2C3_SCL_GPIO_PORT, I2C3_SCL_PIN);
	HAL_GPIO_DeInit(I2C3_SDA_GPIO_PORT, I2C3_SDA_PIN);
	
	HAL_I2C_DeInit(&I2cHandle3);
	
	#ifdef I2C3_IT
	HAL_NVIC_DisableIRQ(I2C3_ER_IRQn);
	HAL_NVIC_DisableIRQ(I2C3_EV_IRQn);
	
	#ifdef I2C3_DMA
	HAL_DMA_DeInit(I2cHandle3.hdmatx);
	HAL_DMA_DeInit(I2cHandle3.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_I2C3_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_I2C3_RX_IRQn);
	#endif
	#endif
}

static void I2C3_Error(void)
{
	_I2C3_MspDeInit();
	i2c3_init();
}

int i2c3_master_transmit(uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return 0;
}

int i2c3_master_receive(uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return 0;
}

void i2c3_mem_write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&I2cHandle3, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x3000);
	if(status != HAL_OK) {
		I2C3_Error();
	}
}

uint8_t i2c3_mem_read(uint8_t Addr, uint8_t Reg)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;
	status = HAL_I2C_Mem_Read(&I2cHandle3, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x3000);
	if(status != HAL_OK) {
		I2C3_Error();
	}
	return value;
}

#ifdef I2C3_IT
int i2c3_master_transmit_it(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return 0;
}

int i2c3_master_receive_it(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	return 0;
}

#ifdef I2C3_DMA
int i2c3_mem_write_dma(uint8_t Addr, uint16_t Reg, uint8_t *pBuffer, uint16_t Length)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write_DMA(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_16BIT, pBuffer, Length);
	if(status != HAL_OK) {
		I2Cx_Error();
	}
	return status;
}

int i2c3_mem_read_dma(uint8_t Addr, uint16_t Reg, uint8_t *pBuffer, uint16_t Length)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read_DMA(&I2cHandle, Addr, Reg, I2C_MEMADD_SIZE_16BIT, pBuffer, Length);
	if(status != HAL_OK) {
		I2Cx_Error();
	}
	return status;
}
#endif
#endif

struct i2c_api i2c3_api = {
	.handle = &I2cHandle3,
	.init = i2c3_init,
	.master_transmit = i2c3_master_transmit,
	.master_receive = i2c3_master_receive,
	.mem_write = i2c3_mem_write,
	.mem_read = i2c3_mem_read,
	#ifdef I2C3_IT
	.master_transmit_it = i2c3_master_transmit_it,
	.master_receive_it = i2c3_master_receive_it,
	#ifdef I2C3_DMA
	.mem_write_dma = i2c3_mem_write_dma,
	.mem_read_dma = i2c3_mem_read_dma,
	#endif
	#endif
};

struct i2c_api* i2c3_binding(void)
{
	return &i2c3_api; //¶Ç»¼¦ì¸m
}

#ifdef I2C3_IT
void I2C3_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&I2cHandle3);
}

void I2C3_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&I2cHandle3);
}

#ifdef I2C3_DMA
void DMA_I2C3_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(I2cHandle3.hdmatx);
}

void DMA_I2C3_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(I2cHandle3.hdmarx);
}
#endif
#endif
