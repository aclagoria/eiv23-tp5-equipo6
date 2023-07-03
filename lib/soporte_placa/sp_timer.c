#include <soporte_placa/sp_timer.h>
#include <stm32f1xx.h> 

void SP_Timer_init(void){
    //Enciende el reloj del TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
}

void SP_Timer_PWM(void){
    //

}