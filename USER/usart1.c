
#include "usart1.h"
#include <stdarg.h>



UART_DEF UartDataRev[3];

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		  //TIM3????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //??????????0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		  //????????3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ?¡§??¡À?????
	NVIC_Init(&NVIC_InitStructure);							  //?¨´??NVIC_InitStruct?????¡§???????????????¨¨NVIC?????¡Â
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		UartDataRev[0].RevBuffer[UartDataRev[0].RevLength++%usart_rev_buflenght]=USART_ReceiveData(USART1);
		UartDataRev[0].RevCount=0;
	}
}
void UART1_SendString(unsigned char *s, unsigned char len)
{
	unsigned char i;
	for (i = 0; i < len; i++)
	{
		USART_SendData(USART1, s[i]);
		while (!(USART1->SR & USART_FLAG_TXE))
			;
	}
}

void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		  //TIM3????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //??????????0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //????????3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ?¡§??¡À?????
	NVIC_Init(&NVIC_InitStructure);							  //?¨´??NVIC_InitStruct?????¡§???????????????¨¨NVIC?????¡Â
}

void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    UartDataRev[1].RevBuffer[UartDataRev[1].RevLength++%usart_rev_buflenght]=USART_ReceiveData(USART2);
		UartDataRev[1].RevCount=0;
	}
}
void UART2_SendString(unsigned char *s, unsigned char len)
{
	unsigned char i;
	for (i = 0; i < len; i++)
	{
		USART_SendData(USART2, s[i]);
		while (!(USART2->SR & USART_FLAG_TXE))
			;
	}
}
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		  //TIM3????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //??????????0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		  //????????3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ?¡§??¡À?????
	NVIC_Init(&NVIC_InitStructure);							  //?¨´??NVIC_InitStruct?????¡§???????????????¨¨NVIC?????¡Â
}

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		UartDataRev[2].RevBuffer[UartDataRev[2].RevLength++%usart_rev_buflenght]=USART_ReceiveData(USART3);
		UartDataRev[2].RevCount=0;
	}
}
void UART3_SendString(unsigned char *s, unsigned char len)
{
	unsigned char i;
	for (i = 0; i < len; i++)
	{
		USART_SendData(USART3, s[i]);
		while (!(USART3->SR & USART_FLAG_TXE))
			;
	}
}
