#include "pbdata.h"
#include "bsp_spi_nrf.h"

u8 dt=0;


void RCC_HSE_Configuration(void) //HSE��ΪPLLʱ�ӣ�PLL��ΪSYSCLK 
{ 
   RCC_DeInit(); /*������RCC�Ĵ�������Ϊȱʡֵ */ 
   RCC_HSEConfig(RCC_HSE_ON); 	 /*�����ⲿ���پ���HSE�� HSE�����(ON)*/ 

   if(RCC_WaitForHSEStartUp() == SUCCESS) {  /*�ȴ�HSE����,  SUCCESS��HSE�����ȶ��Ҿ���*/  

   RCC_HCLKConfig(RCC_SYSCLK_Div1);/*����AHBʱ��(HCLK)RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ*/  
   RCC_PCLK2Config(RCC_HCLK_Div1); /*���ø���AHBʱ��(PCLK2)RCC_HCLK_Div1����APB2ʱ�� = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*���õ���AHBʱ��(PCLK1)RCC_HCLK_Div2����APB1ʱ�� = HCLK / 2*/      

   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);/*����PLLʱ��Դ����Ƶϵ��*/    
   RCC_PLLCmd(ENABLE); 	 /*ʹ��PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/ 
    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*����ϵͳʱ�ӣ�SYSCLK�� */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08��PLL��Ϊϵͳʱ�� */	    
 } 
} 

void delay(u32 nCount)
{
	for(;nCount!=0;nCount--);
}

/****************************************************************************
* ��    �ƣ�delay_us(u32 nus)
* ��    �ܣ�΢����ʱ����
* ��ڲ�����u32  nus
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	 SysTick->LOAD = 9*nus;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

/****************************************************************************
* ��    �ƣ�delay_ms(u16 nms)
* ��    �ܣ�������ʱ����
* ��ڲ�����u16 nms
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_ms(u16 nms)
{
     //ע�� delay_ms�������뷶Χ��1-1863
	 //���������ʱΪ1.8��

	 u32 temp;
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}
