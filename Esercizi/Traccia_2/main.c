/*
*       Realizzare un contatore binario con incremento del conteggio ad ogni pressione del tasto user.
*       L’incremento deve avvenire quando viene rilevato il rilascio del tasto user.
*
*       @Gabriele Felaco
*       11/04/2022
*/

#include "struttura.h"

#define GPIOA ((Gpio_type*) 0x48000000)
#define RCC ((RCC_type*) 0x40021000)

static unsigned int cnt = 0;

void main(void){
  
  RCC -> AHBENR |= (1 << 17);
  
  while(1){
    
    /*
    while((GPIOA -> IDR0 & (1 << 0)) == 0);
        
    while((GPIOA -> IDR0 & (1 << 0)) == (1 << 0));
    
    cnt++;
    
    */
    
    if((GPIOA -> IDR0 & (1 << 0)) == (1 << 0)){
      
      while((GPIOA -> IDR0 & (1 << 0)) == (1 << 0));
      
      cnt ++;
    }
    
    
  }
}
  
  
  
