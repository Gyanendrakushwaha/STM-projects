//
//#include "main.h"
//#include<stdio.h>
////TIM_HandleTypeDef htim2;
//
//
//int main(void)
//{
//
//	RCC -> AHBENR |= (1<<19);   //enable clk for port c
//	GPIOC -> MODER |=(1<<16);//enable port c pin 8 as a digital output
//	GPIOC -> ODR |=(1<<8); //turn GPIOC pin 8 on or assert high
//
//
//
//  while (1)
//  {
//
//
//	   GPIOC -> ODR |=(1<<8);
//
//	   for(int i=0;i<100000;i++);
//
//		GPIOC ->ODR &= ~(1<<8);
//
//  }
//}

#include "main.h"
#include<stdio.h>
void latch(){
	GPIOB -> BSRR |= (1<<2);
	for(int i=0;i<100000;i++);
	GPIOB -> BRR |= (1<<2);
	for(int i=0;i<100000;i++);
}

void s_data()
{
GPIOB->BSRR= (1<<0);
GPIOB->BRR=(1<<1);
}

int main(void)
{

	RCC -> AHBENR |= (1<<19);   //enable clk for port c
	RCC -> AHBENR |= (1<<17);   //port B
	RCC -> AHBENR |= (1<<18);   //port A


	GPIOC -> MODER |=(1<<16)|(1<<18);//enable port c pin 8 and 9 as a digital output
	GPIOA -> MODER |=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	GPIOB -> MODER |=(1<<0)|(1<<1)|(1<<2);

	GPIOC -> ODR |=(1<<8)|(1<<9); //turn GPIOC pin 8 on or assert high




  while (1)
  {
	  for(int i=0;i<100000;i++); //delay
	  //First set RS= 0, R/W=0, EN=1; And give 10ms delay,
	  GPIOB -> BSRR |= (1<<0)|(1<<2);             //PB.2=RS 1,  PB.1=R/W 0 ,PB.0=1 En
	  GPIOC -> BSRR |=(1<<8)|(1<<9);				//led

	  for(int i=0;i<100000;i++);
//	  GPIOB -> BRR |= (1<<2);				//PB.2=RS 1,  PB.1=R/W 0 ,PB.0=0 En
	  GPIOC ->BRR |= (1<<8)|(1<<9);					//led



	      GPIOA -> ODR |= 0X0001;    //data ports D0 -D7
	      latch();
//	      GPIOA -> BRR |= 0X0001;
	      GPIOA -> ODR |= 0X0038;
	      latch();
	      latch();
	      latch();
	      latch();
//	      for(int i =0 ;i<10000;i++);
//	      GPIOA -> BRR |= 0X0038;
	      GPIOA -> ODR |= 0X000E;
	      latch();
//	      for(int i =0 ;i<10000;i++);
//	      GPIOA -> BRR |= 0X000E;
	      GPIOA -> ODR |= 0X0010;
	      latch();
//	      for(int i =0 ;i<10000;i++);
//	      GPIOA -> BRR |= 0X0010;
	      GPIOA -> ODR |= 0X0006;
	      latch();
//	      for(int i =0 ;i<10000;i++);
//	      GPIOA -> BRR |= 0X0006;


	      s_data();
	      GPIOA -> ODR |= 5;
	      for(int i =0 ;i<10000000;i++);
	      GPIOA -> BRR |= 5;
  }
}

