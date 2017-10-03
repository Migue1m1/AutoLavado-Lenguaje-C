#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
const int MaxEstacionamiento = 5;
const int TIEMPOMAXIMODESERVICIOAUTOPEQUENIO = 100;
const int TIEMPOMAXIMODESERVICIOAUTOMEDIANO = 7;
const int TIEMPOMAXIMODESERVICIOAUTOGRANDE = 10;
int SEGUNDOS = 0, MINUTOS = 0, TIEMPODESIMULACION = 0;
bool FINISHANIMATION = false;
typedef struct puesto
{
    int CodigoDeVehiculo;
    int CodigoColorDeVehiculo;
    short Identificador;
}Puesto_t;
typedef struct pilaEst
{
    Puesto_t Puestos[5];
    short Tope;
}Estacionamiento_t;
typedef struct creaColaDeAutos
{
    short Identificador;
    int CodigoColorDeVehiculo;
    int CodigoDeVehiculo;
    struct creaColaDeAutos *AutoProximo;
}ColaDeAutos_t;
typedef struct Auto
{
    bool TarjetaDeCredito;
    bool TarjetaDeDebito;
    bool Efectivo;
    bool LavadoYAspirado;
    bool CambioDeAceite;
    bool LavadoDeMotorOChasis;
    bool CarroPequeno;
    bool CarroMediano;
    bool CarroGrande;
    int CodigoDeVehiculo;
    int CodigoColorDeVehiculo;
    time_t tLlave_Inicio;
    time_t tLlave_Transcurrido;
    bool Llaves;
    bool LlaveOn;
    char ServicioAnterior[5];
    short Identificador;
    bool OrdenDeBorrado1;
    bool OrdenDeBorrado2;
    bool OrdenDeBorrado3;
    bool OrdenDeEstacion;
	struct Auto *AutoProximo;
}Auto_t;
typedef struct nodoCentinela
{
    int TotalTC;
    int TotalTD;
    int TotalEF;
	short PagoTC;
    short PagoTD;
    short PagoEF;
    short PersonasLYA;
    short PersonasCA;
    short PersonasLMC;
    short TotalClientes;
	Auto_t *AutoSiguiente;
}ControlDeAutos_t;
typedef struct estaciones
{
    time_t TiempoTranscurrido;
    time_t TiempoInicial;
    short EstadoDeEstacion;
    short Identificador;
}Estaciones_t;
void animColaLavadoMotor(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animColaCambioAceite(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeEntradaHaciaColaLavadoDeMotor(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeEntradaHaciaColaCambioDeAceite(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animHaciaEstacion1LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animHaciaEstacion2LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animHaciaEstacion3LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animHaciaEstacion4LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeEntradaHaciaColaLavadoYAspirado(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoYAspiradoHaciaColaCambioDeAceite(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoYAspiradoHaciaColaLavadoDeMotor(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoYAspiradoHaciaSalida(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeCambioDeAceiteHaciaColaLavadoYAspirado(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeCambioDeAceiteHaciaColaLavadoMotor(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeCambioDeAceiteHaciaSalida(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoMotorHaciaColaLavadoYAspirado(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoMotorHaciaColaCambioDeAceite(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoMotorHaciaSalida(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoYAspiradoHaciaEstacionamiento(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeCambioDeAceiteHaciaEstacionamiento(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animacionDesdeLavadoDeMotorHaciaEstacionamiento(int CodigoDeVehiculo, int CodigoColorDeVehiculo);
void animSacarAutos(Estacionamiento_t *estacionamiento, Puesto_t puesto);
ColaDeAutos_t *agregarNuevoAutoACola(ColaDeAutos_t * &primero, short identificador, int codColorAuto, int codAuto);
bool autoEnCola(ColaDeAutos_t *primero, short identificador);
void actualizarCola1(ColaDeAutos_t *primeroCola1);
void actualizarCola2(ColaDeAutos_t *primeroCola2);
void actualizarCola3(ColaDeAutos_t *primeroCola3);
void actualizarEstacionamiento(Estacionamiento_t *estacionamiento);
Auto_t *agregarNuevoAutoAlLocal(Auto_t * &autoMovil, short generadorDeIdentificadores);
void borrarLista(Auto_t *nodoPrimero);
void borrarPrimerAutoDeLaCola(ColaDeAutos_t * &primero);
bool colaVacia(ColaDeAutos_t *primero);
void calcularTiempoDeLavadoEnEstaciones(Estaciones_t estacionesDeLavadoYAspirado[4]);
void creditos();
Auto_t *crearNodo();
void DesdeEstacionamientoHaciaSalida(Puesto_t puesto);
void eliminaPorCompletoUnaCola(ColaDeAutos_t *primero);
void eliminarDeLaLista(Auto_t * &autoABorrar, short Identificador);
bool estacionamientoVacio(Estacionamiento_t *estacionamiento);
bool estacionamientoLleno(Estacionamiento_t *estacionamiento);
void estacionarAutos(Estacionamiento_t *estacionamiento, short identificador, int codigoAuto, int codigoColorAuto);
void entregarAuto(Estacionamiento_t *estacionamiento, short identificador);
bool finalizaCicloEnEstacion3o2(short *estacion, time_t *tiempoTranscurrido, time_t *tiempoInicial, short *identificador);
void gotoxy(int fila,int col);
void iniciarSimulacion();
void iniciarEstacionamiento(Estacionamiento_t *estacionamiento);
void menu();
ColaDeAutos_t *nuevoAutoACola();
int numeroDeAutosEnCola(ColaDeAutos_t *primero);
int numAutosEnEstacionamiento(Puesto_t puestos[5]);
void pintarAutolavado();
int ponerAutoEnAlgunaEstacionLibreDeLavadoYAspirado(Estaciones_t estacionesDeLavadoYAspirado[4], short identificador);
void pintarSalaEspera();
void random_autos(Auto_t * &autonuevo);
DWORD WINAPI TemporizadorDeSimulacion(void *data);
bool verificaTiempoDeEstaciones(Estaciones_t estacionesDeLavadoYAspirado[4], short identificador);
bool verificarSiHayEstacionDeLavadoLibre(Estaciones_t estacionesDeLavadoYAspirado[4]);
bool verSiIDEstaEnEstacionamiento(Puesto_t puestos[5], short ID);

int main(int argc, char *argv[]) 
{
    menu();
	pintarAutolavado();
	HANDLE temporizador = CreateThread(NULL, 0, TemporizadorDeSimulacion, NULL, 0, NULL);
    srand(time(NULL));
	iniciarSimulacion();
	CloseHandle(temporizador);
	creditos();	
	return 0;
}
//Animaciones.
void animColaLavadoMotor(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x = 54, y;int i;
    y = 33;
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    for (i = 0; i < 19; i++)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        if (i != 18)
           Sleep(100);
        gotoxy(y, x - 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
    }
    gotoxy (y, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    printf("%c", CodigoDeVehiculo);
}
void animColaCambioAceite(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int y = 16, x = 57, i;
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x - 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x >= 76)
            i = 1;
    }
    gotoxy (y, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    printf("%c", CodigoDeVehiculo);
}
void animacionDesdeEntradaHaciaColaLavadoDeMotor(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 77; y = 48;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 48)
        {
            i = 1;
        }
    }
    i = 0;
    x = 48;y = 48;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 42)
        {
            i = 1;
        }
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 54)
        {
            i = 1;
        }
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 34 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
void animacionDesdeEntradaHaciaColaCambioDeAceite(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 77; y = 48;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 45)
        {
            i = 1;
        }
    }
    i = 0;y = 48;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 27)
        {
            i = 1;
        }
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 57)
        {
            i = 1;
        }
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 17 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
void animHaciaEstacion1LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x = 29, y = 22, i = 0;
    while (i < 6)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y + 1, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        i++;
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x + 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 22)
            i = 1;
    } 
    i = 0;
    while (i < 8)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y + 1, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        i++;
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x + 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 2)
            i = 1;
    }  
    gotoxy (y, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    printf("%c", CodigoDeVehiculo);
}
void animHaciaEstacion2LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x = 29, y = 22, i = 0;
    while (i < 6)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y + 1, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        i++;
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x + 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 22)
            i = 1;
    } 
    i = 0;
    while (i < 4)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y + 1, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        i++;
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x + 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 2)
            i = 1;
    } 
    gotoxy (y, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    printf("%c", CodigoDeVehiculo);
}
void animHaciaEstacion3LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x = 29, y = 22, i = 0;
    while (i < 6)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y + 1, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        i++;
    }
    i = 0;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x + 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 2)
            i = 1;
    }
    gotoxy (y, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    printf("%c", CodigoDeVehiculo);
}
void animHaciaEstacion4LavadoYAspirado(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x = 29, y = 22, i = 0;
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    gotoxy(y--, x);
    printf("%c", CodigoDeVehiculo);
    fflush(stdin);
    Sleep(100);
    gotoxy(y + 1, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
    printf("%c", CodigoDeVehiculo);
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(100);
        gotoxy(y, x + 1);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 2)
            i = 1;
    }
    gotoxy (y, x);
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
    printf("%c", CodigoDeVehiculo);
}
void animacionDesdeEntradaHaciaColaLavadoYAspirado(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 77; y = 48;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 29)
        {
            i = 1;
        }
    }
    i = 0;
    x = 29;y = 48;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 24 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE LAVADO HASTA COLA DE ACEITE
void animacionDesdeLavadoYAspiradoHaciaColaCambioDeAceite(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 3; y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 20)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 27)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 27;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x >= 58)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 58;y = 27;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 17 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE LAVADO HASTA COLA DE MOTOR
void animacionDesdeLavadoYAspiradoHaciaColaLavadoDeMotor(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 3; y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 20)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 52)
        {
            i = 1;
        }
    }
    i = 0;
    x = 52;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 32 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE LAVADO HASTA LA SALIDA
