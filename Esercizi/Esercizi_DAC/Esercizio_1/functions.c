#include "prototypes.h"
#include "struttura.h"
#include <stdio.h>
#include <math.h>

float mean(const float *const values, unsigned int N){
  
  float media = 0;
      
  for(size_t i = 0; i < N; i++){
    
    media += values[i];   
  }
 
  return (media / N);
  
}

float std_dev(const float *const values, float mean, unsigned int N){
  
  float std_dev = 0;
  float partial = 0;
  
  for(size_t i = 0; i < N; i++){
    
    partial = pow((values[i] - mean), 2);
    std_dev += partial;
  
  }

  return (sqrt(std_dev * 1/N));
  
}

void wait_TIMER3(void){
     
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


void timer3_set(unsigned int arr, unsigned int psc){
  
  TIMER3 -> ARR = arr;                
  TIMER3 -> PSC = psc;       
   
}

void timer3Enable(unsigned int enable){
  
    TIMER3 -> CR1 |= enable;

}  

void timer2_set(unsigned int arr, unsigned int psc){
  
  TIMER2 -> ARR = arr;                
  TIMER2 -> PSC = psc;       
   
}

void timer2Enable(unsigned int enable){
  
    TIMER2 -> CR1 |= enable;

}

void timer1_set(unsigned int arr, unsigned int psc){
  
  TIMER1 -> ARR = arr;                
  TIMER1 -> PSC = psc;       
   
}

void timer1Enable(unsigned int enable){
  
    TIMER1 -> CR1 |= enable;

}  


unsigned int TIMER3_PSC_wait_ms(float delta_t){
  
  const float TCK = 0.000125;
  const unsigned int ARR = 65535;
  float diff_delta_t[2];
  
  unsigned int PSC = (unsigned int) roundf((delta_t / (ARR * TCK)) - 1);
  printf("%u\n", PSC);
  
  diff_delta_t[0] = fabsf((ARR * (PSC + 1) * TCK) - delta_t);
  diff_delta_t[1] = fabsf((ARR * PSC * TCK) - delta_t);
    
  for(size_t i = 0; i < 2; i++){
      
      printf("%f\n", diff_delta_t[i]);
  
  }
    
  
  if(diff_delta_t[0] >= diff_delta_t[1]){
    
    return (PSC + 1);
    
  }
  
  else{
    
    return PSC;
    
  }
  
    
}

void sineWave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size; i++){
    
    vector[i] = (unsigned int) (2047 * sin((2 * 3.14159 / size) * i) + 2048);
    
  }
  
}


void fSineWave(unsigned int *const vector, unsigned int freq, unsigned int size){

   for(unsigned int i = 0; i < size; i++){
    
      vector[i] = (unsigned int) (2047 * sin((2 * freq * 3.14159 / size) * i) + 2048);
    
  }


}


void sine3Wave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size; i++){
    
    vector[i] = (unsigned int) (2047 * sin((6 * 3.14159 / size) * i) + 2048);
    
  }
  
}

void squareWave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size; i++){
      
    if(i < size/2){
    
       vector[i] = 4095;
      
    }
    
    else{
      
       vector[i] = 0;
      
    }
  }      
       
}


void triangularWave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size/4; i++){
    
    vector[i] = 2048 + 81 * i;
    
  }
  
  for(unsigned int i = 0; i < size/2; i++){
    
    vector[i + size/4] = 4095 - 81 * i;
    
  }
  
  for(unsigned int i = 0; i < size/4; i++){
    
    vector[i + 3*size/4] = 81 * i;
    
  }
    
}


void DAC1_set(unsigned int boff1, unsigned int ten1, unsigned int tsel1, unsigned int dmaen1){
  
  DAC1 -> CR |= boff1 << 1;
  DAC1 -> CR |= ten1 << 2;
  DAC1 -> CR |= tsel1 << 3;
  DAC1 -> CR |= dmaen1 << 12; 
  
}

void DAC1_en(unsigned int en1){
  
  DAC1 -> CR |= en1;
  
}

void DAC2_set(unsigned int boff2, unsigned int ten2, unsigned int tsel2, unsigned int dmaen2){
  
  DAC1 -> CR |= boff2 << 1;
  DAC1 -> CR |= ten2 << 2;
  DAC1 -> CR |= tsel2 << 3;
  DAC1 -> CR |= dmaen2 << 12; 
  
}

void DAC2_en(unsigned int en2){
  
  DAC1 -> CR |= en2;
  
}
/*
void DMA1_set(unsigned int cpar, unsigned int cmar, unsigned int cndtr, unsigned int priority){
  
  DMA1 -> CPAR
  
  
}
*/

