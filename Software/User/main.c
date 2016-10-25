/**
  ******************************************************************************
  * 主函数代码
	* @Copyright Han ZHANG(haldak) @ Wenhao DING(Gilgamesh) | All rights reserved.
	* 清华大学电子系硬件部 & 未来通信兴趣团队
	* 硬件设计大赛
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port.h"
#include "led.h"
#include "pwm.h"
#include "infrared.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
	//Start with board specific hardware init.
//	u16 led0pwmval = 0;
//	u8 dir = 1;
//	
	Our_Sys_Init();
	LED_Init();
	Infrared_Init();
	Engine_Init();

	//Infinite loop to deal with your project.
	while(1)
	{
		Forward(800);
		Delay(3000);
		Left(800, FORWARD);
		Right(400, FORWARD);
		Delay(1000);
	}
}
