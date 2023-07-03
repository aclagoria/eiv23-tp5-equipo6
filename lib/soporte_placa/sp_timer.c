#include <soporte_placa/sp_timer.h>
#include <stm32f1xx.h> 

void SP_Timer_init(void){
    //Enciende el reloj del TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // Configurar los pines del GPIO
}

void SP_Timer_PWM(void){
    // Configura preescaler, periodo, valor inicial del PWM
    // Configurar Modo PW1 en canal 1
    // Habilitar salida del CH1
    // Habilitar temporizador del TIM2
    


}