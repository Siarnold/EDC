/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART1_H
#define __USART1_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	u8 X,Y;
	u8 HP;
}Player;

typedef struct
{
	Player Self,Opponent;
	u8 MyID;
	u8 Out;
	u8 Damage;
	struct
	{
		u8 X,Y;
		u8 IsExisted;
		u8 Color;
	}Target;
	struct
	{
		u8 Control;
		u8 BringHP;
		u8 TakeHP;
		u8 X,Y;
	}Plane;
	struct
	{
		u8 X,Y;
		u8 Type;
	}Tool;
	struct
	{
		u8 GameStatus;
		u16 GameTime;
	}Platform;
}SysMessage;

typedef struct
{
	u8 X;
	u8 Y;
}CmdMessage;

/* Exported constants --------------------------------------------------------*/
#ifndef BLACK
	#define BLACK 1
	#define WHITE 0
#endif

/* Exported macro ------------------------------------------------------------*/
enum{
	HP=1, TRANS, AIRCMD
};

enum{
	NONE, LITTLE, HUGE, DEADLY
};

extern SysMessage Message;

/* Exported functions ------------------------------------------------------- */
void Usart1_Init(void);
void USART1_IRQHandler(void);
u8 SendMessage(CmdMessage *m);

#endif /* __USART1_H */
