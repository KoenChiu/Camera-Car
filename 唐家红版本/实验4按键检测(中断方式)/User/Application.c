#include"includes.h"
/*
************************************************************************
*  函数名称：void Application(void)
*  函数功能：应用函数接口
*  输入形参：无  	
*  返回值：无	
************************************************************************
*/
void Application(void)
{
	while(1)
	{
		
	}
}

/*
************************************************************************
*  函数名称：void Board_Init(void)
*  函数功能：底层硬件初始化
*  输入形参：无  	
*  返回值：无	
************************************************************************
*/
void Board_Init(void)
{
	/*系统时钟初始化 */
	SystemInit();
	/*LED初始化函数*/
	LED_Init();
	/*外部中断初始化*/
	EXTI_Config();	
}
