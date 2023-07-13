#ifndef SP_COMANDO_SCPI
#define SP_COMANDO_SCPI

#include<soporte_placa/sp_comSerie.h>
#include<soporte_placa/sp_timer.h>
#include<stdbool.h>
#include<stdint.h>
#include <string.h>
#include<stdio.h>


void SP_Comando_SCPI_init(void);

void SP_Comando_SCPI_procesa(char caracter);



#endif