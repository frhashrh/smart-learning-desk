#include "stm32f4xx.h"

int main(void) {
    RCC->AHB1ENR |= 0x05;  // Enable clock for GPIOA

    // ---- YELLOW LED CONFIGURATION (PA6) - Contributor: aisyah sofea ----
    GPIOA->MODER |= 0x00001000;  // Set PA6 as output

    // ---- BUTTON PA1 CONFIGURATION (controls yellow LED) ----
    GPIOA->PUPDR |= 0x00000004;  // Enable pull-up for PA1

    while(1)
    {
        if ((GPIOA->IDR & (1<<1))==0)  // If button PA1 pressed
        {
            GPIOA->ODR |= (1<<6);      // Turn ON yellow LED
        }
        else
        {
            GPIOA->ODR &= ~(1<<6);     // Turn OFF yellow LED
        }
    }
}