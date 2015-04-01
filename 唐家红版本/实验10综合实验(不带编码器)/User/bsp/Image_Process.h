#ifndef __IMAGE_PROCESS_H__
#define __IMAGE_PROCESS_H__

#define ThresholdValue 		100	//��ֵ����ֵ 130

#define White				254
#define Black				0
#define STRM  500
#define STRL  330
#define STRR  670


void Image_Process(void);
void Data_Process(void);
void Get_Mid_Line(void);
s8 Abs8(s8 a);
void SmoothMid(void);
void Least_Squares(int start, int end);
void Steer_control(void);
void DisplayBlackLine(void);
s8 Curve(void);
typedef struct
{
	int SP;//Set Point Ŀ��ֵ
	u8 P;//����ϵ��
	u8 I;//����ϵ��
	u8 D;//΢��ϵ��
	s8 CurErr;//��ǰƫ��ֵ
	s8 LastErr;//��һ��ƫ��ֵ
	s8 PreErr;//���ϴ�ƫ��ֵ
}PID_ParameterTypeDef;


extern uint8_t *Data_Point;
extern int time_count;//����

#endif

