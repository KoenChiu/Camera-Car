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
	/*
	   �ڶ��������ݷ�Ƶϵ������װ��ֵȷ��		����
		Ԥ��Ƶ 3600����ô ��ʱ������һ�� ����ʱ��Ϊ
		3600*10^6/(72*10^6)=50us
		���Լǵ�Cycle_Val�ι���Ҫ 50*Cycle_Val us 
	*/
	/*ȷ������1-100ms*/
	/*��0��ʼ������799һ������800��,���Լ�������Ϊ20ms*/
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
																		
 /* -----------------------------------------------------------------------   
	��ʱ��3��ʱ��Դ������ֱ������RCC_APB1������������о�����һ����Ƶ��	

	�������ƣ�void TIM3_config(uint8_t Channel,uint8_t Cycle,uint16_t Duty)
	�������ܣ���ʼ����ʱ����ʹ֮������Ҫ��PWM����												
	�����βΣ�Channel:��ʱ��ͨ���� Cycle����(1-100ms) duty��ռ�ձ�
	����ֵ����													   
  ----------------------------------------------------------------------- */


//���ڱ�����
void TIM4_Mode_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	/*----------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  	/* Configure PB.06,07 as encoder input */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*----------------------------------------------------------------*/	
 
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܣԣɣ�4
   	TIM_DeInit(TIM4);
   	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
   	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
   	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
   	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
   	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
  	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	//Reset counter
    TIM4->CNT =0;
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��3
}
