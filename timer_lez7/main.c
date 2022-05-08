/*
*       Programma che utilizza il TIMER2 per accendere un LD7 -> PE11 con frequenza f = 1Hz
*       LEZ 7 07/04/2022 - utiilizzo timer
*       @Gabriele Felaco
*
*/


#include "struttura.h"

#define GPIOE ((Gpio_type*) 0x48001000)
#define RCC ((RCC_type*) 0x40021000)
#define TIMER2 ((Timer_type*) 0x40000000)
//#define TIMER3 ((Timer_type*) 0x40000400)

void init_timer(Timer_type*, Timer_cfg*);
static Timer_cfg config = {
  .CR1 = 1,
  .ARR = 2000000
};

void main(){

/*
*       Sezione di configurazione delle periferiche
*/
  
  RCC -> AHBENR |= (1 << 21);       //abilitazione GPIOE
  RCC -> APB1ENR |= 1;              //abilitazione TIMER2
  //RCC -> APB1ENR |= (1 << 1);       //abilitazione TIMER3
  GPIOE -> MODER |= (1 << 22);      //PE11 configurato come pin di output
  //GPIOE -> MODER |= (1 << 30);      //PE15 configurato come pin di output
/*
  TIMER2 -> ARR = 8000000;          //ARR impostato a 8M in modo da avere 1 conteggio ogni secondo
  TIMER2 -> CR1 |= 1;               //Counter abilitato
*/
  
  init_timer(TIMER2, &config);
  
  /*
  TIMER3 -> ARR = 4000000;
  TIMER3 -> CR1 |= 1;
  */


/*
*       Sezione di loop
*/  

  
    while(1){
        
      while((TIMER2 -> SR & (1 << 0)) != (1 << 0));     //Aspetto che UIF vada ad 1 ==> il valore del contatore ha raggiunto il valore contenuto in ARR
      TIMER2 -> SR &= ~(1 << 0);                        //Azzero il valore del flag UIF
      GPIOE -> ODR11 = ~ GPIOE -> ODR11;                //toggle del bit 11 dell'ODR del banco GPIOE
      
      /*
      while((TIMER3 -> SR & (1 << 0)) != (1 << 0));     //Aspetto che UIF vada ad 1 ==> il valore del contatore ha raggiunto il valore contenuto in ARR
      TIMER3 -> SR &= ~(1 << 0);                        //Azzero il valore del flag UIF
      GPIOE -> ODR15 = ~ GPIOE -> ODR15;                //toggle del bit 11 dell'ODR del banco GPIOE
      */
      
        
        
      }
     
      
}


void init_timer(Timer_type* to_configure, Timer_cfg* configuration){
  
    to_configure -> CR1 |= configuration -> CR1;
    to_configure -> ARR = configuration -> ARR;
    
    
}