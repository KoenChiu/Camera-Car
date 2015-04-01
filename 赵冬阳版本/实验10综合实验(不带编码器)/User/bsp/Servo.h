#ifndef __SERVO_H__
#define __SERVO_H__
/*						
��ͷ�ļ������ṩ������������һ���� ��ʼ�� ���� ���ڶ����� �ı� �������ĺ���

*/

#define Servo_Port		GPIOA
#define Servo_Pin		GPIO_Pin_8
#define Servo_Clock		RCC_APB2Periph_GPIOA

void Servo_Init(void);
//���ת����
void Change_Direction(uint16_t direction);
void Servo_GPIO_Configration(void);

#endif
