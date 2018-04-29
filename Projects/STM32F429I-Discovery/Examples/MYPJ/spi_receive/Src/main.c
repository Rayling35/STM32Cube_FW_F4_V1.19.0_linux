#include "system_initialization.h"
#include "uart_printf.h"
#include "main.h"

#include "api_define.h"
#include "spi4_cs1.h"
#include "spi5_cs1.h"


//#define STATUS      			(uint8_t *)0x07

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct spi_api *spi4_cs1 = spi4_cs1_binding();
	struct spi_api *spi5_cs1 = spi5_cs1_binding();
	spi4_cs1->init();
	spi5_cs1->init();
	printf("SPI init\r\n");
	
	int status;
	uint8_t tx_byte = 0x17;
	uint8_t rx_byte;
	
	status = spi4_cs1->transmit_receive(&tx_byte, &rx_byte, 1, 1000);
	if(status) {
		printf("transfer fail! %d\r\n", status);
	}
	printf("rx:%d\r\n", rx_byte);
}



#if 0
#define I_AM_L3GD20                 ((uint8_t)0xD4)
#define I_AM_L3GD20_TR              ((uint8_t)0xD5)

#define L3GD20_WHO_AM_I_ADDR        0x0F

#define READWRITE_CMD              ((uint8_t)0x80)
#define MULTIPLEBYTE_CMD           ((uint8_t)0x40)
#define DUMMY_BYTE                 ((uint8_t)0x00)


static uint8_t SPI_WriteRead(struct spi_api *hspi, uint8_t Byte)
{
	int status;
  uint8_t receivedbyte = 0;
  
	status = hspi->transmit_receive(&Byte, &receivedbyte, 1, 0x1000);
  if(status != 0) {
    printf("transfer fail!\r\n");
		printf("%d\r\n", status);
  }
  return receivedbyte;
}

void GYRO_IO_Read(struct spi_api *hspi, uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
  if(NumByteToRead > 0x01) {
    ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
  }else {
    ReadAddr |= (uint8_t)READWRITE_CMD;
  }
  SPI_WriteRead(hspi, ReadAddr);
	
  while(NumByteToRead > 0x00)
  {
    *pBuffer = SPI_WriteRead(hspi, DUMMY_BYTE);
    NumByteToRead--;
    pBuffer++;
  }
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct spi_api *spi4_cs1 = spi4_cs1_binding();
	struct spi_api *spi5_cs1 = spi5_cs1_binding();
	spi4_cs1->init();
	spi5_cs1->init();
	printf("SPI init\r\n");
	
	uint8_t tmp;
	GYRO_IO_Read(spi5_cs1, &tmp, L3GD20_WHO_AM_I_ADDR, 1);
	printf("0xD4,0xD5 == %X\r\n", tmp);
}
#endif
