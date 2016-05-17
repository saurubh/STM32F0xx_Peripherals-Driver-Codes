
#include "main.h"
#define MESSAGE1   "STM32F05x CortexM0  " 
#define MESSAGE2   "   STM320518-EVAL   " 


__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
ADC_InitTypeDef     ADC_InitStructure;
GPIO_InitTypeDef    GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
int main(void)
{
     
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
  ADC_DeInit(ADC1);
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SampleTime_239_5Cycles);   

  /* ADC Calibration */
     USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  ADC_GetCalibrationFactor(ADC1);
  ADC_Cmd(ADC1, ENABLE);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  ADC_StartOfConversion(ADC1);
  uint16_t s;
  while (1)
  {
  
  
  STM_EVAL_COMInit(COM1, &USART_InitStructure);

  {

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
      s=ADC_GetConversionValue(ADC1);
       while(USART_GetFlagStatus(EVAL_COM1, USART_IT_RXNE)== RESET);
       USART_SendData(EVAL_COM1,s);
      

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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/}
