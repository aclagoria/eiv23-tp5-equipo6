# include <soporte_placa.h>

int main(void){
    SP_ComSerie_init();
    for (;;)
    {
        // recibir y transmitir lo recibido
        SP_ComSerie_write(00001111);
        SP_ComSerie_read();

    }
    return 0;
    
}
