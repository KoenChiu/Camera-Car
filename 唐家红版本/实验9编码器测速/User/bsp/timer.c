#include"includes.h"
/*
-----------------------------------------------------------
   �������ƣ�
   �������ܣ�
   �����βΣ�
   ����ֵ����  
-----------------------------------------------------------
*/

void TIM1_config(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 /*��һ������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
	
  	TIM_TimeBaseStructure.TIM_Period = 7200-1;//�������Ϊ 65535
    /*100��Ƶ*/
  	TIM_TimeBaseStructure.TIM_Prescaler = 200-1;
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
							   
  	/*
	   ��������ȷ��ռ�ձȣ�ռ�ձ�����Ϊ7%
	
	*/
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
	 7%��ռ�ձ� ���㷽�� 7/100=x/Cycle_Val�Ƴ�x=56
	
	*/

  	TIM_OCInitStructure.TIM_Pulse = 504;	/* ���7%��ռ�ձ� */
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/*
		ͨ��4 �Ĵ�����ʼ�� ����ӦIO PA11,������IO��ʼ����ʱ��Ҫ��ʼ��PA11
	
	*/
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
//���ڱ�����
void TIM4_Mode_Config(void)
{
	/*��һ�� ������Ӧ�Ľṹ��*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
		
   	/*�ڶ��� ʹ�ܶ�ʱ��4ʱ��*/
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
   	TIM_DeInit(TIM4);
	/*������ ����ʱ���Ĵ���*/
   	TIM_TimeBaseStructure.TIM_Period =0xffff;      
   	TIM_TimeBaseStructure.TIM_Prescaler =0;	    
   	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
   	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/*���Ĳ� ���ö�ʱ������ģʽ*/
	//��������     
	/*TIM_ICPolarity_Rising�����ز���*/                  
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
  	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	/*Reset counter*/
    TIM4->CNT =0;
	/*ʹ�ܶ�ʱ��4*/
	TIM_Cmd(TIM4, ENABLE);   
}
