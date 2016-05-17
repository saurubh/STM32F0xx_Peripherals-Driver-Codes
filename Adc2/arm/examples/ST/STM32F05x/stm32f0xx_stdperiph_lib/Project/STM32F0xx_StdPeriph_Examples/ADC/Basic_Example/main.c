
#include "main.h"
#define MESSAGE1   "STM32F05x CortexM0  " 
#define MESSAGE2   "   STM320518-EVAL   " 

  __IO uint16_t data=0;
uint16_t T,h,t,u;
ADC_InitTypeDef     ADC_InitStructure;
GPIO_InitTypeDef    GPIO_InitStructure;
void display(char d);

void command(char d);
void clock(void);
void lcd_string(unsigned char *str) ;
void Init(void);
int main(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
   
  ADC_DeInit(ADC1);
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_8 , ADC_SampleTime_239_5Cycles);   

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  ADC_Cmd(ADC1, ENABLE);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  ADC_StartOfConversion(ADC1);
  Init();

  while (1)
  {
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    
   data =ADC_GetConversionValue(ADC1);
   
      command(0x0080);
      T=(data/1000)+48;
      data=(data%1000);
      h=(data/100)+48;
      data=(data%100);
      t=(data/10)+48;
      u=(data%10)+48;
      display(T);
      clock();
      display(h);
      clock();
      display(t);
      clock();
      display(u);
      clock();
    
    
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

GPIO_InitTypeDef        GPIO_InitStructure;



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
{
  volatile uint16_t i;
  for(i=0;i<=10000;i++);

}

void command(char d)
{
  GPIO_Write(GPIOC, d);
GPIO_ResetBits(GPIOA, GPIO_Pin_0);
GPIO_SetBits(GPIOA, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}
void display(char d)
{
 GPIO_Write(GPIOC, d);
GPIO_SetBits(GPIOA, GPIO_Pin_0);
GPIO_SetBits(GPIOA, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void lcd_string(unsigned char *str)            
{
while(*str!='\0')                               
{
display(*str);                    
str++;
}
}
void Init(void)
  {


   command(0x0038);

   command(0x0006);

   command(0x000c);

   command(0x0001);

   command(0x0080);
  
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
