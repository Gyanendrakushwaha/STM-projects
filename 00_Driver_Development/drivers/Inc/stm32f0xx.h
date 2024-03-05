//Linker script for STM32F0DISCOVERY Board embedding STM32F051R8Tx Device from stm32f0 series
//**                      64Kbytes FLASH
//**                      8Kbytes RAM

#ifndef 	INC_STM32F0XX_H_
#define 	INC_STM32F0XX_H_

#include<stdint.h>


/**********************************START:Processor Specific Details **********************************/
/*





 *base address of flash and srm memories
 */

#define FLASH_BASEADDR	0x08000000U  //2kb
#define SRAM1_BASEADDR	0x20000000U
//#define SRAM1_BASEADDR	0x20000000U
#define SRAM 			SRAM1_BASEADDR
#define ROM_BASEADDR	0x1FFFEC00  //check once again


/*
 * defining base address of AHBx, APBx buses
 */
#define PERIPH_BASEADDR	  		0x40000000
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR  //0x40000000
#define APB2PERIPH_BASEADDR		0x40010000
#define AHB1PERIPH_BASEADDR		0x40020000
#define AHB2PERIPH_BASEADDR		0x48000000

/*
 * base address of peripherals which are hanging on AHB1 bus
 * TODO: complete for all other peripherals
 */

#define GPIOA_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB2PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB2PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR			(AHB2PERIPH_BASEADDR + 0x1400)

//RCC Base address
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)

/*
*base address of peripherals which are helping on APB1 BUS
*/
//I2C
#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400)   //APB1PERIPH_BASEADDR = 0x40000000
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)

//SPI peripheral base addresses
#define SPI1_BASEADDR			(APB1PERIPH_BASEADDR + 0x13000)
#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800)

//USART
#define USART1_BASEADDR			(APB1PERIPH_BASEADDR + 0x13800)
#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800)
#define USART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00)
#define USART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000)
#define USART6_BASEADDR			(APB1PERIPH_BASEADDR + 11400)
#define USART7_BASEADDR			(APB1PERIPH_BASEADDR + 0x11800)
#define USART8_BASEADDR			(APB1PERIPH_BASEADDR + 0x11C00)

//EXTI EXTERNAL interupt/event controller
#define EXTI_BASEADDR 			(APB1PERIPH_BASEADDR + 0x10400)

//syscfg
#define SYSCFG_BASEADDR 		(APB1PERIPH_BASEADDR + 0x10000)





/**********************************peripheral register definition structures **********************************/


//Note: registers of a peripheral are specific to mcu.
//e.g: number of registers of spi peripheral of stm32f0x family of MCUs may be different (more or less).
//compared to number of registers of spi peripheral ofd stm32Lx or stm32F0x family of MCUs.
//please check your device RM.
typedef struct
{
	volatile 	uint32_t MODER;				//GPIO port mode register   	//variable(place holder) to hold values for GPIOx_MODE register and so on
	volatile	uint32_t OTYPER;			//GPIO port output type register
	volatile	uint32_t OSPEEDR;			//GPIO port output speed register
	volatile	uint32_t PUPDR;				//GPIO port pull up pull down register
	volatile	uint32_t IDR;				//GPIO port input data register
	volatile	uint32_t ODR;				//GPIO port output data register
	volatile	uint32_t BSRR;				//GPIO port bit set/reset register
	volatile	uint32_t LCKR;				//GPIO port configuration lock register
	volatile	uint32_t AFR[2];			//GPIO alternate function register AFR[0] =low register, AFR[1]=high register
	volatile	uint32_t BRR;				//GPIO port bit reset register
}GPIO_RegDef_t;
//	GPIOA->MODER =25 // storing value 25 in the MODER register
//  *(0x40020000 + 0x00 ) = 25; //this is how compiler does


/*
 * peripheral register definition structure for RCC
 */
typedef struct
{
	volatile uint32_t CR;			//Clock control register (RCC_CR)
	volatile uint32_t CFGR;         //Clock configuration register (RCC_CFGR
	volatile uint32_t CIR;			//Clock interrupt register (RCC_CIR)
	volatile uint32_t APB2RSTR;		//APB peripheral reset register 2 (RCC_APB2RSTR)
	volatile uint32_t APB1RSTR;		//APB peripheral reset register 1 (RCC_APB1RSTR)
	volatile uint32_t AHBENR;		//AHB peripheral clock enable register (RCC_AHBENR)
	volatile uint32_t APB2ENR;		//APB peripheral clock enable register 2 (RCC_APB2ENR)
	volatile uint32_t APB1ENR;		//APB peripheral clock enable register 1 (RCC_APB1ENR)
	volatile uint32_t BDCR;			//RTC domain control register (RCC_BDCR
	volatile uint32_t CSR;			//Control/status register (RCC_CSR)
	volatile uint32_t AHBRSTR;		//AHB peripheral reset register
	volatile uint32_t CFGR2;		//AHB peripheral reset register (RCC_AHBRSTR
	volatile uint32_t CFGR3;		//Clock configuration register 2 (RCC_CFGR2)
	volatile uint32_t CR2;			//Clock configuration register 3 (RCC_CFGR3
}RCC_RegDef_t;


