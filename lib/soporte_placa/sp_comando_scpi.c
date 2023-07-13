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
unsigned coincidente;
int una_vez;
int indice;
char num[4];
}comando;

static comando cmd;

static bool coincide_cmd(char c){
    unsigned const i = cmd.coincidente;
    if(cmd_scpi[i] != 0){
        if(toupper(c)== cmd_scpi[i]){
            cmd.coincidente++;
            return true;
        }
    }
    return false;
}

static bool coincide_preguntar(char c){
    int una_vez=cmd.una_vez;
    if( c == '?' ){
        if(una_vez==0){
            cmd.una_vez++;
            return true;
        }
        else{return false;}
    }
    else{
        if(c == (' ' || '\n' || '\r')){
            return true;
        }
    return false;
    }
}

static bool coincide_establecer(char c){
    int una_vez=cmd.una_vez;
    if( isblank(c) ){
        if(una_vez==0){
            cmd.una_vez++;
            return true;
        }
        else{return false;}
    }
    else{
        if(isdigit(c)){
            if(cmd.indice != 3){
                int j=cmd.indice;
                cmd.num[j]=c;
                cmd.indice++;
                return true;
            }else{return false;}
        }
        else{
            if(c == (' ' || '\n' || '\r')){
            return true;
            }
            else{return false;}
        }
    }
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
    cmd.una_vez=0;
    cmd.indice=0;
    for (int i = 1; i < 4 ; i++){
     cmd.num[i]='0';
    }
}

void SP_Comando_SCPI_procesa(char caracter){
        switch (cmd.est_cmd)
    {
        case INICIO: /*  */
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
            if (coincide_preguntar(caracter)){
                cmd.est_cmd=PREGUNTAR;
            }else{
                if (coincide_establecer(caracter)){
                cmd.est_cmd=ESTABLECER;
                }
                else{
                    cmd.est_cmd=INVALIDO;
                }
            }    
        break; case PREGUNTAR:
            if(coincide_preguntar(caracter)){
                if(caracter=='\n'){
                    /*funcion preguntar (get)*/
                    //printf("preguntar");
                    int ang=SP_Timer_getPWM();
                    SP_ComSerie_write_mensaje("Preguntar");
                    cmd.est_cmd= INICIO;
                    SP_Comando_SCPI_init();
                }
            }
            else{
                cmd.est_cmd= INVALIDO;
            }
        break; case ESTABLECER:
            if(coincide_establecer(caracter)){
                if(caracter=='\n'){
                    if((numeroDelComando(cmd)>=0)&&(numeroDelComando(cmd)<=180)){/*numero entre 0 y 180 */
                        /*establecer*/
                        /*mandar a inicio*/
                        int ang=numeroDelComando(cmd);
                        SP_Timer_setPWM(ang);
                        SP_ComSerie_write_mensaje("Establecer");
                        SP_Comando_SCPI_init();
                    }else{if(numeroDelComando(cmd)>180){
                        /*mandar a inicio*/
                        /*msj de angulo superior*/
                        SP_ComSerie_write_mensaje("ANGULO SUPERIOR");
                        SP_Comando_SCPI_init();
                        }
                        else{cmd.est_cmd=INVALIDO;}}
                }
                else {
                    if (isdigit(caracter)){
                        cmd.est_cmd=ESTABLECER;
                    }
                    else{cmd.est_cmd=INVALIDO;}
                }
            }
            else{
                cmd.est_cmd= INVALIDO;
            }
        break; case INVALIDO:
            if(caracter=='\n'){
                /*MANDAR MSJ DE INVALIDO*/
                SP_ComSerie_write_mensaje("INVALIDO");
                cmd.est_cmd=INICIO;
                SP_Comando_SCPI_init();
            }      
        break;default:
            cmd.est_cmd= INVALIDO;       
    }
}