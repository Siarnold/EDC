/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWM_H
#define __PWM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define FORWARD  1
#define BACKWARD 0

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);
void Wheel_Init(void);
void Engine_Init(void);
void Brake(void);
void Left(u16 speed, u8 dir);
void Right(u16 speed, u8 dir);
void Forward(u16 speed);
void Backward(u16 speed);

#endif /* __PWM_H */
