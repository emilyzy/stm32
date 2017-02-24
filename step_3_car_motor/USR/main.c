#include "pbdata.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART_Configuration(void);

extern float yaw;

u8 status;		 //�����жϽ���/����״̬
u8 txbuf[1];	 //���ͻ���
u8 rxbuf[1];	 //���ջ���


int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int main(void)
{
   
	float last_y=0.0 , der_y , yaw1 ,yaw2,der_y1, der_north,der_north1;
   RCC_Configuration();	//ϵͳʱ�ӳ�ʼ��
   GPIO_Configuration();//�˿ڳ�ʼ��
   USART_Configuration();
   NVIC_Configuration();
	 usart2_init();
	 motor_init();
	 SPI_NRF_Init(); 
	 Car_GPIO_Config();
	
		printf("\r\n ����һ�� NRF24L01 ���ߴ���ʵ�� \r\n");
   	printf("\r\n �������ߴ��� �ӻ��� �ķ�����Ϣ\r\n");
  	printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");
	 
	 /*���NRFģ����MCU������*/
   	status = NRF_Check();   		
	   if(status == SUCCESS)	   
	   		 printf("\r\n      NRF��MCU���ӳɹ�\r\n");  
	   else	  
	   	   printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");
	
		


      delay_ms(1000);
			 //--------����Ϊ��ʼָ��-------
		 
		 
	  	 UART2_CommandRoute();
		   yaw2=yaw+180;//�õ���һ����������
	     
		    printf("yaw=%f\n",yaw2);
			 der_north=yaw2-150;
			 if(der_north>0)
			 {
					motor_back(1,der_north*1.5);
			 }else
		   {
					der_north1=0-der_north;
				  motor_go(1,der_north1*1.5);
			 }
			 delay_ms(5000);
			 //------��ʼָ��---END------------
		 
		 
		 while(1)
		 {
			 
			Car_right();
		 UART2_CommandRoute();
	
		 yaw1=yaw+180;//�õ���һ����������	 
		 //-------����Ϊ����ָ��--------
		 delay_ms(10);
		 UART2_CommandRoute();
		 last_y=yaw+180;
		 der_y=last_y-yaw1;
		 if(der_y>0)
		 {
				motor_back(1,der_y*2);
		 }else
		 {
			  der_y1=0-der_y;
				motor_go(1,der_y1*2);
		 }
			//----------����ָ��----END--------
		 
		 
		/*//����nrf2401������
		 nrf_get(rxbuf);
		
		 if(rxbuf[0] == 0x01)
		 {
			 printf("key1������\n");
		 }
			if(rxbuf[0] == 0x02)
		 {
				printf("key2������\n");
			 
		 }	*/
		 
		 
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



