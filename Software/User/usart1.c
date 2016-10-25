/**
  ******************************************************************************
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart1.h"
#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 CanRead = 0;
SysMessage Message;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Usart1_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	SystemInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	USART_DeInit(USART1);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;			//Connect Rx
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;		//Connect Tx
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate            = 9600;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//接受数据串口响应中断
	//USART_ITConfig(USART1, USART_IT_TC, ENABLE);		//发送完毕串口响应中断
	
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_FLAG_RXNE) == RESET)		//Maybe Wrong
	{
		u8 x, i;
		for(i = 0; i < 18; i++)
		{
			x = USART_ReceiveData(USART1);
			switch(i)
			{
				case 0: 
				{
					Message.MyID                = (x & 0x0C) >> 2;
					Message.Platform.GameStatus = (x & 0x03);
					break;
				}
				case 1:
				{
					Message.Damage              = (x & 0xC0) >> 6;
					Message.Plane.Control       = (x & 0x20) >> 5;
					Message.Plane.BringHP       = (x & 0x10) >> 4;
					Message.Plane.TakeHP        = (x & 0x08) >> 3;
					Message.Out                 = (x & 0x04) >> 2;
					Message.Target.IsExisted    = (x & 0x02) >> 1;
					Message.Target.Color        = (x & 0x01);
					break;
				}
				case 2:  Message.Self.X            = x; break;
				case 3:  Message.Self.Y            = x; break;
				case 4:  Message.Opponent.X        = x; break;
				case 5:  Message.Opponent.Y        = x; break;
				case 6:  Message.Target.X          = x; break; 
				case 7:  Message.Target.Y          = x; break;
				case 8:  Message.Plane.X           = x; break;
				case 9:  Message.Plane.Y           = x; break;
				case 10: Message.Self.HP           = x; break; 
				case 11: Message.Opponent.HP       = x; break;
				case 12: Message.Tool.X            = x; break;
				case 13: Message.Tool.Y            = x; break;
				case 14: Message.Platform.GameTime = x; break;
				case 15: 
				{
					Message.Tool.Type          = (x & 0xC0) >> 6;
					Message.Platform.GameTime |= ((u16)(x & 0x3F) << 8);
					break;
				}
				case 16:
					if(x == 0x0D)
					{
						CanRead = 1;
					}
					break;
				case 17:
					if(x != 0x0A || !CanRead)
					{
						CanRead = 0;
					}
					break;
				default: break;
			}
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

u8 SendMessage(CmdMessage *m)
{
	USART_SendData(USART1, m->X);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, m->Y);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, 0x0D);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, 0x0A);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return 1;
}
