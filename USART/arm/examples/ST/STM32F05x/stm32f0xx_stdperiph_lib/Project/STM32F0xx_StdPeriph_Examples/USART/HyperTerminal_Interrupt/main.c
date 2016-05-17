#include "main.h"
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef        GPIO_InitStructure;

  unsigned char data1;
 // void receive(void);
 // void trans(void);
  void display(char d);
  void command(char c);
  void clock(void);
  //void lcd_string(unsigned char *str) ;
  void init(void);

 
 /* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
/*
PB0------RS
PB1------EN
PC0------D0
PC1------D1
PC2------D2
PC3------D3
PC4------D4
PC5------D5
PC6------D6
PC7------D7
*/

void clock(void)
{volatile uint16_t i;
  for(i=0;i<=1000;i++);

}

void command(char c)
{
  GPIO_Write(GPIOC, c);
GPIO_ResetBits(GPIOB, GPIO_Pin_0);
GPIO_SetBits(GPIOB, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}
void display(char d)
{
 GPIO_Write(GPIOC, d);
GPIO_SetBits(GPIOB, GPIO_Pin_0);
GPIO_SetBits(GPIOB, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}
void init(void)
{
   command(0x0038);

   command(0x0006);
command(0x0001);
   command(0x000c);

   

   command(0x0080);

   command(0x0080);
} 
int main(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  STM_EVAL_COMInit(COM1, &USART_InitStructure);
  init();  
    while(1)
  {
  while(USART_GetFlagStatus(EVAL_COM1, USART_IT_TXE)== RESET);
    data1= (USART_ReceiveData(EVAL_COM2));
    display(data1);
//clock();
  
  }
  
#ifdef  USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/}




