#include<stm32f10x.h>
#include<txusart.h>

void blueteeth_USART2_Init() //蓝牙串口初始化
{
	USART_InitTypeDef USART_InitStructing;
	GPIO_InitTypeDef GPIO_InitStructing;
	NVIC_InitTypeDef NVIC_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&GPIO_InitStructing); //PA3->usart2-txd
	
	GPIO_InitStructing.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructing.GPIO_Pin = GPIO_Pin_2;//PA2->usart2-rxd
	
	GPIO_Init(GPIOA,&GPIO_InitStructing);//初始化引脚
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//使能时钟
	
	USART_DeInit(USART2);//复位串口2
	
	USART_InitStructing.USART_BaudRate = 115200;
	USART_InitStructing.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructing.USART_Parity = USART_Parity_No;
	USART_InitStructing.USART_StopBits = USART_StopBits_1;
	USART_InitStructing.USART_WordLength = USART_WordLength_8b;
	USART_InitStructing.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructing);//初始化串口
	
	NVIC_InitStructing.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructing.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructing.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructing.NVIC_IRQChannelSubPriority = 0x04;
	
	NVIC_Init(&NVIC_InitStructing);//输入中断
	
	USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART2,ENABLE);
	
}



void USART_SendString(USART_TypeDef* USARTx, char *DataString)
{
 int i = 0;
 USART_ClearFlag(USARTx,USART_FLAG_TC);          //发送字符前清空标志位（否则缺失字符串的第一个字符）
 while(DataString[i] != '\0')            //字符串结束符
 {
  USART_SendData(USARTx,DataString[i]);         //每次发送字符串的一个字符
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);     //等待数据发送成功
  USART_ClearFlag(USARTx,USART_FLAG_TC);         //发送字符后清空标志位
  i++;
 }
}

u16 USART2_RX_STA = 0; 
char USART2_RX_BUF[USART_REC_LEN];
int datasize = 100;

void USART2_IRQHandler(void)
{
 int Res;
	int len;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		if((USART2_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART2_RX_STA&0x4000)//接收到了0x0d
				{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);
				if(Res!=0x0a)
				{USART2_RX_STA=0;
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);}//接收错误,重新开始
				else 
				USART2_RX_STA|=0x8000;
			}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
					{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     }  
		if(USART2_RX_STA&0x8000) //接收完成 
  {
   len=USART2_RX_STA&0xfff;//得到此次接收到的数据长度
   USART2_RX_STA=0; //接收指数归零 
   USART2_RX_BUF[len]=0;//接收缓存区后面清零
	 if(USART2_RX_BUF[len - 1] == 0x30){datasize = 0;}
	 if(USART2_RX_BUF[len - 2] == 0x32){datasize +=20;}
	 USART_SendString(USART2,USART2_RX_BUF);
	}
 
}



