#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


//funciones
long int anteriorsal();
void guardarsaldo(struct saldo);
void buscauser(struct usuario*,long int);
float cargamonto();
void recorrersaldos();
void guardaruser(struct usuario);
void cargarsaldo(struct usuario *);

//Poner la fecha actual del pc
void tiempor(int *dia,int *mes,int *ano){
	struct tm *r;
	time_t thd;
	time(&thd);
	r = gmtime(&thd);
	*dia = r->tm_mday;
	*mes = r->tm_mon;
	*ano = r->tm_year;
	*mes=*mes+1;
	*ano=*ano+1900;
}
//Poner la hora actual del pc
void hsiact(int *hora,int *min){
	struct tm *r;
	time_t thd;
	time(&thd);
	r=localtime(&thd);
	*hora = r->tm_hour;
	*min = r->tm_min;
}
//Funcion de cargar saldos del sem
void cargarsaldo(struct usuario *user){
	int ban = 1,ban1,ban2 = 1,guar = 1;
	float total;
	struct saldo sal;
	while(ban){
		sal.nroControl = anteriorsal();
		sal.nroCuenta = user->cel;
		sal.saldoPrevio= user->saldo;
		sal.monto = cargamonto();
		tiempor(&sal.fe.dia,&sal.fe.mes,&sal.fe.ano);
		while(ban2){
			printf("\t\tEstas Seguro de cargar este monto? \n\t\t1.Si \n2.No \n3.Cancelar");
			scanf("%d",&ban1);
			getchar();
			switch(ban1){
				case 1:
					ban2 = 0;
					ban = 0;
					break;
				case 2:
					sal.monto = cargamonto();
					break;
				case 3:
					ban2 = 0;
					ban =0;
					guar = 0;
					break;
				default:
					printf("No es una de las opciones/n");
					getchar();
			}
			total= sal.monto+user->saldo;
			user->saldo=total;
			if(guar){
				hsiact(&sal.hs.hora,&sal.hs.min);
				guardarsaldo(sal);
				}
			}
	}
}
//Colocar el numero de control del saldo
long int anteriorsal(){
FILE *arch;
struct saldo sal;
	long int r=0,n1 = -1;
	if((arch = fopen("saldos.bin","rb"))==NULL){
		printf("El archivo no existe/n");
	}else{
		fseek(arch,n1*sizeof(struct saldo),SEEK_END);
		fread(&sal,sizeof(sal),1,arch);
		r=sal.nroControl;
		r++;
		fclose(arch);
	}
	return (r);//anterior saldo(ant_s)
}
//Ingreso correcto del monto
float cargamonto(){
	float monto;
	int ban=1;
	printf("Ingresa el monto (minimo 100)/n");
	scanf("%f",&monto);
	while(ban){
		if (monto>=100){
			ban=0;
		}else{
			printf("No es el monto minimo/n");
		}
	}
	return (monto);
}
//guarda el saldo en el archivo binario
void guardarsaldo(struct saldo sal){
	FILE *arch;
	if((arch=fopen("saldos.bin","a+b"))!=NULL){
		fwrite(&sal,sizeof(sal),1,arch);
		printf("Saldo guardado/n");
		fclose(arch);
	}else{
		printf("Error: No se pudo encontrar el archivo/n");
		getchar();
	}
}
//revisa si el archivo existe.
void archivosal(){
	struct saldo sal;
	FILE *arguardado;//archivo guardado
	if((arguardado=fopen("saldos.bin","rb"))==NULL){
		if((arguardado=fopen("saldos.bin","wb"))!=NULL){
			sal.nroControl=0;
			fwrite(&sal,sizeof(sal),1,arguardado);
			fclose(arguardado);
		}else printf("Error no se pudo crar el archivo probablemente el programa no funcione\n");
		fclose(arguardado);
	}
}

//Mostrar todos los saldos
void recorrersaldos(){
	FILE *arch;
	struct saldo sal;
	if ((arch=fopen("saldos.bin", "rb"))!=NULL){
		fread(&sal,sizeof(sal),1,arch);
		while(!feof(arch)){
			printf("control:%ld\ncuenta:%ld\nmonto:%lf\nsaldoprevio:%lf\nfecha:%d/%d/%d\nhora:%d:%d\n\n",sal.nroControl,sal.nroCuenta,sal.monto,sal.saldoPrevio,sal.fe.dia,sal.fe.mes,sal.fe.ano,sal.hs.hora,sal.hs.min);
			fread(&sal,sizeof(sal),1,arch);
		}
		fclose(arch);
	}	
}
//mostrar los saldos de una persona
void user_saldos(){
	FILE *ar;
	struct saldo sal;
	long int cel;
	if((ar=fopen("saldos.bin","rb"))!=NULL){
		printf("\t\tIngrese el numero de telefono del usuario\n");
		scanf("%ld",&cel);
		fread(&sal,sizeof(sal),1,ar);
		while(!feof(ar)){
			if(cel==sal.nroCuenta){
				printf("Control:%ld\nCuenta:%ld\nMonto:%lf\nSaldo previo:%lf\nFecha:%d/%d/%d\nHora:%d:%d\n",sal.nroControl,sal.nroCuenta,sal.monto,sal.saldoPrevio,sal.fe.dia,sal.fe.mes,sal.fe.ano,sal.hs.hora,sal.hs.min);
			}
			fread(&sal,sizeof(sal),1,ar);
		}
		fclose(ar);
	}
	getchar();
	system("cls");
}
