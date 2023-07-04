#include <soporte_placa/sp_timer.h>
#include <stm32f1xx.h> 

void SP_Timer_init(void){
    //Enciende el reloj del TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    //reset del TIM2
    RCC->APB1RSTR = RCC_APB1RSTR_TIM2RST;
    RCC->APB1RSTR = 0;    

    /* Configurar  PA0 (canal 1 de TIM2) como salida
    Primero habilita el reloj del GPIOA 
    *Bits[1:0]: Modo E/S, 10 es modo salida frec máx 2 MHZ
    *Bits[3:2]: Configuración de salida, 10 es salida push pull (función alternativa) 
    */
   RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
   GPIOA->CRL = (GPIOA->CRL & ~(0b1111 << GPIO_CRL_MODE0_Pos)) // Lee el registro CRH (de config).1) Puesta a cero
                | (0b1010 << GPIO_CRL_MODE0_Pos);          // 2) BIT SET)
}

void SP_Timer_PWM(void){
    // Configura preescaler= 88, periodo=20 [ms], valor inicial del PWM=0,5 [ms] hay 45 pasos 
    TIM2->PSC=88 ;
    TIM2->ARR=1760 ; // 20 [ms] son 1760 pasos
    TIM2->CCR1=45 ;

    // Configurar Modo PW1 en canal 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

    // Habilitar salida del CH1
    TIM2->CCER |= TIM_CCER_CC1E;

    // Habilitar temporizador del TIM2
    TIM2->CR1 |= TIM_CR1_CEN;
    
}