#include "stm32f0xx.h"
GPIO_InitTypeDef        GPIO_InitStructure;
/*PB0------RS
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
void clock(void);
void command(uint8_t c);
void init(void);
void display(uint8_t d);
void clock(void)
{uint16_t i;
  for(i=0;i<=10000;i++);

}

void command(uint8_t c)
{
  GPIO_Write(GPIOC, c);
GPIO_ResetBits(GPIOA, GPIO_Pin_0);
GPIO_SetBits(GPIOA, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}
void display(uint8_t d)
{
 GPIO_Write(GPIOC, d);
GPIO_SetBits(GPIOA, GPIO_Pin_0);
GPIO_SetBits(GPIOA, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}


void init(void)
{

   command(0x0038);

   command(0x0006);

   command(0x000c);

   command(0x0001);

   command(0x0080);
  
 }



int main(void)
{
  uint16_t i,j,k;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
uint16_t t,u;
  while (1)
  {
    for(i=0;i<=12;i++)
    {
      for(j=0;j<=59;j++)
      {
        for(k=0;k<=59;k++)
        {
        
        
          
          command(0x0080);
			 for(volatile int r=0;r<3000000;r++);
		 	 t=((i/10)+48);
		 	 u=((i%10)+48);
			display(t);
                        for(volatile int r=0;r<300000;r++);
			display(u);
                        for(volatile int r=0;r<300000;r++);
			display(':');
                       

	command(0x0083);
		 	for(volatile int r=0;r<3000000;r++);
			 t=((j/10)+48);
			 u=((j%10)+48);
			display(t);
                        for(volatile int r=0;r<300000;r++);
			display(u);
                        for(volatile int r=0;r<300000;r++);
                        display(':');
                        
                        
        command(0x0086);
                         for(volatile int r=0;r<3000000;r++);
			t=((k/10)+48);
			u=((k%10)+48);
			display(t);
                        for(volatile int r=0;r<300000;r++);
			display(u);
                        for(volatile int r=0;r<300000;r++);
	
	
//if (j==6);

			break;


        }
      }
    }
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
