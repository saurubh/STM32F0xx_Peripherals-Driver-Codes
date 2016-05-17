
#include "main.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

#define sEE_WRITE_ADDRESS1        0x00
#define sEE_READ_ADDRESS1         0x00
#define BUFFER_SIZE1             (countof(Tx1Buffer)-1)
#define BUFFER_SIZE2             (countof(Tx2Buffer)-1)
#define sEE_WRITE_ADDRESS2       (sEE_WRITE_ADDRESS1 + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1 + BUFFER_SIZE1)

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t Tx1Buffer[] = "STR";
//uint8_t Tx2Buffer[] = "wxys";

uint8_t Rx1Buffer[BUFFER_SIZE1];//, Rx2Buffer[BUFFER_SIZE2]; 
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile uint16_t NumDataRead = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
uint8_t a[4],b[4];
GPIO_InitTypeDef   GPIO_InitStructure;
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
  
  /* Initialize the I2C EEPROM driver ----------------------------------------*/
  sEE_Init();  

  /* First write in the memory followed by a read of the written data --------*/
  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS1 */
  sEE_WriteBuffer(Tx1Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1); 

  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState();  
  
  /* Set the Number of data to be read */
  NumDataRead = BUFFER_SIZE1;
  
  /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
  sEE_ReadBuffer(Rx1Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 
 a[0]=Rx1Buffer[0];
  /* Second write in the memory followed by a read of the written data -------*/
  /* Write on I2C EEPROM from sEE_WRITE_ADDRESS2 */
  sEE_WriteBuffer(Tx1Buffer, sEE_WRITE_ADDRESS2, BUFFER_SIZE1); 

  /* Wait for EEPROM standby state */
  sEE_WaitEepromStandbyState();  
  
  /* Set the Number of data to be read */
  NumDataRead = BUFFER_SIZE1;  
  
  /* Read from I2C EEPROM from sEE_READ_ADDRESS2 */
  
 
  /* Check if the data written to the memory is read correctly */
  
  /* TransferStatus2 = PASSED, if the transmitted and received data 
     to/from the EEPROM are the same */
  /* TransferStatus2 = FAILED, if the transmitted and received data 
     to/from the EEPROM are different */
  /* Free all used resources */
  sEE_DeInit();

  while (1)
  {
    if(a[0]=='S')
    {
      GPIO_SetBits(GPIOA,GPIO_Pin_8);
      for (unsigned long int i=0;i<100000;i++);
      GPIO_ResetBits(GPIOA,GPIO_Pin_8);
      for (unsigned long int i=0;i<100000;i++);
    }
    else
    {
      GPIO_SetBits(GPIOA,GPIO_Pin_9);
      for (unsigned long int i=0;i<100000;i++);
    }
  }
}

#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Example of timeout situation management.
  * @param  None.
  * @retval None.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Use application may try to recover the communication by resetting I2C
    peripheral (calling the function I2C_SoftwareResetCmd()) then re-start
    the transmission/reception from a previously stored recover point.
    For simplicity reasons, this example only shows a basic way for errors 
    managements which consists of stopping all the process and requiring system
    reset. */
  /* Block communication and all processes */
  while (1)
  {   
  }  
}
#endif 

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
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
