#include "stm32f4xx.h"
#include "stdio.h"

// Delay subroutine
int delay_time(int delayTime)
{
    volatile int i;
    for (i = 0; i < delayTime; i++);
    return i;
}

int main(void) {
    RCC->AHB1ENR |= 0x05;  // Enable clock for GPIOA

    // ---- BUZZER CONFIGURATION (PA7) - Contributor: Farah ----
    GPIOA->MODER &= ~(0x3 << (7 * 2)); // Clear mode bits for PA7
    GPIOA->MODER |= (0x1 << (7 * 2));  // Set PA7 as output
    GPIOA->OTYPER &= ~(0x1 << 7);      // Set PA7 as push-pull
    GPIOA->OSPEEDR &= ~(0x3 << (7 * 2)); // Set PA7 to low speed
    GPIOA->ODR &= ~(1 << 7);           // Ensure buzzer is off initially

    // ---- BUTTON PA4 CONFIGURATION (controls buzzer) ----
    GPIOA->MODER &= ~(0x3 << (4 * 2)); // Set PA4 as input
    GPIOA->PUPDR &= ~(0x3 << (4 * 2)); // Clear pull-up/pull-down
    GPIOA->PUPDR |= (0x1 << (4 * 2));  // Enable pull-up for PA4

    while(1)
    {
        if (!(GPIOA->IDR & (1 << 4)))  // If button PA4 pressed
        {
            GPIOA->ODR ^= (1 << 7);    // Toggle buzzer ON
            delay_time(1000);
        }
        else
        {
            GPIOA->ODR &= ~(1 << 7);   // Turn buzzer OFF
            delay_time(1000);
        }
    }
}