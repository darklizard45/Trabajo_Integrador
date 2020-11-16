struct fecha{
	int dia;
	int mes;
	int ano;
};

struct horas{
	int hora;
	int min;
};

struct usuario{
	long int id;
	long int cel;
	char patente[9];
	float saldo;
};

struct inspector{   //96tamaño struct
    int numActa;            //4 bytes
    int fecha[3];           //12 bytes
    int hora;               //4 bytes
    char patente[10];       //10 bytes
    int modelo;             //4 bytes
    int tipoVehiculo;       //4 bytes
    int tipoDeInfraccion;   //4 bytes
    char observacion[24];   //24 bytes
    char nombreAgente[24];  //24 bytes
    int legajo;             //4 bytes
};


struct movimiento{
	long int nroControl;
	long int nroCuenta;
	char patente[10];
	float saldoprevio;
	struct fecha fe;
	struct horas hsi;
	struct horas hsf;
	float monto;
};

struct saldo{
    long int nroControl;
    long int nroCuenta;
    float monto;
    float saldoPrevio;
    struct fecha fe;
    struct horas hs;
};
