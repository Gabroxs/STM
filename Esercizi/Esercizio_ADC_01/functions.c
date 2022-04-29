#include "prototypes.h"
#include "struttura.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

float mean(float values[], unsigned int N){
  
  float media = 0;
      
  for(size_t i = 0; i < 15; i++){
    
    media += values[i];   
  }
 
  return (media / N);
  
}

float std_dev(float values[], float mean, unsigned int N){
  
  float acc = 0;
  float appoggio = 0;
  
  for(size_t i = 0; i < 15; i++){
    
    appoggio = pow((values[i] - mean), 2);
    acc += appoggio;
  
  }

  return (sqrt(acc * 1/N));
  
}

void wait_next_acquisition(void){
  
   
  while((TIMER3 -> SR & UIF) != (1 << 0));
  TIMER3 -> SR &= ~UIF;
  //TIMER3 -> CNT = 0;
  //printf("Sono in next_acquisition\n");
  
  
}

void wait_us(unsigned int us){
  
  RCC -> APB1ENR |= 1 << 0;
  TIMER2 -> ARR = (unsigned int) (us * 8);
  TIMER2 -> CR1 |= TIMER2EN;
  while((TIMER2 -> SR & UIF) != (1 << 0));
  TIMER2 -> SR &= ~UIF;
  TIMER2 -> CNT = 0;
  RCC -> APB1ENR &= ~(1 << 0);
  TIMER2 -> CR1 &= ~TIMER2EN; 
  
}


void wait_ms(unsigned int ms){
  
  RCC -> APB1ENR |= 1 << 0;
  TIMER2 -> ARR = (unsigned int) (ms * 8000);
  TIMER2 -> CR1 |= TIMER2EN;
  while((TIMER2 -> SR & UIF) != (1 << 0));
  TIMER2 -> SR &= ~UIF;
  TIMER2 -> CNT = 0;
  RCC -> APB1ENR &= ~(1 << 0);
  TIMER2 -> CR1 &= ~TIMER2EN;
    
}


void ADC1_vreg_en(void){
  
  ADC1 -> CR &= ~(1 << 29);             //abilitazione regotalore di tensione ADC1
  ADC1 -> CR |= 1 << 28;
    
}


void TIMER3_set(unsigned int arr, unsigned int psc, _Bool enable){
  
  TIMER3 -> ARR = arr;                //Config TIMER3 tale da avere delta_t = 0,5s
  TIMER3 -> PSC = psc;       
  TIMER3 -> CR1 |= enable;
    
}