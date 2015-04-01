#include"includes.h"  

//����ָ�������
uint8_t *Data_Point;
uint8_t BlackLineData[R]={80};
uint8_t LastFieldMid1=80;
u8 LastFieldMid2=80;

u8 left[R]={1};
u8 right[R]={C-1};
s8 Err;
s8 Last_Err=0;
s8 Current_Err=0;
u16  Steerangle  = 0;
u16  Current_Direction;
u16 Next_Direction;		   
int time_count=0;//����
int control_count;
/*
-------------------------------------------------------------------
�������ƣ�void Data_Process(void)
�������ܣ��Բɼ�����ͼ�����ݽ��ж�ֵ������(0/1)
�����βΣ���
����ֵ����
-------------------------------------------------------------------
*/
void Data_Process(void)
{
	int i=0;
	int j=0;
	 //��ֵ�� 	
	for (i=0; i<R ;i++)	//��
	{
		for(j=0; j<C ;j++) //��
		{  			
			 if(PIC[i][j]>ThresholdValue)
			 {
			 	PIC[i][j]=White;		
			 }
			 else
			 {
			 	PIC[i][j]=Black;	
			 }
		}  	
	}
	//�˲�
	for (i=0;i<R;i++)
	{
		
		for(j=1;j<C-1;j++)
		{
			if( PIC[i][j-1]==White && PIC[i][j]==Black && PIC[i][j+1]==White )
			{
				PIC[i][j]=White;
			}
			else
		   	if( PIC[i][j-1]==Black && PIC[i][j]==White && PIC[i][j+1]==Black )
			{
				PIC[i][j]=Black;
			}
		}
	}
}

/*
-------------------------------------------------------------------
�������ƣ�void Image_Process(void)
�������ܣ����ⲿ���ã�ͼ�����ֺ���
�����βΣ���
����ֵ����
-------------------------------------------------------------------
*/

void Image_Process(void)
{	
	Data_Point=&PIC[0][0];	
	//��ֵ������
	Data_Process();
	//�õ� �м�ֵ
	Get_Mid_Line();
	//ƽ������
	SmoothMid();
}
/*
-----------------------------------------------------------------------------
����ɨ�衢����ɨ�衢���ұ��߲ɼ���������������

˵���� BlackLineData�������ڼ�¼·�����е�λ��
left ���ڼ�¼��ߺ��߽߱�λ��
Righe ���ڼ�¼�ұ߽߱� ����λ��


-----------------------------------------------------------------------------
*/
void Get_Mid_Line(void)
{
	uint8_t  i;
	uint8_t pLeft;
	uint8_t pRight;
    char bMidEnd=0;	
	/*��¼����ͼ��������ߵ�λ�ã���ʼֵΪ80*/
	BlackLineData[R-1]=LastFieldMid1;
	/*�ӵ����ڶ��п�ʼ���㣬һ��40��Ҳ����˵�ӵ�38�п�ʼ����*/
	for (i=R-2;i>3&&C!=1;i--) //������
    { 	
		//����ɨ��
        for(pLeft=BlackLineData[i+1];pLeft>2;pLeft--) //��i+1�е��е�λ�� ѭ��һ�� ����һ�ν���ɨ��
		{
			if(PIC[i][pLeft]==Black)//����� ɨ������������ڵ�,��ô��ֹͣ���е�ɨ��
			{
				left[i]=pLeft;//���ڵ��λ�ñ�����������
				pLeft=1;//�����˴�ѭ�� ɨ����һ�� 
			}
			else
			{
				//���û�м�⵽�ڵ㣬��ô���е��е�λ�ü�Ϊ 1
				left[i]=1;
			}  		 
		} 	
		//����ɨ��
		for (pRight=BlackLineData[i+1];pRight<C-2;pRight++)
        {
        	if (PIC[i][pRight]==Black)	//�ҵ����ұ߽߱�
            {               
                right[i]=pRight; //��¼i���ұ߽��λ��
				pRight=C-1;//�����˴�ѭ��               
			}
			else
			{
			 	right[i]=C-1;//���û�м�⵽�ұ߽���� ������Ҳû�з��ֺ��ߣ���ô
			}
      	}
       	//���Һ��߽߱�ȷ��֮������е�
		BlackLineData[i]=((left[i]+right[i]))/2;
        //���ұ��߲ɼ���������ʼ�߼������״�С�ģ����� ���ϵĲ��ִ��밲ȫ
		if ((BlackLineData[i]>C-4)||BlackLineData[i]<4)
		{
			bMidEnd=1;
		}
    }
	 LastFieldMid1= BlackLineData[ R-5];
     LastFieldMid2=BlackLineData[ R-6];
}
/*
-----------------------------------------------------------------------------
����ɨ�衢����ɨ�衢���ұ��߲ɼ���������������




-----------------------------------------------------------------------------
*/
s8 Abs8(s8 a)
{
	 s8 temp;
	 temp=a;
	if (temp>0||temp==0)
  	{
  	}
  	else
  	{
    	temp=0-temp;
	}
	return temp;
}
/*
-----------------------------------------------------------------------------
����ɨ�衢����ɨ�衢���ұ��߲ɼ���������������




-----------------------------------------------------------------------------
*/
void SmoothMid(void)
{
	u8  i;
	uint8_t temp;
	uint8_t temp1;
 	for (i=R-3;i>2;i--) 
	{

		 if(BlackLineData[i]<BlackLineData[i-1])
		 {
		 	temp=BlackLineData[i-1]-BlackLineData[i];
		 }
		 else
		 {
		 	temp=BlackLineData[i]-BlackLineData[i-1];	
		 }

		 if(BlackLineData[i]<BlackLineData[i+1])
		 {
		 	temp1=BlackLineData[i+1]-BlackLineData[i];
		 }
		 else
		 {
		 	temp1=BlackLineData[i]-BlackLineData[i+1];	
		 }

		if (temp>5&&temp1>5 )
		{
			BlackLineData[i]=(BlackLineData[i-1]+BlackLineData[i+1] )/2;
		}
	}
}
/*
-----------------------------------------------------------------------------
	�������ƣ�void Steer_control
	�������ܣ����ƶ��ת��
	�����βΣ���
   	����ֵ����
-----------------------------------------------------------------------------
*/
void  Steer_control(void)
{

  	u8 kp,kd,ki;
  	s16 steererr  = 0;
  	Err=((BlackLineData[11]+BlackLineData[12]+BlackLineData[13]+BlackLineData[14]+BlackLineData[15])/5)-80;
  	kp=8;
  	kd=0;
  	ki=0;	   
  	steererr  = kp*Err;
	// 500+ ��- ������ת��ʱ�� ����500 ��������ת��ʱ��С��500
  	Steerangle  = STRM-steererr;   		
	LED_1(ON);
	LED_2(ON);
	if(Steerangle>STRR)
	{
		Steerangle=700;	
		LED_1(ON);
		LED_2(OFF);
	}
	if(Steerangle<STRL)
	{
		Steerangle=330;//1 ms�ߵ�ƽ
		LED_1(OFF);
		LED_2(ON);
		
	}
	Change_Direction(Steerangle); 
}
