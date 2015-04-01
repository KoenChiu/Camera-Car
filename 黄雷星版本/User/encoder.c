/********************************************************************************
  ���ֵ�ʵ����                        
  *******************************************************************************/
#include "encoder.h"
//volatile s16 encoder_num;
// void TIM2_Mode_Config(void)
// {
//   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ�ܣԣɣͣ�
//   TIM_TimeBaseStructure.TIM_Period =5000;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
//   TIM_TimeBaseStructure.TIM_Prescaler =7200-1;	    //����Ԥ��Ƶ��
//   TIM_TimeBaseStructure.TIM_ClockDivision =0 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
// 	/*��ʼ��TIM2��ʱ�� */
//   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
// 	/* ʹ��TIM2�ж� */
// 	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
// 	/* ʹ��TIM2��ʱ�� */
// 	TIM_Cmd(TIM2, ENABLE);
// }

void TIM3_Mode_Config(void)
{
	//u16 CCR1_Val = 2500;
	//u16 CCR2_Val = 1000;
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	

	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܣԣɣͣ�
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM2��ʱ�� */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM3->CNT =0;
	
	
	TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ��3
}
void TIM_Init(void)
{
  TIM3_Mode_Config();
}


void TIM4_Mode_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	

	
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܣԣɣ�4
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM2��ʱ�� */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI1, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
 // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM4->CNT =0;
	
	
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��4
}
void TIM4_Init(void)
{
  TIM4_Mode_Config();
}

