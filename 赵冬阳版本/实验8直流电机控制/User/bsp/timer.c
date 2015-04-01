#include"includes.h"
/*
-----------------------------------------------------------
   �������ƣ�void TIM1_config(void)
   �������ܣ�����TIM1ΪPWMģʽ�������ݲ���������ռ�ձ�
   �����βΣ��� 
   ����ֵ����
   ˵��:
-----------------------------------------------------------
*/

void TIM1_config(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 /*��һ������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
	/*
	   �ڶ��������ݷ�Ƶϵ������װ��ֵȷ������  		 
	*/
	/*��0��ʼ������7199һ������7200��,Ԥ��ƵΪ200��ô����=(200/72M)x7200=20MS*/
  	TIM_TimeBaseStructure.TIM_Period = 7200-1;//�������Ϊ 65535
    /*200��Ƶ*/
  	TIM_TimeBaseStructure.TIM_Prescaler = 200;
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
							   
  	/*
	   �����������ö�ʱ������ģʽΪPWM��ģʽ��������ռ�ձ���ֵ
	
	*/
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
	 7%��ռ�ձ� ���㷽�� 7/100=x/7200�Ƴ�x=504
	
	*/	 
  	TIM_OCInitStructure.TIM_Pulse = 504;	/* ���7%��ռ�ձ� */
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/*
	��ʼ��TIM1��ͨ��1��ͨ��4����Ӧ�Ĺܽ����������ֲ�	
	
	*/
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  	
	/*ʹ������*/
  	TIM_ARRPreloadConfig(TIM1, ENABLE);	
  	/* ʹ�ܶ�ʱ��1 */
  	TIM_Cmd(TIM1, ENABLE); 
  	/* ������仰����TIM1��TIM8�Ǳ���ģ�����TIM2-TIM6�򲻱�Ҫ */
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
