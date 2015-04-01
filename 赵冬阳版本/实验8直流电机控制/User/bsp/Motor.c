#include"includes.h"  
/*
-----------------------------------------------
�������ƣ�void Motor_GPIO_Configration(void)
�������ܣ����õ�����ƽӿ�Ϊ�������
�����βΣ���
����ֵ����
-----------------------------------------------
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
-----------------------------------------------
�������ƣ������ʼ��
�������ܣ������ṩ�ĺ����ӿ�
�����βΣ���
����ֵ����
-----------------------------------------------
*/
void Motor_Init(void)
{
	Motor_GPIO_Configration();
}

/*
-----------------------------------------------
�������ƣ�void Change_Speed(uint16_t Speed)
�������ܣ��ı�PWM��ռ�ձȴﵽ����ֱ������ٶȵ�Ŀ��
�����βΣ��ٶ�ֵ
����ֵ�� ��
-----------------------------------------------
*/
void Change_Speed(uint16_t Speed)
{ 
	/*��ֹTIM1��ͨ��4�ļ�������*/
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable);
	/*����ռ�ձ���ֵ*/
	TIM_SetCompare4(TIM1, Speed); 
	/*ʹ��TIM1ͨ��4��������*/
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
