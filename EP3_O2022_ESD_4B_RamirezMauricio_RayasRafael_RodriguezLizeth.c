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
    char telefono[30];
};

struct nodo{
    struct Persona dato; 
    struct nodo *izq;
    struct nodo *der;
};


int insertar(struct Persona dato, struct nodo **raiz);
int eliminar(struct nodo **raiz, struct Persona dato);
void imprimir(struct nodo *raiz);
int imprimirFecha(struct nodo *raiz, int dia, int mes, int anio);
int imprimirMes(struct nodo *raiz, int mes);
int imprimirTelefono(struct nodo *raiz, char num[]);
int buscar(struct nodo **raiz, struct Persona dato);
int menu();

int main(){
    struct nodo *raiz = NULL;
    struct Persona dato;
    int opcion;
    int contador;
    int bandera = 1;
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
                scanf("%[^\n]%*c", dato.telefono);
                insertar(dato, &raiz);
                break;
        case 2:
            printf(" Ingrese el nombre: ");
            scanf("%[^\n]%*c", dato.nombre);
            printf(" Ingrese el apellido paterno: ");
            scanf("%[^\n]%*c", dato.apellidoPaterno);
            printf(" Ingrese el apellido materno: ");
            scanf("%[^\n]%*c", dato.apellidoMaterno);
            eliminar(&raiz, dato);
            break;
        case 3:
            imprimir(raiz);
            break;
        case 4:
            printf(" Ingrese el dia de nacimiento: ");
            scanf("%d%*c", &dato.diaNacimiento);
            printf(" Ingrese el mes de nacimiento: ");
            scanf("%d%*c", &dato.mesNacimiento);
            printf(" Ingrese el anio de nacimiento: ");
            scanf("%d%*c", &dato.anioNacimiento);
            contador=imprimirFecha(raiz, dato.diaNacimiento, dato.mesNacimiento, dato.anioNacimiento);
            printf("Hay %d personas con la fecha de nacimiento %d/%d/%d" , contador, dato.diaNacimiento, dato.mesNacimiento, dato.anioNacimiento);
           break;
        case 5:
            printf(" Ingrese el mes de nacimiento: ");
            scanf("%d%*c", &dato.mesNacimiento);
            contador=imprimirMes(raiz, dato.mesNacimiento);
            printf("Hay %d personas con el mes de nacimiento %d" , contador, dato.mesNacimiento);
            break;
        case 6:
            printf(" Ingrese el numero de telefono: ");
            scanf("%[^\n]*c", dato.telefono);
            imprimirTelefono(raiz, dato.telefono);
            break;
        case 7:
            printf(" Ingrese el nombre: ");
            scanf("%[^\n]%*c", dato.nombre);
            printf(" Ingrese el apellido paterno: ");
            scanf("%[^\n]%*c", dato.apellidoPaterno);
            printf(" Ingrese el apellido materno: ");
            scanf("%[^\n]%*c", dato.apellidoMaterno);
            buscar(&raiz, dato);
            break;
        default:
            printf(" Opcion no valida. \n ");
            break;
        }
    }while(opcion != 8);
}

int menu(){
    int opc;
    printf("\n1. Agregar persona\n");
    printf("2. Eliminar persona\n");
    printf("3. Visualizar todas las persona\n");
    printf("4. Visualizar personas por fecha de nacimiento\n");
    printf("5. VIsualizar personas con mes de nacimiento\n");
    printf("6. Consultar por numero de telefono\n");
    printf("7. Modificar datos de una persona\n");
    printf("8. Salir \n");
    scanf("%d%*c",&opc);
    return opc;
}

int insertar(struct Persona dato, struct nodo **raiz){
    if(*raiz == NULL){
        *raiz = (struct nodo *)malloc(sizeof(struct nodo));
        (*raiz)->dato = dato;
        (*raiz)->izq = NULL;
        (*raiz)->der = NULL;
        return 1;
    }else{
        if(strcmp(dato.nombre, (*raiz)->dato.nombre) < 0){
            insertar(dato, &(*raiz)->izq);
        }else if(strcmp(dato.nombre, (*raiz)->dato.nombre) > 0){
            insertar(dato, &(*raiz)->der);
        }else{
            if(strcmp(dato.apellidoPaterno, (*raiz)->dato.apellidoPaterno) < 0){
                insertar(dato, &(*raiz)->izq);
            }else if(strcmp(dato.apellidoPaterno, (*raiz)->dato.apellidoPaterno) > 0){
                insertar(dato, &(*raiz)->der);
            }else{
                if(strcmp(dato.apellidoMaterno, (*raiz)->dato.apellidoMaterno) < 0){
                    insertar(dato, &(*raiz)->izq);
                }else if(strcmp(dato.apellidoMaterno, (*raiz)->dato.apellidoMaterno) > 0){
                    insertar(dato, &(*raiz)->der);
                }else{
                    printf(" El registro ya existe. \n ");
                    return 0;
                }
            }
        }
    }
}

