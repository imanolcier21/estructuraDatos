#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona{
    char nombre[40];
    char apellidoPaterno[40];
    char apellidoMaterno[40];
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
    char correo[60];
    int telefono;
};

struct nodo{
    struct Persona dato;
    struct nodo *izq;
    struct nodo *der;
};


int insertar(struct Persona dato, struct nodo **raiz);
void eliminar(struct nodo **raiz);
int menu();

int main(){
    struct nodo *raiz = NULL;
    struct Persona dato;
    int opcion;
    int bandera = 1;
    opcion = menu();
    do{
        switch(opcion){
            case 1:
                printf(" Ingrese el nombre: ");
                scanf("%[^\n]%*c", dato.nombre);
                printf(" Ingrese el apellido paterno: ");
                scanf("%[^\n]%*c", dato.apellidoPaterno);
                printf(" Ingrese el apellido materno: ");
                scanf("%[^\n]%*c", dato.apellidoMaterno);
                printf(" Ingrese el dia de nacimiento: ");
                scanf("%d%*c", &dato.diaNacimiento);
                printf(" Ingrese el mes de nacimiento: ");
                scanf("%d%*c", &dato.mesNacimiento);
                printf(" Ingrese el anio de nacimiento: ");
                scanf("%d%*c", &dato.anioNacimiento);
                /*do{
                if(dato.diaNacimiento > 0 && dato.diaNacimiento < 32 && dato.mesNacimiento > 0 && dato.mesNacimiento < 13 && dato.anioNacimiento > 1900 && dato.anioNacimiento < 2022){
                    int edad = 2022 - dato.anioNacimiento;
                    if(edad >= 18 && edad <= 35){
                        bandera = 0;
                    }else{
                        printf(" La edad debe estar entre 18 y 35 anios. \n ");
                        printf(" Ingrese el dia de nacimiento: ");
                        scanf("%d%*c", &dato.diaNacimiento);
                        printf(" Ingrese el mes de nacimiento: ");
                        scanf("%d%*c", &dato.mesNacimiento);
                        printf(" Ingrese el anio de nacimiento: ");
                        scanf("%d%*c", &dato.anioNacimiento);
                    }
                }
                }while(bandera != 0);*/
                printf(" Ingrese el correo: ");
                scanf("%[^\n]%*c", dato.correo);
                printf(" Ingrese el telefono: ");
                scanf("%d%*c", &dato.telefono);
                //insertar(dato, &raiz);
                break;
        case 2:
            break;

        }
    }while(opcion != 8);
}

int menu(){
    int opc;
    printf("\n1. Agregar persona\n");
    printf("2. Eliminar persona\n");
    printf("3.Visualizar todas las persona\n");
    printf("4.Visualizar personas por fecha de nacimiento\n");
    printf("5. VIsualizar personas con misma fecha de nacimiento\n");
    printf("6. Consultar por número de teléfono\n");
    printf("7. Modificar datos de una persona\n");
    printf("8. Salir \n");
    scanf("%d%*c",&opc);
    return opc;
}


//función para insertar un nodo en el árbol 