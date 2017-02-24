
#include "pbdata.h"

void Car_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE); 
														   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;	

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
																   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;

		GPIO_Init(GPIOA, &GPIO_InitStructure);
																   
}

void Car_run(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
  GPIO_SetBits(GPIOB,GPIO_Pin_8);
  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
  GPIO_SetBits(GPIOB,GPIO_Pin_10);
  GPIO_ResetBits(GPIOB,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_11);
  GPIO_ResetBits(GPIOA,GPIO_Pin_12);

}

void Car_stop(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
  GPIO_SetBits(GPIOB,GPIO_Pin_1);
  GPIO_SetBits(GPIOB,GPIO_Pin_8);
  GPIO_SetBits(GPIOB,GPIO_Pin_9);
  GPIO_SetBits(GPIOB,GPIO_Pin_10);
  GPIO_SetBits(GPIOB,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_12);

}

void Car_back(void)
{
  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
  GPIO_SetBits(GPIOB,GPIO_Pin_1);
  GPIO_ResetBits(GPIOB,GPIO_Pin_8);
  GPIO_SetBits(GPIOB,GPIO_Pin_9);
  GPIO_ResetBits(GPIOB,GPIO_Pin_10);
  GPIO_SetBits(GPIOB,GPIO_Pin_11);
  GPIO_ResetBits(GPIOA,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_12);

}

void Car_left(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
  GPIO_SetBits(GPIOB,GPIO_Pin_8);
  GPIO_SetBits(GPIOB,GPIO_Pin_9);
  GPIO_SetBits(GPIOB,GPIO_Pin_10);
  GPIO_SetBits(GPIOB,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_11);
  GPIO_ResetBits(GPIOA,GPIO_Pin_12);

}


void Car_right(void)
{
  GPIO_SetBits(GPIOB,GPIO_Pin_0);
  GPIO_SetBits(GPIOB,GPIO_Pin_1);
  GPIO_SetBits(GPIOB,GPIO_Pin_8);
  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
  GPIO_SetBits(GPIOB,GPIO_Pin_10);
  GPIO_ResetBits(GPIOB,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_11);
  GPIO_SetBits(GPIOA,GPIO_Pin_12);

}

