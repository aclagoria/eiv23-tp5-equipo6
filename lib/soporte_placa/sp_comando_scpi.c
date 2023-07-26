#include <soporte_placa/sp_comando_scpi.h>
#include<soporte_placa/sp_comSerie.h>
#include<ctype.h>

static const char * cmd_scpi="ANG";

typedef enum estado{
    INICIO,
    COINCIDE,
    PREGUNTAR,
    ESTABLECER,
    INVALIDO
}estado;

typedef struct comando{
estado est_cmd;
unsigned coincidente; // uso para ver si coincide con "ANG"
int potencia;          
int ang;
}comando;

static comando cmd;

static bool coincide_cmd(char c){
    unsigned const i = cmd.coincidente;
    bool e = false;
    if(cmd_scpi[i] != 0){ // '\0' final del char
        if(toupper(c)== cmd_scpi[i]){
            cmd.coincidente++;
            e = true;
        }
    }
    
    return e;
}

static bool coincide_preguntar(char c){
	bool e = false;
    if( c == '?' ){
        e = true;
    }
    return e;
}

static bool coincide_establecer(char c){
    bool e = false;
    if(isblank(c)){
        e = true;
    }
    return e;
}

 static bool coincide_digito(char c){
    bool e = false;
 
    if(isdigit(c)){
            e = true;
            int digito = (int)c - 48;
            cmd.ang = cmd.ang * 10 + digito;
           
    }
    return e;
 }


void SP_Comando_SCPI_init(void){
    cmd.est_cmd= INICIO;
    cmd.coincidente=0;
    cmd.potencia=1;
    cmd.ang=0;
}

void SP_Comando_SCPI_procesa(char caracter){
    switch (cmd.est_cmd){
        case INICIO:
            if(caracter=='\n' || caracter=='\r' || caracter==' '){
                cmd.est_cmd=INICIO;
            }else{
                if(coincide_cmd(caracter)){
                    cmd.est_cmd=COINCIDE;
                }
                else{
                    cmd.est_cmd=INVALIDO;
                }
            }       
        break; case COINCIDE:
            if(coincide_cmd(caracter)){
                cmd.est_cmd=COINCIDE;
            }else{
                if (coincide_preguntar(caracter)){
                cmd.est_cmd=PREGUNTAR;
                }else{
                    if (coincide_establecer(caracter)){
                    cmd.est_cmd=ESTABLECER;
                    }else{
                    cmd.est_cmd=INVALIDO;
                    }
                }
            }    
        break; case PREGUNTAR:
        if(caracter==' ' || caracter=='\r'){
            cmd.est_cmd=PREGUNTAR;
        }else{
            if(caracter=='\n'){
                /*funcion preguntar (get)*/
                //printf("preguntar");
                int ang=SP_Timer_getPWM();
                SP_ComSerie_write_mensaje("El ángulo del servomotor está en: ");
                SP_ComSerie_write_numero(ang);
                SP_ComSerie_write_mensaje(" grados.");
                SP_ComSerie_write('\n');
                cmd.est_cmd= INICIO;
                SP_Comando_SCPI_init();
            }else{
                cmd.est_cmd= INVALIDO;
            }
        }
        break; case ESTABLECER:
            if(caracter==' ' || caracter=='\r'){
	            cmd.est_cmd=ESTABLECER;
            }else{
                	if(coincide_digito(caracter)){
					cmd.est_cmd=ESTABLECER;
				}else{
                    if(caracter=='\n'){
                        int ang = cmd.ang;
                        if((ang >= 0) && (ang <= 180)){/*numero entre 0 y 180 */
                        /*establecer*/
                        /*mandar a inicio*/
                        
                        SP_Timer_setPWM(ang);
                        SP_ComSerie_write_mensaje("Se estableció el ángulo del servomotor en: ");
                        SP_ComSerie_write_numero(ang);
                        SP_ComSerie_write_mensaje(" grados.");
                        SP_ComSerie_write('\n');
                        SP_Comando_SCPI_init();
                        }else{
                            if(ang > 180){
                            /*mandar a inicio*/
                            /*msj de angulo superior*/
                            //SP_ComSerie_write_mensaje("ANGULO SUPERIOR");
                            SP_ComSerie_write_mensaje("ERROR: Ángulo inválido. El valor debe ser entre 0 y 180 grados.");
                            SP_ComSerie_write('\n');
                            SP_Comando_SCPI_init();
                            }else{
                            cmd.est_cmd=INVALIDO;
                            }
                        }
                    }else {
                        cmd.est_cmd=INVALIDO;
                    }
                }
            }
        break; case INVALIDO:
            if(caracter=='\n'){
                /*MANDAR MSJ DE INVALIDO*/
                SP_ComSerie_write_mensaje("ERROR: Comando inválido.");
                cmd.est_cmd=INICIO;
                SP_Comando_SCPI_init();
                SP_ComSerie_write('\n');
            }else{
				cmd.est_cmd=INVALIDO;
			}   
        break;default:
            cmd.est_cmd= INVALIDO;       
    }
} 