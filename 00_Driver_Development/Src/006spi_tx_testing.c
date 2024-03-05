/*
 * SPI pins
 * PB14 for SPI2_MISO
 * PB15 for SPI2_MOSI
 * PB12 for SPI2_NSS
 * PB13 for SPI2_SCK
 * ALT fun mode is 0
 */
#include<string.h>
#include "stm32f0xx.h"

void SPI2_GPIOInit(void){
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx=GPIOB;
	GPIO_PeriClockControl(GPIOB, ENABLE);

	SPIPins.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 3;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_HIGH;


	//SCLK PIN
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_14;
	//	GPIO_Init(&SPIPins);

	//NSS
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
	//	GPIO_Init(&SPIPins);
}

void SPI2_Inits(void){
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig=SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; //Generates sereal clock OF 8 Mhz
	SPI2handle.SPIConfig.SPI_CRCL = SPI_CRCL_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL=SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA=SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM=SPI_SSM_EN; 	//software slave management for NSS pin

	SPI_Init(&SPI2handle);
}

int  main(){
	char *user_data="hello world";
	SPI2_GPIOInit();
	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_Inits();

	//enable the SPI peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	//send data
	SPI_SendData(SPI2,user_data,strlen(user_data));
	while(1);
	return 0;

}