void animacionDesdeLavadoYAspiradoHaciaSalida(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 3; y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 20)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 54)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 54;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x >= 75)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE ACEITE HASTA COLA DE LAVADO
void animacionDesdeCambioDeAceiteHaciaColaLavadoYAspirado(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 28)
        {
            i = 1;
        }
    }
    i = 0;
    x = 28;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 23 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE ACEITE HASTA COLA DE MOTOR
void animacionDesdeCambioDeAceiteHaciaColaLavadoMotor(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 53)
        {
            i = 1;
        }
    }
    i = 0;
    x = 53;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 33 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE ACEITE HASTA SALIDA
void animacionDesdeCambioDeAceiteHaciaSalida(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 54)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 54;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y , x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x >= 75)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE MOTOR HASTA COLA DE LAVADO
void animacionDesdeLavadoMotorHaciaColaLavadoYAspirado(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 28)
        {
            i = 1;
        }
    }
    i = 0;
    x = 28;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 23 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE MOTOR HASTA COLA DE ACEITE
void animacionDesdeLavadoMotorHaciaColaCambioDeAceite(int personasEnCola, int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 38)
        {
            i = 1;
        }
    }
    i = 0;
    x = 38;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 27)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 27;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x >= 58)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 58;y = 27;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y--, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y + 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y <= 17 + personasEnCola)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
