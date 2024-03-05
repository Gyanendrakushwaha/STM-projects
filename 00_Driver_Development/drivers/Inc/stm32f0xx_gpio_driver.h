/*
 * stm32f0xx_gpio_driver.h
 *
 *  Created on: Jul 6, 2023
 *  Author: 158184
 */

#ifndef INC_STM32F0XX_GPIO_DRIVER_H_
#define INC_STM32F0XX_GPIO_DRIVER_H_

//driver header file contains mcu specific header file
#include "stm32f0xx.h"


// THIS structure variable is for the users,user will use this variables as parameters
typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;  //possible values from  @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed; //possible values from @GPIO_PIN_VALUES
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType; //possible values from @GPIO_OUTPUT_VALUES 0: Output push-pull (reset state)
															          //1: Output open-drain

	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;


/*
 * this is a handle structure for GPIOx PINs
 */
typedef struct
{
	//creating a pointer variable of type struct GPIO_RegDef_t   to hold the base address of GPIO Peripheral
	GPIO_RegDef_t *pGPIOx; //this holds the base address of the GPIO port to which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig;  //this variable holds GPIO Pin configuration settings entered by user

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * @GPIO Pin numbers
 */
#define GPIO_PIN_NO_0 		0
#define GPIO_PIN_NO_1 		1
#define GPIO_PIN_NO_2 		2
#define GPIO_PIN_NO_3 		3
#define GPIO_PIN_NO_4 		4
#define GPIO_PIN_NO_5 		5
#define GPIO_PIN_NO_6 		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9 		9
#define GPIO_PIN_NO_10 		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15 		15


 /*@GPIO_PIN_MODES
 * GPIO pins possible modes
 */
//NON INTERUPT MODES
#define GPIO_MODE_IN 		0   //input mode
#define GPIO_MODE_OUT		1	//general purpose mode
#define GPIO_MODE_ALTFN		2	//alternate function mode
#define GPIO_MODE_ANALOG 	3	//analog mode
//INTERUPT MODES
#define GPIO_MODE_IT_FL	 	4
#define GPIO_MODE_IT_FT		5
#define GPIO_MODE_IT_RFT	6


/*@GPIO_OUTPUT_VALUES
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP		0   //output type is push pull - no pull up pull down required in this mode
#define GPIO_OP_TYPE_OD		1	//output type is open drain -after this a pull up required

/*@GPIO_PIN_VALUES
 * GPIO output type speed register
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
//#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/*
 * GPIO port pullup/pull down register
 */
#define GPIO_NO_PUPD		0   //no pull up or pull down
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

/*******************************************************************
 *						API supported by this driver
 *						for more information about the API check the function defination
 *
 ********************************************************************/

/*
 * peripheral clock setup
 */
//by using this function we are going to enable or disable the peripheral clock for given gpio base address
//so first parameter pointer to the base address
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnroDi);

/*
 * initialize  and de-initialize
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);    //API to initialize clock for given gpio pin
void GPIO_Denit(GPIO_RegDef_t *pGPIOx);    //API to Deinitialize clock for given gpio pin


/*
 * data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber); //heere we need pin number and base address of the gpio peripheral and here output will be pin state that is a 0 or 1
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx); //same as above but it reads from 16 pins so 16 pin states,only port name needed as parameter
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value); // this Value can take pinset or pinreset
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);//as 16 pin are there hence 16 inputs for pin state is required
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);


/*
 * IRQ configuration and ISR  handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber,uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);











#endif /* INC_STM32F0XX_GPIO_DRIVER_H_ */
