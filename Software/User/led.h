/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define ON 1
#define OFF 0

#define LED(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_2)

/* Exported functions ------------------------------------------------------- */

void LED_Init(void);
					
#endif /* __LED_H */
