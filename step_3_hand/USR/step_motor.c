# include "pbdata.h"

//c 6789

void motor_init(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);


}

void motor_go(int n,float deg)
{
	int i=0;
	for(i=0;i<deg;i++)
	{
		//1
  GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//2
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//3
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//4
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//5
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//6
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//7
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//8
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	}
	
}
void motor_back(int n,float deg)
{
	int j=0;
	for(j=0;j<deg;j++)
	{
		//8
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//7
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//6
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//5
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//4
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  GPIO_ResetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//3
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//2
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	//1
  GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_8);
  GPIO_SetBits(GPIOC,GPIO_Pin_9);
	delay_ms(n);
	
	}
}

	
	
	
	
	
	

