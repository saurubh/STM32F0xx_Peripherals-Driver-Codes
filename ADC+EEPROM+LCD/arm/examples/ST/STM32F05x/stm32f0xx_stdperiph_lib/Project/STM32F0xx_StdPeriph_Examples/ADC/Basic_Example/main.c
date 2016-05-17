#include "main.h"
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
ADC_InitTypeDef     ADC_InitStructure;
GPIO_InitTypeDef    GPIO_InitStructure;
  I2C_InitTypeDef  I2C_InitStructure;
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
#define MESSAGE1   "STM32F05x CortexM0  " 
#define MESSAGE2   "   STM320518-EVAL   " 
#define sEE_WRITE_ADDRESS1        0x00
#define sEE_READ_ADDRESS1         0x00
#define BUFFER_SIZE1             (countof(Tx1Buffer)-1)
#define BUFFER_SIZE2             (countof(Tx2Buffer)-1)
#define sEE_WRITE_ADDRESS2       ( sEE_WRITE_ADDRESS1  + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1   + BUFFER_SIZE1)
#define countof(a) (sizeof(a) / sizeof(*(a)))

uint32_t v=0,mv=0;
uint8_t Tx1Buffer[] = "abcd";
uint8_t Tx2Buffer[] = "wxys";
uint8_t Rx1Buffer[BUFFER_SIZE1], Rx2Buffer[BUFFER_SIZE2]; 
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile uint16_t NumDataRead = 0;
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint8_t a[4],b[4];
void Display(uint8_t d);
void command(uint8_t c);
void clock(void);
void sEE_DeInit(void);
void sEE_Init(void);
void clock(void)
{uint16_t i;
  for(i=0;i<=10000;i++);

}
int main(void)
{
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* Configure ADC Channel11 as analog input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

  
    
  ADC_DeInit(ADC1);
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  

  ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SampleTime_239_5Cycles);   
  ADC_GetCalibrationFactor(ADC1);
  ADC_Cmd(ADC1, ENABLE);     
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  ADC_StartOfConversion(ADC1);
 

   command(0x0038);

   command(0x0006);

   command(0x000c);

   command(0x0001);

   command(0x0080);

  sEE_Init();  
  sEE_WriteBuffer(Tx1Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1); 
  sEE_WaitEepromStandbyState();    
  NumDataRead = BUFFER_SIZE1;
  sEE_ReadBuffer(Rx1Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 
  a[0]=Rx1Buffer[0];
  sEE_WriteBuffer(Tx2Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE2); 
  sEE_WaitEepromStandbyState();  
  NumDataRead = BUFFER_SIZE2;  
  sEE_ReadBuffer(Rx2Buffer, sEE_READ_ADDRESS2, (uint16_t *)(&NumDataRead));
  b[0]=Rx2Buffer[3];
  TransferStatus2 = Buffercmp(Tx2Buffer, Rx2Buffer, BUFFER_SIZE2);
  sEE_DeInit();


  while (1)
  {

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    ADC1ConvertedValue =ADC_GetConversionValue(ADC1);
    Display(ADC1ConvertedValue);
    
  }
}


void Display(uint8_t d)
{
  GPIO_Write(GPIOA, d);
GPIO_SetBits(GPIOB, GPIO_Pin_0);
GPIO_SetBits(GPIOB, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOB, GPIO_Pin_1);

  v=(ADC1ConvertedVoltage)/1000;
  mv = (ADC1ConvertedVoltage%1000)/100;
 }
void command(uint8_t c)
{
  GPIO_Write(GPIOA, c);
GPIO_ResetBits(GPIOB, GPIO_Pin_0);
GPIO_SetBits(GPIOB, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
