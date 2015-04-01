#include"includes.h"
//�ⲿ�ж�����
void EXTI_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;/*����Ƕ���жϽṹ��*/ 	
  	EXTI_InitTypeDef EXTI_InitStructure;/*�����ж����ýṹ��*/		
	GPIO_InitTypeDef GPIO_InitStructure;/*����ͨ��IO�����ýṹ��*/ 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);/*����GPIO��AFIOʱ��*/
	/*ѡ���ж����ȼ���2��*/
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	    	
	/*�ⲿ�ж�10 */
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	/*��ռ���ȼ� 1*/					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    
	/*�����ȼ�0*/ 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	/*ʹ��*/				 
  	NVIC_Init(&NVIC_InitStructure);	
	 //PC10
   	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource10);/*�ⲿ�ж�����AFIO--ETXI10*/		    
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	/*�ж�ģʽ*/
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;/*�½��ش���*/	 
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;//PC10 				  
  	EXTI_Init(&EXTI_InitStructure);

	 //PC11
	 	/*�ⲿ�ж�10 */
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	/*��ռ���ȼ� 2*/					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    
	/*�����ȼ�0*/ 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	/*ʹ��*/				 
  	NVIC_Init(&NVIC_InitStructure);	

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);/*�ⲿ�ж�����AFIO--ETXI11*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;	//PC11 			 
  	EXTI_Init(&EXTI_InitStructure);	  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	         	 	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   	 		//�ڲ���������
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
