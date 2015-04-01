
#include <stm32f10x.h>
#include <stdio.h>
#include <usart.h>
#include <Nvic_Exit.h>
#include <delay.h>
#include <tft.h>
#include <ov7670.h>
#include<I2C.h>
#include "stm32f10x_tim.h"
#include "include.h"
#include "Image.h"

#define YUANBAN

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void EXIT_configuration();
void IO_Init(void);	
void Timer3_configuration();
void Timer1_configuration();

//void delay_ms(u16 nms);	
extern u8 KEY;


u16 PixelCounter;   //�������ؼ���
u8 datareadyflag;

u8 data[R][C];
u8 * Data;
u8 deadline=0;

//#define   White   244
//#define   Black   0

u8 InterruptLine=0;
u8 TrueLine;
u8 DataReadyFlag=0;


u8 BlackLineData[R];
u8 Left[R]={1};
u8 Right[R]={C-1};
//uchar Mid[R]={R/2};

u8 LastFieldMid1=80;
u8 LastFieldMid2=80;

u8 ThresholdValue=130;
s16 Err = 0;
s16 Errlast   = 0;
s16 Errwhy = 0;
s16 Errd  = 0;
s16 Errdlast  = 0;
s16 Erri  = 0;
s16 Roadtype  = 0;
s16 Errhistory[8]={0};
u16  Steerangle  = 0;

const u16 SlampeLine[R]=     //�����У�У׼�������
  {
     57,//107.5
     59,//104
     60,//100.5
     62,//97
     64,//93.5
     66,//90
     68,//86.5
     70,//83
     72,//79.5
     74,//76
     75,//72.5
     76, //69
     78,//65.5
     83,//62
     88,//58.5
     91,//55
     95,//51.5
     99,//48
     103,//44.5
     108,//41
     113,//37.5
    
	
     118,//34
     123,//30.5
     129,//27
     135,//23.5cm
     141,//20cm
     148,//16.5cm
	 155,
     163,//13cm
	 171
     
  };






int main()
{ 
	RCC_Configuration();;//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��

	IO_Init(); 
 	GPIO_Configuration();
	NVIC_Configuration();
	USART_Configuration();

	Timer3_configuration();
  	//Timer1_configuration();	
	EXIT_configuration();

   
	CMOS1_PWDN=0;
	CMOS1_RST=0;
	delay_ms(20);
	CMOS1_RST=1;
	InitI2C0();	 
	while(1!=Cmos7670_init());   //CMOS��ʼ��	
	Exit_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_IPU, EXTI_Trigger_Falling, 2, 5);	//VSYNC

   delay_ms(1000);
   TIM3->CCR1 = 530;
   GPIO_WriteBit( GPIOB,GPIO_Pin_0, 1);
   GPIO_WriteBit( GPIOB,GPIO_Pin_1, 1);
   delay_ms(1000);
   delay_ms(1000);
   delay_ms(1000);
   delay_ms(1000);
      
   	
   SpeedContiol(560);
  
  	while(1) 
	{
	
		    static int w=0; 
			static int z=0;
		//static int =0;
		
		if (datareadyflag==1)//10���൱��20��
		{
		/*	q++;
			if(q==1)
			{   GPIO_WriteBit( GPIOB,GPIO_Pin_1, 1);
			}
			if(q==2)
				{   GPIO_WriteBit( GPIOB,GPIO_Pin_1, 0);q=0;
			}*/
				
			 EXTI->IMR &=~(1<<0);  //�����ж�           
			 EXTI->PR |=(1<<0);  //������ұ��λ��
			 datareadyflag=0;
			//-----------------------------------------------------------------------
			DataAnalyse(1);
			mygetLmr();
			SmoothMid() ;
			Steer_control();
			
			 if(Err<15&&Err>-15)					//���
			 {
				 w=0;
				 z++;
				 if(z<=4)
				 SpeedContiol(541);    // ��Χ 400~600֮�䣬Խ��Խ��
				 if(z>4)
				SpeedContiol(546);
			 }
			  if(Err>15||Err<-15)				//S��
			  {
				  w++;
				  z=0;
				  if(w<=3)
				  SpeedContiol(537); 
				  if(w>3)
				  SpeedContiol(547);	
			  }
			  

			//-----------------------------------------------------------------------
			 EXTI->IMR|=(1<<0);	  //�����ⲿ�жϣ��Ա������֡ͼ������
			   
		}			
	}
}


 
void RCC_Configuration(void)
{
   SystemInit();
   // Enable GPIO clock 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                          |RCC_APB2Periph_GPIOB
                          |RCC_APB2Periph_GPIOC
                          |RCC_APB2Periph_AFIO
                          |RCC_APB2Periph_TIM1                            
                          |RCC_APB2Periph_USART1,ENABLE);
  
   // Enable USART2 Clock 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2
                         
                          |RCC_APB1Periph_TIM3,ENABLE);
 
}
void IO_Init(void)
{

  	RCC->APB2ENR|=1<<0;//��������ʱ��
	RCC->APB2ENR|=1<<2;//��ʹ������PORTAʱ��
	RCC->APB2ENR|=1<<3;//��ʹ������PORTBʱ��
 	RCC->APB2ENR|=1<<4;//��ʹ������PORTCʱ��


	GPIOC->CRL=0X88888888; //PORTC ����	   //����ͷ ��λ����
	GPIOC->CRH=0X33333333; 
	GPIOC->ODR=0XFFFF;	


	GPIOA->CRH=0X33333333; //PORTA�������	   //����ͷ���
	GPIOA->CRL=0X33333333;
	GPIOA->ODR=0XFFFF;	 

	GPIOB->CRL=0X33333333; //PB0-7   �������
	GPIOB->CRH=0X33333333; //PB8-15  �������
	GPIOA->ODR=0XFFFF;



		    
   	JTAG_Set(JTAG_SWD_DISABLE);	 //JTAG���ܽ�ֹ������JTAG�˿�
}


