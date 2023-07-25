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
int indice;           //indice del num debe comenzar en 1
char num[4];          // char[4]=char de 3 componentes "xxx"
}comando;

static comando cmd;

static bool coincide_cmd(char c){
    unsigned const i = cmd.coincidente;
    bool e = false;
    if(cmd_scpi[i] != '\0'){ // '\0' final del char
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
	int i = cmd.indice;  
    if(isdigit(c)){
        if(cmd.indice < 4){
            cmd.num[i]=c;
            cmd.indice++;
            e = true;
        }
    }
    return e;
 }

static int numeroDelComando(comando comando){ 
    int num=0;
    char n = comando.num;
    
    num=atoi(n);
    return num; 
}

void SP_Comando_SCPI_init(void){
    cmd.est_cmd= INICIO;
    cmd.coincidente=0;
    cmd.indice=1;
    for (int i = 1; i < 4 ; i++){
     cmd.num[i]='0';
    }
}

void SP_Comando_SCPI_procesa(char caracter){
    switch (cmd.est_cmd){
        case INICIO:
            if(caracter==('\n'||'\r'||'\0')){
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
        if(caracter==('\0' || '\r')){
            cmd.est_cmd=PREGUNTAR;
        }else{
            if(caracter=='\n'){
                /*funcion preguntar (get)*/
                //printf("preguntar");
                int ang=SP_Timer_getPWM();
                SP_ComSerie_write_mensaje("Preguntar");
                cmd.est_cmd= INICIO;
                SP_Comando_SCPI_init();
            }else{
                cmd.est_cmd= INVALIDO;
            }
        }
        break; case ESTABLECER:
            if(caracter==('\0' || '\r')){
	            cmd.est_cmd=ESTABLECER;
            }else{
                	if(coincide_digito(caracter)){
					cmd.est_cmd=ESTABLECER;
				}else{
                    if(caracter=='\n'){
                        if((numeroDelComando(cmd)>=0)&&(numeroDelComando(cmd)<=180)){/*numero entre 0 y 180 */
                        /*establecer*/
                        /*mandar a inicio*/
                        int ang=numeroDelComando(cmd);
                        SP_Timer_setPWM(ang);
                        SP_ComSerie_write_mensaje("Establecer");
                        SP_Comando_SCPI_init();
                        }else{
                            if(numeroDelComando(cmd)>180){
                            /*mandar a inicio*/
                            /*msj de angulo superior*/
                            SP_ComSerie_write_mensaje("ANGULO SUPERIOR");
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
                SP_ComSerie_write_mensaje("INVALIDO");
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