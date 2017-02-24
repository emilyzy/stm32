#include "pbdata.h"
/// ??????
static void Key_Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

/**
  * @brief  ???????I/O?
  * @param  ?
  * @retval ?
  */


void key_configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

 
uint8_t Key2_press(void)
{			
	u8 x[1] ={0x02};
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == KEY_ON )  
	{	 
		//printf("\nkey2被按下 \n");
		nrf_send(x);

		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

uint8_t Key1_press(void)
{			
		u8 x[1] ={0x01};
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == KEY_ON )  
	{	 
		//printf("\nkey1被按下 \n");
		nrf_send(x);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}

