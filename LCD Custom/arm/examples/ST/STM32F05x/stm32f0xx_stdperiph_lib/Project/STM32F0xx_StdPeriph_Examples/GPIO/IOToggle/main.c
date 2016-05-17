#include "stm32f0xx.h"

GPIO_InitTypeDef        GPIO_InitStructure;

void display(uint8_t d);
void build(void);
void command(uint8_t c);
void clock(void);
void lcd_string(unsigned char *str) ;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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
 
   void build()
   { 
     command(0x40);       
	display(0x04);    
	display(0x0E);      
	display(0x0E);      
	display(0x0E);      
	display(0x1F);      
	display(0x00);      
	display(0x04); 
        command(0x85);
       
	//display(0x00); 
  
   }


int main(void)
{


 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

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

 
   command(0x0038);

   command(0x0006);

   command(0x000C);

   command(0x0001);

   command(0x0080);
 
   build();  
  while (1)
  {
   

 
//while(1);
  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
