#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
//Funciones
void inimov(struct usuario*);//Iniciar movimiento
void finmov(struct usuario*);//Finalizar movimiento
unsigned long int autocontrol();//autoid
float calcularmon(struct movimiento);//Calcular monto
void mostrarmovimientos();//Muestra los movimientos entre dos fechas
int leerdia();//Leer los dias
int leermes();//Leer los meses
int leerano();//Leer los a�os
void tiempor(int*,int*,int*);
int controlexis(struct usuario);
void archmov();

//Menu sin emulacion
int controlexis(struct usuario);//Verificacion de movimiento
void totalmov();//Muestra todos los movimientos
void archmovi();//Verifica si el archivo existe

//Menu del movimiento.
/*void movmenu(struct usuario us){
	int ban=1,op;
	while(ban){
		printf("Movimientos:\n\n\n1.Iniciar estacionamiento\n2.Finalizar estacionamiento\n3.Salir\n");
		scanf("%d",&op);
		getchar();
		switch(op){
			case 1:
				inimov(&us);
				break;
			case 2:
				finmov(&us);
				break;
			case 3:
				ban=0;
				break;
			default:
				printf("No es una de las funciones\n");
		}	
	}
}*/

//Inicio de estacionamiento
void inimov(struct usuario *user){
	FILE *arch;
	struct movimiento mov;
	int ban=1,op,guar;
	guar=controlexis(*user);//Indica si el usuario ya esta estacionado o no tiene saldo suficiente
	if(guar == 0) return;
	mov.nroControl=autocontrol();
	mov.nroCuenta=user->cel;
	tiempor(&mov.fe.dia,&mov.fe.mes,&mov.fe.ano);
	mov.saldoprevio=user->saldo;
	strcpy(mov.patente,user->patente);
	hsiact(&mov.hsi.hora,&mov.hsi.min);
	mov.hsf.hora=-1;//Se coloca -1 para indicar que aun esta estacionado el veiculo del usuario
	mov.monto=20;//Se deja preeterminado $20 (1hs = $20)
	if((arch=fopen("movimientos.bin","a+b"))!=NULL){//guar significa que si ya existe el veiculo estacionado no lo guarda
		while(ban&&guar!=0){
			printf("Iniciar estacionamiento?\n\n.Si\n\n2.No\n");//Se elije una opcion si el usuario decide cancelar el estacionamiento
			scanf("%d",&op);
			switch(op){
				case 1:
					printf("Iniciando estacionamiento\n");
					ban=0;
					break;
				case 2:
					printf("Cancelando estacionamiento\n");
					guar=0;
					ban=0;
					break;
				default:
					printf("No es una de las opciones\n");
			}
		}
		if(guar==1){
			fwrite(&mov,sizeof(mov),1,arch);
		}
		fclose(arch);
	}else{
		printf("No se pudo encontrar el archivo\n");
	}
}
//Fin del estacionamiento
void finmov(struct usuario *user){
	FILE *arch;
	struct movimiento mov,mov1;
	int ban=1,n1=-1;
	if((arch=fopen("movimientos.bin","r+b"))!=NULL){
		fread(&mov,sizeof(mov),1,arch);
		while(!feof(arch)){
			if(mov.nroCuenta==user->cel&&mov.hsf.hora==-1){
				mov1.nroControl=mov.nroControl;
				mov1.nroCuenta=mov.nroCuenta;
				strcpy(mov1.patente,mov.patente);
				mov1.saldoprevio=mov.saldoprevio;
				mov1.fe.dia=mov.fe.dia;
				mov1.fe.mes=mov.fe.mes;
				mov1.fe.ano=mov.fe.ano;
				mov1.hsi.hora=mov.hsi.hora;
				mov1.hsi.min=mov.hsi.min;
				mov1.hsf.hora=mov.hsf.hora;
				mov1.hsf.min=mov.hsf.min;
			}
			fread(&mov,sizeof(mov),1,arch);
		}
		fclose(arch);
	}else printf("Error: No se pudo abrir el archivo\n");
	if((arch=fopen("movimientos.bin","r+b"))!=NULL){
		hsiact(&mov1.hsf.hora,&mov1.hsf.min);
		mov1.monto=calcularmon(mov1);
		user->saldo=user->saldo-mov1.monto;
		fseek(arch,mov1.nroControl*sizeof(mov1),SEEK_SET);
		fwrite(&mov1,sizeof(mov1),1,arch);
		printf("\t\tEstacionamiento finalizado\n");
		fclose(arch);
	}else{
		printf("Error: No se pudo abrir el archivo\n");
	}
}

