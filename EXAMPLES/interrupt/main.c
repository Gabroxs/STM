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
* Vogliamo scrivere un programma che effettua il toggle di il led eseguito a seguito di un interrupt generato da TIMER2.
*/

#include <stm32f30x.h>

void main(void){
  
//1. Configurare la porta GPIOE 
  
  RCC -> AHBENR |= 1 <<21;
  GPIOE -> MODER |= 1 << 16;
  
  
//2. Configurare il Timer

  RCC -> APB1ENR |= 1;  //abilito timer2
  TIM2 -> ARR = 72000000; //flash led con T = 1s
  
//3. Configurare l'interrupt  
//Quando il contatore del TIMER2 satura voglio che generi una richiesta di interrupt...In tale richiesta di interrupt verra' effettuato il lampeggio del LED   
//Per fare questo devo andare a vedere come la periferica gestisce gli interrupt (REF MANUAL)... REGISTRO DIER bit UIE (quando il flag UIF si alza, viene generata una richiesta di interrupt da TIM2)
  
  TIM2 -> DIER |= 1;  //Abilito interrupt lato periferica
  
  //OSS: Nel REF MANUAL alla sezione NVIC sono riportate tutte le possibili cause di interrupt con le relative priorita'. Per il TIM2 vediamo che questo genera un interrupt globale, difatti nel registro DIER del TIM2 si vede come questo
  //possa effettivamente generare diverse richieste di interrupt. Per tale motivo la causa che ha generato l'interrupt non puo' essere determinata via HW (dato che la linea e' unica) ma deve essere determinata via SW tramite la relativa ISR.
  
  //I registri dell'NVIC si trovano nel PROGRAM MANUAL...nel particolare i registri di nostro interesse sono i NVIC_ISERx
  
  NVIC ->ISER[0] |= 1 << 28;  //Abilito interrupt TIM2 lato CPU/NVIC
  TIM2 -> CR1 |= 1; //Dopo aver configurato l'interrupt abilitiamo il TIMER2
  
  while(1);

}

void TIM2_IRQHandler(){
  
  //La prima cosa da fare quando si entra nell'ISR e' disabilitare la richiesta di interrupt (servire l'interruzione)
  //Nel nostro caso il bit UIF che ha richiesto l'interruzione dovra' essere resettato.
  
  TIM2 -> SR &= ~1;
  GPIOE ->ODR ^= 1 << 8;
  
}//ISR TIMER2