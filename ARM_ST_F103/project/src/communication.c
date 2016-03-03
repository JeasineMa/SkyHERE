#include "communication.h"
#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include <stdarg.h>


uint8_t Cmd_Ble[Buffer_Size] = "#000-N*";
/*
  #089-C*
  C-Clockwise
  A-AntiClockwise
  N- Noturn
*/

uint8_t Buff_Ble[20];
uint8_t order = 0;

void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//I/O¿ú3õê¼»ˉ½á11ìå
    NVIC_InitTypeDef NVIC_InitStructure;//ÖD¶Ï3õê¼»ˉ½á11ìå
    USART_InitTypeDef USART_InitStructure;//′®¿ú3õê¼»ˉ½á11ìå  
    
    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
    
    
    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = 115200;                //ò»°ãéèÖÃÎa9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö3¤Îa8Î»êy¾Y¸ñê½
    USART_InitStructure.USART_StopBits = USART_StopBits_1;     //ò»¸öí￡Ö1Î»
    USART_InitStructure.USART_Parity = USART_Parity_No;        //ÎTÆæÅ¼D￡ÑéÎ»
    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Yá÷¿ØÖÆ
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//êÕ·￠Ä￡ê½   
    
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE);



	// GPIO_InitTypeDef GPIO_InitStructure;
	// USART_InitTypeDef USART_InitStructure;
	
	// /* config USART2 clock */
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// RCC_APB2PeriphClockCmd()RCC_APB2Periph_AFIO,ENABLE);
	
	// /* USART2 GPIO config */
	// /* Configure USART1 Tx (PA.09) as alternate function push-pull */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_Init(GPIOA, &GPIO_InitStructure);    
	// /* Configure USART1 Rx (PA.10) as input floating */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	// GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	// /* USART2 mode config */
	// USART_InitStructure.USART_BaudRate = 115200;
	// USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// USART_InitStructure.USART_Parity = USART_Parity_No ;
	// USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// USART_Init(USART2, &USART_InitStructure); 

	// USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// USART_Cmd(USART2, ENABLE); 

	// NVIC_InitTypeDef NVIC_InitStructure;

	// /* Configure one bit for preemption priority */
	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// /* 配置P[A|B|C|D|E]0为中断源 */
	// NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
	
}


void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	/* 使能 USART3 时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	 
	 
	/* USART3 使用IO端口配置 */    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //初始化GPIOA
	 
	/* USART3 工作模式配置 */
	USART_InitStructure.USART_BaudRate = 9600; //波特率设置：115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位数设置：8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //停止位设置：1位
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //是否奇偶校验：无
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制模式设置：没有使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收与发送都使能
	USART_Init(USART3, &USART_InitStructure);  //初始化USART3
	 
	/*使能串口3的发送和接收中断*/
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  
	USART_Cmd(USART3, ENABLE);// USART3 Enable

	/* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
}


void USART3_IRQHandler(void)
{
	uint8_t tmp;
	//Car_Run(1);
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收中断
	{
		tmp = USART_ReceiveData(USART3);
		if(tmp == '#')
		{
			order = 0;
			//USART_SendData(USART3, 'c');
		}
		Buff_Ble[order] = tmp;
		order++;
		if(tmp == '*')
		{
			memcpy(Cmd_Ble, Buff_Ble, Buffer_Size);
			order = 0;
			//USART_SendData(USART3, 'b');
			//USART1_printf(USART3,Cmd_Ble);
		}
	}
	USART_ClearITPendingBit(USART3,USART_IT_RXNE);
}

void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_SendData(USART2, USART_ReceiveData(USART2)); 
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}






// /*
//  * 函数名：DMA_Config
//  * 描述  ：DMA 串口的初始化配置
//  * 输入  ：无
//  * 输出  : 无
//  * 调用  ：外部调用
//  */
// void DMA_Config(void)
// {
//     DMA_InitTypeDef DMA_InitStructure;

// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟
// 	NVIC_Config();	   			//配置DMA中断

//  	/*设置DMA源：内存地址&串口数据寄存器地址*/
//     DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   

// 	/*内存地址(要传输的变量的指针)*/
//     DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
	
// 	/*方向：从内存到外设*/		
//     DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
// 	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
//     DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
	
// 	/*外设地址不增*/	    
//     DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
// 	/*内存地址自增*/
//     DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
// 	/*外设数据单位*/	
//     DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
// 	/*内存数据单位 8bit*/
//     DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
// 	DMA模式：一次传输，循环
//     DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
// 	/*优先级：中*/	
//     DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
// 	/*禁止内存到内存的传输	*/
//     DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
// 	/*配置DMA1的4通道*/		   
//     DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
	
// 	DMA_Cmd (DMA1_Channel4,ENABLE);					//使能DMA
// 	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断

// }
// /*
//  * 函数名：NVIC_Config
//  * 描述  ：DMA 中断配置
//  * 输入  ：无
//  * 输出  : 无
//  * 调用  ：外部调用
//  */
// static void NVIC_Config(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;
  
//   /* Configure one bit for preemption priority */
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
//   /* 配置P[A|B|C|D|E]0为中断源 */
//   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
// }





/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
	/* 将Printf内容发往串口 */
	USART_SendData(USART1, (unsigned char) ch);
//	while (!(USART1->SR & USART_FLAG_TXE));
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART1_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	
	    /* Make the value positive. */
	    value *= -1;
	}
	
	for (i = 10000; i > 0; i /= 10)
	{
	    d = value / i;
	
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	
	/* Null terminate the string. */
	*ptr = 0;
	
	return string;

} /* NCL_Itoa */

/*
 * 函数名：USART1_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口1，即USART1
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
	{									  
	switch ( *++Data )
	{
		case 'r':							          //回车符
			USART_SendData(USARTx, 0x0d);
			Data ++;
		break;
		
		case 'n':							          //换行符
			USART_SendData(USARTx, 0x0a);	
			Data ++;
		break;
		
		default:
			Data ++;
		break;
	}			 
	}
	else if ( *Data == '%')
	{									  //
	switch ( *++Data )
	{				
		case 's':										  //字符串
			s = va_arg(ap, const char *);
	for ( ; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
		Data++;
		break;
	
	case 'd':										//十进制
	d = va_arg(ap, int);
	itoa(d, buf, 10);
	for (s = buf; *s; s++) 
	{
		USART_SendData(USARTx,*s);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
	Data++;
	break;
		 default:
				Data++;
		    break;
	}		 
	} /* end of else if */
	else USART_SendData(USARTx, *Data++);
	while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

