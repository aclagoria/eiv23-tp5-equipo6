# include <soporte_placa.h>

int main(void){
    uint8_t buffer;
    int ang1=90;

    SP_ComSerie_init();
    SP_Timer_init();
    SP_Timer_PWM();
    for (;;)
    {
        // recibir y transmitir lo recibido
        //SP_ComSerie_write(buffer);
        //SP_ComSerie_read(&buffer);
        //for(int j=0;j<60000;++j){ //Retardo por fuerza bruta
        //    for(int volatile i=0;i<(8000000/(1000*13));++i); //Calibro para que sea de 1 milisegundo, Calificar como volatile para que el compilador no lo elimine
        //}
        SP_Timer_setPWM(ang1);
        
    }
    return 0;
    
}







