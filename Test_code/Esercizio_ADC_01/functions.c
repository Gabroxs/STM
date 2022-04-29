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
  
  float std_dev = 0;
  float partial = 0;
  
  for(size_t i = 0; i < 15; i++){
    
    partial = pow((values[i] - mean), 2);
    std_dev += partial;
  
  }

  return (sqrt(std_dev * 1/N));
  
}

void wait_next_acquisition(void){
     
  while((TIMER3 -> SR & UIF) != (1 << 0));
  TIMER3 -> SR &= ~UIF;
   
  
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
  
  TIMER3 -> ARR = arr;                
  TIMER3 -> PSC = psc;       
  TIMER3 -> CR1 |= enable;
    
}


unsigned int TIMER3_PSC_wait_ms(float delta_t){
  
  //const float TCK = 0.000125;
  const unsigned int ARR = 65535;
  float diff_delta_t[2] = {0.0};
  
  unsigned int PSC = (unsigned int) roundf((delta_t / ((float)(ARR) * TCK_MS)) - 1);
  printf("%u\n", PSC);
  
  diff_delta_t[0] = fabsf((ARR * ((float)(PSC) + 1) * TCK_MS) - delta_t);
  diff_delta_t[1] = fabsf((ARR * (float)(PSC) * TCK_MS) - delta_t);
    
  for(size_t i = 0; i < 2; i++){
      
      printf("%f\n", diff_delta_t[i]);
  
  }
    
  
  if(diff_delta_t[0] >= diff_delta_t[1]){
    
    return PSC;
    
  }
  
  else{
    
    return PSC + 1;
    
  }
  
  return 0;
  
}