/*
 * peripheral register definition structure for SPI
 */
typedef struct
{
	volatile uint32_t CR1;        /*!< TODO,     										Address offset: 0x00 */
	volatile uint32_t CR2;        /*!< TODO,     										Address offset: 0x04 */
	volatile uint32_t SR;         /*!< TODO,     										Address offset: 0x08 */
	volatile uint32_t DR;         /*!< TODO,     										Address offset: 0x0C */
	volatile uint32_t CRCPR;      /*!< TODO,     										Address offset: 0x10 */
	volatile uint32_t RXCRCR;     /*!< TODO,     										Address offset: 0x14 */
	volatile uint32_t TXCRCR;     /*!< TODO,     										Address offset: 0x18 */
	volatile uint32_t I2SCFGR;    /*!< TODO,     										Address offset: 0x1C */
	volatile uint32_t I2SPR;      /*!< TODO,     										Address offset: 0x20 */
} SPI_RegDef_t;


/*
 * peripheral definitions (peripheral base addresses typecasted to GPIO_RegDef_t)
 */
//pointer variables to  structure type GPIO_RegDef_t
#define GPIOA  	(GPIO_RegDef_t*)GPIOA_BASEADDR //base address of GPIOA = (AHB2PERIPH_BASEADDR + 0x0000) = 0x40010000 + 0x0000 = 0x40010000
#define GPIOB  	(GPIO_RegDef_t*)GPIOB_BASEADDR
#define GPIOC  	(GPIO_RegDef_t*)GPIOC_BASEADDR
#define GPIOD  	(GPIO_RegDef_t*)GPIOD_BASEADDR
#define GPIOE  	(GPIO_RegDef_t*)GPIOE_BASEADDR
#define GPIOF  	(GPIO_RegDef_t*)GPIOF_BASEADDR



//to use the RCC register for different purpose which are stored in structure RCC_RegDef_t we are defining a pointer variable RCC whose base address will be base address of RCC register
#define RCC     ((RCC_RegDef_t*)RCC_BASEADDR)   //created a structure variable of RCC_RegDef_t with starting address (RCC_BASEADDR == (AHB1PERIPH_BASEADDR + 0x1000) )  and  named it RCC

//peripheral base addresses of SPI typecasted to SPI_RegDef_t
#define SPI1	((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2	((SPI_RegDef_t*)SPI2_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN() 	(RCC->AHBENR |= (1<<17))
#define GPIOB_PCLK_EN() 	(RCC->AHBENR |= (1<<18))
#define GPIOC_PCLK_EN() 	(RCC->AHBENR |= (1<<19))
#define GPIOD_PCLK_EN() 	(RCC->AHBENR |= (1<<20))
#define GPIOE_PCLK_EN() 	(RCC->AHBENR |= (1<<21))
#define GPIOF_PCLK_EN() 	(RCC->AHBENR |= (1<<22))

/*
 * Clock disable macro for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()		(RCC->AHBENR &= ~(1<<17))
#define GPIOB_PCLK_DI() 	(RCC->AHBENR &= ~(1<<18))
#define GPIOC_PCLK_DI() 	(RCC->AHBENR &= ~(1<<19))
#define GPIOD_PCLK_DI() 	(RCC->AHBENR &= ~(1<<20))
#define GPIOE_PCLK_DI() 	(RCC->AHBENR &= ~(1<<21))
#define GPIOF_PCLK_DI() 	(RCC->AHBENR &= ~(1<<22))


/*
 * clock enable macros for I2C peripherals
 */
#define I2C1_PCLK_EN()      (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()      (RCC->APB1ENR |= (1<<22))

/*
 * clock DISABLE macros for I2C peripherals
 */
#define I2C1_PCLK_DI()      (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()      (RCC->APB1ENR &= ~(1<<22))


/*
 * CLOCK enable for SPIx peripherals
 */
//SPI1 is in APB2 WHILE SPI2 is in APB1

#define SPI1_PCLK_EN()      (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN() 		(RCC->APB1ENR |= (1<<14))


/*
 * CLOCK DISABLE for SPIx peripherals
 */
#define SPI1_PCLK_DI()      (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI() 		(RCC->APB1ENR &= ~(1<<14))