int eliminar(struct nodo **raiz, struct Persona dato){
    if(*raiz == NULL){
        printf(" El dato no existe. \n ");
        return 0;
    }else{
        if(strcmp(dato.nombre, (*raiz)->dato.nombre) < 0){
            eliminar(&(*raiz)->izq, dato);
        }else if(strcmp(dato.nombre, (*raiz)->dato.nombre) > 0){
            eliminar(&(*raiz)->der, dato);
        }else{
            if(strcmp(dato.apellidoPaterno, (*raiz)->dato.apellidoPaterno) < 0){
                eliminar(&(*raiz)->izq, dato);
            }else if(strcmp(dato.apellidoPaterno, (*raiz)->dato.apellidoPaterno) > 0){
                eliminar(&(*raiz)->der, dato);
            }else{
                if(strcmp(dato.apellidoMaterno, (*raiz)->dato.apellidoMaterno) < 0){
                    eliminar(&(*raiz)->izq, dato);
                }else if(strcmp(dato.apellidoMaterno, (*raiz)->dato.apellidoMaterno) > 0){
                    eliminar(&(*raiz)->der, dato);
                }else{
                    if((*raiz)->izq == NULL && (*raiz)->der == NULL){ //si es hoja lo borra directamente 
                        free(*raiz);
                        *raiz = NULL;
                        return 1;
                    }else if((*raiz)->izq == NULL){ //si solo tiene hijo derecho lo reemplaza por el hijo derecho
                        struct nodo *aux = *raiz;
                        *raiz = (*raiz)->der;
                        free(aux);
                        return 1;
                    }else if((*raiz)->der == NULL){ //si solo tiene hijo izquierdo lo reemplaza por el hijo izquierdo
                        struct nodo *aux = *raiz;
                        *raiz = (*raiz)->izq;
                        free(aux);
                        return 1;
                    }else{
                        struct nodo *aux = (*raiz)->der; //si tiene dos hijos, busca el menor del subarbol derecho y lo reemplaza por el nodo a eliminar
                        while(aux->izq != NULL){
                            aux = aux->izq;
                        }
                        (*raiz)->dato = aux->dato;
                        eliminar(&(*raiz)->der, aux->dato);
                    }
                }
            }
        }
    }
}

void imprimir(struct nodo *raiz){
    if(raiz != NULL){
        imprimir(raiz->izq);
        printf("*************************************************\n");
        printf(" Nombre: %s %s %s\n", raiz->dato.nombre, raiz->dato.apellidoPaterno, raiz->dato.apellidoMaterno);
        printf(" Fecha de nacimiento: %d/%d/%d\n", raiz->dato.diaNacimiento, raiz->dato.mesNacimiento, raiz->dato.anioNacimiento);
        printf(" Correo: %s\n", raiz->dato.correo);
        printf(" Telefono: %s\n", raiz->dato.telefono);
        printf("*************************************************\n");
        imprimir(raiz->der);
    }
}

int imprimirFecha(struct nodo *raiz, int dia, int mes, int anio){
    int contador = 0;
    if(raiz != NULL){
        imprimirFecha(raiz->izq, dia, mes, anio);
        if(raiz->dato.diaNacimiento == dia && raiz->dato.mesNacimiento == mes && raiz->dato.anioNacimiento == anio){
            printf("*************************************************\n");
            printf(" Nombre: %s %s %s\n", raiz->dato.nombre, raiz->dato.apellidoPaterno, raiz->dato.apellidoMaterno);
            printf(" Fecha de nacimiento: %d/%d/%d\n", raiz->dato.diaNacimiento, raiz->dato.mesNacimiento, raiz->dato.anioNacimiento);
            printf(" Correo: %s\n", raiz->dato.correo);
            printf(" Telefono: %s\n", raiz->dato.telefono);
            printf("*************************************************\n");
            contador++;
        }
        imprimirFecha(raiz->der, dia, mes, anio);
        return contador;
    }
}

