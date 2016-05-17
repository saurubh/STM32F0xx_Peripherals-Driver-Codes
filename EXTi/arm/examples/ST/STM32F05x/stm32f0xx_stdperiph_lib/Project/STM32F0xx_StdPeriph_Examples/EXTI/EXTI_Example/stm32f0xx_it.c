
#include "stm32f0xx_it.h"
#include "stm320518_eval.h"
#include "stm32f0xx.h"
extern GPIO_InitTypeDef   GPIO_InitStructure;

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}
void PendSV_Handler(void)
{
}
void SysTick_Handler(void)
{
}

void EXTI0_1_IRQHandler(void)
{
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
   GPIO_SetBits(GPIOC,GPIO_Pin_0);
  
    /* Clear the EXTI line 0 pending bit */
   EXTI_ClearITPendingBit(EXTI_Line0);
  }
}



/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
