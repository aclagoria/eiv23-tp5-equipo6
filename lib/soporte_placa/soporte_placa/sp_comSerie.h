#ifndef SP_COMSERIE
#define SP_COMSERIE

#include <stdbool.h> //bool
#include <stdlib.h>


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
char SP_ComSerie_read(void);

/**
 * @brief escribe lo que el UART transmite
 * 
 * @param escribir 
 */
void SP_ComSerie_write(char buffer_Tx);

bool SP_ComSerie_hayDatoDisponible(void);

bool SP_ComSerie_hayLugarEnElTransmisor(void);


//void SP_ComSerie_procesa(void);
//void SP_ComSerie_set_errorHadler(void);
//void SP_ComSerie_getError(void);
//void SP_ComSerie_setRxEvent(void);
//void SP_ComSerie_setTxEvent(void);
#endif