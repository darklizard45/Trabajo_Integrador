#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
//#include"movimiento.h"

FILE *fp;
FILE *txt;
time_t now;
void inspectores();
void infracciones();
int modelo();
int tipoV();
int inspector();
void SelecIn();
struct inspector acta;
struct tm *timer;

int inspector(){
    int i = 0, buscar = 0;
    int rname;
    int pont = 0;
    char nombreA[14];
uno:
    cabecera();
    printf("INGRESE QUE DESEA HACER:");
    printf("\n\t\t1-HACER UNA INFRACCION\n\t\t2-BUSCAR UN VEHICULO\n\t\t3-TOP\n\t\t0-SALIR\n");
    scanf("%d", &pont);
    switch(pont){
        case 1:
            cabecera();
            fp = fopen("infracciones.bin","ab");
                time(&now);
                timer = localtime(&now);
                if(fp != NULL){
                    acta.numActa = time(&now);
                    acta.fecha[0] = timer->tm_mday;
                    acta.fecha[1] = timer->tm_mon+1;
                    acta.fecha[2] = timer->tm_year+1900;
                    acta.hora = timer->tm_hour;
                    printf("Ingrese la patente: \n");
                    fflush(stdin);
                    fgets(acta.patente,10,stdin);
                    getchar();
                    strtok(acta.patente, "\n");
                    for(i = 0; i < 14; i ++){ 
                        if(i < 10) strcpy(nombreA,acta.patente);
                        if(i == 10) nombreA[i] = '.';
                        if(i == 11) nombreA[i] = 't';
                        if(i == 12) nombreA[i] = 'x';
                        if(i == 13) nombreA[i] = 't';
                    }
                    txt = fopen("Oldfile.txt", "at");
                    //fprintf(fp, "%10s", acta.patente);
                    acta.modelo = modelo();
                    //fprintf(fp, "%d", acta.modelo);
                    acta.tipoVehiculo = tipoV();
                    //fprintf(fp, "%d", acta.tipoVehiculo);
                    fflush(stdin);
                    printf("\nIngrese el tipo de infraccion:\n");
                    scanf(" %d",&acta.tipoDeInfraccion);
                    getchar();
                    //fprintf(fp, "%d", acta.tipoDeInfraccion);
                    printf("\nObservacion:\n");
                    fflush(stdin);
                    fgets(acta.observacion,24,stdin);
                    strtok(acta.observacion, "\n");
                    //fprintf(fp, "%24s", acta.observacion);
                    printf("\nIngrese su nombre:\n");
                    fflush(stdin);
                    fgets(acta.nombreAgente,24,stdin);
                    strtok(acta.nombreAgente, "\n");
                    //fprintf(fp, "%24s", acta.nombreAgente);
                    printf("\nIngrese su legajo:\n");
                    fflush(stdin);
                    scanf(" %d", &acta.legajo);
                    //fprintf(fp, "%d", acta.legajo);
                    cabecera();
                    printf("\nSe ha cargado el acta");
                    fwrite(&acta, sizeof(struct inspector), 1, fp);
                    fprintf(txt, "\t\t\tACTA\nNumero de acta: %d\nFecha del acta: %2d/%2d/%4d\nHora:%d\nPatente: %10s\nModelo: %d\nTipo de vehiculo: %d\nTipo de infracciÃ³n: %d\nObservacion: %24s\nNombre del agente: %24s \nLegajo del agente: %d", acta.numActa, acta.fecha[0], acta.fecha[1], acta.fecha[2], acta.hora, acta.patente, acta.modelo, acta.tipoVehiculo, acta.tipoDeInfraccion, acta.observacion, acta.nombreAgente, acta.legajo);
                    Sleep(900);
                    fclose(fp);
                    fclose(txt);
                    rname = rename("Oldfile.txt", nombreA);
                    goto uno;
                }else{
                    printf("Error de archivo");
                    Sleep(900);
                    goto uno;
                }
                
            fclose(fp);
        break;

        case 2:
            cabecera();
            buscar = buscarP();
            if(buscar == 1) printf("Patente con SEM activado");
            if(buscar == 0) printf("Patente sin SEM activado");
            Sleep(1050);
            goto uno;
        break;

        case 3:
            cabecera();
            SelecIn();
            goto uno;
        break;

        default:
            return 0;
        break;
    }
    return 0;
}

void infracciones(){

}
void inspectores(){

}

