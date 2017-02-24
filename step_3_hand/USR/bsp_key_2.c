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
void Key2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*??????(PA)???*/
	RCC_APB2PeriphClockCmd(macKEY1_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = macKEY1_GPIO_PIN; 
	
	// IO ??????,????????
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	
	GPIO_Init(macKEY1_GPIO_PORT, &GPIO_InitStructure);
}

 /*
 * ???:Key_Scan
 * ??  :?????????
 * ??  :GPIOx:x ??? A,B,C,D?? E
 *		     GPIO_Pin:??????? 	
 * ??  :KEY_OFF(?????)?KEY_ON(????)
 */
uint8_t Key2_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*????????? */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*?????? */
		printf("\nkey2±»°´ÏÂ \n");
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}