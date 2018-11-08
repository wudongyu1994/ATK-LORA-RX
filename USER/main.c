#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "lora_app.h"
#include "usart3.h"

/************************************************
�߼�ժҪ
    1.��ʼ��loraģ��
    2.loraģ������
    3.����lora���ݣ�����ʾ�����Զ�

************************************************/
extern u8 ii;
extern u16 jj;
int main(void)
{

//	SystemInit();
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart1_init(115200);
    printf("uart1_init success!\n");
    LED_Init();

    while(LoRa_Init())  //��ʼ��ATK-LORA-01ģ��,����ʼ��ʧ����300ms�����ԣ�ֱ���ɹ�
    {
        printf("LoRa undetected...\n");
        delay_ms(300);
    }
    printf("LoRa detected!\n");
    
    LoRa_Set();     //LoRa����(�������������ô��ڲ�����Ϊ115200)

    printf("start while(1)\n");
	
    while(1)
    {
		printf("USART3_RX_STA=%d\n",USART3_RX_STA);
        if(USART3_RX_STA&0X8000)	
		{
			printf("%s",(const char*)USART3_RX_BUF);
			USART3_RX_STA=0;
		}
        delay_ms(1000);
    }
}
