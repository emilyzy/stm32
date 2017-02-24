#include "pbdata.h"


//uart reicer flag
#define b_uart_head  0x80  
#define b_rx_over    0x40 
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 

void Decode_frame(unsigned char data);
volatile unsigned char rx_buffer[RX_BUFFER_SIZE]; 
volatile unsigned char rx_wr_index; 
volatile unsigned char RC_Flag;  


float 	yaw,//???
		pitch,//??
		roll, //??
		alt,  //??
		tempr,//??
		press;//??
//ADC?
int16_t ax, ay, az;//????
int16_t gx, gy, gz;//???
int16_t hx, hy, hz;//???
//GPS????
float GPS_Altitude , //?????????,-9999.9?9999.9?
	  Latitude_GPS , //??	 ????
	  Longitude_GPS , //??  ????
	  Speed_GPS , //????  ??  ???
	  Course_GPS ; //????(000.0~359.9?,????????)
unsigned char GPS_STA_Num ;


void usart2_init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		USART_InitTypeDef  USART_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	 
		//usart
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//TX
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA,&GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//RX
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		 

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
	

		USART_InitStructure.USART_BaudRate=115200;
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;
		USART_InitStructure.USART_StopBits=USART_StopBits_1;
		USART_InitStructure.USART_Parity=USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

		USART_Init(USART2,&USART_InitStructure);
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		USART_Cmd(USART2,ENABLE);
		USART_ClearFlag(USART2,USART_FLAG_TC);
	
}

void UART2_Get_IMU(void)
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	yaw=(float)temp / 10.0f; //???
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	pitch=(float)temp / 10.0f;//??
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	roll=(float)temp / 10.0f;//??

	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	alt=(float)temp / 10.0f;//??
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	tempr=(float)temp / 10.0f;//??
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	press=(float)temp * 10.0f;//??

}

//?????ReportMotion ???????????ADC??
void UART2_Get_Motion(void)
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ax=temp;//???? X??ADC?
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ay=temp;//???? Y??ADC?
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	az=temp;//???? Z??ADC?
	
	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gx=temp;//??? X??ADC?
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gy=temp;//??? Y??ADC?
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gz=temp;//??? Z??ADC?
	
	temp = 0;
	temp = rx_buffer[14];
	temp <<= 8;
	temp |= rx_buffer[15];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hx=temp;//??? X??ADC?
	
	temp = 0;
	temp = rx_buffer[16];
	temp <<= 8;
	temp |= rx_buffer[17];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hy=temp;//??? Y??ADC?
	
	temp = 0;
	temp = rx_buffer[18];
	temp <<= 8;
	temp |= rx_buffer[19];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hz=temp;//??? Z??ADC?
}

unsigned char Sum_check(void)
{ 
  unsigned char i;
  unsigned int checksum=0; 
  for(i=0;i<rx_buffer[0]-2;i++)
   checksum+=rx_buffer[i];
  if((checksum%256)==rx_buffer[rx_buffer[0]-2])
   return(0x01); //Checksum successful
  else
   return(0x00); //Checksum error
}



//--???????????? ????,??? ???????????
void UART2_CommandRoute(void)
{
 if(RC_Flag&b_rx_over){  //????????
		RC_Flag&=~b_rx_over; //????
		if(Sum_check()){ 
		//????
		if(rx_buffer[1]==0xA1){ //UART2_ReportIMU ???
		 UART2_Get_IMU();	//???
		}
		if(rx_buffer[1]==0xA2){ //UART2_ReportMotion ???
		 UART2_Get_Motion();	 //???
		} 
		 
		}//???????
	}
}

//??????????????????????
void Decode_frame(unsigned char data){
  if(data==0xa5) 
  { 
	RC_Flag|=b_uart_head; //?????A5 ???????
    rx_buffer[rx_wr_index++]=data; //??????.
  }
  else if(data==0x5a)
       { 
	   if(RC_Flag&b_uart_head) //????????A5 ???? ????????
	     { rx_wr_index=0;  //?? ?????
		   RC_Flag&=~b_rx_over; //?????????
         }
         else //???????A5
		  rx_buffer[rx_wr_index++]=data;
         RC_Flag&=~b_uart_head; //?????
       }
	   else
	   { rx_buffer[rx_wr_index++]=data;
		 RC_Flag&=~b_uart_head;
		 if(rx_wr_index==rx_buffer[0]) //??????.
	     {  
			RC_Flag|=b_rx_over; //?? ?????????
			UART2_CommandRoute(); //???????
          }
	   }

  if(rx_wr_index==RX_BUFFER_SIZE) //???????
  rx_wr_index--;
}

