/*
*
*       Programma per realizzare una sinusoide con frequenza f = 100Hz e numero samples N = 100 mediante utilizzo di TIMER2
*       Essendo f = 100Hz --> DeltaT = T/N = 100 us
*       
*       12/05/2022
*       @Gabriele Felaco 
*/

#include "struttura.h"
#include "prototypes.h"
#include <math.h>
#define SAMPLES 100
#define PI 3.14159

unsigned int vector[SAMPLES] = {0}; //vettore che conterrà i 100 campioni della sinusoide

int main(void){
  
  /*    1. Abilitiamo GPIOA mediante RCC
  *     2. Abilitiamo TIMER2 mediante RCC
  *     3. Carichiamo il valore 800 in ARR tale da avere un DeltaT di 100us
  *     4. Abilitiamo il clock del DAC mediante RCC
  *     5. Utilizziamo DAC1_OUT1 --> PA4 (configurazione PA4 come analogico dal MODER)             
  *     6. Abilitazione del DAC dal registro CR (disabilitando il buffer di uscita)
  */
  
  RCC -> AHBENR |= GPIOAEN;
  RCC -> APB1ENR |= TIMER2EN;
  TIMER2 -> ARR = 800;
  TIMER2 -> CR1 |= 1;
  RCC -> APB1ENR |= DACEN;
  GPIOA -> MODER4 = 3;
  DAC1 -> CR |= EN1 | BOFF1;
 
  /*
  for(unsigned int i = 0; i < SAMPLES; i++){
    
    vector[i] = (unsigned int) (2047 * sin((2 * PI / SAMPLES) * i) + 2048);
    
  }
  */
  
  sineWave(vector, SAMPLES);
    
  while(1){
    
    for(unsigned int i = 0; i < SAMPLES; i++){
      
      DAC1 -> DHR12R1 = vector[i];    
     // wait_us(100);
      
      while((TIMER2 -> SR & UIF) != (1 << 0));
      TIMER2 -> SR &= ~UIF;
      //TIMER2 -> CNT = 0;
    
    }
  }
     
}