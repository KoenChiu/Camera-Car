#include"includes.h"
/*
-----------------------------------------------------------
   �������ƣ�TIM1_config()
   �������ܣ�Channel ͨ�� Cycle ����
   �����βΣ� 
   ����ֵ��
   ˵��:��Ƶ�Ĵ���Խ�٣���ʱ����Խ��������Ҳ�͸��ÿ���
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
	/*��0��ʼ������7199һ������7200��,���Լ�������Ϊ20ms*/
  	TIM_TimeBaseStructure.TIM_Period = 7200-1;//�������Ϊ 65535  �Զ���װ�ؼĴ�������
    /*200��Ƶ*/
  	TIM_TimeBaseStructure.TIM_Prescaler = 200; //Ԥ��Ƶֵ
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//ʱ�ӷָ�
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//������ģʽ TIM���ϼ���ģʽ
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
							   
  	/*
	   ������������TIM1��ͨ������ģʽ
	   �����ö�ʱ����4��ͨ����
	
	*/
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //TIM�����ȵ���ģʽ1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
	 7%��ռ�ձ� ���㷽�� 7/100=x/7200�Ƴ�x=504
	
	*/

  	TIM_OCInitStructure.TIM_Pulse = 504;	/* ���7%��ռ�ձ� ����*/
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//TIM������Ը� 
	//��ʼ��TIM1��ͨ��1��4
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
 	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
  	
	// ʹ������
  	TIM_ARRPreloadConfig(TIM1, ENABLE);	
  	/* TIM1 enable counter */
  	TIM_Cmd(TIM1, ENABLE); 
  	/* ������仰����TIM1��TIM8�Ǳ���ģ�����TIM2-TIM6�򲻱�Ҫ */
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);

}
