/*
 * timer3.c
 *
 *  Created on: Apr 4, 2023
 *      Author: ataha
 */

#include "stm32f0xx_hal.h"

void timer3_init(void){
  /************** STEPS TO FOLLOW *****************
  1. Enable Timer clock
  2. Set the prescalar and the ARR
  3. Enable the Timer, and wait for the update Flag to set
  ************************************************/

RCC->APB1ENR |=RCC_APB1ENR_TIM3EN; // enable clock for TIM3
TIM3->PSC=47-1; //Prescalar value
TIM3->ARR=0xffff-1;
TIM3->CR1 |=(1<<0);// enable timer
TIM3->SR |=(1<<0);// UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated

/************** STEPS TO FOLLOW *****************
	1. Enable the GPIOC clock
	2. Configure the Pin as output
************************************************/
RCC->AHBENR |=RCC_AHBENR_GPIOAEN;// Enable GPIOC Clock
GPIOA->MODER |=(1<<10);
GPIOA->MODER &=~(1<<11);
GPIOA->OTYPER &=~(1<<5);
GPIOA->OSPEEDR |=(1<<10);
GPIOA->OSPEEDR &=~(1<<11);
GPIOA->PUPDR &=~(1<<10);
GPIOA->PUPDR &=~(1<<11);
}

void Delay_us(uint16_t us) {
	TIM3->CNT = 0;
	while (TIM3->CNT < us)
		;
}

void Delay_ms(uint16_t ms) {
	for (uint16_t i = 0; i < ms; i++) {
		Delay_us(1000); //delay of ms
	}
}
