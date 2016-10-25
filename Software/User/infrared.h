/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INFRARED_H
#define __INFRARED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define INFRARED_PROT GPIOA
#define Inf1 GPIO_Pin_1
#define Inf2 GPIO_Pin_2
#define INFRARED1 (Get_Adc_Average(ADC_Channel_1, 1)*(3.3/4096)>1.5)?1:0  //1表示黑, 0表示白
#define INFRARED2 (Get_Adc_Average(ADC_Channel_2, 1)*(3.3/4096)>1.5)?1:0
#define BLACK 1
#define WHITE 0

//u8 INFRARED1,INFRARED2;

/* Exported functions ------------------------------------------------------- */

void Infrared_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);

#endif /* __INFRARED_H */
