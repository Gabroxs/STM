/*
*   Programma per la misura di resistenza incognita mediante partitore resistivo.
*   Valori di resistenze note: 100k, 10k, 1k, 100 [ohm]
*   
*   Periferiche in uso: AC3_IN1, GPIOB, RCC, TIM3       
*
*   
*/

#include "struttura.h"
#include <stdio.h>

float vx[4] = {0.0};
float Rs[4] = {100000.0, 10500.0, 1000.0, 100.0};
float vmax = 0.0;
float Rx = 0.0;
float R = 0.0;

void main(void){
  
  //Configurazione periferiche
  
  //1. Abilitare le periferiche tramite RCC
  RCC -> AHBENR |= (1 << 18) | (1 << 29);
  RCC -> APB1ENR |= 1 << 1;
  
  //2. Configurare le varie porte di GPIO
  GPIOB -> MODER1 = 3;  //canale ADC3_IN1
  GPIOB -> MODER0 = 1;
  GPIOB -> MODER2 = 1;
  GPIOB -> MODER10 = 1;
  GPIOB -> MODER12 = 1;
    
  //3. Configurare TIM3 per avere DeltaT = 10us
  TIMER3 -> ARR = 80; 
  
  //4. Configurazione ADC3
  TIMER3 -> CR1 |= 1;
  ADC3_4 -> CCR |= 1 << 16;
  ADC3 -> CR &= ~(1 << 29);
  ADC3 -> CR |= 1 << 28;
    
  while(!(TIMER3 -> SR & 1));   //ADCVREG enabling sequence
  TIMER3 -> SR &= ~1;
  TIMER3 -> CR1 &= ~1;
  
  if(!(ADC3 -> CR & 1)){        //Calibratiion procedure...Assicurarsi che ADEN = 0 prima di iniziare la calibrazione
    
    ADC3 -> DIFSEL &= ~(1 << 1);
    ADC3 -> CR |= (unsigned int) 1 << 31;
    while((ADC3 -> CR & (unsigned int)(1 << 31)) == (unsigned int)(1 << 31));                //Calibration is running
  
  }//End of calibration procedure

  ADC3 -> SQR1 |= 1 << 6;       //Acquisizione singola su ADC3_ch1
  ADC3 -> SMPR1 |= 7 << 3;      //Sampling time massimo
  
  ADC3 -> CR |= 1;                //ADEN = 1
  while(!(ADC3 -> ISR & 1));     //Attendo che ADRDY vada ad 1
  ADC3 -> CFGR &= ~(1 << 13);   //CONT = 0 --> single conversion mode
  
  
  while(1){
    
   for(unsigned int i = 0; i < 4; i++){
    
    switch(i){
      
    case 0:     //Rs = 100kohm PB0 configurato come output digitale mentre gli altri pin come OpenDrain
      
      GPIOB -> OTYPER |= (1 << 2) | (1 << 10) | (1 << 12);
      GPIOB -> OTYPER &= ~1;
      
      GPIOB -> ODR0 = 1;
      GPIOB -> ODR2 = 1;
      GPIOB -> ODR10 = 1;
      GPIOB -> ODR12 = 1;
      
      ADC3 -> CR |= 1 << 2;
      while(!(ADC3 -> ISR & (1 << 2)));
      ADC3 -> ISR &= ~(1 << 2);
      vx[i] = (float) ((ADC3 -> DR) * (3.0/4095.0));
      
      break;
      
      
    case 1:     //Rs = 10kohm PB2 configurato come output digitale mentre gli altri pin come OpenDrain
      
      GPIOB -> OTYPER |= 1 | (1 << 10) | (1 << 12);
      GPIOB -> OTYPER &= ~(1 << 2);
      
      GPIOB -> ODR0 = 1;
      GPIOB -> ODR2 = 1;
      GPIOB -> ODR10 = 1;
      GPIOB -> ODR12 = 1;
      
      ADC3 -> CR |= 1 << 2;
      while(!(ADC3 -> ISR & (1 << 2)));
      ADC3 -> ISR &= ~(1 << 2);
      vx[i] = (float) ((ADC3 -> DR) * (3.0/4095.0));
      
      break;
      
    case 2:     //Rs = 1kohm PB10 configurato come output digitale mentre gli altri pin come OpenDrain
      
      GPIOB -> OTYPER |= 1 | (1 << 2) | (1 << 12);
      GPIOB -> OTYPER &= ~(1 << 10);
      
      GPIOB -> ODR0 = 1;
      GPIOB -> ODR2 = 1;
      GPIOB -> ODR10 = 1;
      GPIOB -> ODR12 = 1;
      
      ADC3 -> CR |= 1 << 2;
      while(!(ADC3 -> ISR & (1 << 2)));
      ADC3 -> ISR &= ~(1 << 2);
      vx[i] = (float) ((ADC3 -> DR) * (3.0/4095.0));
      
      break;
      
    case 3:     //Rs = 100 ohm PB12 configurato come output digitale mentre gli altri pin come OpenDrain
      
      GPIOB -> OTYPER |= 1 | (1 << 2) | (1 << 10);
      GPIOB -> OTYPER &= ~(1 << 12);
      
      GPIOB -> ODR0 = 1;
      GPIOB -> ODR2 = 1;
      GPIOB -> ODR10 = 1;
      GPIOB -> ODR12 = 1;
      
      ADC3 -> CR |= 1 << 2;
      while(!(ADC3 -> ISR & (1 << 2)));
      ADC3 -> ISR &= ~(1 << 2);
      vx[i] = (float) ((ADC3 -> DR) * (3.0/4095.0));
      
      break;
            
      
          }
    
      }

   for (unsigned int j = 0; j < 4; j++){
     
      if(vx[j] > (3.0/10.0)){
        
        vmax = vx[j];
        R = Rs[j];
        break;
        }
     
   }
   
   Rx = (vmax * R)/(3.0 - vmax);
   
 }
       
}
   
 
 