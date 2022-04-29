#include "struttura.h"
#include <stdio.h>

unsigned int delta_t = 0xE4A9;          //58537
unsigned int time_step = 0x32D1;        //13009

void main(void){
  
  RCC -> AHBENR |= 1 << 21;
  RCC -> APB1ENR |= 1 | (1 << 1);
  GPIOE -> MODER12 |= 1;        //led PE12 
  
  TIMER2 -> PSC = 0;
  TIMER2 -> ARR = 40000000;
  
  TIMER3 -> PSC = 122;
  TIMER3 -> ARR = 65535;
  
  TIMER2 -> CR1 |= 1; 
  TIMER3 -> CR1 |= 1;
  
  while(1){
    
    TIMER3 -> CNT = 0;
    
    while((TIMER3 -> SR & 1) != 1){
      
      
      while(TIMER3 -> CNT <= delta_t){
      
      GPIOE -> ODR12 = 1;
            
    }
      GPIOE -> ODR12 = 0;

    }
    
    TIMER2 -> CNT = 0;
             
    while((TIMER2 -> SR & 1) != 1);
    
    TIMER3 -> SR &= ~1;
    TIMER2 -> SR &= ~1;
    
    delta_t -= time_step;
    
    if(delta_t == 0x1965){
      
      delta_t = 0xE4A9; 
    }
    
  }



    
    /*
    while((TIMER2 -> SR & 1) != 1);
    TIMER2 -> SR &= ~1;
    GPIOE -> ODR12 = ~GPIOE -> ODR12;
    */
    
  }
