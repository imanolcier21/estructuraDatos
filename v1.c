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
void eliminar(struct nodo **raiz, char nombre[40], char apellidoPaterno[40], char apellidoMaterno[40]);
void visualizar(struct nodo *raiz);
int menu();

int main(){
    struct nodo *raiz = NULL;
    struct Persona dato;
    int opcion;
    int bandera = 0;
    do{
    opcion = menu();
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
            do{
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
            }while(bandera != 0);
            printf(" Ingrese el correo: ");
            scanf("%[^\n]%*c", dato.correo);
            printf(" Ingrese el telefono: ");
            scanf("%d%*c", &dato.telefono);
            insertar(dato, &raiz);
            break;
        case 2:
            printf(" Ingrese el nombre: ");
            scanf("%[^\n]%*c", dato.nombre);
            printf(" Ingrese el apellido paterno: ");
            scanf("%[^\n]%*c", dato.apellidoPaterno);
            printf(" Ingrese el apellido materno: ");
            scanf("%[^\n]%*c", dato.apellidoMaterno);
            eliminar(&raiz, dato.nombre, dato.apellidoPaterno, dato.apellidoMaterno);
            break;
        case 3:
            visualizar(raiz);
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

//funcion para insertar un nodo en el arbol ordenados por nombre completo de la persona (nombre, apellido paterno y apellido materno), si el nombre completo es igual, no se inserta y se muestra un mensaje de error en pantalla.
int insertar(struct Persona dato, struct nodo **raiz){
    if(*raiz == NULL){
        *raiz = (struct nodo *)malloc(sizeof(struct nodo));
        (*raiz)->dato = dato;
        (*raiz)->izq = NULL;
        (*raiz)->der = NULL;
        return 1;
    }else{
        if(strcmp(dato.nombre, (*raiz)->dato.nombre) == 0){
            if(strcmp(dato.apellidoPaterno, (*raiz)->dato.apellidoPaterno) == 0){
                if(strcmp(dato.apellidoMaterno, (*raiz)->dato.apellidoMaterno) == 0){
                    printf(" El nombre completo ya existe. \n ");
                    return 0;
                }
            }
        }else{
            if(strcmp(dato.nombre, (*raiz)->dato.nombre) < 0){
                insertar(dato, &(*raiz)->izq);
            }else{
                insertar(dato, &(*raiz)->der);
            }
        }
    }
}

//funcion para eliminar un nodo del arbol con el nombre completo de la persona (nombre, apellido paterno y apellido materno), si el nombre completo no existe, se muestra un mensaje de error en pantalla.
void eliminar(struct nodo **raiz, char nombre[40], char apellidoPaterno[40], char apellidoMaterno[40]){
    if(*raiz == NULL){
        printf(" El nombre completo no existe. \n ");
        return;
    }else{
        if(strcmp(nombre, (*raiz)->dato.nombre) == 0){
            if(strcmp(apellidoPaterno, (*raiz)->dato.apellidoPaterno) == 0){
                if(strcmp(apellidoMaterno, (*raiz)->dato.apellidoMaterno) == 0){
                    struct nodo *aux = *raiz;
                    if((*raiz)->izq == NULL){
                        *raiz = (*raiz)->der;
                    }else{
                        if((*raiz)->der == NULL){
                            *raiz = (*raiz)->izq;
                        }else{
                            aux = (*raiz)->izq;
                            while(aux->der != NULL){
                                aux = aux->der;
                            }
                            aux->der = (*raiz)->der;
                            *raiz = (*raiz)->izq;
                        }
                    }
                    free(aux);
                    return;
                }
            }
        }else{
            if(strcmp(nombre, (*raiz)->dato.nombre) < 0){
                eliminar(&(*raiz)->izq, nombre, apellidoPaterno, apellidoMaterno);
            }else{
                eliminar(&(*raiz)->der, nombre, apellidoPaterno, apellidoMaterno);
            }
        }
    }
}

//funcion para visualizar todos los nodos del arbol en orden ascendente por nombre completo de la persona (nombre, apellido paterno y apellido materno).
void visualizar(struct nodo *raiz){
    if(raiz != NULL){
        visualizar(raiz->izq);
        printf(" Nombre: %s \n ", raiz->dato.nombre);
        printf(" Apellido paterno: %s \n ", raiz->dato.apellidoPaterno);
        printf(" Apellido materno: %s \n ", raiz->dato.apellidoMaterno);
        printf(" Fecha de nacimiento: %d/%d/%d \n ", raiz->dato.diaNacimiento, raiz->dato.mesNacimiento, raiz->dato.anioNacimiento);
        printf(" Correo: %s \n ", raiz->dato.correo);
        printf(" Telefono: %d \n ", raiz->dato.telefono);
        visualizar(raiz->der);
    }
}