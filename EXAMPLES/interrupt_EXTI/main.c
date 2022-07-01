/* Interrupt esempio lezione
*
* Bisogna utilizzare la libreria della ST per poter utilizzare gli
* interrupt.
* 
* Ai fini del progetto, la libreria va inclusa nel path del preprocessore
*
* Inoltre bisogna includere due file dalla cartella libreria:
* 
* 1- startup_stm32f30x.s
* 2- system_stm32f30x.c
*
* OSS: Con l'utilizzo di questa libreria il clock e' impostato a 72MHz
* 
* Vogliamo scrivere un programma che effettua il toggle di il led a seguito della pressione del tasto USER (PA0).
*/

#include <stm32f30x.h>

void main(void){
  
//1. Configurare la porta GPIOE e GPIOA
  
  RCC -> AHBENR |= (1 <<21) | (1 << 17);
  GPIOE -> MODER |= 1 << 16;
  
  
//2. Configurare l'interrupt  
  
  //Questa volta bisogna utilizzare i registri relativi alla periferica EXTI. Nel SYSCFG_EXTICR1 vado a selezionare da quale linea voglio
  //che sia generato l'interrrupt.
  
  SYSCFG -> EXTICR[0] &= 0;
  
  //Abilito interrupt da EXTI0
  
  EXTI -> IMR |= 1;
  
  //Bisogna specificare se il fronte di attivazione e' di salita o discesa (registro EXTI_FTSR1 per falling edge mentre EXTI_RTST1 per rising edge)
  
  EXTI ->RTSR |= 1;
     
  //I registri dell'NVIC si trovano nel PROGRAM MANUAL...nel particolare i registri di nostro interesse sono i NVIC_ISERx
  
  NVIC ->ISER[0] |= 1 << 6;  //Abilito interrupt EXTI0 (ha posizione 6 cfr.pag 184 ref manual) lato CPU/NVIC
  
  
  while(1);

}

void EXTI0_IRQHandler(){
  
  //La prima cosa da fare quando si entra nell'ISR e' disabilitare la richiesta di interrupt (servire l'interruzione)
  //Nel nostro caso per la periferica EXTI e' presente un registro EXTI_PR1 (Pending Request) il cui bit relativo alla linea utilizzata va resettato.
  EXTI -> PR |= 1;
  
  GPIOE ->ODR ^= 1 << 8;
  
}//ISR PA0 (EXTI0)

