#ifndef SP_COMSERIE
#define SP_COMSERIE

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Inicialización del periferico USART 1
 * 
 */
void SP_ComSerie_init(void);

/**
 * @brief lee lo que el UART transmite
 * 
 * @return char 
 */
char SP_ComSerie_read(void);

/**
 * @brief escribe lo que el UART recibe
 * 
 * @param caracter 
 * @return true 
 * @return false 
 */
bool SP_ComSerie_write(char caracter);

//void SP_ComSerie_procesa(void);
//void SP_ComSerie_set_errorHadler(void);
//void SP_ComSerie_getError(void);
//void SP_ComSerie_setRxEvent(void);
//void SP_ComSerie_setTxEvent(void);
#endif