//Autocontrol: retorna un numero mayor del ultimo numero de control de movimiento del archivo
unsigned long int autocontrol(){
	FILE *arch;
	struct movimiento sal;
	long int r=0,n1 = -1;
	if((arch = fopen("movimientos.bin","rb"))==NULL){
		printf("El archivo no existe\n");
	}else{
		fseek(arch,n1*sizeof(struct saldo),SEEK_END);
		fread(&sal,sizeof(sal),1,arch);
		r=sal.nroControl;
		r++;
		fclose(arch);
	}
	return (r);
}
//Calcularmonn: retorna el monto total a pagar por el estacionamiento
float calcularmon(struct movimiento mov){
	float precio = 20;
	int horaini,horafin,h_ini,h_fin;
	float monto;
	h_ini=mov.hsi.hora;
	h_fin=mov.hsf.hora;
	horaini=mov.hsi.min+(h_ini*60);
	horafin=mov.hsf.min+(h_fin*60);
	monto=((horafin-horaini)*precio)/60;
	return(monto);
}
//Controlexis: retorna 1 o 0 si el usuario ya esta estacionado o no tiene saldo suficiente
int controlexis(struct usuario user){
	FILE *arch;
	struct movimiento mov;
	int res=1;
	if((arch=fopen("movimientos.bin","rb"))!=NULL){
		fread(&mov,sizeof(mov),1,arch);
		while(!feof(arch)){
			if((mov.nroCuenta==user.cel)&&(mov.hsf.hora==-1)){
				printf("Ya esta estacionado un veiculo a tu cuenta\n");
				Sleep(1060);
				res=0;
				fseek(arch,sizeof(mov),SEEK_END);
			}else{
				fread(&mov,sizeof(mov),1,arch);
			}
		}
		fclose(arch);
	}else{
		printf("No se pudo abrir el archivo\n");
	}
	if(user.saldo<=0){
		printf("No tiene saldo suficiente\n");
		res=0;
	}
	return(res);
}
//Mostrar todos los movimientos
void totalmovi(){
	FILE *arch;
	struct movimiento mov;
	if((arch=fopen("movimientos.bin","rb"))!=NULL){
		fread(&mov,sizeof(mov),1,arch);
		while(!feof(arch)){
			printf("Control:%ld\nCuenta:%ld\nPatente:%s\nSaldo Previo:%lf\nFecha:%d/%d/%d\nHora Inicio:%d:%d/nHora Fin:%d:%d/nMonto:%lf\n\n",mov.nroControl,mov.nroCuenta,mov.patente,mov.saldoprevio,mov.fe.dia,mov.fe.mes,mov.fe.ano,mov.hsi.hora,mov.hsi.min,mov.hsf.hora,mov.hsf.min,mov.monto);
			fread(&mov,sizeof(mov),1,arch);
		}
		getchar();
		fclose(arch);
	}
}
//Archmov: verifica si el arcivo existe, si no existe se crea uno.
void archmov(){
	FILE *arch;
	struct movimiento mov;
	if((arch=fopen("movimientos.bin","rb"))!=NULL){
		printf("Archivo existente\n");
		fclose(arch);
	}else{
		if((arch=fopen("movimientos.bin","wb"))!=NULL){
			mov.nroControl=0;
			mov.hsf.hora=0;
			mov.hsf.min=0;
			fwrite(&mov,sizeof(mov),1,arch);
			printf("Archivo creado\n");
			fclose(arch);
		}else{
			printf("No se pudo crear el archivo\n");
		}
	}
}
//Mostrar los movimientos entre dos fechas
void mostrarmovimientos(){
	FILE *ar;
	struct movimiento mov;
	struct fecha fe1,fe2;
	if((ar=fopen("movimientos.bin","rb"))!=NULL){
		printf("\t\tIngrese la fecha inicial\n\t\tDia:");
		fe1.dia=leerdia();
		printf("\t\tMes:");
		fe1.mes=leermes();
		printf("\t\tA�o:");
		fe1.ano=leerano();
		printf("\t\tIngrese la segunda fecha\nDia:");
		fe2.dia=leerdia();
		printf("\t\tMes:");
		fe2.mes=leermes();
		printf("\t\tA�o:");
		fe2.ano=leerano();
		system("cls");
		fread(&mov,sizeof(mov),1,ar);
		while(!feof(ar)){
			if((fe1.dia>=mov.fe.dia&&fe1.mes>=mov.fe.mes&&fe1.ano>=mov.fe.ano)&&(fe2.dia<=mov.fe.dia&&fe2.mes<=mov.fe.mes&&fe2.ano<=mov.fe.ano)){
				printf("\tControl:%ld\tCuenta:%ld\tfecha:%d/%d/%d\tPatente:&s\n\tSaldo previo:%s&tHora de inicio:%f:%d\tHora Final:%d:&d\tMonto:&lf",mov.nroControl,mov.nroCuenta,mov.fe.dia,mov.fe.mes,mov.fe.ano,mov.patente,mov.saldoprevio,mov.hsi.hora,mov.hsi.min,mov.hsf.hora,mov.hsf.min,mov.monto);
			}
			fread(&mov,sizeof(mov),1,ar);
		}
		getchar();
		fclose(ar);
	}else printf("No se pudo abrir el archivo\n");
}
//lee las los dias de forma correcta
int leerdia(){
	int a,ban=1;
	while(ban){
		scanf("%d",&a);
		getchar();
		if(a>0&&a<=31){
			//printf("(Dia guardado)\n");
			ban=0;
		}else{
			printf("No esta en el rango permitido\nDia:");
		}
	}
	return(a);
}
//lee los meses de forma correcta
int leermes(){
	int a,ban=1;
	while(ban){
		scanf("%d",&a);
		getchar();
		if(a>0&&a<=12){
			//printf("(Mes guardado)\n");
			ban=0;
		}else{
			printf("No esta en el rango permitido\nMes:");
		}
	}
	return(a);	
}
//lee los a�os de forma correcta
int leerano(){
	int a,ban=1;
	while(ban){
		scanf("%d",&a);
		getchar();
		if(a>1990&&a<=2100){
			//printf("(Ano guardado)\n");
			ban=0;
		}else{
			printf("No esta en el rango permitido\nAno:");
		}
	}
	return(a);
}
//Ingresar tiempo actual (PC)
void hsiact(int *hora,int *min){
	struct tm *r;
	time_t thd;
	time(&thd);
	r=localtime(&thd);
	*hora=r->tm_hour;
	*min=r->tm_min;
}
