/*
*       Realizzare un contatore binario che si incrementa periodicamente ogni 1,2 s. 
*       Utilizzare il TIM3 per la base dei tempi del contatore. Utilizzare la massima risoluzione possibile.
*       Utilizzare il registro BSRR per accendere e spegnere i led.
*
*       @Gabriele Felaco
*       12/04/2022
*/


#include "struttura.h"
#define GPIOE ((Gpio_type*) 0x48001000)
#define RCC ((RCC_type *) 0x40021000)
#define TIMER3 ((Timer_type *) 0x40000400)

static unsigned int cnt = 0;

void main(void){
  
  /*
  *     Sezione configurazione periferiche
  */
  
  RCC -> AHBENR |= 1 << 21;             //abilito GPIOE
  RCC -> APB1ENR |= 1 << 1;             //abilito TIMER3
  GPIOE -> MODER |=  0x55550000;        //setto PE8 -- PE15 come output
  
  TIMER3 -> CR1 |= 1;                   
  TIMER3 -> PSC = 146;                  //Configurazione TIMER3
  TIMER3 -> ARR = 65535;                
  
  while(1){
   /* 
    if(cnt == 8 && ((TIMER3 -> SR & 1) == 1)){
    
      cnt = 0;
      GPIOE -> BSRR |= 0xFF000000;  
      
    }
     */   
    while((TIMER3 -> SR & 1) == 1){             //mentre il flag UIF è 1
    /*
    if((TIMER3 -> SR & 1) == 1){
      
      GPIOE -> BSRR |= (1 << (cnt + 8));
      cnt++;
    }
    */
    
    if(cnt == 8){
      
      TIMER3 -> SR &= 0;
      cnt = 0;
      GPIOE -> BSRR |= 0xFF000000;  
      
    }  
    
    else{
      
      TIMER3 -> SR &= 0;
      GPIOE -> BSRR |= (1 << (cnt + 8));
      cnt++;  
      
    }     
  
  }
}

}