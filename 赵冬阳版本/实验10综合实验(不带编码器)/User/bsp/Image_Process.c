#include"includes.h"  

//����ָ�������
uint8_t *Data_Point;
uint8_t BlackLineData[R]={80};	//��¼�����е��ֵ
uint8_t LastFieldMid1=80;
u8 LastFieldMid2=80;

u8 left[R]={1};	   //��¼��i����ߺ��߽߱�λ��
u8 right[R]={C-1};	  //��¼��i���ұߺ��߽߱�λ��
s8 Err;
s8 Last_Err=0;
s8 Current_Err=0;
u16 Steerangle  = 0;
u16 Current_Direction;
u16 Next_Direction;		   
int time_count=0;//����
int control_count;
PID_ParameterTypeDef PID;
uint8_t y[R]={80};

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
	//�˲�������ֻ�ṩһ���������л��кܶ�����Ż��ĵط��������������δ��룬����Ȥ��ͬѧ�����о�һ��
	for (i=0;i<R;i++)
	{
		
		for(j=1;j<C-1;j++)
		{
			if( PIC[i][j-1]==White && PIC[i][j]==Black && PIC[i][j+1]==White )	 //���˰׺ڰ׵����
			{
				PIC[i][j]=White;
			}
			else if( PIC[i][j-1]==Black && PIC[i][j]==White && PIC[i][j+1]==Black )	//���˺ڰ׺ڵ����
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
˵��:�ó�����һ����ש������������л�����಻����Ҫͬѧ�ʽ�������
-------------------------------------------------------------------
*/

void Image_Process(void)
{	
	int end = R-5;
	int start = end-7;
		
	Data_Point=&PIC[0][0];	
	
	//��ֵ������
	Data_Process();

	//�õ� �м�ֵ
	Get_Mid_Line();
	
	//ƽ������
	SmoothMid();

	//��С���˷���һ��ƽ������
	for (;start>=4;start -= 6, end -= 6)
	{
		Least_Squares(start, end);
	}
	//Least_Squares(4, R-5);
	
	//��ʾ���ĺ���
	//DisplayBlackLine();
}
/*
--------------------------------------------------------------------
  �������ƣ�void Get_Mid_Line(void)
  �������ܣ���ȡ����
  �����βΣ���
  ����ֵ����
--------------------------------------------------------------------
*/	
void Get_Mid_Line(void)
{
	uint8_t i;
	uint8_t pLeft;
	uint8_t pRight;
    //char bMidEnd=0;	
	/*��¼����ͼ��������ߵ�λ�ã���ʼֵΪ80*/
	BlackLineData[R-1]=((LastFieldMid1+LastFieldMid2)/2);
	
	/*�ӵ����ڶ��п�ʼ���㣬һ��40��Ҳ����˵�ӵ�38�п�ʼ����*/
	for (i=R-2;i>3&&C!=1;i--) //������
    { 	
		//����ɨ��
        for(pLeft=BlackLineData[i+1];pLeft>2;pLeft--) //��i+1�е��е�λ�� ѭ��һ�� ����һ�ν���ɨ��
		{
			if(PIC[i][pLeft]==Black)//����� ɨ������������ڵ�,��ô��ֹͣ���е�ɨ��  Ҫ���жϼ�����
			{
				left[i]=pLeft--;//��¼i����߽��λ��
				if(PIC[i][pLeft]==Black) //ȷ����һ��Ҳ�Ǻڵ�
				{
					pLeft=1;//�����˴�ѭ�� ɨ����һ��	
				}
			}
			else
			{
				//���û�м�⵽�ڵ㣬��ô���е��е�λ�ü�Ϊ 1
				left[i]=1;
			}  		 
		} 	
		//����ɨ��
		for (pRight=BlackLineData[i+1];pRight<C-3;pRight++)
        {
        	if (PIC[i][pRight]==Black)	//�ҵ����ұ߽߱�
            {               
                right[i]=pRight++; //��¼i���ұ߽��λ��
				if(PIC[i][pRight]==Black)
				{
					pRight=C-1;//�����˴�ѭ�� ɨ����һ��	
				}
				               
			}
			else
			{
			 	right[i]=C-1;//���û�м�⵽�ұ߽���� ������Ҳû�з��ֺ��ߣ���ô
			}
      	}
       	//���Һ��߽߱�ȷ��֮������е㣬��i�е��е�
		BlackLineData[i]=((left[i]+right[i]))/2;
        //���ұ��߲ɼ���������ʼ�߼������״�С�ģ����� ���ϵĲ��ִ��밲ȫ
	
    }
	
	/*Ӧ��¼ͼ���и����е�ֵ*/
	//LastFieldMid1= BlackLineData[R-5];
    //LastFieldMid2= BlackLineData[R-6];
	LastFieldMid1= BlackLineData[4];
    LastFieldMid2= BlackLineData[5];
	
}
/*
--------------------------------------------------------------------
  �������ƣ�s8 Abs8(s8 a)
  �������ܣ�ȡ����ֵ
  �����βΣ�
  ����ֵ��
--------------------------------------------------------------------
*/	
s8 Abs8(s8 a)
{
	s8 temp;
	temp=a;
	if (temp>=0)
  	{
  	}
  	else
  	{
    	temp=0-temp;
	}
	return temp;
}
/*
--------------------------------------------------------------------
  �������ƣ�SmoothMid()
  �������ܣ�ƽ������
  �����βΣ���
  ����ֵ����
--------------------------------------------------------------------
*/	
void SmoothMid(void)
{
	uint8_t  i;
	uint8_t temp;
	uint8_t temp1;
 	for (i=R-1;i>3;i--) 
	{
		if(BlackLineData[i] != BlackLineData[i-1])
		{
			temp = Abs8(BlackLineData[i-1]-BlackLineData[i]);
		}
		/*else
		{
		 	temp=BlackLineData[i]-BlackLineData[i-1];	
		}*/

		if(BlackLineData[i] != BlackLineData[i+1])
		{
		 	temp1 = Abs8(BlackLineData[i+1]-BlackLineData[i]);
		}
		/*else
		{
		 	temp1=BlackLineData[i]-BlackLineData[i+1];	
		} */

		if (((temp>5)&&(temp1>5)) || ((BlackLineData[i-1]<BlackLineData[i])&&(BlackLineData[i+1]<BlackLineData[i])) || ((BlackLineData[i-1]>BlackLineData[i])&&(BlackLineData[i+1]>BlackLineData[i])))	 //���������5�Ļ����������������е���м�
		{
			BlackLineData[i]=(BlackLineData[i-1]+BlackLineData[i+1])/2;
		}
	}
}
/*
-----------------------------------------------------------------------------
�������ƣ�Curve()
�������ܣ�����ͼ���ϰ벿�ֵ������������̶�
�����βΣ�
����ֵ��PIC�е�4�е�14�����ĺ��ߵ������̶�
˵����ͨ����ֵ����ǰ�б����
-----------------------------------------------------------------------------
*/
s8 Curve(void)
{
	int8_t i;
	s8 sum_BlackLine=0;
	s8 average_BlackLine=0;
	s8 curve_BlackLine=0;
	s8 differ_BlackLine=0;
	for(i=14, sum_BlackLine=0; i>=4; i--)
	{
		sum_BlackLine+=BlackLineData[i];
	}
	average_BlackLine = sum_BlackLine / 10;
	for(i=14, curve_BlackLine=0;i>=14;i--)
	{
		differ_BlackLine= Abs8(BlackLineData[i]-average_BlackLine);
		curve_BlackLine += differ_BlackLine;
	}
	return curve_BlackLine;
}
/*
-----------------------------------------------------------------------------
�������ƣ�Least_Squares()
�������ܣ�����С���˷���һ��ƽ������
�����βΣ�start,end
����ֵ��
˵������BlackLineData[]��start��end������С���˷�ƽ��
-----------------------------------------------------------------------------
*/
void Least_Squares(int start, int end)
{
	uint8_t i=0;
	double A=0, B=0, D=0, F=0, Delta;
	
	
	double a,b;
	int t;

	for (i=end;i>=start;i--)
	{
		//BlackLineData[i]=y[i];
		y[i]=BlackLineData[i];
	}

	
	for (i=start;i<=end;i++)
	{
		A += i*i; //pow(i,2)
		B += i;
 		D += i*y[i];
		F += y[i];
	}
	
	
	t = end-start+1;
	Delta = A*t-B*B;
	a = (D*t-B*F)/Delta;
	b = (A*F-D*B)/Delta;
	
	
	for (i=start;i<=end;i++)
	{
		BlackLineData[i]=(a*i+b);
	}
	
	
	A=0;
	B=0;
	D=0;
	F=0;
	
	//y[]={0};
}
/*
-----------------------------------------------------------------------------
�������ƣ�DisplayBlackLine()
�������ܣ������ĺ��߼���ͼ��PIC��
�����βΣ�
����ֵ��
˵�������ڵ��õ�ʱ�����ĺ��߼���PIC�����۴���ǰ���Ǵ����
-----------------------------------------------------------------------------
*/

void DisplayBlackLine(void)
{
	uint8_t i;
	for (i=R-2;i>3;i--)
	{
		PIC[i][BlackLineData[i]] = Black;
	}
}
				   

/*
-----------------------------------------------------------------------------
	�������ƣ�void Steer_control
	�������ܣ����ƶ��ת��
	�����βΣ���
   	����ֵ����
	˵��������ķ�����ƻ�������PD�����㷨
-----------------------------------------------------------------------------
*/
void  Steer_control(void)
{
	s16 steererr  = 0;
  	PID.CurErr=((BlackLineData[11]+BlackLineData[12]+BlackLineData[13]+BlackLineData[14]+BlackLineData[15])/5)-80;
  	PID.P=6;//����
    PID.I=0;
	PID.D=1;
  	steererr  = PID.P * (PID.CurErr-PID.LastErr)+PID.D * (PID.CurErr-2*PID.LastErr+PID.PreErr);
	//steererr = PID.P * Err;
	// 500+ ��- ������ת��ʱ�� ����500 ��������ת��ʱ��С��500
  	Steerangle  = STRM-steererr;   		
	LED_1(ON);
	LED_2(ON);
	if(Steerangle>STRR)
	{
		Steerangle=600;	
		LED_1(ON);
		LED_2(OFF);
	}
	if(Steerangle<STRL)
	{
		Steerangle=400;//1 ms�ߵ�ƽ
		LED_1(OFF);
		LED_2(ON);
		
	}
	Change_Direction(Steerangle); 
}


