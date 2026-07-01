#include "stm32f4xx.h"

int main(void) {
    RCC->AHB1ENR |= 0x05;  // Enable clock for GPIOA

    // ---- GREEN LED CONFIGURATION (PA5) - Contributor: izzatul najwa ----
    GPIOA->MODER |= 0x00000400;  // Set PA5 as output

    // ---- BUTTON PA0 CONFIGURATION (controls green LED) ----
    GPIOA->PUPDR |= 0x00000001;  // Enable pull-up for PA0

    while(1)
    {
        if ((GPIOA->IDR & (1<<0))==0)  // If button PA0 pressed
        {
            GPIOA->ODR |= (1<<5);      // Turn ON green LED
        }
        else
        {
            GPIOA->ODR &= ~(1<<5);     // Turn OFF green LED
        }
    }
}