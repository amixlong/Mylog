#include "My_Usart.h"

//
u8 len;
u8 i;
extern int count;
void ControlLed(void)
{
if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
		
			if(USART_RX_BUF[3]==0x31|USART_RX_BUF[3]==0x32|USART_RX_BUF[3]==0x33)//��������
			{
				count++;
			}
				
			switch(USART_RX_BUF[3])
			{
				case(0x31)://debug��USART_RX_BUF[3],0x31��Ӧ��1��
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);	//PB0��0 
				   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
				   
				break;
				case(0x32)://debug��USART_RX_BUF[3],0x32��Ӧ��2��
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
				
				break;
				case(0x33)://���������������ѭ����6�κ󣬲ſ����������벢�ư�������
					for(i=0;i<6;i++)
				{
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
				   delay_ms(500);
				   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
				   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
				   delay_ms(500);
				}
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
				
					break;
				default:
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
				   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
				break;
			}	
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}
}
	
	



