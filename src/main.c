# include <soporte_placa.h>

int main(void){
    uint8_t buffer;
    int ang1=90;

    SP_ComSerie_init();
    SP_Timer_init();
    SP_Timer_PWM();
    SP_Timer_setPWM(90);
    for (;;)
    {
        
    }
    return 0;
    
}







