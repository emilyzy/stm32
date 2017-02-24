#ifndef __KEY_H
#define	__KEY_H


#include "pbdata.h"

// ??KEY1,?????KEY2??,??KEY1_PA0?????
//#define   KEYI_PA0

#ifdef    KEYI_PA0
#define               macKEY1_GPIO_CLK                      RCC_APB2Periph_GPIOA
#define               macKEY1_GPIO_PORT    	                GPIOA			   
#define               macKEY1_GPIO_PIN		                  GPIO_Pin_0

#else    //KEY2_PC13
#define               macKEY1_GPIO_CLK                      RCC_APB2Periph_GPIOC
#define               macKEY1_GPIO_PORT    	                GPIOC		   
#define               macKEY1_GPIO_PIN		                  GPIO_Pin_13

#endif

 /*******
 *??????,??K1?K2??????,???????????
 KEY_ON 0
 KEY_OFF 1
 ********/
#define KEY_ON	1
#define KEY_OFF	0


void Key2_GPIO_Config(void);
uint8_t Key2_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /* __LED_H */

