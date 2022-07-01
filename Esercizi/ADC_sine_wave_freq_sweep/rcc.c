#include "rcc.h"
#include "struttura.h"

void RCC_GPIOA(unsigned int enable){

    RCC -> AHBENR |= enable << 17;
}

void RCC_GPIOB(unsigned int enable){

    RCC -> AHBENR |= enable << 18;
}

void RCC_GPIOC(unsigned int enable){

    RCC -> AHBENR |= enable << 19;
}

void RCC_GPIOD(unsigned int enable){

    RCC -> AHBENR |= enable << 20;
}

void RCC_GPIOE(unsigned int enable){

    RCC -> AHBENR |= enable << 21;
}

void RCC_GPIOF(unsigned int enable){

    RCC -> AHBENR |= enable << 22;
    
}

void RCC_DMA1(unsigned int enable){

    RCC -> AHBENR |= enable;

}

void RCC_DMA2(unsigned int enable){

    RCC -> AHBENR |= enable << 1;

}

void RCC_ADC12(unsigned int enable){

    RCC -> AHBENR |= enable << 28;

}

void RCC_ADC34(unsigned int enable){

    RCC -> AHBENR |= enable << 29;
    
}
void RCC_TIM1(unsigned int enable){

    RCC -> APB2ENR |= enable << 11;

}

void RCC_TIM2(unsigned int enable){

    RCC -> APB1ENR |= enable;

}

void RCC_TIM3(unsigned int enable){

    RCC -> APB1ENR |= enable << 1;

}