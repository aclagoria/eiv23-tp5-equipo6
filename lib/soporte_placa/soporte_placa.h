#ifndef SOPORTE_PLACA_H
#define SOPORTE_PLACA_H

// Espacio de nombres: SP_

#include <soporte_placa/sp_pin.h>
#include <soporte_placa/sp_tiempo.h>
#include<soporte_placa/sp_comSerie.h>
#include<soporte_placa/sp_timer.h>
#include <soporte_placa/sp_comando_scpi.h>

// Declaraciones


/**
 * @brief Inicializa la librería. Es necesario llamar a
 * esta función antes de usar la misma.
 * 
 */
void SP_init(void);


#endif
