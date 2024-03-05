/*
 * stm32f0xx_spi_driver.h
 *
 *  Created on: Aug 1, 2023
 *      Author: 158184
 */

#ifndef INC_STM32F0XX_SPI_DRIVER_H_
#define INC_STM32F0XX_SPI_DRIVER_H_

#include "stm32f0xx.h"

/*
 *  Configuration structure for SPIx peripheral
 */
typedef struct
{
	uint8_t SPI_DeviceMode;  //master or slave device mode
	uint8_t SPI_BusConfig;	 //THIS IS USED TO DECIDE WHETHER THE BUS will be full duplex, half duplex or simplex
	uint8_t SPI_SclkSpeed;	 //CLOCK SPEED
	uint8_t SPI_CRCL;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;


/*
 *Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_RegDef_t 	*pSPIx;   /*!< This holds the base address of SPIx(x:0,1,2) peripheral >*/
	SPI_Config_t 	SPIConfig;
//	uint8_t 		*pTxBuffer; /* !< To store the app. Tx buffer address > */
//	uint8_t 		*pRxBuffer;	/* !< To store the app. Rx buffer address > */
//	uint32_t 		TxLen;		/* !< To store Tx len > */
//	uint32_t 		RxLen;		/* !< To store Tx len > */
//	uint8_t 		TxState;	/* !< To store Tx state > */
//	uint8_t 		RxState;	/* !< To store Rx state > */
}SPI_Handle_t;

/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3


/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16		    3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

/*
 * @SPI_CRCL
 * 1 CRCL: CRC length
This bit is set and cleared by software to select the CRC length.
0: 8-bit CRC length
1: 16-bit CRC length
 */
#define SPI_CRCL_8BITS 		0
#define SPI_CRCL_16BITS 	1


/*
 * @CPOL
 */
#define SPI_CPOL_HIGH  	1
#define SPI_CPOL_LOW   	0



/*
 * @CPHA
 */
#define SPI_CPHA_HIGH 1
#define SPI_CPHA_LOW 0

//
///*
// * @SPI_SSM
// */
//#define SPI_SSM_HW 		1
//#define SPI_SSM_SW		0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN     1
#define SPI_SSM_DI     0

/*
 * SPI related status flags macro
 */
#define SPI_TXE_FLAG (1<<SPI_SR_TXE)
#define SPI_RXNE_FLAG (1<<SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1<<SPI_SR_BSY)


/*
 *@DS : Data size
 */
#define SPI_DS_8BITS        7


/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */

//by using this function we are going to enable or disable the peripheral clock for given gpio base address
//so first parameter pointer to the base address
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnroDi);


/*
 * initialize  and deinitialize
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);    //API to initialize clock for given gpio pin
void SPI_Denit(SPI_RegDef_t *pSPIx);    //API to Deinitialize clock for given gpio pin


/*
 * Data send and receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len);


/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/*
 * SPI peripheral control api
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi);


#endif /* INC_STM32F0XX_SPI_DRIVER_H_ */
