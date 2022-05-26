/*
*       Programma di esempio che utilizza DMA e DAC per generare una forma d'onda i cui campione sono memorizzati in un opportuna array.
*       Il flusso dei dati � from memory to peripheral (DMA --> DAC)
*       Supponiamo di generare una sinusoide, un'onda quadra ed una triangolare con f = 100 Hz e N = 100 samples
*       Ad ogni pressione del tasto user, il DAC deve generare un'onda diversa.
*
*
*       @Gabriele Felaco
*/

#include "struttura.h"
#include "prototypes.h"
#define N 100

unsigned int sine_samples[N] = {0};
unsigned int square_samples[N] = {0};
unsigned int triangular_samples[N] = {0};

unsigned int *samplePtr[3];
unsigned int i = 0;

int main(void){
    
   //Generiamo i 100 campioni della sinusoide, onda quadra e triangolare
   sineWave(sine_samples, N);  
   squareWave(square_samples, N); 
   triangularWave(triangular_samples, N);
   
   samplePtr[0] = (unsigned int*)&sine_samples;
   samplePtr[1] = (unsigned int*)&square_samples;
   samplePtr[2] = (unsigned int*)&triangular_samples;
   
   
   //Abilitiamo GPIO4 da RCC
   RCC -> AHBENR |= GPIOAEN;
   
   //Configurazione PA4 come analogico dal MODER
   GPIOA -> MODER4 = 3;
      
   //Abilitiamo TIMER2 da RCC
   RCC -> APB1ENR |= TIMER2EN;
   
   //Abilitiamo TIMER3 da RCC
   RCC -> APB1ENR |= TIMER3EN;
   TIMER3 -> PSC = 60;
   TIMER3 -> ARR = 65535;
   
   //Abilitiamo DAC1 da RCC
   RCC -> APB1ENR |= 1 << 29;
   
   //Abilitiamo DMA2 da RCC
   RCC -> AHBENR |= 1 << 1;
   
   //Configuriamo il TIMER2 affinch� Delta_t = T/N = 100 us   
   TIMER2_set(800, 0); //ARR = 800, PSC = 0
         
   //Settiamo i bit MMS[2:0] di CR2 del TIMER2 a 010 (Update ext trigger)
   TIMER2 -> CR2 |= 2 << 4;
   
   //Configuriamo e abilitiamo il canale 1 del DAC
   DAC1_set(1, 1, 4, 1);
   DAC1_en(1);
   
   //Configuriamo il DMA2 canale 3
   DMA2 -> CPAR3 |= (unsigned int) &DAC1 -> DHR12R1;
   DMA2 -> CMAR3 |= (unsigned int)samplePtr[0];//(unsigned int) &sine_samples;
   DMA2 -> CNDTR3 |= 100;
   //DMA2 -> CCR3 |= 3 << 12;
   //DMA2 -> CCR3 &= ~(1 << 14);
   DMA2 -> CCR3 |= 2 << 10;
   DMA2 -> CCR3 |= 2 << 8;
   DMA2 -> CCR3 |= 1 << 7;
   //DMA2 -> CCR3 &= ~(1 << 6);
   DMA2 -> CCR3 |= 1 << 5;
   DMA2 -> CCR3 |= 1 << 4;
   
   TIMER3 -> CR1 |= 1;
   timer2Enable(1);
   DMA2 -> CCR3 |= 1;
   
   while(1){
     
     while(!(GPIOA -> IDR0));           //attendo che il pulsante user sia premuto
     
     while(!(TIMER3 -> SR & 1));        //Mediante timer3 attendo 500ms tra la pressione del tasto e la successiva istruzione (debouncing)
     TIMER3 -> SR &= ~1;                
     
     DMA2 -> CCR3 &= ~1;                //disabilito il DMA2 al fine di aggiornare CMAR
     
     while(!(TIMER3 -> SR & 1));        //tra la disabilitazione di DMA2 e l'aggiornamento di CMAR attendo altri 500ms
     TIMER3 -> SR &= ~1;
     
     DMA2 -> CMAR3 = (unsigned int)samplePtr[i];        //aggiorno CMAR con il puntatore all'array dei samples che voglio generare
     DMA2 -> CCR3 |= 1;
     i++;
     
     if(i == 3){
       
       i = 0;
     
    }
     

   }
   
}