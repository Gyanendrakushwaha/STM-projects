/*
 * stm32f0xx_spi_driver.c
 *
 *  Created on: Aug 1, 2023
 *      Author: 158184
 */

#include "stm32f0xx_spi_driver.h"

/*********************************************************************
 * @fn      		  - SPI_PeriClockControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
if(EnorDi == ENABLE)
{
	if(pSPIx == SPI1)
	{
		SPI1_PCLK_EN();
	}else if(pSPIx == SPI2)
	{
		SPI2_PCLK_EN();
	}
}else{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if(pSPIx == SPI2)
		{
			SPI1_PCLK_DI();
		}
}
}





/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void SPI_Init(SPI_Handle_t *pSPIHandle){
//first lets configure the SPI_CR1 register
	uint32_t tempreg =0;

	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);

//1.configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

//2. Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &= ~(1<<15);
	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg |= (1<<15);
	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BIDI mode should be cleared
		tempreg &= ~(1<<15);
		//RXONLY bit must be set
		tempreg |= (1<<10);
	}

	//3.configuration the spi serial clock (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed <<SPI_CR1_BR;

	//4. Configure the CRCL
	tempreg |= pSPIHandle->SPIConfig.SPI_CRCL <<SPI_CR1_CRCL;  //here issue will created

	//5.configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL <<SPI_CR1_CPOL;

	//6. configure the CPha
	tempreg|= pSPIHandle->SPIConfig.SPI_CPHA<<SPI_CR1_CPHA;


//saving the tempreg in reagister
	pSPIHandle->pSPIx->CR1  = tempreg;

	//additionaly accessing the CR2 register then setting the DS
	pSPIHandle->pSPIx->CR2 |= (SPI_DS_8BITS<<SPI_CR2_DS);
}




/*********************************************************************
 * @fn      		  - SPI_DeInit
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */

void SPI_Denit(SPI_RegDef_t *pSPIx){

}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName){

	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;

}


/*********************************************************************
 * @fn      		  - SPI_SendData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - This is blocking call

 */

void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len){

	while(Len>0)
	{
		//1. wait until TXE is set, so check status register if 0 then wait
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG)==FLAG_RESET);

		//2.check the CRCL bit in CR1
		//if 16 bit
		if(pSPIx->CR1 & (1<<SPI_CRCL_16BITS))      //need to check and update
		{
			//if 16 bit DFF
			//1. load the data in to the data register.
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else{
			//elseif 8 bit DFF
			pSPIx->DR =*pTxBuffer;
			Len--;
			pTxBuffer++;
		}

	}
}






/*********************************************************************
 * @fn      		  - SPI_ReceiveData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len){

}


/*********************************************************************
 * @fn      		  - SPI_PeripheralControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */


/*********************************************************************
 * @fn      		  - SPI_SSIConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */


/*********************************************************************
 * @fn      		  - SPI_SSOEConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */


/*********************************************************************
 * @fn      		  - SPI_IRQInterruptConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi){

}


/*********************************************************************
 * @fn      		  - SPI_IRQPriorityConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

}
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/***************************************************************************
 * spi peripheral enable
 */

 void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
 {
	 if(EnOrDi == ENABLE)
	 {
		 pSPIx->CR1 |= (1<<SPI_CR1_SPE);
	 }else{
		 pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
	 }
 }


