#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "movimiento.h"
//Funciones

void login();
void registers();
int leercel(long int*);
long int autoiduser();
void guardaruser(struct usuario);
void mostraruser();
void archuser();

//Logeo del usuario y operaciones del usuario
void login(){
	fpos_t pos;
	archmov();
	FILE *arch;
	struct usuario us,user;
	long int bus,op,ben=1;
	us.id=-1;
	system("cls");
	if((arch=fopen("usuario.bin","rb"))!=NULL){//Recorre el archivo en busca del usuario
		printf("\t\tIngrese su numero de celular\n\t\tCel:");
		scanf("%ld",&bus);
		fread(&user,sizeof(user),1,arch);
		while(!feof(arch)){
			if(user.cel==bus){
				us.cel=user.cel;
				us.saldo=user.saldo;
				strcpy(us.patente,user.patente);
				fseek(arch,sizeof(user),SEEK_END);
			}
			fread(&user,sizeof(user),1,arch);
		}
		fclose(arch);
	}
	system("cls");
	while(ben&&us.id!=-1){//Ingreso al menu de login
		printf("\t\t1.Iniciar estacionamiento\n\t\t2.Finalizar estacionamiento\n\t\t3.Cargar Saldo\n\t\t4.Salir\n");
		scanf("%ld",&op);
		getchar();
		switch(op){
			case 1:
				inimov(&us);
				system("cls");
				break;
			case 2:
				finmov(&us);
				system("cls");
				break;
			case 3:
				cargarsaldo(&us);
				system("cls");
				break;
			case 4:
				ben=0;
				break;
			default:
				printf("No es una de las opciones\n");
				getchar();
				system("cls");
		}
	}
	if(us.id==-1){//Informa que no encontro el usuario
		printf("No se pudo encontrar el usuario\n");
	}
	guardaruser(us);
}
//Registro de usuario
void registers(){
	FILE *arch;
	archuser();
	struct usuario user;
	int ban=0,guar=0;
	printf("\t\tIngrese numero de telefono\n");
	scanf("%ld",&user.cel);
	getchar();
	user.id=autoiduser();
	printf("\t\tIngrese la patente\n");
	fgets(&user.patente,8,stdin);
	user.saldo=0;
	if((arch=fopen("usuario.bin","ab"))!=NULL){
		fwrite(&user,sizeof(user),1,arch);
		printf("\t\tRegistro completados\n");
		fclose(arch);
	}else printf("Error:No se pudo abrir el archivo");
	getchar();
}
//Funcion para leer el celular de forma correcta
int leercel(long int *p){
	int ban=1,r=1;
	struct usuario us;
	FILE *arch;
	while(ban){
		printf("\t\tIngresa el tu numero de telefono\t0.Salir\n");
		scanf("%ld",p);
		getchar();
		if((*p)>0){
			if((arch=fopen("usuario.bin","rb"))!=NULL){//busca si no esta repetido el cel
				fread(&us,sizeof(us),1,arch);
				while(!feof(arch)){
					if(*p==us.cel){
						r=0;
					}
					fread(&us,sizeof(us),1,arch);
				}
				fclose(arch);
			}
		}else{
			if(p==0){
				ban=0;
				r=0;
			}else{
				printf("Error: fallo de ingreso del celular\n");
			}
		}
		if(r==0){
			ban=0;
			printf("No se pudo guardar el telefono\n\n\t\t1.Cancelaste el registro\n\n\t\t2.El celular esta repetido\n");
		}	
	}
	return (r);
}
//Auto id del usuario
long int autoiduser(){
	struct usuario user;
	long int r=0,e=-1;
	FILE* bine;
	if((bine=fopen("usuario.bin","a+b"))!=NULL){
		fseek(bine,e*sizeof(user),SEEK_END);
		fread(&user,sizeof(user),1,bine);
		r=user.id;
		r++;
		fclose(bine);
	}else {printf("Error id");}
	return (r);
}
//guarda los cambios del usuario
void guardaruser(struct usuario user){
	FILE *ar;
	if((ar=fopen("usuario.bin","r+b"))!=NULL){
		fseek(ar,user.id*sizeof(user),SEEK_SET);
		fwrite(&user,sizeof(user),1,ar);
		fclose(ar);
	}else printf("Error no se pudo cargar el archivo\n");
}
//Muestra todos los usuarios registrados
void mostraruser(){
	FILE *ar;
	struct usuario us;
	if((ar=fopen("usuario.bin","rb"))!=NULL){
		fread(&us,sizeof(us),1,ar);
		while(!feof(ar)){
			printf("\t\tCel:%ld\n\t\tPatente:%s\n\t\tSaldo:%lf\n\n",us.cel,us.patente,us.saldo);
			fread(&us,sizeof(us),1,ar);
		}
		fclose(ar);
	}
	getchar();
	system("cls");
}
void archuser(){
	FILE *arch;
	struct usuario mov;
	if((arch=fopen("usuario.bin","rb"))!=NULL){
		printf("usuario.bin cargado\n");
		fclose(arch);
	}else{
		if((arch=fopen("usuario.bin","wb"))!=NULL){
			mov.cel=0;
			mov.id=0;
			fwrite(&mov,sizeof(mov),1,arch);
			printf("Archivo creado\n");
			fclose(arch);
		}else{
			printf("No se pudo crear el archivo\n");
		}
	}
}