int modelo(){
    int cod = 0;
    do{
        cabecera();
        printf("\nIngrese el modelo del vehiculo:");
        printf("\n1-Audi");
        printf("\n2-Bmw");
        printf("\n3-Citroen");
        printf("\n4-Chevy");
        printf("\n5-M. Benz");
        printf("\n6-Toyota");
        printf("\n7-Peugeot");
        printf("\n8-Yamaha");
        printf("\n9-Nissan");
        printf("\n10-Honda");
        printf("\n");
        fflush(stdin);
        scanf("%d", &cod);
        getchar();
        if (cod > 0 && cod <= 10) return (cod);
        if(cod <= 0 || cod > 10){
            printf("\nError de ingreso\n");
            Sleep(900);
        }
    }while(cod <= 0 || cod > 10);
    return (cod);
}

int tipoV(){
    int cod = 0;
    do{
        cabecera();
        printf("\nIngrese el tipo de vehiculo:");
        printf("\n1-Automovil");
        printf("\n2-Camioneta");
        printf("\n3-Motor");
        printf("\n4-Omnibus");
        printf("\n5-Camion");
        printf("\n6-Acoplado");
        printf("\n7-Trailer");
        printf("\n8-Otro");
        printf("\n");
        fflush(stdin);
        scanf("%d", &cod);
        getchar();
        if (cod > 0 && cod <= 8) return (cod);
        if(cod <= 0 || cod > 8){
            printf("\nError de ingreso\n");
            Sleep(900);
        }
    }while(cod <= 0 || cod > 8);
    return (cod);
}

int buscarP(){
    long int marca = 0;
    FILE *est;
    struct movimiento auxiliar,mov;
    char matricula[10];
    printf("Ingrese la patente: \n");
    fflush(stdin);
    fgets(matricula,10,stdin);
    getchar();
    strtok(matricula, "\n");
    est = fopen("movimientos.bin","rb");
    if(est != NULL){
        while(!feof(est)){
            fseek(est, marca,SEEK_SET);
            fread(&auxiliar, sizeof(auxiliar), 1,est);
            if(auxiliar.patente == matricula){
                if(auxiliar.hsf.hora == -1){
                    fclose(est);
                    //printf("\nACA");
                    return 1;
                }
            }
            marca = marca + sizeof(mov);
        }
    }else{
        fclose(est);
        est = fopen("movimientos.bin","wb");
        //printf("\n Error al abrir el archivo");
        fclose(est);
        Sleep(1080);
        return 0;
    }
    fclose(est);
    return 0;
}

void SelecIn(){
    int legajoAux, legajo[2], i, j, contador, contadoraux, top[2];
    fp = fopen("infracciones.bin", "rb");
    top[1] = 0;
    if(fp != NULL){
        i = sizeof(struct inspector) - sizeof(acta.legajo);
        while(!feof(fp)){
            fseek(fp, i, SEEK_SET);
            fread(&legajo[0], sizeof(legajo[0]), 1, fp);
            fseek(fp,(i + sizeof(struct inspector)), SEEK_SET);
            fread(&legajo[1], sizeof(legajo[1]), 1, fp);
            j = sizeof(struct inspector) - sizeof(acta.legajo);
            contadoraux = 0;
            contador = 0;
            while(!feof(fp)){
                fseek(fp, j, SEEK_SET);
                fread(&legajoAux, sizeof(legajoAux), 1, fp);
                //printf(" El legajo es: %d", legajoAux);
                if(legajo[0] == legajoAux) contador = contador + 1; 
                if(legajo[1] == legajoAux) contadoraux = contadoraux + 1; 
                j = j + sizeof(struct inspector);
            }
            if((contador > contadoraux) && (contador > top[1])){
                top[0] = legajo[0];
                top[1] = contador;
            }
            else if((contador < contadoraux) && (contadoraux > top[1])){
                top[0] = legajo[1];
                top[1] = contadoraux;
            }
            else if((contador == contadoraux) && (contadoraux > top[1])){
                top[0] = legajo[1];
                top[1] = contadoraux;
            }
            i = i + sizeof(struct inspector);
            //printf("|%d||%d|", ftell(fp), i); 
            if(i >= ftell(fp)){
                if(top[1] == 0){
                    printf("\n\n No existen suficientes actas para hacer un top");
                    getchar();
                    Sleep(1100);
                return;
                }
                printf("\n\n El legajo correspondiente al agente con mas actas labradas es: %d. \nTOTAL: %d actas.", top[0], (top[1] -1));
                getchar();
                Sleep(1100);
                return;
            }
            rewind(fp);
        }
    }else{
        fclose(fp);
        printf("\nERROR\nEl registro no se ha creado");
        Sleep(900);
    }
    fclose(fp);
    
}
