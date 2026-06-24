#include "stm32f4xx.h"
#include "stdio.h"



int delay_time(int delayTime);


int delay_time(int delayTime)
{

	volatile int i;
for (i = 0; i < delayTime; i++);
	// Just a delay loop
return i;

}


int main(void) {
	RCC->AHB1ENR |= 0x05;
	GPIOA->MODER |= 0x00000400; //Set mode bits output for PA5 green
	GPIOA->MODER |= 0x00001000; //Set mode bits output for PA6 yellow
GPIOA->MODER |= 0x00040000; //Set mode bits output for PA9 red


	GPIOA->PUPDR |= 0x00000001; //Activate pull-up register for PA0
	GPIOA->PUPDR |= 0x00000004; //Activate pull-up register for PA1
	GPIOA->PUPDR |= 0x00010000; //Activate pull-up register for PA8


	GPIOA->MODER &= ~(0x3 << (7 * 2)); // Clear mode bits for PA7
GPIOA->MODER |= (0x1 << (7 * 2)); // Set PA7 as output
GPIOA->OTYPER &= ~(0x1 << 7); // Set PA7 as push-pull
GPIOA->OSPEEDR &= ~(0x3 << (7 * 2)); // Set PA7 to low speed
GPIOA->ODR &= ~(1 << 7); // Ensure buzzer is off initially


	GPIOA->MODER &= ~(0x3 << (4 * 2)); // Set PA4 as input
GPIOA->PUPDR &= ~(0x3 << (4 * 2)); // Clear pull-up/pull-down for PA4
GPIOA->PUPDR |= (0x1 << (4 * 2)); // Enable pull-up for PA4



while(1)
	{

		//check PC13 pressed or not(active-low)
		if ((GPIOA->IDR & (1<<0))==0) //if button PA0 pressed

			{
				GPIOA->ODR |= (1<<5); //Turn ON LED PA5

			}

		else

			{

				GPIOA->ODR &= ~(1<<5); //Turn OFF LED PA5

			}
		if ((GPIOA->IDR & (1<<1))==0) //if button PA1 pressed
		{

			GPIOA->ODR |= (1<<6); //Turn ON LED PA6
}
else
{
			GPIOA->ODR &= ~(1<<6); //Turn OFF LED PA6
}
if (!(GPIOA->IDR & (1 << 4))) //if button PA4 pressed
	{

		GPIOA->ODR ^= (1 << 7); // Turn on buzzer (PA7 HIGH)

		delay_time(1000); //set frequency of buzzer
}
	else
		{

GPIOA->ODR &= ~(1 << 7); // Turn off buzzer (PA7 LOW)
			delay_time(1000); //set frequency of buzzer

		}

	if ((GPIOA->IDR & (1<<8))==0) // if button PA8 pressed
	{

			GPIOA->ODR |= (1<<9); //Turn ON LED PA9
}
else
{
		GPIOA->ODR &= ~(1<<9); //Turn OFF LED PA9
	}
}
} 26