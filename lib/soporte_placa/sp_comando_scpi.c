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
int potencia;
char num[3];
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
        else{return false}
    }
    else{
        if(isdigit(c)){
            if(cmd.potencia != 3){
                int j=cmd.potencia;
                cmd.num[j]=c;
                cmd.potencia++;
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

void SP_Comando_SCPI_init(void){
    cmd.est_cmd= INICIO;
    cmd.coincidente=0;
    cmd.una_vez=0;
    cmd.potencia=0;
    cmd.num="000";
}

void SP_Comando_SCPI_procesa(char caracter){
    switch (est_cmd)
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
                    cmd.est_cmd=INVALIDO
                }
            }    
        break; case PREGUNTAR:
            if(coincide_preguntar(caracter)){
                if(caracter=='\n'){
                    /*funcion preguntar (get)*/
                    cmd.est_cmd= INICIO;
                }
            }
            else{
                cmd.est_cmd= INVALIDO;
            }
        break; case ESTABLECER:
            if(coincide_establecer(caracter)){
                if(caracter=='\n'){
                    /*convertir cadena en número*/
                    /*numero entre 0 y 180 */
                    if((num>=0)&&(num<=180)){
                        /*establecer*/
                        /*mandar a inicio*/
                    }else{if(num>180){
                        /*mandar a inicio*/
                        /*msj de angulo superior*/}
                        else{cmd.est_cmd=INVALIDO}}
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
                cmd.est_cmd=INICIO;
            }      
        break;default:
            cmd.est_cmd= INVALIDO;       
    }
}
