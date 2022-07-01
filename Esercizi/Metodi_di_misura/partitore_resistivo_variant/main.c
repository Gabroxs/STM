/*
*   Programma che esegue la misura di resistenza incognita mediante l'utilizzo di partitore resistivo.
*   Pressione tasto USER --> richiesta di interruzione (IRQ che effettua le misurazioni necessarie)
*   I dati acquisiti dall'ADC vengono salvati in memoria mediante l'utilizzo del DMA.
*   
*   Periferiche in uso: RCC, GPIOA, GPIOB, ADC3_IN1, DMA2 (ADC3 --> channel 5), EXTI (periferica che gestisce gli interrupt esterni)   
*
*/



#include "stm32f30x.h"
#include "struttura.h"

void main(void){
  
  //Abilitazione periferiche mediante RCC
  My_RCC -> AHBENR |= DMA2EN | GPIOAEN | GPIOBEN | ADC34EN;
  
  //Specifichiamo la linea esterna che EXTI0 deve usare per gestire l'interruzione (nel nostro caso PA0)
  My_SYSCFG -> EXTICR1 &= ~7;
  
  //Abilitiamo l'interrupt da EXTI0 (deve essere non mascherato...agiamo su IMR)
  My_EXTI -> IMR1 |= 1; //scriviamo 1 dato che PA0 è la linea interessata (se avessimo settato PA2 avremmo scritto 1 << 2)
  
  //Bisogna specificare se il fronte di attivazione è di salita o discesa (agiamo sul registro FTSRx o RTSRx in dipendeza dalla scelta fatta)
  My_EXTI -> FTSR1 |= 1; //abbiamo scelto falling edge come fronte di attivazione dell'interrupt
  
  //Con queste istruzioni abbiamo attivato l'interrupt lato periferica (EXTI0). Bisogna abilitare l'interrupt lato CPU/NVIC
  NVIC -> ISER[0] |= 1 << 6;   //Scriviamo 1 << 6 siccome EXTI0 ha come posizione nell'NVIC proprio 6!
  
  
    
  
}