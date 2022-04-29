/*
*
*       Scrivere un programma che esegue 15 misure ripetute della tensione in ingresso su PA0 con un intervallo di 500 ms tra ogni misura. 
*       Calcolare media e deviazione standard. Utilizzare le periferiche ADC1 e TIMER3.
*
*       @Gabriele Felaco
*       29/04/2022
*/


#include "struttura.h"
#include "prototypes.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


unsigned int cnt = 0;
unsigned int data_reg = 0;
float acquisition[15];
float voltage = 0.0;
float media;
float dev_std;


void main(void){
  

  RCC -> AHBENR |= GPIOAEN | ADC12EN;   //abilitazione GPIOA e ADC12
  RCC -> APB1ENR |= TIMER3EN;           //abilitazione TIMER3
  
  GPIOA -> MODER0 = 3;                  //PA0 impostato come analog MODER0 = 11
  
  //TIMER3_set(65535, 61, 1);
  
  ADC1_vreg_en();       
  
  TIMER3_set(65535, TIMER3_PSC_wait_ms(0.01) , 1);

  //wait_us(10);
  
  ADC1_2 -> CCR |= 1 << 16;             //impostazione clock da AHB per ADC1_2
  ADC1 -> DIFSEL &= ~(1 << 1);          //impostazione canale ADC1_IN1 come single-ended
  ADC1 -> CR |= ADC_CAL;                //calibrazione ADC1
  
  while((ADC1 -> CR & ADC_CAL) == ADC_CAL);     //attendo che ADC_CAL passi a 0...fine fase di calibrazione
  
  ADC1 -> CR |= 1;                      //abilitazione ADC1
  
  while(!(ADC1 -> ISR & 1));            //attendoo che il bit ADRDY vada ad 1... adc pronto all'uso
  
  ADC1 -> SQR1 |= 1 << 6;                       //effettuo una sola conversione sul canale 1 di ADC1
  
  ADC1 -> SMPR1 |= 7 << 3;                      //imposto il sampling time del canale 1 di ADC1
  
  TIMER3_set(65535, TIMER3_PSC_wait_ms(500) , 1);

  while(1){
    
    
    while(cnt < 15){
      
      ADC1 -> CR |= 1 << 2;               //setto ad 1 il bit ADSTART
    
      while(!(ADC1 -> ISR & (1 << 2)));   //attendo che EOC si alzi (mi segnala la fine della conversione)      
    
      data_reg = (unsigned int) ADC1 -> DR;
    
      voltage = (float)(data_reg * (3.0/4095));
    
      acquisition[cnt] = voltage;
      cnt++;
    
      printf("%.3f V\n", voltage);
    
      wait_next_acquisition();
    
    }
    
    cnt = 0;
    
  TIMER3_set(65535, TIMER3_PSC_wait_ms(1000) , 1);
  
  media =  mean(acquisition, 15);
  //wait_ms(1000);
  wait_next_acquisition();
  printf("MEAN: %.3f V\n",media);
  //wait_ms(1000);
  wait_next_acquisition();
  dev_std = std_dev(acquisition, media, 15);
  printf("STD_DEV: %.3f V\n", dev_std); 
    
}
}
 
