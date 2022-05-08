/*
*       Programma per settare il DAC come generatore di tensione continua
*       LEZ 10
*
*
*/

#include "struttura.h"
#include "prototypes.h"


void main(void){
  
    /*  1. Abilitazione DAC dal registro RCC e abilitazione GPIOA da RCC
    *   2. Impostare PA4 (DAC01) come pin ANALOGICO (previa abilitazione della stessa PORTA)
    *   3. Abilitazione canale DAC1_OUT1 dal registro CR
    *   4. Disabilitare il buffer del canale 1 del DAC dal registro CR (abilitato di default, disabilitare se non necessario)
    *   5. Scrivere la parola che si vuole convertire nel registro DAC_DHR12R1
    */
    
    //1.
    RCC -> APB1ENR |= DACEN;
    RCC -> APB1ENR |= GPIOAEN;  
    
    //2.    
    GPIOA -> MODER4 = 3;
    
    //3 e 4
    DAC1 -> CR |= EN1 | BOFF1;
    
    //5.    
    DAC1 -> DHR12R1 = 1365;
}