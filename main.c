#include <stdio.h>
#include <stdlib.h>

/* Menu y rama principal del programa */
void cabecera();


void main() {
	int op,ban=1;
	while(ban){
		cabecera();
		printf("\n\t\t1-LOGIN\n\t\t2-REGISTRAR\n\t\t3-INSPECTOR\n\t\t4-CERRAR\n");
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
				opcionesIns();
				break;
			case 4:
				ban=0;
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