/*
 * CLOCK ENABLE MACROS FOR USART
 */
#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1<<14))
#define USART8_PCLK_EN()	(RCC->APB2ENR |= (1<<7))
#define USART7_PCLK_EN()	(RCC->APB2ENR |= (1<<6))
#define USART6_PCLK_EN()	(RCC->APB2ENR |= (1<<5))

#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1<<18))
#define USART4_PCLK_EN()	(RCC->APB1ENR |= (1<<19))
#define USART5_PCLK_EN()	(RCC->APB1ENR |= (1<<20))

/*
 * CLOCK DISABLE MACROS FOR USART
 */
#define USART1_PCLK_DI()	(RCC->APB2ENR  &= ~(1<<14))
#define USART8_PCLK_DI()	(RCC->APB2ENR  &= ~(1<<7))
#define USART7_PCLK_DI()	(RCC->APB2ENR  &= ~(1<<6))
#define USART6_PCLK_DI()	(RCC->APB2ENR  &= ~(1<<5))

#define USART2_PCLK_DI()	(RCC->APB1ENR  &= ~(1<<17))
#define USART3_PCLK_DI()	(RCC->APB1ENR  &= ~(1<<18))
#define USART4_PCLK_DI()	(RCC->APB1ENR  &= ~(1<<19))
#define USART5_PCLK_DI()	(RCC->APB1ENR  &= ~(1<<20))

/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()	do{(RCC->AHBRSTR |= (1<<17));(RCC->AHBRSTR &= ~(1<<17)); }while(0) //TO reset the gpio we have to set and reset the corresponding AHBRSTR
#define GPIOB_REG_RESET()	do{(RCC->AHBRSTR |= (1<<18));(RCC->AHBRSTR &= ~(1<<18)); }while(0) //TO reset the gpio we have to set and reset the corresponding AHBRSTR
#define GPIOC_REG_RESET()	do{(RCC->AHBRSTR |= (1<<19));(RCC->AHBRSTR &= ~(1<<19)); }while(0) //TO reset the gpio we have to set and reset the corresponding AHBRSTR
#define GPIOD_REG_RESET()	do{(RCC->AHBRSTR |= (1<<20));(RCC->AHBRSTR &= ~(1<<20)); }while(0) //TO reset the gpio we have to set and reset the corresponding AHBRSTR
#define GPIOE_REG_RESET()	do{(RCC->AHBRSTR |= (1<<21));(RCC->AHBRSTR &= ~(1<<21)); }while(0) //TO reset the gpio we have to set and reset the corresponding AHBRSTR
#define GPIOF_REG_RESET()	do{(RCC->AHBRSTR |= (1<<22));(RCC->AHBRSTR &= ~(1<<22)); }while(0) //TO reset the gpio we have to set and reset the corresponding AHBRSTR



//SOME generic macros
#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_RESET 		RESET
#define FLAG_SET		SET

/***************************************************************
 *Bit position definitions of SPI peripheral CR1 register.
 ****************************************************************/
#define SPI_CR1_CPHA       0
#define SPI_CR1_CPOL 	   1
#define SPI_CR1_MSTR 	   2
#define SPI_CR1_SPE		   6        //spi peripheral enable bit, all the init settings of SPI are done in SPE disabled mode
									//while in enable mode it only perform data communication
#define SPI_CR1_BR	       3
#define SPI_CR1_CRCL	   11   	// CRC length
									//This bit is set and cleared by software to select the CRC length.
									//0: 8-bit CRC length
									//1: 16-bit CRC length
#define SPI_CR1_BIDIOE	   14
#define SPI_CR1_BIDIMODE   15

/***************************************************************
 *Bit position definitions of SPI peripheral CR2 register.
 ****************************************************************/
#define SPI_CR2_RXDMAEN       0
#define SPI_CR2_TXDMAEN       1
#define SPI_CR2_RXNEIE       6
#define SPI_CR2_TXEIE       7
#define SPI_CR2_DS       	8      //if we wnat 8bit DS then DS should be set to 0111: 8-bit
#define SPI_CR2_LDMA_RX       13
#define SPI_CR2_LDMA_TX       14


/***************************************************************
 *Bit position definitions of SPI peripheral status register.
 ****************************************************************/
#define SPI_SR_RXNE       0
#define SPI_SR_TXE       1
#define SPI_SR_CHSIDE     2
#define SPI_SR_UDR       3
#define SPI_SR_BSY       7



#include "stm32f0xx_gpio_driver.h"
#include "stm32f0xx_spi_driver.h"
//#include "stm32f0xx_usart_driver.h"
#endif  /*INC_STM32F0XX_H_ */
