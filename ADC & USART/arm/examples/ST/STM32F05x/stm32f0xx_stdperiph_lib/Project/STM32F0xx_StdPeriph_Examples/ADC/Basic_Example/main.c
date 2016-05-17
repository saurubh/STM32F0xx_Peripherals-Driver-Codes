
#include "main.h"

#define MESSAGE1   "STM32F05x CortexM0  " 
#define MESSAGE2   "   STM320518-EVAL   " 
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
ADC_InitTypeDef     ADC_InitStructure;
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef    GPIO_InitStructure;

int main(void)
{
  
    
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
 
  ADC_DeInit(ADC1);
  
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SampleTime_239_5Cycles);   

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  ADC_Cmd(ADC1, ENABLE);   
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
   ADC_StartOfConversion(ADC1);
   
    USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  

  
  while (1)
  {
    /* Test EOC flag */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    char i;
    /* Get ADC1 converted data */
    ADC1ConvertedValue =ADC_GetConversionValue(ADC1);
   
  STM_EVAL_COMInit(COM1, &USART_InitStructure);
   
  {
    
    i=ADC1ConvertedValue/1000+48;
  while(USART_GetFlagStatus(EVAL_COM1, USART_IT_TXE)!= RESET);
    (USART_SendData(EVAL_COM1,i));
    for (volatile int i=0;i<5000;i++);
     i=(ADC1ConvertedValue%1000)/100+48;
     (USART_SendData(EVAL_COM1,i));
     for (volatile int i=0;i<5000;i++);
    i=((ADC1ConvertedValue%1000)%100)/10+48;
      (USART_SendData(EVAL_COM1,i));
      for (volatile int i=0;i<5000;i++);
    i=(((ADC1ConvertedValue%1000)%100)%10)+48;
    (USART_SendData(EVAL_COM1,i));
    for (volatile int i=0;i<5000000;i++);
  
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
