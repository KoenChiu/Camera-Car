#include"includes.h"	
/*���ڼ�¼�������*/
s16 encoder_num;
/*
************************************************************
*�������ƣ�void Encorder_GPIO_Config(void)
*�������ܣ��������ӿڳ�ʼ��
*�����βΣ���
*����ֵ��	 ��
************************************************************
*/
void Encorder_GPIO_Config(void)
{
	/*��һ�� ����GPIO�ṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*�ڶ�ʱ�Ӳ� ʹ������*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
  	/*������ ���ýṹ����� */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*���Ĳ� ���������ʼ������*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
************************************************************
*�������ƣ�void Encoder_Init(void)
*�������ܣ���������ʼ���������ⲿ����
*�����βΣ���
*����ֵ����
************************************************************
*/
void Encoder_Init(void)
{
	TIM4_Mode_Config();
	Encorder_GPIO_Config();
}
