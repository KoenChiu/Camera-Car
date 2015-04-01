#include"includes.h"

void Application(void)
{  
	while(1)
	{ 	
		Change_Direction(700);
		delay_ms(1000);
		Change_Direction(300);
		delay_ms(1000);
	}	
}

/*
-------------------------------------------------------------------------
*  �������ƣ�
*  �������ܣ�
*  �����βΣ�  	
*  ����ֵ��		 	
---------------------------------------------------------------------------
*/
void Board_Init(void)
{	
	//ϵͳʱ������
	SystemInit();
	//��ʱ������ʼ��		    	
	delay_init(72);
	//��ʱ��1��ʼ��		 
	TIM1_config();
	//�����ʼ��
	Servo_Init(); 
	//��������
	USART_Config();
	//�����ж�����	   
	NVIC_Config();
	//LED��ʼ��	
	LED_Init();
	//������ʼ��				
	KEY_Init();	 	

}
