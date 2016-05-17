/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-May-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef        GPIO_InitStructure;

void display(uint8_t d);

void command(uint8_t c);
void clock(void);
void lcd_string(unsigned char *str) ;

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
{uint16_t i;
  for(i=0;i<=10000;i++);

}

void command(uint8_t c)
{
  GPIO_Write(GPIOC, c);
GPIO_ResetBits(GPIOB, GPIO_Pin_0);
GPIO_SetBits(GPIOB, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}
void display(uint8_t d)
{
 GPIO_Write(GPIOC, d);
GPIO_SetBits(GPIOB, GPIO_Pin_0);
GPIO_SetBits(GPIOB, GPIO_Pin_1);
clock();
GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}

void lcd_string(unsigned char *str)            
{
while(*str!='\0')                               
{
display(*str);                    
str++;
}
}
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
SystemInit();
  /* GPIOC Periph clock enable */
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

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PC10 and PC11 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */

   command(0x0038);

   command(0x0006);

   command(0x000c);

   command(0x0001);

   command(0x0080);
  
  while (1)
  {
     command(0x0080);
   lcd_string("teva");
 

  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
