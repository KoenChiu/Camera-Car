#include"includes.h"  
/*
------------------------------------------------------------------------
�������ƣ�
�������ܣ�
�����βΣ�
����ֵ��
------------------------------------------------------------------------
*/
void Motor_GPIO_Configration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* �ڶ�������ͨ������������·GPIO��ʱ��  */		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(MOTOR_Clock , ENABLE);
	/*������ ����Channel ���ò�ͬ�� GPIO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  MOTOR_Pin;
	GPIO_Init(MOTOR_Port, &GPIO_InitStructure); 	 //PA8

}
/*
------------------------------------------------------------------------
�������ƣ�
�������ܣ�
�����βΣ�
����ֵ��
------------------------------------------------------------------------
*/
void Motor_Init(void)
{
	Motor_GPIO_Configration();
}

/*
------------------------------------------------------------------------
�������ƣ�
�������ܣ�
�����βΣ�
����ֵ��
------------------------------------------------------------------------
*/
void Change_Speed(uint16_t Speed)
{
	
	//TIM1->CCR4=Speed;
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
	TIM_SetCompare4(TIM1, Speed); 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	/*ͨ��4����20ms ռ�ձ�5*/
}
