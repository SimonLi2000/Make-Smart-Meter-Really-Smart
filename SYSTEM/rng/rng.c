#include "rng.h"
#include "delay.h"
#include "sys.h"

//����0 ��ʼ���ɹ�������1��ʼ��ʧ��
u8 RNG_Init(void)    
{
    u16 i;
	  delay_init(168);
    //ʹ��RNGʱ��
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,ENABLE);  //ʹ��RNGʱ�ӣ���AHB2������
    //ʹ��RNG
    RNG_Cmd(ENABLE);//ʹ��RNG
    while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==0){  //�ȴ�DRDY�ȶ����ȶ�֮��Ϊ0������1     
        i++;
        delay_us(100);                
        if(i >= 10000){
            return 1;       //��ʱǿ�Ʒ���
        }         
    }
    return 0;     
}


//��ȡ��ֵ����
u32 RNG_Get_RandomNum(void)
{
    while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==0);   //�ȴ��ȶ�
    return RNG_GetRandomNumber();    //��ȡ��������ֵ
}


//����[min,max]��Χ�����������������������䳤��ȡ�������ټ���min�õ������
int RNG_Get_RandomRange(int min,int max)
{
  return RNG_Get_RandomNum()%(max-min+1)+min;
}

