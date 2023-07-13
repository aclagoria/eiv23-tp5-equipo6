#ifndef SP_COMSERIE
#define SP_COMSERIE

#include <stdbool.h> //bool
#include <stdlib.h>
#include <stdint.h>    // uint32_t
#include <stddef.h>    // size_t
#include <stm32f1xx.h> //



/**
 * @brief Inicialización del periferico USART 1
 * Configura pines: PA9-> USART1_TX ;  PA10->USART1_RX 
 * Modo: Full Duplex
 * Baudrate: 9600
 * nro de bit de datos:8
 * bit de parada:1
 * sin paridad
 */
void SP_ComSerie_init(void);

/**
 * @brief lee lo que el UART recibe
 * 
 * @param leer 
 */
void SP_ComSerie_read(uint8_t *buffer_Rx);

/**
 * @brief escribe lo que el UART transmite
 * 
 * @param escribir 
 */
void SP_ComSerie_write(uint8_t buffer_Tx);

bool SP_ComSerie_hayDatoDisponible(void);

bool SP_ComSerie_hayLugarEnElTransmisor(void);

void SP_ComSerie_write_mensaje(char *mensaje);

//void SP_ComSerie_procesa(void);
//void SP_ComSerie_set_errorHadler(void);
//void SP_ComSerie_getError(void);
//void SP_ComSerie_setRxEvent(void);
//void SP_ComSerie_setTxEvent(void);
#endif