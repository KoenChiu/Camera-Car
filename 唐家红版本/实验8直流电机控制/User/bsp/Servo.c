#include"includes.h"
/*˽�к�����������Щ�����ǲ���ֱ�ӱ��ⲿ���õ�*/

/*
************************************************************************
*  �������ƣ�
*  �������ܣ�
*  �����βΣ�  	
*  ����ֵ��	
*
************************************************************************
*/
void Servo_GPIO_Configration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* �ڶ�������ͨ������������·GPIO��ʱ��  */		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(Servo_Clock , ENABLE);
	/*������ ����Channel ���ò�ͬ�� GPIO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  Servo_Pin;
	GPIO_Init(Servo_Port, &GPIO_InitStructure); 	 //PA8
}
/*
************************************************************************
*  �������ƣ�
*  �������ܣ�
*  �����βΣ�  	
*  ����ֵ��	
*
************************************************************************
*/
void Servo_Init(void)
{
	Servo_GPIO_Configration(); 	
}
/*
************************************************************************
*  �������ƣ�
*  �������ܣ�
*  �����βΣ�  	
*  ����ֵ��	
*
************************************************************************
*/
void Change_Direction(uint16_t direction)
{
		
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);    
	TIM_SetCompare1(TIM1, direction); 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);    

}
