#include"includes.h"
/*
-----------------------------------------------------------------------
  �������ƣ�void LED_Init(void)
  �������ܣ���ʼ��LED���ƶ˿�
  �����βΣ���  	
  ����ֵ����	
-----------------------------------------------------------------------
*/
void LED_Init(void)
{
	/*ͨ��GPIO�ṹ������*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*��һ�� ����GPIOʱ��*/
	RCC_APB2PeriphClockCmd(LED_1_Clock,ENABLE);
	RCC_APB2PeriphClockCmd(LED_2_Clock,ENABLE);
	/*�ڶ��� ����GPIO�ṹ�����*/	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;/*�������*/ 	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;/*�����ٶ�*/ 	
	//GPIO_InitStructure.GPIO_Pin=LED_1_Pin;/*LED_1���ƹܽź�����*/  
	GPIO_InitStructure.GPIO_Pin=LED_1_Pin | LED_2_Pin; //�滻�Ͼ�
	
	//GPIO_Init(LED_1_Port,&GPIO_InitStructure);	/*�������ó�ʼ���ܽŷ���*/		
	//GPIO_InitStructure.GPIO_Pin=LED_2_Pin;/*LED_2���ƹܽź�����*/  	
	//GPIO_Init(LED_2_Port,&GPIO_InitStructure);/*�������ó�ʼ���ܽŷ���*/
	GPIO_Init(GPIOB,&GPIO_InitStructure);	//�滻
	LED_1(OFF);
	LED_2(OFF);		
}
