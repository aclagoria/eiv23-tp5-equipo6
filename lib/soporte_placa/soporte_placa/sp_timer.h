#ifndef SP_TIMER
#define SP_TIMER
#include <stm32f1xx.h> 
#include <stdint.h>

/**
 * @brief Inicializa el TIM2,
 *  Enciende reloj del timer 2, configura pin de GPIOA 
 */

void SP_Timer_init(void);


/**
 * @brief Configura el TIM2 como modulacion de ancho de pulso
 * Configura preescaler, periodo, valor inicial del PWM
 */
void SP_Timer_PWM(void);

/**
 * @brief Configura el valor de carga del PWM
 * 
 * @param angulo Ángulo de posición del servo 
 */
void SP_Timer_setPWM(int angulo);

/**
 * @brief Obtiene la posición del servo
 * 
 * @return int Ángulo
 */
int SP_Timer_getPWM(void);

//void SP_Timer_setCapture();
//void SP_Timer_procesa();
//void SP_Timer_setCaptureEvent();
//void SP_Timer_setCompareEvent();

#endif