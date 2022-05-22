/*
*       Per la traccia dell'esercizio vedi cartella.
*       
*       21/05/2022
*       @Gabriele Felaco
*/



#include "struttura.h"
#include "prototypes.h"
#define N 200        

unsigned int sine_samples[N] = {0};
unsigned int sine3t_samples[N] = {0};
unsigned int signal[N] = {0};

//RICEVIMENTO SU VALORE Vpp forma d'onda di uscita!

int main(void){

//  sineWave(sine_samples, N);
//  sine3Wave(sine3t_samples, N);
   
  fSineWave(sine_samples, 1, N);
  fSineWave(sine3t_samples, 3, N);
  
  for(unsigned int i = 0; i < N; i++){
    
    signal[i] = (2* sine_samples[i] / 3) + (sine3t_samples[i] / 3);
    
  }
  
   RCC -> AHBENR |= GPIOAEN;
   
   //Configurazione PA4 come analogico dal MODER
   GPIOA -> MODER4 = 3;
   
   //Abilitiamo TIMER1 da RCC
   RCC -> APB2ENR |= TIMER1EN;
   
   //Abilitiamo DAC1 da RCC
   RCC -> APB1ENR |= 1 << 29;
         
   //Configuriamo il TIMER1 affinchè Delta_t = T/N = 33.3 us   
   timer1_set(267, 0); //ARR = 267, PSC = 0
   timer1Enable(1);      
   
   //Configuriamo e abilitiamo il canale 1 del DAC
   DAC1_set(1, 0, 0, 0);
   DAC1_en(1);
  
   
   while(1){
     
      for(unsigned int i = 0; i < N; i++){
      
         DAC1 -> DHR12R1 = signal[i];    
          
         while((TIMER1 -> SR & UIF) != (1 << 0));
         TIMER1 -> SR &= ~UIF;
          
     }
   
    }
     
   
}