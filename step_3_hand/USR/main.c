#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);
void Key_GPIO_Config(void);	
void Key2_GPIO_Config(void);

extern float yaw;

u8 status;		 //用于判断接收/发送状态
u8 txbuf[1];	 //发送缓冲
u8 rxbuf[1];	 //接收缓冲


int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
   
	
   RCC_Configuration();	//系统时钟初始化
   GPIO_Configuration();//端口初始化
   USART_Configuration();
   NVIC_Configuration();
	 key_configuration();
	 //usart2_init();
	 //motor_init();
	   SPI_NRF_Init(); 
	 //Car_GPIO_Config();
	
		printf("\r\n 这是一个 NRF24L01 无线传输实验 \r\n");
   	printf("\r\n 这是无线传输 从机端 的反馈信息\r\n");
	printf("\r\n   正在检测NRF与MCU是否正常连接。。。\r\n");
	 
	 /*检测NRF模块与MCU的连接*/
   	status = NRF_Check();   		
	   if(status == SUCCESS)	   
	   		 printf("\r\n      NRF与MCU连接成功\r\n");  
	   else	  
	   	     printf("\r\n   正在检测NRF与MCU是否正常连接。。。\r\n");
			  
	
	
	
	
	while(1)                            
	{	   
		Key2_press();
		Key1_press();
	}
	
  
 }

void RCC_Configuration(void)
{
    SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
   	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void USART_Configuration(void)
{
  USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
}



