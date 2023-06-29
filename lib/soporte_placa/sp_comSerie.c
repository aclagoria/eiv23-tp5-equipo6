#include <soporte_placa/sp_comSerie.h>
#include <stdbool.h>   // bool, true, false
#include <stdint.h>    // uint32_t
#include <stddef.h>    // size_t
#include <stm32f1xx.h> // __WFI

void SP_ComSerie_init(void){
    /* Habilitar reloj de GPIOA y USART1*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    /*Configurar PA9 para Transmisión 
    *Bits[1:0]: Modo E/S, 11 es modo salida frec máx 5o MHZ
    *Bits[3:2]: Configuración de salida, 10 es salida push pull (función alternativa) 
    */
    GPIOA->CRH = (GPIOA->CRH & ~(0b1111 << GPIO_CRH_MODE9_Pos)) // Lee el registro CRH (de config).1) Puesta a cero
                | (0b1011 << GPIO_CRH_MODE9_Pos);               // 2) BIT SET

  
    /*Configurar PA10 para Recepción
    *Bits[1:0]: Modo E/S, 00 es modo entrada
    *Bits[3:2]: Configuración de entrada, 01 es entrada flotante
    */
    GPIOA->CRH = (GPIOA->CRH & ~(0b1111 << GPIO_CRH_MODE10_Pos)) // Lee el registro CRH (de config).1) Puesta a cero
                | (0b0100 << GPIO_CRH_MODE10_Pos);               // 2) BIT SET
    
    SystemCoreClockUpdate(); /* Determina frecuencia de reloj y actualiza SystemCoreClock */

    /*Registro de tasa de baudios*/
    USART1->BRR=(SystemCoreClock+1)/9600;

    /*Registro de control 1*/
    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; // Máscara para habilitar: el usart, el transmisor y el receptor  
}