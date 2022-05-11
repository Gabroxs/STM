/*
*       Programma di esempio per settare il PWM.
*
*       Si fa uso del TIM3_CH1 collegato su PC6 (abilitazione alternate functions)
*
*
*/

#include "struttura.h"


int main(void){
  
  //Abilitiamo GPIOC dall'RCC
  RCC -> AHBENR |= GPIOCEN;
    
  //PC6 -> TIM3_CH1 tramite il registro MODER
  GPIOC -> MODER6 |= 2;
  
  //Dobbiamo specificare quale alternate function deve essere collegata a PC6 mediante registro AFRL
  GPIOC -> AFRL |= 2 << 24;
  
  //Abilitiamo il TIMER3 dall'RCC
  RCC -> APB1ENR |= TIMER3EN;
  //Impostiamo ARR = 8000 in modo da avere f = 1kHz
  TIMER3 -> ARR = 8000;
  //Impostiamo il registro CCR1 = 1000 in modo da avere un duty cycle del 12.5% (ARR / CCR1)
  TIMER3 -> CCR1 = 1000; //quando il valore del contatore raggiunge CCR1 si alza un flag interno!
  
  /*La modalita' del PWM di nostro interesse e' la PWM MODE 1 --> scrivere 110 nel registro CCMR1 del timer
    in tale modalita' viene effettuato sempre il confronto tra il valore del registro CNTx e del registro CCRx (l'esito del confronto 
    determina se l'uscita del canale sara' alta o bassa)
  */
  
  //CCMR1 usato per impostare il PWM mode 1
  TIMER3 -> CCMR1 = 6 << 4;     //vedi ref manual per approfondimento
  
  //CCER viene usato per abilitare il canale 1 del PWM in output
  TIMER3 -> CCER |= 1;
  
  //Abilitiamo il contatore del TIMER3 mediante registro CR1
  TIMER3 -> CR1 |= 1;
  
  
  while(1);
  //codice opzionale
  
}