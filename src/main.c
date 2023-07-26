# include <soporte_placa.h>

int main(void){
    uint8_t buff;
    //char cad="mensaje";
    SP_ComSerie_init();
    SP_Timer_init();
    SP_Timer_PWM();
    //SP_Timer_setPWM(90);
    SP_Comando_SCPI_init();
    for (;;)
    {
      SP_ComSerie_read(& buff);
      SP_ComSerie_write(buff);
      SP_Comando_SCPI_procesa(buff);
    //SP_ComSerie_write_mensaje(&cad);

    }
    return 0;
    
}







