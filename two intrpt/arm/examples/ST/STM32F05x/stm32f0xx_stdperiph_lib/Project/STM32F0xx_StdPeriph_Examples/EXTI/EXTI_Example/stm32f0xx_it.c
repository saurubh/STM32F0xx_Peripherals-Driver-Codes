
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "stm320518_eval.h"
extern GPIO_InitTypeDef   GPIO_InitStructure;
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 0 to 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
  
     /* Enable GPIOA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    GPIO_SetBits(GPIOC,GPIO_Pin_0);
    /* Clear the EXTI line 0 pending bit */
   // EXTI_ClearITPendingBit(EXTI_Line0);
  }
   if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    GPIO_SetBits(GPIOC,GPIO_Pin_1);
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

/**
  * @brief  This function handles External lines 4 to 15 interrupt request.
  * @param  None
  * @retval None
  */
//void EXTI1_IRQHandler(void)
//{
//  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
//  {
//    /* Toggle LED1 */
//    GPIO_SetBits(GPIOC,GPIO_Pin_1);
//    
//    /* Clear the EXTI line 8 pending bit */
//   EXTI_ClearITPendingBit(EXTI_Line1);
//  }
  
//  if(EXTI_GetITStatus(EXTI_Line9) != RESET)
//  {
//    /* Toggle LED3 */
//    STM_EVAL_LEDToggle(LED3);
//
//    /* Clear the EXTI line 9 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line9);
//  }
//
//  if(EXTI_GetITStatus(EXTI_Line13) != RESET)
//  {
//    /* Toggle LED4 */
//    STM_EVAL_LEDToggle(LED4);
//
//    /* Clear the EXTI line 13 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line13);
//  }
//
//}

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
