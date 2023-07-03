# include <soporte_placa.h>

int main(void){
    uint8_t buffer;
    SP_ComSerie_init();
    for (;;)
    {
        // recibir y transmitir lo recibido
        SP_ComSerie_write(buffer);
        SP_ComSerie_read(&buffer);
    }
    return 0;
    
}
