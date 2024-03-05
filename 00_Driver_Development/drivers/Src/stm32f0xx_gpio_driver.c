/*
 * stm32f0xx_gpio_driver.c
 *
 *  Created on: Jul 6, 2023
 *      Author: 158184
 */
//driver source file should containg driver header file
#include "stm32f0xx_gpio_driver.h"
#include "stm32f0xx.h"
/*
 * peripheral clock setup
 */
//by using this function we are going to enable or disable the peripheral clock for given gpio base address
//so first parameter pointer to the base address
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi)
{
if(EnorDi == ENABLE)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_PCLK_EN();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_PCLK_EN();
	}else if(pGPIOx == GPIOC)
	{

		GPIOC_PCLK_EN();
	}else if(pGPIOx == GPIOD)
	{
		GPIOD_PCLK_EN();
	}else if(pGPIOx == GPIOE)
	{
		GPIOE_PCLK_EN();
	}else if(pGPIOx == GPIOF)
	{
		GPIOF_PCLK_EN();
	}
}else{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
}
}
/*
 * initialize  and de-initialize
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)    //API to initialize  given gpio pin.
{
	uint32_t temp = 0;
	//enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

//1.configure the mode of gpio pin.
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG )
	{
		//the non interrupt mode
		//temp is the variable to store the number which will set to the required register.
		temp= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//clearing before setting.
		pGPIOHandle->pGPIOx->MODER |= temp; //setting

	}else{
		//this part will see later. //interrupt mode


	}
	temp=0;
//2. configure the speed.
	temp= (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//clearing bits before setting
	pGPIOHandle->pGPIOx->OSPEEDR |=temp;

	temp=0;

//3. configure the pull up and pull down speed
	temp= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl <<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//clearing bits before setting
	pGPIOHandle->pGPIOx->PUPDR |=temp;

	temp=0;

//4.configure the output type
	temp= (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//clearing bits before setting
	pGPIOHandle->pGPIOx->OTYPER |=temp;

	temp=0;

//5.configure the Alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode == GPIO_MODE_ALTFN){

		//configure the alt function register
		uint32_t temp1, temp2;

		temp1= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8;   //this will decide the AFR register
		temp2= pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;  //this is for reaching the address to set the values

		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF <<(4*temp2));  //clearing bits before setting
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <<(4*temp2));
	}
}

void GPIO_Denit(GPIO_RegDef_t *pGPIOx)    //API to Deinitialize clock for given gpio pin
{
	if(pGPIOx == GPIOA)
		{
			GPIOA_REG_RESET();
		}else if(pGPIOx == GPIOB)
		{
			GPIOA_REG_RESET();
		}else if(pGPIOx == GPIOC)
		{
			GPIOA_REG_RESET();
		}else if(pGPIOx == GPIOD)
		{
			GPIOA_REG_RESET();
		}else if(pGPIOx == GPIOE)
		{
			GPIOA_REG_RESET();
		}else if(pGPIOx == GPIOF)
		{
			GPIOA_REG_RESET();
		}
}

/*
 * data read
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber) //here we need pin number and base address of the gpio peripheral and here output will be pin state that is a 0 or 1.
{
uint8_t value;
value = (uint8_t)((pGPIOx->IDR >> PinNumber)& 0x00000001 );

return value;  //return value will be 0 or 1
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) //same as above but it reads from 16 pins so 16 pin states,only port name needed as parameter
{
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);

	return value;  //return value will be 16 bit number
}

/*
 * data write
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value) // this Value can take pinset or pinreset
{
if(Value == GPIO_PIN_SET){
	//write 1
	pGPIOx->ODR |= (1<<PinNumber);
}else{
	//write 0
	pGPIOx->ODR &= ~(1<<PinNumber);
}
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value)//as 16 pin are there hence 16 inputs for pin state is required
{
	pGPIOx->ODR =Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}


/*
 * IRQ configuration and ISR  handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber,uint8_t IRQPriority, uint8_t EnorDi)
{

}
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
