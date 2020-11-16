#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "recargas.h"
#include "inspecion.h"

/* Menu y rama principal del programa */
void cabecera();


void main() {
	int op,ban=1;
	while(ban){
		cabecera();
		printf("\n\t\t1-LOGIN\n\t\t2-REGISTRAR\n\t\t3-INSPECTOR\n\t\t4-CERRAR\n\t\t5.MOSTRAR USUARIOS\n\t\t6.MOSTRAR SALDOS DE USUARIO\n\t\t7.MOSTRAR MOVIMIENTOS");
		scanf("%d",&op);
		getchar();
		switch(op){
			case 1:
				login();
				break;
			case 2:
				registers();
				break;
			case 3:
				inspector();
				break;
			case 4:
				ban=0;
				break;
			case 5:
				mostraruser();
				break;
			case 6:
				user_saldos();
				break;
			case 7:
				mostrarmovimientos();
				break;
			default:
				printf("No es una de las opciones\n");
				getchar();
				system("cls");
		}
	}
}

void cabecera(){
    system("cls");
    printf("  _______________________________________________________________________________________________________________\n");
    printf("|                                                                                                                 |\n");
    printf("|                                                                                                                 |\n");
    printf("|                                           SEM                                                                   |\n");
    printf("|                                                                                                                 |\n");
    printf("|                                                                                                                 |\n");
    printf(" ________________________________________________________________________________________________________________\n");
}
