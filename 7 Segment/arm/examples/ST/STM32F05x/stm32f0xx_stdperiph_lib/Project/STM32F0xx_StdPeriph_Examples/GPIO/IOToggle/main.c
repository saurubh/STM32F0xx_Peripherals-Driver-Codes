#include "stm32f0xx.h"
#define BSRR_VAL 0x0C00
GPIO_InitTypeDef        GPIO_InitStructure;
unsigned int d;
  unsigned int num;
void seg(void);
void seg()
  {
    switch(d)
{
case 0: 
 
    GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5);
    GPIO_ResetBits(GPIOB,GPIO_Pin_6);
     

break;

case 1: 
 
    GPIO_SetBits(GPIOB, GPIO_Pin_1| GPIO_Pin_2);
    GPIO_ResetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_6);
     
break;
case 2: 

    GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_6| GPIO_Pin_3| GPIO_Pin_4); 
    GPIO_ResetBits(GPIOB,GPIO_Pin_2|GPIO_Pin_5);

break;

case 3: 
 
    GPIO_SetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_6);
     
    GPIO_ResetBits(GPIOB, GPIO_Pin_4| GPIO_Pin_5);
break;
case 4: 

    GPIO_SetBits(GPIOB,GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_5|GPIO_Pin_6);
     
    GPIO_ResetBits(GPIOB, GPIO_Pin_0| GPIO_Pin_3| GPIO_Pin_4);
 
    
break;

case 5: 
    
    GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_6| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_5);
    GPIO_ResetBits(GPIOB,GPIO_Pin_1| GPIO_Pin_4);
     
 
break;
case 6: 
 
    GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_6| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5);    
    GPIO_ResetBits(GPIOB,GPIO_Pin_1);
     
    break;

case 7: 
 
    GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_2);
     
    GPIO_ResetBits(GPIOB,  GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_6);
break;
case 8: 
 
    GPIO_SetBits(GPIOB, GPIO_Pin_6|GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5);

break;

case 9: 
 
    GPIO_SetBits(GPIOB,GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_4| GPIO_Pin_5|GPIO_Pin_6);
     
    GPIO_ResetBits(GPIOB, GPIO_Pin_3);
break;
}
    
  }

int main(void)
{
  unsigned int d;
  unsigned int num;
  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
  while (1)
  {
    
	for (int i=0;i<=99;i++)
		{
		for(int j=0;j<10;j++)
			{
			num=4;
			d=num/10;
			num=(num-(d*10));
                        seg();
                        for(volatile int a=0;a<=3000;a++);
   
    
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/}}

