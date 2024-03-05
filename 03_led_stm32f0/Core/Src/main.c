#include"stm32F0xx.h"
#include<stdio.h>
extern void initialise_monitor_handles(void);
int main()
{	//to blink led on port c.9 first we need to enable CLK for port C

	//why clock needed
	//to Microcontrollers are reliant on their clock source.
	//The processor, the bus, and the peripherals all use the clock to synchronize their operations.
	//The clock determines how fast the processor executes its instructions, so it is fundamental to performance.



	//1//to enable clock we use RCC reset and clock control
	//AHB peripheral clock enable register (RCC_AHBENR) is 32 bit register used to set clock for ports
	//port c is at 19 th bit
    RCC -> AHBENR |= (1<<19); //ORing of RCC->AHBENR and (1 at 19th bit)



    //2//now we need to set Port C.8 as output port.
    // GPIOx_MODER general purpose I/Os port Mode Registers, used to set pin of port as output/input.
    GPIOC -> MODER |= (1<<18); // enable Port C pin 9 as a digital output.
while(1)
    {



    //3// // turn GPIOC pin 8 ON or asset high
//     GPIO port output data register (GPIOx_ODR) (x = A to F) used to send 0 or 1 on port pins
    GPIOC -> ODR |= (1<<9);
//    initialise_monitor_handles();
//    printf("on");
    for(int i =0 ;i<1000000;i++);
    GPIOC -> ODR &= ~(1<<9);
//    initialise_monitor_handles();
//    printf("off");
    for(int i=0;i<1000000;i++);
    }
}
