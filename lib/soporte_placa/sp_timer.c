#include <soporte_placa/sp_timer.h>
#include <stm32f1xx.h> 

void SP_Timer_init(void){
    //Enciende el reloj del TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* Configurar  PA1 (canal 2 de TIM2) como salida
    No se habilita el reloj del GPIOA porque ya lo hace el UART
    *Bits[1:0]: Modo E/S, 10 es modo salida frec máx 2 MHZ
    *Bits[3:2]: Configuración de salida, 10 es salida push pull (función alternativa) 
    */
   GPIOA->CRL = (GPIOA->& ~(0b1111 << GPIO_CRL_MODE1_Pos)) // Lee el registro CRH (de config).1) Puesta a cero
                | (0b1010 << GPIO_CRL_MODE1_Pos);          // 2) BIT SET)

                
}

void SP_Timer_PWM(void){
    // Configura preescaler= 88, periodo=20 [ms], valor inicial del PWM=0,5 [ms] hay 45 pasos 
    TIM2->PSC=88 ;
    TIM2->ARR=1759 ; // 20 [ms] son 1760 pasos
    TIM2->CCR1=44 ;

    // Configurar Modo PW1 en canal 2

    // Habilitar salida del CH2

    // Habilitar temporizador del TIM2
    


}