#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#define usart_rev_buflenght 1024
typedef struct
{
  unsigned char RevBuffer[usart_rev_buflenght];
  unsigned short RevLength;
  void (*RevHandler)(unsigned char *str,unsigned short len);
  unsigned char RevCount;
}UART_DEF;
extern UART_DEF UartDataRev[3];
void USART1_Config(void);
void USART2_Config(void);
void USART3_Config(void);
void UART1_SendString(unsigned char *s,unsigned char len);
void UART2_SendString(unsigned char *s,unsigned char len);
#endif /* __USART1_H */
