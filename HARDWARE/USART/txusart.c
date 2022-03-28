#include<stm32f10x.h>
#include<txusart.h>

void blueteeth_USART2_Init() //�������ڳ�ʼ��
{
	USART_InitTypeDef USART_InitStructing;
	GPIO_InitTypeDef GPIO_InitStructing;
	NVIC_InitTypeDef NVIC_InitStructing;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructing.GPIO_Mode=GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructing.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructing.GPIO_Pin=GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&GPIO_InitStructing); //PA3->usart2-txd
	
	GPIO_InitStructing.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructing.GPIO_Pin = GPIO_Pin_2;//PA2->usart2-rxd
	
	GPIO_Init(GPIOA,&GPIO_InitStructing);//��ʼ������
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//ʹ��ʱ��
	
	USART_DeInit(USART2);//��λ����2
	
	USART_InitStructing.USART_BaudRate = 115200;
	USART_InitStructing.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructing.USART_Parity = USART_Parity_No;
	USART_InitStructing.USART_StopBits = USART_StopBits_1;
	USART_InitStructing.USART_WordLength = USART_WordLength_8b;
	USART_InitStructing.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructing);//��ʼ������
	
	NVIC_InitStructing.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructing.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructing.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructing.NVIC_IRQChannelSubPriority = 0x04;
	
	NVIC_Init(&NVIC_InitStructing);//�����ж�
	
	USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART2,ENABLE);
	
}



void USART_SendString(USART_TypeDef* USARTx, char *DataString)
{
 int i = 0;
 USART_ClearFlag(USARTx,USART_FLAG_TC);          //�����ַ�ǰ��ձ�־λ������ȱʧ�ַ����ĵ�һ���ַ���
 while(DataString[i] != '\0')            //�ַ���������
 {
  USART_SendData(USARTx,DataString[i]);         //ÿ�η����ַ�����һ���ַ�
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == 0);     //�ȴ����ݷ��ͳɹ�
  USART_ClearFlag(USARTx,USART_FLAG_TC);         //�����ַ�����ձ�־λ
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
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		if((USART2_RX_STA&0x8000)==0)//����δ���
			{
			if(USART2_RX_STA&0x4000)//���յ���0x0d
				{
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);
				if(Res!=0x0a)
				{USART2_RX_STA=0;
				GPIO_ResetBits(GPIOB, GPIO_Pin_5);}//���մ���,���¿�ʼ
				else 
				USART2_RX_STA|=0x8000;
			}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART2_RX_STA|=0x4000;
				else
					{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     }  
		if(USART2_RX_STA&0x8000) //������� 
  {
   len=USART2_RX_STA&0xfff;//�õ��˴ν��յ������ݳ���
   USART2_RX_STA=0; //����ָ������ 
   USART2_RX_BUF[len]=0;//���ջ�������������
	 if(USART2_RX_BUF[len - 1] == 0x30){datasize = 0;}
	 if(USART2_RX_BUF[len - 2] == 0x32){datasize +=20;}
	 USART_SendString(USART2,USART2_RX_BUF);
	}
 
}