//DE MOTOR HASTA SALIDA
void animacionDesdeLavadoMotorHaciaSalida(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 54)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 54;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y , x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x >= 75)
        {
            /*SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
            gotoxy(y, x);
            printf("%c", 2);*/
            i = 1;
        }
    }
}
void animacionDesdeLavadoYAspiradoHaciaEstacionamiento(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 3; y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 20)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 25;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 20;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x >= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 54)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 54;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 16)
        {
            i = 1;
        }
    }
}
//DE CAMBIO DE ACEITE -----> ESTACIONAMIENTO
void animacionDesdeCambioDeAceiteHaciaEstacionamiento(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 19;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 54)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 54;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 16)
        {
            i = 1;
        }
    }
}// DE LAVADO DE MOTOR -----> ESTACIONAMIENTO
void animacionDesdeLavadoDeMotorHaciaEstacionamiento(int CodigoDeVehiculo, int CodigoColorDeVehiculo)
{
    int x, y, i = 0;

    x = 75; y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 63)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 35;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 42)
        {
            i = 1;
        }
    }
    i = 0;
    x = 63;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);

        printf("%c", CodigoDeVehiculo);
        
        if (x <= 40)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 42;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y++, x);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y - 1, x);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (y >= 54)
        {
            i = 1;
        }
    }
    i = 0;
    x = 40;y = 54;
    while (!i)
    {
        if (FINISHANIMATION)
            break;
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),CodigoColorDeVehiculo);
        gotoxy(y, x--);
        printf("%c", CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x + 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", CodigoDeVehiculo);
        
        if (x <= 16)
        {
            i = 1;
        }
    }
}
void animSacarAutos(Estacionamiento_t *estacionamiento, Puesto_t puesto)
{
    int x = 0, y = 0, i = 0, numAutos = 0;
    x = 20;
    y = 46;
    for (; i < 5;i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
        gotoxy(y,x);
        printf("%c", 219);
        x += 3;
    }
    i = 0;
    x = 20;
    for (numAutos = numAutosEnEstacionamiento(estacionamiento -> Puestos);numAutos >= 0;numAutos--)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), estacionamiento -> Puestos [numAutos].CodigoColorDeVehiculo);
        gotoxy(y,x);
        printf("%c", estacionamiento -> Puestos [numAutos].CodigoDeVehiculo);
        
        x += 3;
    }
    DesdeEstacionamientoHaciaSalida(puesto);
    i = 0;
    x = 20;
    for (; i < 5;i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        gotoxy(y,x);
        printf("%c", 219);
        x += 3;
    }
}
ColaDeAutos_t *agregarNuevoAutoACola(ColaDeAutos_t * &primero, short identificador, int codColorAuto, int codAuto)
{
    ColaDeAutos_t *nuevoAuto = nuevoAutoACola(), *autoAux = NULL;
    nuevoAuto -> Identificador = identificador;
    nuevoAuto -> CodigoColorDeVehiculo = codColorAuto;
    nuevoAuto -> CodigoDeVehiculo = codAuto;
    if (!primero)
        primero = nuevoAuto;
    else
    {
        autoAux = primero;
        while (autoAux -> AutoProximo)
            autoAux = autoAux -> AutoProximo;
        autoAux -> AutoProximo = nuevoAuto;
    }
    return nuevoAuto;
}
bool autoEnCola(ColaDeAutos_t *primero, short identificador)
{
    while (primero)
    {
        if (primero -> Identificador == identificador)
            return true;
        primero = primero -> AutoProximo;
    }
    return false;
}
void actualizarCola1(ColaDeAutos_t *primeroCola1)
{
    int i = 0, x = 0, y = 0;
    x = 29;
    y = 23;
    for (i = 0; i < 6; i++)
    {
        gotoxy(y + i, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        fflush(stdin);
        printf("%c", 219);
    }
    
    i = 0;
    while(primeroCola1)
    {
        gotoxy(y + i, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), primeroCola1 -> CodigoColorDeVehiculo);
        fflush(stdin);
        printf("%c", primeroCola1 -> CodigoDeVehiculo);
        primeroCola1 = primeroCola1 -> AutoProximo;
        i++;
    }
}
void actualizarCola2(ColaDeAutos_t *primeroCola2)
{
    int i = 0, x = 0, y = 0;
    x = 57;
    y = 17;
    for (i = 0; i < 6; i++)
    {
        gotoxy(y + i, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        fflush(stdin);
        printf("%c", 219);
    }
    i = 0;
    while(primeroCola2)
    {
        gotoxy(y + i, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), primeroCola2 -> CodigoColorDeVehiculo);
        fflush(stdin);
        printf("%c", primeroCola2 -> CodigoDeVehiculo);
        primeroCola2 = primeroCola2 -> AutoProximo;
        i++;
    }
}
void actualizarCola3(ColaDeAutos_t *primeroCola3)
{
    int i = 0, x = 0, y = 0;
    x = 54;
    y = 34;
    for (i = 0; i < 6; i++)
    {
        gotoxy(y + i, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        fflush(stdin);
        printf("%c", 219);
    }
    i = 0;
    while(primeroCola3)
    {
        gotoxy(y + i, x);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), primeroCola3 -> CodigoColorDeVehiculo);
        fflush(stdin);
        printf("%c", primeroCola3 -> CodigoDeVehiculo);
        primeroCola3 = primeroCola3 -> AutoProximo;
        i++;
    }
}
void actualizarEstacionamiento(Estacionamiento_t *estacionamiento)
{
    int numAutos = 0;
    int x = 0, y = 0, i = 0;
    x = 6;
    y = 34;
    for (; i < 5; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
        gotoxy(y,x);
        printf("%c", 219);
        y += 5;
    }
    y = 34;
    numAutos = numAutosEnEstacionamiento(estacionamiento -> Puestos);
    for (i = 0; i < numAutos; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),estacionamiento -> Puestos[i].CodigoColorDeVehiculo);
        gotoxy(y,x);
        printf("%c", estacionamiento -> Puestos[i].CodigoDeVehiculo);
        y += 5;
    }
}
Auto_t *agregarNuevoAutoAlLocal(Auto_t * &autoMovil, short generadorDeIdentificadores)
{
    Auto_t *nuevoAuto = crearNodo(), *autoAux = NULL;
    nuevoAuto -> Identificador = generadorDeIdentificadores;
    strcpy(nuevoAuto -> ServicioAnterior, " ");    
    nuevoAuto -> OrdenDeEstacion = true;
    random_autos(nuevoAuto);
    if (!autoMovil)
        autoMovil = nuevoAuto;
    else
    {
        autoAux = autoMovil;
        while (autoAux -> AutoProximo)
            autoAux = autoAux -> AutoProximo;
        autoAux -> AutoProximo = nuevoAuto;
    }
    return nuevoAuto;
}
void borrarLista(Auto_t *nodoPrimero)
{
    Auto_t *autoAux;
    while (nodoPrimero)
    {
        autoAux = nodoPrimero;
        nodoPrimero = nodoPrimero -> AutoProximo;
        free(autoAux);
    }
}
void borrarPrimerAutoDeLaCola(ColaDeAutos_t * &primero)
{
    ColaDeAutos_t *Aux = NULL;
    Aux = primero;
    primero = primero -> AutoProximo;
    free (Aux);
}
bool colaVacia(ColaDeAutos_t *primero)
{
    if (!primero)
        return true;
    else
        return false;
}
void calcularTiempoDeLavadoEnEstaciones(Estaciones_t estacionesDeLavadoYAspirado[4])
{
    if (estacionesDeLavadoYAspirado[0].EstadoDeEstacion == 1)
    {
        estacionesDeLavadoYAspirado[0].TiempoTranscurrido = time(NULL) - estacionesDeLavadoYAspirado[0].TiempoInicial;
    }   
    if (estacionesDeLavadoYAspirado[1].EstadoDeEstacion == 1)
    {
        estacionesDeLavadoYAspirado[1].TiempoTranscurrido = time(NULL) - estacionesDeLavadoYAspirado[1].TiempoInicial;
    }
    if (estacionesDeLavadoYAspirado[2].EstadoDeEstacion == 1)
    {
        estacionesDeLavadoYAspirado[2].TiempoTranscurrido = time(NULL) - estacionesDeLavadoYAspirado[2].TiempoInicial;
    }
    if (estacionesDeLavadoYAspirado[3].EstadoDeEstacion == 1)
    {
        estacionesDeLavadoYAspirado[3].TiempoTranscurrido = time(NULL) - estacionesDeLavadoYAspirado[3].TiempoInicial;
    }
}
void creditos()
{
    system("cls");fflush(stdin);
    gotoxy(0, 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("Universidad Nacional Experimental de Guayana\n");
    printf("Programadores :\nMiguel Guevara CI 25 693 142, Rover Gonzales CI 25 744 442\n");
    printf("Profesor: Andres Lillo");
    printf("\nProgramacion 2\n\n");
    system("PAUSE");
}
Auto_t *crearNodo()
{
    Auto_t *p;
    p = (Auto_t *)malloc(sizeof(Auto_t));
    p -> AutoProximo = NULL;
    p -> Identificador = 0;
    p -> TarjetaDeCredito = false;
    p -> TarjetaDeDebito = false;
    p -> Efectivo = false;
    p -> LavadoYAspirado = false;
    p -> CambioDeAceite = false;
    p -> LavadoDeMotorOChasis = false;
    p -> CarroPequeno = false;
    p -> CarroMediano = false;
    p -> CarroGrande = false;
    p -> CodigoDeVehiculo = 0;
    p -> CodigoColorDeVehiculo = 0;
    p -> tLlave_Inicio = 0;
    p -> tLlave_Transcurrido = 0;
    p -> Llaves = false;
    p -> LlaveOn = false;
    strcpy(p -> ServicioAnterior, " ");
    p -> OrdenDeBorrado1 = false;
    p -> OrdenDeBorrado2 = false;
    p -> OrdenDeBorrado3 = false;
    p -> OrdenDeEstacion = false;
    return p;
}
//DE ESTACIONAMIENTO -----> SALIDA
void DesdeEstacionamientoHaciaSalida(Puesto_t puesto)
{
    int x = 0,y = 0 ,i=0;
    
    x = 16;y = 54;
    while (!i)
    {
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),puesto.CodigoColorDeVehiculo);
        gotoxy(y, x++);
        printf("%c", puesto.CodigoDeVehiculo);
        fflush(stdin);
        Sleep(200);
        gotoxy(y, x - 1);

        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),0);
        printf("%c", 2);
        
        if (x >= 75)
        {
            i = 1;
        }
    }
}
void eliminaPorCompletoUnaCola(ColaDeAutos_t *primero)
{
    ColaDeAutos_t *aux;
    while (primero)
    {
        aux = primero;
        primero = primero -> AutoProximo;
        free (aux);
    }
}
void eliminarDeLaLista(Auto_t * &autoABorrar, short Identificador)
{
    Auto_t *autoProximo, *autoAnterior;
    if (!autoABorrar)
        return;
    if (autoABorrar -> Identificador == Identificador)
    {    
        autoProximo = autoABorrar;
        autoABorrar = autoABorrar -> AutoProximo;
        free (autoProximo);
        return;
    }
    autoAnterior = autoABorrar;
    autoProximo = autoABorrar -> AutoProximo;
    while(autoProximo)
    {
        if (autoProximo -> Identificador == Identificador)
        {
            autoAnterior -> AutoProximo = autoProximo -> AutoProximo;
            free(autoProximo);
            return;
        }
        autoAnterior = autoProximo;
        autoProximo = autoProximo -> AutoProximo;
    }
    return;
}
bool estacionamientoVacio(Estacionamiento_t *estacionamiento)
{
    if (estacionamiento -> Tope == -1)
        return true;
    else
        return false;
}
bool estacionamientoLleno(Estacionamiento_t *estacionamiento)
{
    if (estacionamiento -> Tope == MaxEstacionamiento - 1)
        return true;
    else
        return false;
}
void estacionarAutos(Estacionamiento_t *estacionamiento, short identificador, int codigoAuto, int codigoColorAuto)
{
    if (!estacionamientoLleno(estacionamiento))
    {
        estacionamiento -> Tope++;
        estacionamiento -> Puestos[estacionamiento -> Tope].Identificador = identificador;
        estacionamiento -> Puestos [estacionamiento -> Tope].CodigoDeVehiculo = codigoAuto;
        estacionamiento -> Puestos [estacionamiento -> Tope].CodigoColorDeVehiculo = codigoColorAuto;
    }
}
void entregarAuto(Estacionamiento_t *estacionamiento, short identificador)
{
    Estacionamiento_t estacionamientoAux, *pEstacionamientoAux = NULL;
    pEstacionamientoAux = &estacionamientoAux;
    Puesto_t aux, aux2;
    aux.Identificador = 0;
    aux.CodigoColorDeVehiculo = 0;
    aux.CodigoDeVehiculo = 0;
    aux2.Identificador = 0;
    aux2.CodigoColorDeVehiculo = 0;
    aux2.CodigoDeVehiculo = 0;
    if (verSiIDEstaEnEstacionamiento(estacionamiento->Puestos, identificador))
    {
        iniciarEstacionamiento (pEstacionamientoAux);
        actualizarEstacionamiento (estacionamiento); 
        while (!estacionamientoVacio(estacionamiento))
        {
            if (estacionamiento -> Puestos [estacionamiento -> Tope].Identificador == identificador)
            {

                aux2.Identificador = estacionamiento -> Puestos [estacionamiento -> Tope].Identificador;
                aux2.CodigoColorDeVehiculo = estacionamiento -> Puestos [estacionamiento -> Tope].CodigoColorDeVehiculo;
                aux2.CodigoDeVehiculo = estacionamiento -> Puestos [estacionamiento -> Tope].CodigoDeVehiculo;
                estacionamiento -> Puestos [estacionamiento -> Tope].Identificador = -1;
                estacionamiento -> Puestos [estacionamiento -> Tope].CodigoColorDeVehiculo = 0;
                estacionamiento -> Puestos [estacionamiento -> Tope].CodigoDeVehiculo = 0;
                estacionamiento -> Tope--;
                break;
            }
            aux.Identificador = estacionamiento -> Puestos [estacionamiento -> Tope].Identificador;
            aux.CodigoColorDeVehiculo = estacionamiento -> Puestos [estacionamiento -> Tope].CodigoColorDeVehiculo;
            aux.CodigoDeVehiculo = estacionamiento -> Puestos [estacionamiento -> Tope].CodigoDeVehiculo;
            estacionamiento -> Puestos [estacionamiento -> Tope].Identificador = -1;
            estacionamiento -> Puestos [estacionamiento -> Tope].CodigoColorDeVehiculo = 0;
            estacionamiento -> Puestos [estacionamiento -> Tope].CodigoDeVehiculo = 0;
            estacionamiento -> Tope--;
            estacionarAutos (pEstacionamientoAux, aux.Identificador, aux.CodigoDeVehiculo, aux.CodigoColorDeVehiculo);
        }
        actualizarEstacionamiento (estacionamiento);
        Sleep(600);
        animSacarAutos(pEstacionamientoAux, aux2);
        while (!estacionamientoVacio(pEstacionamientoAux))
        {
            aux.Identificador = pEstacionamientoAux -> Puestos [pEstacionamientoAux -> Tope].Identificador;
            aux.CodigoColorDeVehiculo = pEstacionamientoAux -> Puestos [pEstacionamientoAux -> Tope].CodigoColorDeVehiculo;
            aux.CodigoDeVehiculo = pEstacionamientoAux -> Puestos [pEstacionamientoAux -> Tope].CodigoDeVehiculo;
            pEstacionamientoAux -> Tope--;
            estacionarAutos (estacionamiento, aux.Identificador, aux.CodigoDeVehiculo, aux.CodigoColorDeVehiculo);
        }
        
        actualizarEstacionamiento (estacionamiento);
    }
}
bool finalizaCicloEnEstacion3o2(short *estacion, time_t *tiempoTranscurrido, time_t *tiempoInicial, short *identificador)
{
    bool result = false;
    (*tiempoTranscurrido) = time(NULL) - (*tiempoInicial);
            
    if (*tiempoTranscurrido >= 30)
    {
        *tiempoTranscurrido = 0;
        *estacion = 0; 
        *tiempoInicial = 0;
        *identificador = 0;
        result = true;          
    }
    return result;
}
void gotoxy(int fila,int col)
{
    HANDLE hConsoleOutput;
    COORD d;
    hConsoleOutput = GetStdHandle (STD_OUTPUT_HANDLE);
    d.X=col; d.Y=fila;
    SetConsoleCursorPosition (hConsoleOutput, d);
}
void iniciarSimulacion()
{
    short generadorDeIdentificadores = 0;
    //Estructura de la lista.
    Auto_t *autoAux = NULL, *autoActual = NULL;
    //Nodo centinela de control.
    ControlDeAutos_t controlDeAutos;
    //Variables que controlaran cada cuanto tiempo entra un auto al autolavado.
    time_t controladorPasoDeClientesInicio = 0, controladorPasoDeClientesTranscurrido = 0;
    Estaciones_t estacionesDeLavadoYAspirado[4];//Vector que contiene los estados en que se encuentran las estaciones de lavado y aspirado.
    Estaciones_t estacionDeCambioDeAceite;//Dato que contiene el estado de la estacion de cambio de aceite.
    Estaciones_t estacionDeLavadoDeMotorOChasis;//Dato que contiene el estado de la estacion lavado de motor o chasis.
    ColaDeAutos_t *autoPrimero_Cola1 = NULL, *autoUltimo_Cola1 = NULL;
    ColaDeAutos_t *autoPrimero_Cola2 = NULL, *autoUltimo_Cola2 = NULL;
    ColaDeAutos_t *autoPrimero_Cola3 = NULL, *autoUltimo_Cola3 = NULL;

    Estacionamiento_t estacionamiento, *pEstacionamiento = NULL;

    pEstacionamiento = &estacionamiento;
    //Inicializacion de variables de lavado y aspirado.
    estacionesDeLavadoYAspirado[0].TiempoTranscurrido = 0;
    estacionesDeLavadoYAspirado[0].TiempoInicial = 0;
    estacionesDeLavadoYAspirado[0].EstadoDeEstacion = 0;
    estacionesDeLavadoYAspirado[0].Identificador = 0;
    
    estacionesDeLavadoYAspirado[1].TiempoTranscurrido = 0;
    estacionesDeLavadoYAspirado[1].TiempoInicial = 0;
    estacionesDeLavadoYAspirado[1].EstadoDeEstacion = 0;
    estacionesDeLavadoYAspirado[1].Identificador = 0;

    estacionesDeLavadoYAspirado[2].TiempoTranscurrido = 0;
    estacionesDeLavadoYAspirado[2].TiempoInicial = 0;
    estacionesDeLavadoYAspirado[2].EstadoDeEstacion = 0;
    estacionesDeLavadoYAspirado[2].Identificador = 0;

    estacionesDeLavadoYAspirado[3].TiempoTranscurrido = 0;
    estacionesDeLavadoYAspirado[3].TiempoInicial = 0;
    estacionesDeLavadoYAspirado[3].EstadoDeEstacion = 0;
    estacionesDeLavadoYAspirado[3].Identificador = 0;
    //Inicializacion de variables de cambio de aceite.  
    estacionDeCambioDeAceite.EstadoDeEstacion = 0;
    estacionDeCambioDeAceite.Identificador = 0;
    estacionDeCambioDeAceite.TiempoInicial = 0;
    estacionDeCambioDeAceite.TiempoTranscurrido = 0;
    //Inicializacion de variables de lavado de motor o chasis.
    estacionDeLavadoDeMotorOChasis.EstadoDeEstacion = 0;
    estacionDeLavadoDeMotorOChasis.Identificador = 0;
    estacionDeLavadoDeMotorOChasis.TiempoInicial = 0;
    estacionDeLavadoDeMotorOChasis.TiempoTranscurrido = 0;
    
    //Inicializando nodo de control.
    controlDeAutos.TotalTD = 0;
    controlDeAutos.TotalTC = 0;
    controlDeAutos.TotalEF = 0;
    controlDeAutos.PagoTC = 0;
    controlDeAutos.PagoTD = 0;
    controlDeAutos.PagoEF = 0;
    controlDeAutos.PersonasLYA = 0;
    controlDeAutos.PersonasCA = 0;
    controlDeAutos.PersonasLMC = 0;
    controlDeAutos.TotalClientes = 0;
    controladorPasoDeClientesInicio = time(NULL);
    controlDeAutos.AutoSiguiente = NULL;
    iniciarEstacionamiento (pEstacionamiento);
    
    do
    {
        controladorPasoDeClientesTranscurrido = time(NULL) - controladorPasoDeClientesInicio;
        if (controladorPasoDeClientesTranscurrido % 20 == 0)
        {
            generadorDeIdentificadores++;
            controlDeAutos.TotalClientes++;
            autoActual = agregarNuevoAutoAlLocal(controlDeAutos.AutoSiguiente, generadorDeIdentificadores);
            autoAux = controlDeAutos.AutoSiguiente;

            if (autoActual -> TarjetaDeDebito)
            {
                controlDeAutos.PagoTD++;
                if(autoActual -> LavadoYAspirado)
                {
                    if(autoActual -> CarroPequeno)
                        controlDeAutos.TotalTD += 50;
                    else
                    {
                        if(autoActual -> CarroMediano)
                            controlDeAutos.TotalTD += 70;
                        else
                            controlDeAutos.TotalTD += 100;
                    }
                }
                if(autoActual -> CambioDeAceite)
                {
                    if(autoActual -> CarroPequeno)
                        controlDeAutos.TotalTD += 80;
                    else
                    {
                        if(autoActual -> CarroMediano)
                            controlDeAutos.TotalTD += 100;
                        else
                            controlDeAutos.TotalTD += 120;
                    }   
                }
                if(autoActual -> LavadoDeMotorOChasis)
                {
                    if(autoActual -> CarroPequeno)
                        controlDeAutos.TotalTD += 120;
                    else
                    {
                        if(autoActual -> CarroMediano)
                            controlDeAutos.TotalTD += 150;
                        else
                            controlDeAutos.TotalTD += 200;
                    }
                }
                    
            }
            else
            {
                if (autoActual -> TarjetaDeCredito)
                {
                    controlDeAutos.PagoTC++;
                    if(autoActual -> LavadoYAspirado)
                    {
                        if(autoActual -> CarroPequeno)
                            controlDeAutos.TotalTC += 50;
                        else
                        {
                            if(autoActual -> CarroMediano)
                                controlDeAutos.TotalTC += 70;
                            else
                                controlDeAutos.TotalTC += 100;
                        }   
                    }
                    if(autoActual -> CambioDeAceite)
                    {
                        if(autoActual -> CarroPequeno)
                            controlDeAutos.TotalTC += 80;
                        else
                        {
                            if(autoActual -> CarroMediano)
                                controlDeAutos.TotalTC += 100;
                            else
                                controlDeAutos.TotalTC += 120;
                        }   
                    }
                    if(autoActual -> LavadoDeMotorOChasis)
                    {
                        if(autoActual -> CarroPequeno)
                            controlDeAutos.TotalTC += 120;
                        else
                        {
                            if(autoActual -> CarroMediano)
                                controlDeAutos.TotalTC += 150;
                            else
                                controlDeAutos.TotalTC += 200;
                        }
                    }
                        
                }
                else
                {
                    if (autoActual -> Efectivo)
                    {
                        controlDeAutos.PagoEF++;
                        if(autoAux -> LavadoYAspirado)
                        {
                            if(autoActual -> CarroPequeno)
                                controlDeAutos.TotalEF += 50;
                            else
                            {
                                if(autoActual -> CarroMediano)
                                    controlDeAutos.TotalEF += 70;
                                else
                                    controlDeAutos.TotalEF += 100;
                            }   
                        }
                        if(autoActual -> CambioDeAceite)
                        {
                            if(autoActual -> CarroPequeno)
                                controlDeAutos.TotalEF += 80;
                            else
                            {
                                if(autoActual -> CarroMediano)
                                    controlDeAutos.TotalEF += 100;
                                else
                                    controlDeAutos.TotalEF += 120;
                            }   
                        }
                        if(autoActual -> LavadoDeMotorOChasis)
                        {
                            if(autoActual -> CarroPequeno)
                                controlDeAutos.TotalEF += 120;
                            else
                            {
                                if(autoActual -> CarroMediano)
                                    controlDeAutos.TotalEF += 150;
                                else
                                    controlDeAutos.TotalEF += 200;
                            }
                        }
                    }
                }
            }
            if (autoActual -> Llaves)
            {
                autoActual -> tLlave_Inicio = time(NULL);
                autoActual -> tLlave_Transcurrido = time(NULL) - autoActual -> tLlave_Inicio;
            }
            if ((autoActual -> LavadoYAspirado)&& (autoActual -> OrdenDeEstacion))
            {
                
                autoUltimo_Cola1 = agregarNuevoAutoACola(autoPrimero_Cola1, autoActual -> Identificador, autoActual -> CodigoColorDeVehiculo, autoActual -> CodigoDeVehiculo);
               
                autoActual -> OrdenDeEstacion = false;
                autoActual -> LavadoYAspirado = false;
                
                (controlDeAutos.PersonasLYA)++;
                strcpy(autoActual -> ServicioAnterior, "LYA");
                animacionDesdeEntradaHaciaColaLavadoYAspirado(numeroDeAutosEnCola(autoPrimero_Cola1), autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                actualizarCola1(autoPrimero_Cola1);
                if ((verificarSiHayEstacionDeLavadoLibre(estacionesDeLavadoYAspirado)) && (autoActual -> Identificador == autoPrimero_Cola1 -> Identificador))
                {
                    //poner primer elemento de la cola en la estacion y eliminarlo de la cola
                    if (!colaVacia(autoPrimero_Cola1))
                    {
                        borrarPrimerAutoDeLaCola(autoPrimero_Cola1);
                    }
                    actualizarCola1(autoPrimero_Cola1);
                    switch (ponerAutoEnAlgunaEstacionLibreDeLavadoYAspirado(estacionesDeLavadoYAspirado, autoActual -> Identificador))
                    {
                        case 1:
                            animHaciaEstacion1LavadoYAspirado(autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                            break;
                        case 2:
                            animHaciaEstacion2LavadoYAspirado(autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                            break;
                        case 3:
                            animHaciaEstacion3LavadoYAspirado(autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                            break;
                        case 4:
                            animHaciaEstacion4LavadoYAspirado(autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                            break;
                    }
                }
            }
            else
            {
                if ((autoActual -> CambioDeAceite) && (autoActual -> OrdenDeEstacion))
                {
                    
                    autoUltimo_Cola2 = agregarNuevoAutoACola(autoPrimero_Cola2, autoActual -> Identificador, autoActual -> CodigoColorDeVehiculo, autoActual -> CodigoDeVehiculo); 


                    autoActual -> OrdenDeEstacion = false;
                    autoActual -> CambioDeAceite = false;
                    (controlDeAutos.PersonasCA)++;
                    strcpy(autoActual -> ServicioAnterior, "CA");
                    animacionDesdeEntradaHaciaColaCambioDeAceite(numeroDeAutosEnCola(autoPrimero_Cola2), autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                    actualizarCola2(autoPrimero_Cola2);
                    if ((estacionDeCambioDeAceite.EstadoDeEstacion == 0) && (autoActual -> Identificador == autoPrimero_Cola2 -> Identificador))
                    {
                        
                        if(!colaVacia(autoPrimero_Cola2))
                            
                        {
                            borrarPrimerAutoDeLaCola(autoPrimero_Cola2);
                        }
                        actualizarCola2(autoPrimero_Cola2);
                        estacionDeCambioDeAceite.EstadoDeEstacion = 1;
                        estacionDeCambioDeAceite.Identificador = autoActual -> Identificador;
                        animColaCambioAceite(autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                        estacionDeCambioDeAceite.TiempoInicial = time(NULL);
                    }
                }
                else
                {
                    if ((autoActual -> LavadoDeMotorOChasis) && (autoActual -> OrdenDeEstacion))
                    {
                        
                        autoUltimo_Cola3 = agregarNuevoAutoACola(autoPrimero_Cola3, autoActual -> Identificador, autoActual -> CodigoColorDeVehiculo, autoActual -> CodigoDeVehiculo); 

                        autoActual -> OrdenDeEstacion = false;
                        autoActual -> LavadoDeMotorOChasis = false;
                        (controlDeAutos.PersonasLMC)++;
                        strcpy(autoActual -> ServicioAnterior, "MOC");
                        animacionDesdeEntradaHaciaColaLavadoDeMotor(numeroDeAutosEnCola(autoPrimero_Cola3), autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                        actualizarCola3(autoPrimero_Cola3);
                        if ((estacionDeLavadoDeMotorOChasis.EstadoDeEstacion == 0) && (autoActual -> Identificador == autoPrimero_Cola3 -> Identificador))
                        {
                            if(!colaVacia(autoPrimero_Cola3))
                                borrarPrimerAutoDeLaCola(autoPrimero_Cola3);
                            actualizarCola3(autoPrimero_Cola3);
                            estacionDeLavadoDeMotorOChasis.EstadoDeEstacion = 1;
                            estacionDeLavadoDeMotorOChasis.Identificador = autoActual -> Identificador;
                            animColaLavadoMotor(autoActual -> CodigoDeVehiculo, autoActual -> CodigoColorDeVehiculo);
                            estacionDeLavadoDeMotorOChasis.TiempoInicial = time(NULL);
                        }
                    }
                }
            }
        }
        autoAux = controlDeAutos.AutoSiguiente;
        while(autoAux)
        {
            if((autoEnCola (autoPrimero_Cola1, autoAux -> Identificador)) || (autoEnCola (autoPrimero_Cola2, autoAux -> Identificador)) || (autoEnCola (autoPrimero_Cola3, autoAux -> Identificador)))
            {
                if (autoPrimero_Cola1)
                {
                    if ((verificarSiHayEstacionDeLavadoLibre(estacionesDeLavadoYAspirado)) && (autoAux -> Identificador == autoPrimero_Cola1 -> Identificador))
                    {
                        //poner primer elemento de la cola en la estacion y eliminarlo de la cola
                        if (!colaVacia(autoPrimero_Cola1))
                        {
                            borrarPrimerAutoDeLaCola(autoPrimero_Cola1);
                        }
                        actualizarCola1(autoPrimero_Cola1);
                        switch (ponerAutoEnAlgunaEstacionLibreDeLavadoYAspirado(estacionesDeLavadoYAspirado, autoAux -> Identificador))
                        {
                            case 1:
                                animHaciaEstacion1LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                            case 2:
                                animHaciaEstacion2LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                            case 3:
                                animHaciaEstacion3LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                            case 4:
                                animHaciaEstacion4LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                        }
                    }
                }
                if (autoPrimero_Cola2)
                {
                    if ((estacionDeCambioDeAceite.EstadoDeEstacion == 0) && (autoAux -> Identificador == autoPrimero_Cola2 -> Identificador))
                    {
                            
                        if(!colaVacia(autoPrimero_Cola2))
                            borrarPrimerAutoDeLaCola(autoPrimero_Cola2);
                        estacionDeCambioDeAceite.EstadoDeEstacion = 1;
                        estacionDeCambioDeAceite.Identificador = autoAux -> Identificador;
                        actualizarCola2(autoPrimero_Cola2);
                        animColaCambioAceite(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                        estacionDeCambioDeAceite.TiempoInicial = time(NULL);
                    } 
                }
                if (autoPrimero_Cola3)
                {
                    if ((estacionDeLavadoDeMotorOChasis.EstadoDeEstacion == 0) && (autoAux -> Identificador == autoPrimero_Cola3 -> Identificador))
                    {
                        if(!colaVacia(autoPrimero_Cola3))
                            borrarPrimerAutoDeLaCola(autoPrimero_Cola3);
                        estacionDeLavadoDeMotorOChasis.EstadoDeEstacion = 1;
                        estacionDeLavadoDeMotorOChasis.Identificador = autoAux -> Identificador;
                        actualizarCola3(autoPrimero_Cola3);
                        animColaLavadoMotor(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                        estacionDeLavadoDeMotorOChasis.TiempoInicial = time(NULL);
                    }
                }
            }  
            else
            {
                if ((autoAux -> LavadoYAspirado)&& (autoAux -> OrdenDeEstacion))
                {
                
                    autoUltimo_Cola1 = agregarNuevoAutoACola(autoPrimero_Cola1, autoAux -> Identificador, autoAux -> CodigoColorDeVehiculo, autoAux -> CodigoDeVehiculo);
               
                    autoAux -> OrdenDeEstacion = false;
                    autoAux -> LavadoYAspirado = false;
                    (controlDeAutos.PersonasLYA)++;

                    
                    if (strcmp(autoAux -> ServicioAnterior, "CA") == 0)
                    {
                        //Animacion de Lav y Asp a Cambio de Aceite.
                        strcpy(autoAux -> ServicioAnterior, "LYA");
                        animacionDesdeCambioDeAceiteHaciaColaLavadoYAspirado(numeroDeAutosEnCola(autoPrimero_Cola1), autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                    }
                    else
                    {
                        if (strcmp(autoAux -> ServicioAnterior, "MOC") == 0)
                        {
                            //Animacion de Lav y Asp a Motor o Chasis.
                            strcpy(autoAux -> ServicioAnterior, "LYA");
                            animacionDesdeLavadoMotorHaciaColaLavadoYAspirado(numeroDeAutosEnCola(autoPrimero_Cola1), autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                        }
                    }
                    actualizarCola1(autoPrimero_Cola1);
                    if ((verificarSiHayEstacionDeLavadoLibre(estacionesDeLavadoYAspirado)) && (autoAux -> Identificador == autoPrimero_Cola1 -> Identificador))
                    {
                        //poner primer elemento de la cola en la estacion y eliminarlo de la cola
                        if (!colaVacia(autoPrimero_Cola1))
                        {
                            borrarPrimerAutoDeLaCola(autoPrimero_Cola1);
                        }
                        actualizarCola1(autoPrimero_Cola1);
                        switch (ponerAutoEnAlgunaEstacionLibreDeLavadoYAspirado(estacionesDeLavadoYAspirado, autoAux -> Identificador))
                        {
                            case 1:
                                animHaciaEstacion1LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                            case 2:
                                animHaciaEstacion2LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                            case 3:
                                animHaciaEstacion3LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                            case 4:
                                animHaciaEstacion4LavadoYAspirado(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                break;
                        }
                    }
                }
                else
                {
                    if ((autoAux -> CambioDeAceite) && (autoAux -> OrdenDeEstacion))
                    {
                    
                        autoUltimo_Cola2 = agregarNuevoAutoACola(autoPrimero_Cola2, autoAux -> Identificador, autoAux -> CodigoColorDeVehiculo, autoAux -> CodigoDeVehiculo);


                        autoAux -> OrdenDeEstacion = false;
                        autoAux -> CambioDeAceite = false;
                        (controlDeAutos.PersonasCA)++;
                        if (strcmp(autoAux -> ServicioAnterior, "LYA") == 0)
                        {
                            //Animacion de CA a LYA.
                            strcpy(autoAux -> ServicioAnterior, "CA");
                            animacionDesdeLavadoYAspiradoHaciaColaCambioDeAceite(numeroDeAutosEnCola(autoPrimero_Cola2), autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                            
                        }
                        else
                        {
                            if (strcmp(autoAux -> ServicioAnterior, "MOC") == 0)
                            {
                                //Animacion de CA a MOC
                                strcpy(autoAux -> ServicioAnterior, "CA");
                                animacionDesdeLavadoMotorHaciaColaCambioDeAceite(numeroDeAutosEnCola(autoPrimero_Cola2), autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                            }
                        }
                        actualizarCola2(autoPrimero_Cola2);
                        if ((estacionDeCambioDeAceite.EstadoDeEstacion == 0) && (autoAux -> Identificador == autoPrimero_Cola2 -> Identificador))
                        {
                        
                            if (!colaVacia(autoPrimero_Cola2))
                                borrarPrimerAutoDeLaCola(autoPrimero_Cola2);
                
                            estacionDeCambioDeAceite.EstadoDeEstacion = 1;
                            estacionDeCambioDeAceite.Identificador = autoAux -> Identificador;
                            actualizarCola2(autoPrimero_Cola2);
                            animColaCambioAceite(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                            estacionDeCambioDeAceite.TiempoInicial = time(NULL);
                        }
                    }
                    else
                    {
                        if ((autoAux -> LavadoDeMotorOChasis) && (autoAux -> OrdenDeEstacion))
                        {
                            autoUltimo_Cola3 = agregarNuevoAutoACola(autoPrimero_Cola3, autoAux -> Identificador, autoAux -> CodigoColorDeVehiculo, autoAux -> CodigoDeVehiculo);

                            autoAux -> OrdenDeEstacion = false;
                            autoAux -> LavadoDeMotorOChasis = false;
                            (controlDeAutos.PersonasLMC)++;
                            if (strcmp(autoAux -> ServicioAnterior, "LYA") == 0)
                            {
                                //Animacion de Lavado de motor o chasis hacia Lavado y aspirado.
                                strcpy(autoAux -> ServicioAnterior, "MOC");
                                animacionDesdeLavadoYAspiradoHaciaColaLavadoDeMotor(numeroDeAutosEnCola(autoPrimero_Cola3), autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                            }
                            else
                            {
                                if (strcmp(autoAux -> ServicioAnterior, "CA") == 0)
                                {
                                    //Animacion de Lavado de motor o chasis hacia Cambio de aceite.
                                    strcpy(autoAux -> ServicioAnterior, "MOC");
                                    animacionDesdeCambioDeAceiteHaciaColaLavadoMotor(numeroDeAutosEnCola(autoPrimero_Cola3), autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                    
                                }
                            }
                            actualizarCola3(autoPrimero_Cola3);
                            if ((estacionDeLavadoDeMotorOChasis.EstadoDeEstacion == 0) && (autoAux -> Identificador == autoPrimero_Cola3 -> Identificador))
                            {
                                if(!colaVacia(autoPrimero_Cola3))
                                    borrarPrimerAutoDeLaCola(autoPrimero_Cola3);

                                estacionDeLavadoDeMotorOChasis.EstadoDeEstacion = 1;
                                estacionDeLavadoDeMotorOChasis.Identificador = autoAux -> Identificador;
                                actualizarCola3(autoPrimero_Cola3);
                                animColaLavadoMotor(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                                estacionDeLavadoDeMotorOChasis.TiempoInicial = time(NULL);
                            }
                        }
                    }
                }
            } 

            
            calcularTiempoDeLavadoEnEstaciones(estacionesDeLavadoYAspirado);
            if (verificaTiempoDeEstaciones(estacionesDeLavadoYAspirado, autoAux -> Identificador))
            {
                autoAux -> OrdenDeBorrado1 = true;
                autoAux -> OrdenDeEstacion = true;
            }
            if ((estacionDeCambioDeAceite.EstadoDeEstacion == 1) && (estacionDeCambioDeAceite.Identificador == autoAux -> Identificador))
            {
                if (finalizaCicloEnEstacion3o2(&estacionDeCambioDeAceite.EstadoDeEstacion, &estacionDeCambioDeAceite.TiempoTranscurrido, &estacionDeCambioDeAceite.TiempoInicial, &estacionDeCambioDeAceite.Identificador))
                {  
                    autoAux -> OrdenDeBorrado2 = true;
                    autoAux -> OrdenDeEstacion = true;
                    gotoxy (13, 76);
                    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
                    printf("%c", 219);
                }
            }
            
            if ((estacionDeLavadoDeMotorOChasis.EstadoDeEstacion == 1) && (estacionDeLavadoDeMotorOChasis.Identificador == autoAux -> Identificador))
            {
                if (finalizaCicloEnEstacion3o2(&estacionDeLavadoDeMotorOChasis.EstadoDeEstacion, &estacionDeLavadoDeMotorOChasis.TiempoTranscurrido, &estacionDeLavadoDeMotorOChasis.TiempoInicial, &estacionDeLavadoDeMotorOChasis.Identificador))
                {
                    autoAux -> OrdenDeBorrado3 = true;
                    autoAux -> OrdenDeEstacion = true;
                    gotoxy (30, 73);
                    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
                    printf("%c", 219);
                }
            }
            

            // veriicar si cumplio lo de las estaciones, sino eliminar
            //if ((!autoAux -> LavadoYAspirado) && (!autoAux -> CambioDeAceite) && (!autoAux -> LavadoDeMotorOChasis) && (autoAux -> OrdenDeBorrado1) && (autoAux -> OrdenDeBorrado2) && (autoAux -> OrdenDeBorrado3) && (!autoAux -> LlaveOn))
            if ((!autoAux -> LavadoYAspirado) && (!autoAux -> CambioDeAceite) && (!autoAux -> LavadoDeMotorOChasis) && (autoAux -> OrdenDeBorrado1) && (autoAux -> OrdenDeBorrado2) && (autoAux -> OrdenDeBorrado3) && (!autoAux -> Llaves))
            {
                //if(autoAux == controlDeAutos.AutoSiguiente -> AutoProximo)
                if (strcmp(autoAux -> ServicioAnterior, "LYA") == 0)
                    animacionDesdeLavadoYAspiradoHaciaSalida(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                else
                {
                    if (strcmp(autoAux -> ServicioAnterior, "CA") == 0)
                        animacionDesdeCambioDeAceiteHaciaSalida(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                    else
                    {
                        if (strcmp(autoAux -> ServicioAnterior, "MOC") == 0)
                            animacionDesdeLavadoMotorHaciaSalida(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                         
                    }
                }

                eliminarDeLaLista(controlDeAutos.AutoSiguiente, autoAux -> Identificador);
                
            }   
            else
            {
                if ((!autoAux -> LavadoYAspirado) && (!autoAux -> CambioDeAceite) && (!autoAux -> LavadoDeMotorOChasis) && (autoAux -> OrdenDeBorrado1) && (autoAux -> OrdenDeBorrado2) && (autoAux -> OrdenDeBorrado3) && (autoAux -> Llaves) && (autoAux -> LlaveOn))
                {
                    autoAux -> LlaveOn = false;
                    //Estacionar.
                    if (strcmp(autoAux -> ServicioAnterior, "LYA") == 0)
                        animacionDesdeLavadoYAspiradoHaciaEstacionamiento(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                    else
                    {
                        if (strcmp(autoAux -> ServicioAnterior, "CA") == 0)
                            animacionDesdeCambioDeAceiteHaciaEstacionamiento(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                        else 
                        {
                            if (strcmp(autoAux -> ServicioAnterior, "MOC") == 0)
                                animacionDesdeLavadoDeMotorHaciaEstacionamiento(autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                        }
                    }
                    estacionarAutos (pEstacionamiento, autoAux -> Identificador, autoAux -> CodigoDeVehiculo, autoAux -> CodigoColorDeVehiculo);
                    actualizarEstacionamiento (pEstacionamiento);
                    Sleep(600);
                }
                if ((autoAux -> Llaves) && (!autoAux -> LlaveOn))
                {
                    autoAux -> tLlave_Transcurrido = time(NULL) - autoAux -> tLlave_Inicio;
                    if (autoAux -> tLlave_Transcurrido >= 180)
                    {
                        //Dar a cliente
                        entregarAuto (pEstacionamiento, autoAux -> Identificador);
                        actualizarEstacionamiento (pEstacionamiento);
                        eliminarDeLaLista(controlDeAutos.AutoSiguiente, autoAux -> Identificador);
                    }
                }
            }
            autoAux = autoAux -> AutoProximo;
        }
    }while(!FINISHANIMATION);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("\n __________ESTADISTICAS GLOBALES__________");
    printf("\n\n   NUMERO DE CLIENTES EN TOTAL: %d", controlDeAutos.TotalClientes);
    printf("\n\n   NUMERO DE PERSONAS QUE USARON EL SERVICIO DE LAVADO Y ASPIRADO: %d", controlDeAutos.PersonasLYA);
    printf("\n   NUMERO DE PERSONAS QUE USARON EL SERVICIO DE CAMBIO DE ACEITE: %d", controlDeAutos.PersonasCA);
    printf("\n   NUMERO DE PERSONAS QUE USARON EL SERVICIO DE LAVADO DE MOTOR O CHASIS: %d\n", controlDeAutos.PersonasLMC);
    printf("\n\n   NUMERO DE PERSONAS QUE PAGARON CON TARJETA DE DEBITO: %d", controlDeAutos.PagoTD);
    printf("\n     INGRESOS CON TARJETA DE DEBITO: %d", controlDeAutos.TotalTD);
    printf("\n\n   NUMERO DE PERSONAS QUE PAGARON CON TARJETA DE CREDITO: %d", controlDeAutos.PagoTC);
    printf("\n     INGRESOS CON TARJETA DE CREDITO: %d", controlDeAutos.TotalTC);
    printf("\n\n   NUMERO DE PERSONAS QUE PAGARON EN EFECTIVO: %d", controlDeAutos.PagoEF);
    printf("\n     INGRESOS EN EFECTIVO: %d", controlDeAutos.TotalEF);
    printf("\n\n\n INGRESOS TOTALES DEL DIA: %d\n\n   ", controlDeAutos.TotalTC + controlDeAutos.TotalTD + controlDeAutos.TotalEF);
    system("PAUSE");
    borrarLista(controlDeAutos.AutoSiguiente);
    eliminaPorCompletoUnaCola(autoPrimero_Cola1);
    eliminaPorCompletoUnaCola(autoPrimero_Cola2);
    eliminaPorCompletoUnaCola(autoPrimero_Cola3);
}
void iniciarEstacionamiento(Estacionamiento_t *estacionamiento)
{
    estacionamiento -> Tope = -1;
    for (int i = 0; i < MaxEstacionamiento; i++)
    {
        estacionamiento -> Puestos [i].Identificador = -1;
        estacionamiento -> Puestos [i].CodigoDeVehiculo = 0;
        estacionamiento -> Puestos [i].CodigoColorDeVehiculo = 0;
    }
}
void menu()
{
    SetConsoleTitleA("Simulacion de Autolavado.");
    gotoxy(6, 0);printf("  ____   _   _  _____   _____     _      ____    _   _    ____    __    _____ ");
    gotoxy(7, 0);printf(" /    \\ | | | ||__ __| |     |   | |    /    \\  | | | |  /    \\  |  \\  |  _  |");
    gotoxy(8, 0);printf("|  __  || | | |  | |   | | | | _ | |   |  __  | | | | | |  __  | |   | | | | |");
    gotoxy(9, 0);printf("| |__| || | | |  | |   | | | ||_|| |   | |__| | | | | | | |__| | |   | | | | |");
    gotoxy(10, 0);printf("|  __  || |_| |  | |   | |_| |   | |__ |  __  | | |_| | |  __  | |   | | |_| |");
    gotoxy(11, 0);printf("|_|  |_||_____|  |_|   |_____|   |____||_|  |_|  \\___/  |_|  |_| |__/  |_____|");


    gotoxy(40, 10);printf(" _       _    ____    _____  _   _    _   _   _     ____  _____");
    gotoxy(41, 10);printf("| |     | |  / __ \\  | |__  | |_| |  | | | | | | | |     | ____|");
    gotoxy(42, 10);printf("| |  _  | | | |__| | |__  | |  _  |  | | | | | | | |___  | |  __");
    gotoxy(43, 10);printf("| |_| |_| | |  __  |  __| | | | | |  | |_| | | | | |     | |__| |");
    gotoxy(44, 10);printf("|_________| |_|  |_| |____| |_| |_|  |_____| | |_/ |____ |______|");
    gotoxy(20, 16);printf("Carros: Grandes %c, Medianos %c y Pequenios %c.", 219, 220, 254);
    gotoxy(0, 0);
    gotoxy(25, 10);printf("Ingrese tiempo que durara la animacion: (Segundos)");
    gotoxy(27, 19);fflush(stdin);scanf("%d", &TIEMPODESIMULACION);

    gotoxy(30, 15);system("PAUSE"); 
    system("cls");
}
ColaDeAutos_t *nuevoAutoACola()
{
    ColaDeAutos_t *nuevo = (ColaDeAutos_t *)malloc(sizeof(ColaDeAutos_t));
    nuevo -> AutoProximo = NULL;
    nuevo -> CodigoColorDeVehiculo = 0;
    nuevo -> CodigoDeVehiculo = 0;
    nuevo -> Identificador = 0;
    return nuevo;
}
int numeroDeAutosEnCola(ColaDeAutos_t *primero)
{
    int tam = 0;
    while(primero)
    {
        tam++;
        primero = primero -> AutoProximo;
    }
    return tam;
}
int numAutosEnEstacionamiento(Puesto_t puestos[5])
{
    int cont =0;
    for (int i = 0; i < MaxEstacionamiento; i++)
    {
        if (puestos[i].Identificador != -1)
            cont++;
    }
    return cont;
}
void pintarAutolavado()
{
    int i, x, y;
    //Pinta contorno
    y = 0;
    for (x = 0; x < 80; x++)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    x = 79;
    for (y = 0; y < 56; y++)
    {
        gotoxy(y, x);
        printf("%c", 124);
        Sleep(20);
    }
    y = 56;
    for (x = 79; x >= 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    x = 0;
    for (y = 55; y >= 0; y--)
    {
        gotoxy(y, x);
        printf("%c", 124);
        Sleep(20);
    }
    y = 46;
    for (x = 78; x >= 50; x--)
    {
        gotoxy(y, x);
        printf("_");
        Sleep(20);
    }
    y = 51;
    for (x = 78; x >= 53; x--)
    {
        gotoxy(y, x);
        printf("%c", 29);
        Sleep(20);
    }


    //Estacionamiento
    y = 51;
    for (x = 30; x > 15; x--)
    {
        gotoxy(y, x);
        printf("_");
        Sleep(20);
    }
    x = 16;


    for (; y > 30; y--)
    {
        gotoxy(y, x);
        printf("%c", 186);
        Sleep(20);
    }

    y = 31;
    for (x = 16; x > 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 205);
        Sleep(20);
    }
    y = 36;
    for (x = 10; x > 4; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 41;
    for (x = 10; x > 4; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 46;
    for (x = 10; x > 4; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 51;
    for (x = 10; x > 4; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }


    //Lavado y aspirado

    y = 22;
    for (x = 16; x > 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 18;
    for (x = 16; x > 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 14;
    for (x = 16; x > 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 10;
    for (x = 16; x > 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 6;
    for (x = 16; x > 0; x--)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    gotoxy(4, 18);
    Sleep(20);
    printf("o");
    gotoxy(4, 17);
    Sleep(20);
    printf("d");
    gotoxy(4, 16);
    Sleep(20);
    printf("a");
    gotoxy(4, 15);
    Sleep(20);
    printf("r");
    gotoxy(4, 14);
    Sleep(20);
    printf("i");
    gotoxy(4, 13);
    Sleep(20);
    printf("p");
    gotoxy(4, 12);
    Sleep(20);
    printf("s");
    gotoxy(4, 11);
    Sleep(20);
    printf("A");
    gotoxy(4, 9);
    Sleep(20);
    printf("y");
    gotoxy(4, 7);
    Sleep(20);
    printf("o");
    gotoxy(4, 6);
    Sleep(20);
    printf("d");
    gotoxy(4, 5);
    Sleep(20);
    printf("a");
    gotoxy(4, 4);
    Sleep(20);
    printf("v");
    gotoxy(4, 3);
    Sleep(20);
    printf("a");
    gotoxy(4, 2);
    Sleep(20);
    printf("L");
    //Sala de espera
    x = 51;
    for (y = 12; y > 0; y--)
    {
        gotoxy(y, x);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        Sleep(25);
        printf("%c", 186);
    }

    x = 28;
    for (y = 11; y > 0; y--)
    {
        gotoxy(y, x);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        Sleep(25);
        printf("%c", 186);
    }
    y = 12;

    for (x = 28; x < 52; x++)
    {
        gotoxy(y, x);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        printf("%c", 205);
        Sleep(25);
    }
    y = 0;
    for (x = 28; x < 52; x++)
    {
        gotoxy(y, x);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        Sleep(25);
        printf("%c", 205);
    }
    pintarSalaEspera();
    
    gotoxy(9,60);
    Sleep(20);
    printf("C");
    Sleep(20);
    printf("a");
    Sleep(20);
    printf("m");
    Sleep(20);
    printf("b");
    Sleep(20);
    printf("i");
    Sleep(20);
    printf("o");
    Sleep(20);
    printf(" d");
    Sleep(20);
    printf("e ");
    Sleep(20);
    printf("A");
    Sleep(20);
    printf("c");
    Sleep(20);
    printf("e");
    Sleep(20);
    printf("i");
    Sleep(20);
    printf("t");
    Sleep(20);
    printf("e");
   
    //Cambio de Aceite
    y = 12;
    for (x = 67; x < 79; x++)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 16;
    for (x = 67; x < 79; x++)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }

    //Lavado de Motor
    y = 28;
    for (x = 67; x < 79; x++)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }
    y = 32;
    for (x = 67; x < 79; x++)
    {
        gotoxy(y, x);
        printf("%c", 196);
        Sleep(20);
    }

    gotoxy(34, 70);
    Sleep(20);
    printf("L");
    Sleep(20);
    printf("a");
    Sleep(20);
    printf("v");
    Sleep(20);
    printf("a");
    Sleep(20);
    printf("d");
    Sleep(20);
    printf("o");
    gotoxy(35,72);
    Sleep(20);
    printf("d");
    Sleep(20);
    printf("e");
    gotoxy(36,71);
    Sleep(20);
    printf("M");
    Sleep(20);
    printf("o");
    Sleep(20);
    printf("t");
    Sleep(20);
    printf("o");
    Sleep(20);
    printf("r");
    //Cola 1
    x = 25;
    for (y = 33; y > 23; y--)
    {
        gotoxy(y, x);
        printf("|");
        Sleep(20);
    }
    x = 32;
    for (y = 33; y > 23; y--)
    {
        gotoxy(y, x);
        printf("|");
        Sleep(20);
    }

    //Cola 2
    x = 54;
    for (y = 24; y > 17; y--)
    {
        gotoxy(y, x);
        printf("|");
        Sleep(20);
    }
    x = 61;
    for (y = 24; y > 17; y--)
    {
        gotoxy(y, x);
        printf("|");
        Sleep(20);
    }

    //Cola 3
    x = 50;
    for (y = 39; y > 33; y--)
    {
        gotoxy(y, x);
        printf("|");
        Sleep(20);
    }
    x = 57;
    for (y = 39; y > 33; y--)
    {
        gotoxy(y, x);
        printf("|");
        Sleep(20);
    }
}
void pintarSalaEspera()
{
    int y, x;
    for (y = 1; y < 12; y++)
    {
        for(x = 29; x < 51; x++)
        {
            gotoxy(y,x);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            printf("%c", 219);
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
int ponerAutoEnAlgunaEstacionLibreDeLavadoYAspirado(Estaciones_t estacionesDeLavadoYAspirado[4], short identificador)
{
    if (estacionesDeLavadoYAspirado[0].EstadoDeEstacion == 0)
    {
        estacionesDeLavadoYAspirado[0].EstadoDeEstacion = 1;
        estacionesDeLavadoYAspirado[0].TiempoInicial = time(NULL);
        estacionesDeLavadoYAspirado[0].Identificador = identificador;
        return 1;
    }
    else
    {
        if (estacionesDeLavadoYAspirado[1].EstadoDeEstacion == 0)
        {
            estacionesDeLavadoYAspirado[1].EstadoDeEstacion = 1;
            estacionesDeLavadoYAspirado[1].TiempoInicial = time(NULL);
            estacionesDeLavadoYAspirado[1].Identificador = identificador;
            return 2;
        }
        else
        {
            if (estacionesDeLavadoYAspirado[2].EstadoDeEstacion == 0)
            {
                estacionesDeLavadoYAspirado[2].EstadoDeEstacion = 1;
                estacionesDeLavadoYAspirado[2].TiempoInicial = time(NULL);
                estacionesDeLavadoYAspirado[2].Identificador = identificador;
                return 3;
            }
            else
            {
                if (estacionesDeLavadoYAspirado[3].EstadoDeEstacion == 0)
                {
                    estacionesDeLavadoYAspirado[3].EstadoDeEstacion = 1;
                    estacionesDeLavadoYAspirado[3].TiempoInicial = time(NULL);
                    estacionesDeLavadoYAspirado[3].Identificador = identificador;
                    return 4;
                }
            }
        }
    }
    return 0;
}
void random_autos(Auto_t * &autonuevo)
{
    int tipopago, tiposervicio, tipocarro, llaves;
    if(autonuevo == NULL)
    {
        printf("NO HAY MEMORIA");
    }
    else
    {
        tipopago = 1 + rand() % 100;
        if(tipopago <= 50)
        {
            autonuevo -> TarjetaDeDebito = true;
            autonuevo -> TarjetaDeCredito = false;
            autonuevo -> Efectivo = false;
        }
        else
        {
            if((tipopago > 50) && (tipopago < 80))
            {
                autonuevo -> TarjetaDeDebito = false;
                autonuevo -> TarjetaDeCredito = true;
                autonuevo -> Efectivo = false;
            }
            else
            {
                autonuevo -> TarjetaDeDebito = false;
                autonuevo -> TarjetaDeCredito = false;
                autonuevo -> Efectivo = true;
            }
        }
        
        tiposervicio = 1 + rand() % 100;
        
        if(tiposervicio <= 60)
        {
            autonuevo -> LavadoYAspirado = true;
            autonuevo -> CambioDeAceite = false;
            autonuevo -> LavadoDeMotorOChasis = false;

            autonuevo -> OrdenDeBorrado1 = false;
            autonuevo -> OrdenDeBorrado2 = true;
            autonuevo -> OrdenDeBorrado3 = true;
        }
        else
        {
            if((tiposervicio > 60) && (tiposervicio <= 70))
            {
                autonuevo -> LavadoYAspirado = false;
                autonuevo -> CambioDeAceite = true;
                autonuevo -> LavadoDeMotorOChasis = false;

                autonuevo -> OrdenDeBorrado1 = true;
                autonuevo -> OrdenDeBorrado2 = false;
                autonuevo -> OrdenDeBorrado3 = true;
            }
            else
            {
                if((tiposervicio > 70) && (tiposervicio <= 80))
                {
                    autonuevo -> LavadoYAspirado = false;
                    autonuevo -> CambioDeAceite = false;
                    autonuevo -> LavadoDeMotorOChasis = true;

                    autonuevo -> OrdenDeBorrado1 = true;
                    autonuevo -> OrdenDeBorrado2 = true;
                    autonuevo -> OrdenDeBorrado3 = false;
                }
                else
                {
                    if((tiposervicio > 80) && (tiposervicio <= 85))
                    {
                        autonuevo -> LavadoYAspirado = true;
                        autonuevo -> CambioDeAceite = true;
                        autonuevo -> LavadoDeMotorOChasis = false;

                        autonuevo -> OrdenDeBorrado1 = false;
                        autonuevo -> OrdenDeBorrado2 = false;
                        autonuevo -> OrdenDeBorrado3 = true;
                    }
                    else
                    {
                        if((tiposervicio > 85)&&(tiposervicio <= 90))
                        {
                            autonuevo -> LavadoYAspirado = true;
                            autonuevo -> CambioDeAceite = true;
                            autonuevo -> LavadoDeMotorOChasis = true;

                            autonuevo -> OrdenDeBorrado1 = false;
                            autonuevo -> OrdenDeBorrado2 = false;
                            autonuevo -> OrdenDeBorrado3 = false;
                        }
                        else
                        {
                            if((tiposervicio > 90) && (tiposervicio <= 95))
                            {
                                autonuevo -> LavadoYAspirado = false;
                                autonuevo -> CambioDeAceite = true;
                                autonuevo -> LavadoDeMotorOChasis = true;

                                autonuevo -> OrdenDeBorrado1 = true;
                                autonuevo -> OrdenDeBorrado2 = false;
                                autonuevo -> OrdenDeBorrado3 = false;
                            }
                            else
                            {
                                autonuevo -> LavadoYAspirado = true;
                                autonuevo -> CambioDeAceite = true;
                                autonuevo -> LavadoDeMotorOChasis = true;

                                autonuevo -> OrdenDeBorrado1 = false;
                                autonuevo -> OrdenDeBorrado2 = false;
                                autonuevo -> OrdenDeBorrado3 = false;
                            }
                        }
                    }
                }
            }
        }
        
        tipocarro = 1 + rand() % 99;
        if(tipocarro <= 33)
        {
            autonuevo -> CarroPequeno = true;
            autonuevo -> CarroMediano = false;
            autonuevo -> CarroGrande = false;
            autonuevo -> CodigoDeVehiculo = 254;
        }
        else
        {
            if((tipopago > 33) && (tipopago <= 66))
            {
                autonuevo -> CarroPequeno = false;
                autonuevo -> CarroMediano = true;
                autonuevo -> CarroGrande = false;
                autonuevo -> CodigoDeVehiculo = 220;
            }
            else
            {
                autonuevo -> CarroPequeno = false;
                autonuevo -> CarroMediano = false;
                autonuevo -> CarroGrande = true;
                autonuevo -> CodigoDeVehiculo = 219;
            }
        }
        autonuevo -> CodigoColorDeVehiculo = 1 + rand() % 6;

        llaves = 1 + rand() % 100;
        
        if(llaves <= 80)
            autonuevo -> Llaves = false;
        else
            autonuevo -> Llaves = true;

        if (autonuevo -> Llaves)
            autonuevo -> LlaveOn = true;
        else
            autonuevo -> LlaveOn = false;
    }
}
DWORD WINAPI TemporizadorDeSimulacion(void *data)
{
    char Segundero[12];
    int segundosVerdaderos = 0;
    for (;SEGUNDOS <= 60; SEGUNDOS++)
    {
        if (SEGUNDOS == 60)
        {
            SEGUNDOS = 0;
            MINUTOS++;
        }
        if (SEGUNDOS < 10)
        {
            if (MINUTOS < 10)
            {
                sprintf(Segundero, "0%d : 0%d", MINUTOS, SEGUNDOS);
            }
            else
            {
                if (MINUTOS >= 10)
                {
                    sprintf(Segundero, "%d : 0%d", MINUTOS, SEGUNDOS);
                }
            }
        }
        else
        {
            if (SEGUNDOS >= 10)
            {
                if (MINUTOS < 10)
                {
                    sprintf(Segundero, "0%d : %d", MINUTOS, SEGUNDOS);
                }
                else
                {
                    if (MINUTOS >= 10)
                    {
                        sprintf(Segundero, "%d : %d", MINUTOS, SEGUNDOS);
                    }
                }
            }
        }
        gotoxy(6, 36);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
        printf("%s", Segundero);
        fflush(stdin);
        segundosVerdaderos++;
        Sleep(1000);
        if (segundosVerdaderos >= TIEMPODESIMULACION)
        {
            FINISHANIMATION = true;
            break;
        }
    }
    return 0;
}
bool verificaTiempoDeEstaciones(Estaciones_t estacionesDeLavadoYAspirado[4], short identificador)
{
    bool result = false;
    if ((estacionesDeLavadoYAspirado[0].EstadoDeEstacion == 1) && (estacionesDeLavadoYAspirado[0].TiempoTranscurrido >= TIEMPOMAXIMODESERVICIOAUTOPEQUENIO) && (estacionesDeLavadoYAspirado[0].Identificador == identificador))
    {
        estacionesDeLavadoYAspirado[0].EstadoDeEstacion = 0;
        estacionesDeLavadoYAspirado[0].TiempoInicial = 0;
        estacionesDeLavadoYAspirado[0].TiempoTranscurrido = 0;
        estacionesDeLavadoYAspirado[0].Identificador = 0;
        result = true;
        gotoxy (8, 2);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", 219);
    }
    if ((estacionesDeLavadoYAspirado[1].EstadoDeEstacion == 1) && (estacionesDeLavadoYAspirado[1].TiempoTranscurrido >= TIEMPOMAXIMODESERVICIOAUTOPEQUENIO) && (estacionesDeLavadoYAspirado[1].Identificador == identificador))
    {
        estacionesDeLavadoYAspirado[1].EstadoDeEstacion = 0;
        estacionesDeLavadoYAspirado[1].TiempoInicial = 0;
        estacionesDeLavadoYAspirado[1].TiempoTranscurrido = 0;
        estacionesDeLavadoYAspirado[1].Identificador = 0;
        result = true;
        gotoxy (12, 2);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", 219);
    }
    if ((estacionesDeLavadoYAspirado[2].EstadoDeEstacion == 1) && (estacionesDeLavadoYAspirado[2].TiempoTranscurrido >= TIEMPOMAXIMODESERVICIOAUTOPEQUENIO) && (estacionesDeLavadoYAspirado[2].Identificador == identificador))
    {
        estacionesDeLavadoYAspirado[2].EstadoDeEstacion = 0;
        estacionesDeLavadoYAspirado[2].TiempoInicial = 0;
        estacionesDeLavadoYAspirado[2].TiempoTranscurrido = 0;
        estacionesDeLavadoYAspirado[2].Identificador = 0;
        result = true;
        gotoxy (16, 2);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", 219);
    }
    if ((estacionesDeLavadoYAspirado[3].EstadoDeEstacion == 1) && (estacionesDeLavadoYAspirado[3].TiempoTranscurrido >= TIEMPOMAXIMODESERVICIOAUTOPEQUENIO) && (estacionesDeLavadoYAspirado[3].Identificador == identificador))
    {
        estacionesDeLavadoYAspirado[3].EstadoDeEstacion = 0;
        estacionesDeLavadoYAspirado[3].TiempoInicial = 0;
        estacionesDeLavadoYAspirado[3].TiempoTranscurrido = 0;
        estacionesDeLavadoYAspirado[3].Identificador = 0;
        result = true;
        gotoxy (20, 2);
        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0);
        printf("%c", 219);
    }
    return result;
}
bool verificarSiHayEstacionDeLavadoLibre(Estaciones_t estacionesDeLavadoYAspirado[4])
{
    bool verificador = false;
    if ((estacionesDeLavadoYAspirado[0].EstadoDeEstacion == 0) || (estacionesDeLavadoYAspirado[1].EstadoDeEstacion == 0) || (estacionesDeLavadoYAspirado[2].EstadoDeEstacion == 0) || (estacionesDeLavadoYAspirado[3].EstadoDeEstacion == 0))
        verificador = true;
    return verificador;
}
bool verSiIDEstaEnEstacionamiento(Puesto_t puestos[5], short ID)
{
    for (int i = 0; i < 5; i++)
    {
        if (puestos[i].Identificador == ID)
            return true;
    }
    return false;
}