/*      Programma di prova accensione led LD7 (PE11) e LD10 (PE13) / e i led LD3 (PE9) e LD6 (PE15) mediante utilizzo di direttive preprocessore e operatori di shift/bitwise
*       Quando il bottone USER non è premuto i led (LD3 e LD6) devono rimanere spenti, non appena viene premuto devono accendersi contemporaneamente i led LD7 e LD10.
*
*       Gabriele Felaco
*       18/03/2022
*/

#define RCC_AHBENR  0x40021014  //reset value 0x00000014
#define GPIOA_MODER 0x48000000  //reset value 0xA8000000
#define GPIOE_MODER 0x48001000  //reset value 0x00000000
#define GPIOA_IDR   0x48000010  //reset value 0x0000XXXX
#define GPIOE_ODR   0x48001014  //reset value 0x00000000

static unsigned int *p; //puntatore per accedere ai registri interni del MCU

void main(void){
  
p = (unsigned int *) RCC_AHBENR;
*p |= (1 << 17);                        //clock abilitato su port A
*p |= (1 << 21);                        //clock abilitato su port E
  
p = (unsigned int *) GPIOA_MODER;  
*p |= 0; //solo a scopo didattico !

p = (unsigned int *) GPIOE_MODER;
*p |= (1 << 22);        // PE11 output
*p |= (1 << 26);        // PE13 output 
*p |= (1 << 18);        // PE9 output
*p |= (1 << 30);        // PE15 output

while(1){
  
     p = (unsigned int *) GPIOA_IDR;   
  
     if((*p & (1 << 0)) == 0){
        
        p = (unsigned int *) GPIOE_ODR;
        *p &= ~(1 << 15);
        *p &= ~(1 << 9);
        *p |= (1 << 11);
        *p |= (1 << 13);
}

     else{
        
        p = (unsigned int *) GPIOE_ODR;
        *p &= ~(1 << 11);
        *p &= ~(1 << 13);
        *p |= (1 << 9);
        *p |= (1 << 15);
    
}

}

}