/*Mauricio Imanol Ramirez Paulin RPMO211621
4°B
ED2 22 NOVIEMBRE 2022*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    float dato;
    struct nodo *izq;
    struct nodo *der;
};

int insertar(float dato, struct nodo **raiz);
void imprimir(struct nodo *raiz, int nivel, int altura);
void vaciar(struct nodo **raiz);

int menu();

int main(){
    struct nodo *raiz = NULL;
    int opcion;
    float dato;
    int nivel = 0;
    int altura = 0;
    do{
        opcion = menu();
        switch(opcion){
            case 1:
                printf(" Ingrese el dato a insertar: ");
                scanf("%f%*c", &dato);
                insertar(dato, &raiz);
                break;
            case 2:
                imprimir(raiz, nivel, altura);
                break;
            case 3:
                vaciar(&raiz);
                break;
            case 4:
                printf(" Fin del programa. \n ");
                break;
            default:
                printf(" Opcion incorrecta. \n ");
                break;
        }
}while(opcion != 4);
    return 0;
}

int menu(){
    int opc;
    printf("\n1. Insertar numeros\n");
    printf("2. Redorrido en orden\n");
    printf("3. Vaciar arbol\n");
    printf("4. Salir \n");
    scanf("%d%*c",&opc);
    return opc;
}

int insertar(float dato, struct nodo **raiz){
    struct nodo *nuevo;
    struct nodo *anterior;
    struct nodo *actual;
    nuevo = (struct nodo *)malloc(sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    if(*raiz == NULL){
        *raiz = nuevo;
    }else{
        anterior = NULL;
        actual = *raiz;
        while(actual != NULL){
            if(dato == actual->dato){
                printf(" El dato ya existe. \n ");
                return 0;
            }
            anterior = actual;
            if(dato < actual->dato){
                actual = actual->izq;
            }else{
                actual = actual->der;
            }
        }
        if(dato < anterior->dato){
            anterior->izq = nuevo;
        }else{
            anterior->der = nuevo;
        }
    }
    return 1;
}


void imprimir(struct nodo *raiz, int nivel, int altura){
    if(raiz != NULL){
        imprimir(raiz->izq, nivel + 1, altura);
        printf(" %f \t ", raiz->dato);
        printf("Nivel: %d \t\n ", nivel);
        printf(" \n ");
        imprimir(raiz->der, nivel + 1, altura+1);
    }
}

void vaciar(struct nodo **raiz){
    if(*raiz != NULL){
        vaciar(&(*raiz)->izq);
        vaciar(&(*raiz)->der);
        printf(" Se elimino el dato: %.2f \n ", (*raiz)->dato);
        free(*raiz);
        *raiz = NULL;
    }else{
        return;
    }
}


