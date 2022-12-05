#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct persona{
    char nombre[40];
    char apellidoPaterno[40];
    char apellidoMaterno[40];
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
    char correo[60];
    int telefono;
};

struct elemento{
    struct persona datos;
    struct elemento *siguiente;
    struct elemento *anterior;
};


int insertarInicio(struct elemento **inicio, struct elemento **fin, struct persona datos);
int menu();

int main(){
struct elemento *inicio1 = NULL, *fin1 = NULL;
int opcion;
struct persona datos;

}