/*      Esercizio_01_timer
*       
*       Realizzare un contatore che misuri il tempo trascorso tra la pressione e il rilascio del tasto USER. Il contatore deve poter misurare un tempo massimo di 10s.
*       Se il tempo misurato è inferiore a 10s accendere il led PE8, altrimenti il led rosso PE9 non appena si raggiunge il tempo massimo senza che il tasto USER sia stato rilasciato. 
*       Utilizzare solo il TIMER 3. 
*       
*       09/04/2022
*       @Gabriele Felaco
*/


#include "struttura.h"

#define GPIOE ((Gpio_type*) 0x48001000 )
#define GPIOA ((Gpio_type*) 0x48000000 )
#define RCC ((RCC_type*) 0x40021000 )
#define TIMER3 ((Timer_type*) 0x40000400 )

void GpioA_init(Gpio_type*, GpioA_cfg*);
void GpioE_init(Gpio_type*, GpioE_cfg*);
void RCC_init(RCC_type*, RCC_cfg*);
void Timer3_init(Timer_type*, Timer3_cfg*);
unsigned int timer_has_ended(Timer_type*);

//struct di configurazione 

static Timer3_cfg Timer3_config = {
  
  .ARR = 65535,
  .CR1 = 1,
  .PSC = 1220
};

static GpioA_cfg GpioA_config = {
  
  .MODER = 0

};

static GpioE_cfg GpioE_config = {
  
  .MODER = 0x00050000
  
};

static RCC_cfg Rcc_config = {
  
  .AHBENR = 0x00220014,
  .APB1ENR = 2
  
};


void main(void){
  
  
  /*
  *    Sezione configurazione periferiche
  */
  
  RCC_init(RCC, &Rcc_config); 
  GpioA_init(GPIOA, &GpioA_config);
  GpioE_init(GPIOE, &GpioE_config);
  Timer3_init(TIMER3, &Timer3_config);
  
  /*
  *     Sezione di loop
  */
  
  while(1){
    
   
    while(GPIOA -> IDR0 != 1){          //pressione tasto USER --> start counter
    
      TIMER3 -> SR &= ~(1 << 0);        //reset flag UIF finchè il tasto non viene premuto
    }
   
    while(GPIOA -> IDR0 == 1){         //se il pulsante è stato premuto per un tempo >= 10s allora accendi PE9
      
      GPIOE -> ODR9 = timer_has_ended(TIMER3);  
      
    }
   
    GPIOE -> ODR9 = timer_has_ended(TIMER3);    
    GPIOE -> ODR8 = !timer_has_ended(TIMER3);
    
   /*
   if(((TIMER3 -> SR & (1 << 0)) != (1 << 0)) && (GPIOA -> IDR0 == 0)){
     TIMER3 -> SR &= ~(1 << 0);
     GPIOE -> ODR8 = 1;
   }
   
   if(((TIMER3 -> SR & (1 << 0)) == (1 << 0)) && (GPIOA -> IDR0 == 1)){
     TIMER3 -> SR &= ~(1 << 0);
     GPIOE -> ODR9 = 1;
   }
   
   */
  }  

}


unsigned int timer_has_ended(Timer_type* t){    //funzione che ritorna 1 se il timer ha saturato
  
  return((t -> SR & (1 << 0)) == (1 << 0));
  
}

void GpioA_init(Gpio_type* to_config, GpioA_cfg* configuration){
  
  to_config -> MODER |= configuration -> MODER;
  
}

void GpioE_init(Gpio_type* to_config, GpioE_cfg* configuration){
  
  to_config -> MODER |= configuration -> MODER;
  
}

void RCC_init(RCC_type* to_config , RCC_cfg* configuration){
  
  to_config -> AHBENR  |= configuration -> AHBENR;
  to_config -> APB1ENR |=  configuration -> APB1ENR;

}

void Timer3_init(Timer_type* to_config, Timer3_cfg* configuration) {
  
  to_config -> ARR = configuration -> ARR;
  to_config -> CR1 |= configuration -> CR1;
  to_config -> PSC |= configuration -> PSC;
  
}
