#include "timer.h"
#include "usart.h"
#include "My_Usart.h"
TIM_HandleTypeDef TIM3_Handler;
int count=0;

void TIM3_Init(u16 arr,u16 psc)
{ 
 TIM3_Handler.Instance=TIM3; //ͨ�ö�ʱ�� 3
 TIM3_Handler.Init.Prescaler=psc; //��Ƶϵ��
 TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //���ϼ�����
 TIM3_Handler.Init.Period=arr; //�Զ�װ��ֵ
 TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //ʱ�ӷ�Ƶ����
 HAL_TIM_Base_Init(&TIM3_Handler); //��ʼ����ʱ�� 3
 
 HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ�� 3 �Ͷ�ʱ�� 3 �����ж�
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
 __HAL_RCC_TIM3_CLK_ENABLE(); //ʹ�� TIM3 ʱ��
 HAL_NVIC_SetPriority(TIM3_IRQn,1,2); //�����ж����ȼ�����ռ 1�������ȼ� 2
 HAL_NVIC_EnableIRQ(TIM3_IRQn); //���� ITM3 �ж� 
}

void TIM3_IRQHandler(void)
{
	 HAL_TIM_IRQHandler(&TIM3_Handler);

}
struct MyTime
{
	int m;
	int s;

}Time={0,0};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 if(htim==(&TIM3_Handler))
 {	 
	Time.s++;
	 
			
	 printf("\r\n���ϵ� %2d��%2d�� �����¼���%2d��\r\n",Time.m,Time.s,count);
	 
   if(Time.s>=60)
	{
		
		Time.s%=60;	
		Time.m++;
	}		
	 
  }
}


