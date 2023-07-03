#ifndef SP_TIMER
#define SP_TIMER
#include <stm32f1xx.h> 
#include <stdint.h>

/**
 * @brief inicializa el TIM2
 */

void SP_Timer_init(void);

//void SP_Timer_procesa();
//void SP_Timer_setCompare();
//void SP_Timer_setCapture();

/**
 * @brief Configura el TIM2 como modulacion de ancho de pulso
 */
void SP_Timer_PWM(void);

//void SP_Timer_setCaptureEvent();
//void SP_Timer_setCompareEvent();

#endif