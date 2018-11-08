#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "lora_app.h"
#include "usart3.h"

/************************************************
逻辑摘要
    1.初始化lora模块
    2.lora模块设置
    3.接收lora数据，并显示到电脑端

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

    while(LoRa_Init())  //初始化ATK-LORA-01模块,若初始化失败则300ms后重试，直到成功
    {
        printf("LoRa undetected...\n");
        delay_ms(300);
    }
    printf("LoRa detected!\n");
    
    LoRa_Set();     //LoRa配置(进入配置需设置串口波特率为115200)

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