int imprimirMes(struct nodo *raiz, int mes){
    int contador = 0;
    if(raiz != NULL){
        imprimirMes(raiz->izq, mes);
        if(raiz->dato.mesNacimiento == mes){
            printf("*************************************************\n");
            printf(" Nombre: %s %s %s\n", raiz->dato.nombre, raiz->dato.apellidoPaterno, raiz->dato.apellidoMaterno);
            printf(" Fecha de nacimiento: %d/%d/%d\n", raiz->dato.diaNacimiento, raiz->dato.mesNacimiento, raiz->dato.anioNacimiento);
            printf(" Correo: %s\n", raiz->dato.correo);
            printf(" Telefono: %s\n", raiz->dato.telefono);
            printf("*************************************************\n");
            contador++;
        }
        imprimirMes(raiz->der, mes);
        return contador;
    }
}

int imprimirTelefono(struct nodo *raiz, char telefono[]){
    int contador = 0;
    if(raiz != NULL){
        imprimirTelefono(raiz->izq, telefono);
        if(strcmp(raiz->dato.telefono, telefono) == 0){
            printf("*************************************************\n");
            printf(" Nombre: %s %s %s\n", raiz->dato.nombre, raiz->dato.apellidoPaterno, raiz->dato.apellidoMaterno);
            printf(" Fecha de nacimiento: %d/%d/%d\n", raiz->dato.diaNacimiento, raiz->dato.mesNacimiento, raiz->dato.anioNacimiento);
            printf(" Correo: %s\n", raiz->dato.correo);
            printf(" Telefono: %s\n", raiz->dato.telefono);
            printf("*************************************************\n");
            contador++;
        }
        imprimirTelefono(raiz->der, telefono);
        return contador;
    }
}


int buscar(struct nodo **raiz, struct Persona dato){
    int opcion;
    if(*raiz == NULL){
        return 0;
    }else{
        if(strcmp((*raiz)->dato.nombre, dato.nombre) == 0 && strcmp((*raiz)->dato.apellidoPaterno, dato.apellidoPaterno) == 0 && strcmp((*raiz)->dato.apellidoMaterno, dato.apellidoMaterno) == 0){
            printf("*************************************************\n");
            printf(" Nombre: %s %s %s\n", (*raiz)->dato.nombre, (*raiz)->dato.apellidoPaterno, (*raiz)->dato.apellidoMaterno);
            printf(" Fecha de nacimiento: %d/%d/%d\n", (*raiz)->dato.diaNacimiento, (*raiz)->dato.mesNacimiento, (*raiz)->dato.anioNacimiento);
            printf(" Correo: %s\n", (*raiz)->dato.correo);
            printf(" Telefono: %s\n", (*raiz)->dato.telefono);
            printf("*************************************************\n");
            do{
            printf("¿Desea modificar algun dato? (1 = si, 0 = no): ");
            scanf("%d%*c", &opcion);
            if(opcion == 1){
                printf("¿Que dato desea modificar? (1 = nombre, 2 = fecha de nacimiento, 3 = correo, 4 = telefono): ");
                int opcion2;
                scanf("%d%*c", &opcion2);
                switch(opcion2){
                    case 1:
                        printf("Ingrese el nuevo nombre: ");
                        scanf("%[^\n]%*c", (*raiz)->dato.nombre);
                        printf("Ingrese el nuevo apellido paterno: ");
                        scanf("%[^\n]%*c", (*raiz)->dato.apellidoPaterno);
                        printf("Ingrese el nuevo apellido materno: ");
                        scanf("%[^\n]%*c", (*raiz)->dato.apellidoMaterno);
                        break;
                    case 2:
                        printf("Ingrese el nuevo dia de nacimiento: ");
                        scanf("%d%*c", &(*raiz)->dato.diaNacimiento);
                        printf("Ingrese el nuevo mes de nacimiento: ");
                        scanf("%d%*c", &(*raiz)->dato.mesNacimiento);
                        printf("Ingrese el nuevo anio de nacimiento: ");
                        scanf("%d%*c", &(*raiz)->dato.anioNacimiento);
                        break;
                    case 3:
                        printf("Ingrese el nuevo correo: ");
                        scanf("%[^\n]%*c", (*raiz)->dato.correo);
                        break;
                    case 4:
                        printf("Ingrese el nuevo telefono: ");
                        scanf("%[^\n]%*c", (*raiz)->dato.telefono);
                        break;
                    default:
                        printf("Opcion no valida :(\n");
                        break; 
                }
            } 
        }while(opcion != 0);}
    }
}