//����ԭ������
void GPIO_Configuration(void)
{

GPIO_InitTypeDef GPIO_InitStructure;

 //****** TIM3 CH1  ch2 (PA6   pa7) ******************************
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  //******** �ⲿ�ж� GPIO ��ʼ�� ***************
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_4;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;       //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

 

    /* ����USART1��Tx�ţ�PA.9��Ϊ�ڶ������������ģʽ */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
    /* ����USART1��Rx�ţ�PA.10��Ϊ��������� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA , &GPIO_InitStructure);


}



/*******************************************************************************
* ������  		: USART_Configuration	     ����ԭ������
* ��������    	: ����USART1
* �������      : None
* ������      : None
* ����ֵ        : None
*******************************************************************************/
void USART_Configuration(void)
{
    /* ����USART��ʼ���ṹ�� USART_InitStructure */
    USART_InitTypeDef USART_InitStructure;
    
    /*	
    *	������Ϊ9600bps
    *	8λ���ݳ���
    *	1��ֹͣλ����У��
    *	����Ӳ��������
    *	��ֹUSARTʱ��
    *	ʱ�Ӽ��Ե�
    *	�ڵ�2�����ز�������
    *	���һλ���ݵ�ʱ�����岻�� SCLK ���
    */ 
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1 , &USART_InitStructure);
    
    /* ʹ��USART1 */
    USART_Cmd(USART1 , ENABLE);
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;//�ж�Ĭ�ϲ���

  // Configure the NVIC Preemption Priority Bits
                                         

  //********** �ⲿ�ж� (PA0 PA4)****************************************
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;             //�����¼�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //��Ӧ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
  NVIC_Init(&NVIC_InitStructure);
  
 
}
void EXIT_configuration()
{

  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_ClearITPendingBit(EXTI_Line0);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line0; 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_Line0);
 

}

//timer1 ��ͨ��1  ����������pwm pa8

void Timer1_configuration()
{
  //TIM_DeInit(TIM1);
  TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

  TIM1_TimeBaseStructure.TIM_Period = 7200-1;                              // 0xFFFF; ������ֵ         !@#$%^&*()~
  TIM1_TimeBaseStructure.TIM_Prescaler = 200;                          //0xF;   ��Ƶ
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //TIM1_TimeBaseStructure.TIM1_RepetitionCounter= 1000-1;        //���������ڼ�����ֵ;RCR���¼�����ÿ�μ�����0������� !@#$%^&*()~
                                                            //һ�������¼��Ҽ�����������RCRֵ��N����ʼ����������???
  TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseStructure);             // ��������ʱ��Ƶ��72MHz,����=72M/(36000-1+1)/1000

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 540;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OC1Init(TIM1,&TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);                           //!@#$%^&*()~
  TIM_ARRPreloadConfig(TIM1, ENABLE);                                         //!@#$%^&*()~
  TIM_Cmd(TIM1,ENABLE);
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

//********************* ��� PWM ******************
void Timer3_configuration()
{
  //TIM_DeInit(TIM1);
  TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  TIM1_TimeBaseStructure.TIM_Period = 7200-1;                              // 0xFFFF; ������ֵ         !@#$%^&*()~
  TIM1_TimeBaseStructure.TIM_Prescaler = 200;                          //0xF;   ��Ƶ
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                                                              //һ�������¼��Ҽ�����������RCRֵ��N����ʼ����������???
  TIM_TimeBaseInit(TIM3, &TIM1_TimeBaseStructure);                      // ��������ʱ��Ƶ��36MHz,����=36M/(36000-1+1)/1000
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 504;                                    //��������504   504/7119=7%,�Ƕ���м�λ��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3,&TIM_OCInitStructure);                     
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM3,&TIM_OCInitStructure);                     
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //!@#$%^&*()~
  TIM_Cmd(TIM3,ENABLE);
  
  TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //!@#$%^&*()~
  TIM_Cmd(TIM3,ENABLE);

}



