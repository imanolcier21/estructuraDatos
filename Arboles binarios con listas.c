/******************************************************************************

Arbol BINARIO

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct medicion{
    float estatura;
    float peso;
};

struct listaMediciones{
    struct medicion datoM;
    struct listaMediciones *ant;
    struct listaMediciones *sig;
};

struct Persona{
    char nombre[30];
    int edad;
    struct listaMediciones *inicio;
    struct listaMediciones *fin;
};

struct nodo{
    struct Persona dato;
    struct nodo *izq;
    struct nodo *der;
};

//Cada elemento en la cola va a ser la raiz de un Arbol
struct elemento
{
    struct nodo *dato;
    struct elemento *sig;
    
};

//Funciones de colas NOOO cambian.
int insertarCola(struct elemento **inicio, struct elemento **fin, struct nodo *datoNuevo);
struct nodo* eliminarCola(struct elemento **inicio, struct elemento **fin);
int vacia(struct elemento *incio);
struct nodo* verPrimero(struct elemento *inicio);

//          ARBOLEEEEEEEEES
int insertar(struct nodo **raiz, struct Persona datoN);
//Recorridos de profundidad
void preOrden(struct nodo *raiz);
void inOrden(struct nodo *raiz);
void postOrden(struct nodo *raiz);
//Recorridos de amplitud
void recorridoAmplitud(struct nodo *raiz);
//Para eliminar
int buscar(struct nodo *raiz, struct Persona datoB);
struct Persona buscarPersona(struct nodo *raiz, struct Persona datoB);
struct Persona eliminar(struct nodo **raiz, struct Persona datoB);

//Menú, busqueda y captura.
int menu();
void imprimirPersona(struct Persona persona);
void capturarPersona(struct Persona *datoPersona);
int buscarEdadP(struct nodo *raiz, int edad);//devolver el número de personas con esa edad e imprimir las que la tengan, búsqueda de profuncidad
int buscarEdadA(struct nodo *raiz, int edad);//Lo mismo, pero recorrido por amplitud

//Funciones doblemente enlazadas
int insertarInicio(struct listaMediciones **inicio, struct listaMediciones **fin, struct medicion datoNuevo);
int insertarFin(struct listaMediciones **inicio, struct listaMediciones **fin, struct medicion datoNuevo);
int insertarDespues(struct listaMediciones *anterior, struct medicion datoNuevo);
int insertarOdenado(struct listaMediciones **inicio, struct listaMediciones **fin, struct medicion datoNuevo);
void imprimirLista(struct listaMediciones *inicio);
int agregarMedPersona(struct nodo *raiz, struct Persona datoB, struct medicion nuevaM);

void inicializar(struct nodo **raiz);

int main()
{
    struct nodo *raiz=NULL;
    struct Persona dato;
    struct medicion medida={160, 65};
    int opc, edad;
    inicializar(&raiz);
    do{
        opc=menu();
        switch(opc){
            case 1:
                capturarPersona(&dato);
                insertar(&raiz,dato);
                break;
            case 2:
                //capturarPersona(&dato);
                printf("Introduce el nombre de quien quieres eliminar: ");
                scanf("%[^\n]%*c", dato.nombre);
                imprimirPersona(eliminar(&raiz,dato));
                break;
            case 3:
                printf("Introduce el nombre de quien quieres eliminar: ");
                scanf("%[^\n]%*c", dato.nombre);
                imprimirPersona(buscarPersona(raiz,dato));
                break;
            case 4:
                printf("\nPreorden\n");
                preOrden(raiz);
                printf("\nInOrden\n");
                inOrden(raiz);
                break;
            case 5:
                printf("\nIntroduce la edad por la que quieres buscar: ");
                scanf("%d%*c", &edad);
                printf("\nTotal: %d\n", buscarEdadP(raiz, edad));
                break;
            case 6:
                printf("Introduce el nombre: ");
                scanf("%[^\n]%*c", dato.nombre);
                //capturar medición
                if(agregarMedPersona(raiz, dato, medida)){
                    printf("Medición agregada\n");
                }
                break;
            default:
                printf("bye");
                break;
        }
        
    }while(opc != 0);
    
    return 0;
}

int menu(){
    int opc;
    printf("\nOPCIONES:\n");
    printf("1. Insertar Persona.\n");
    printf("2. Eliminar Persona.\n");
    printf("3. Buscar Persona.\n");
    printf("4. Imprimir Arbol.\n");
    printf("5. Imprimir por edad\n");
    printf("6.Agregar medición a persona\n");
    printf("0. Salir\n");
    scanf("%d%*c",&opc);
    return opc;
}

void inicializar(struct nodo **raiz){
    struct Persona pers1={"María",11, NULL, NULL};
    struct Persona pers2={"Jose",15, NULL, NULL};
    struct medicion med1={150, 50};
    struct medicion med2={145, 49};
    struct medicion med3={156, 55};
    struct medicion med4={153, 53};
    insertarOdenado(&pers1.inicio, &pers1.fin, med1);
    insertarOdenado(&pers1.inicio, &pers1.fin, med2);
    insertarOdenado(&pers1.inicio, &pers1.fin, med3);
    insertarOdenado(&pers1.inicio, &pers1.fin, med4);
}

int insertar(struct nodo **raiz, struct Persona datoN){
    if(*raiz==NULL){
        struct nodo *nuevo;
        nuevo = (struct nodo*)malloc(sizeof(struct nodo));
        if(nuevo==NULL) return 0;
        nuevo -> dato = datoN;
        nuevo -> izq = NULL;
        nuevo -> der = NULL;
        *raiz = nuevo;
        return 1;
    }
    if(strcmp((*raiz)->dato.nombre, datoN.nombre) > 0){
        return insertar(&(*raiz)->izq, datoN);
    }else{
        return insertar(&(*raiz)->der, datoN);
    }
}

void preOrden(struct nodo *raiz){
    if(raiz==NULL) return;
    printf("%s, %d\n", raiz->dato.nombre, raiz->dato.edad);//Hacer función
    preOrden(raiz->izq);
    preOrden(raiz->der);
    return;
}

void inOrden(struct nodo *raiz){
    if(raiz==NULL) return;
    inOrden(raiz->izq);
    printf("%s, %d\n", raiz->dato.nombre, raiz->dato.edad);//Hacer función
    inOrden(raiz->der);
    return;
}

void postOrden(struct nodo *raiz){
    if(raiz==NULL) return;
    postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%s, %d\n", raiz->dato.nombre, raiz->dato.edad);//Hacer función
    return;
    //imprimirLista (ra)
}

//RECORRIDO DE AMPLITUD 

void recorridoAmplitud(struct nodo *raiz){
    if(raiz==NULL){
        return;
    }
    struct elemento *inicio=NULL, *fin=NULL;
    struct nodo *aux;
    
    insertarCola(&inicio, &fin, raiz);
    while(!vacia(inicio)){
        aux=eliminarCola(&inicio, &fin);
        printf("%s, %d\n", aux->dato.nombre, aux->dato.edad);//Hacer función
        if(aux-> izq != NULL){
            insertarCola(&inicio, &fin, aux->izq);
        }
        if(aux-> der != NULL){
            insertarCola(&inicio, &fin, aux->der);
        }
    }
}

int insertarCola(struct elemento **inicio, struct elemento **fin, struct nodo *datoNuevo){
    struct elemento *nuevo;
    nuevo=(struct elemento*)malloc(sizeof(struct elemento));
    if(nuevo==NULL){
        return 0;
    }
    nuevo->dato=datoNuevo;
    nuevo->sig=NULL;
    if(*inicio==NULL && *fin==NULL){
        *inicio=nuevo;
    }else{
        (*fin)->sig=nuevo;
    }
    *fin=nuevo;
    return 1;
}


struct nodo* eliminarCola(struct elemento **inicio, struct elemento **fin){
    struct nodo *datoElim=NULL;
    if(*inicio==NULL){
        return datoElim;
    }
    
    struct elemento *nodoElim=*inicio;
    datoElim=nodoElim->dato;
    *inicio=nodoElim->sig;
    if(*inicio==NULL){
        *fin=NULL;
    }
    free(nodoElim);
    return datoElim;
}

int vacia(struct elemento *inicio){
    if(inicio==NULL){
        return 1;
    }
    return 0;
}

struct nodo* verPrimero(struct elemento *inicio){
    if(inicio==NULL){
        return NULL;
    }
    return inicio->dato;
}

//PARA ELIMINAR

int buscar(struct nodo *raiz, struct Persona datoB){
    if(raiz==NULL) return 0;
    if(strcmp(raiz -> dato.nombre, datoB.nombre) == 0) return 1;
    if(strcmp(raiz -> dato.nombre, datoB.nombre) > 0){
        return buscar(raiz -> izq, datoB);
    } else{
        return buscar(raiz -> der, datoB);
    }
}

struct Persona buscarPersona(struct nodo *raiz, struct Persona datoB){
    if(raiz==NULL){
        struct Persona dato={""};
        return dato;
    }
    if(strcmp(raiz -> dato.nombre, datoB.nombre) == 0){
        return raiz->dato;
    }
    if(strcmp(raiz -> dato.nombre, datoB.nombre) > 0){
        return buscarPersona(raiz -> izq, datoB);
    } else{
        return buscarPersona(raiz -> der, datoB);
    }
}

int buscarEdadP(struct nodo *raiz, int edad){
    //Forma fácil: void buscarEdadP(struct nodo *raiz, int edad, int *cont)
    if(raiz==NULL){
        return 0;//return
    }
    int cont=0;// se quita
    if(raiz->dato.edad == edad){
        cont++;//(*cont)
        imprimirPersona(raiz->dato);
    }
    cont += buscarEdadP(raiz->izq, edad);
    cont += buscarEdadP(raiz->der, edad);
    return cont;
}

void buscarEdadP2(struct nodo *raiz, int edad, int *cont){
    if(raiz==NULL){
        return;
    }
    if(raiz->dato.edad == edad){
        (*cont)++;
        imprimirPersona(raiz->dato);
    }
    buscarEdadP2(raiz->izq, edad, cont);
    buscarEdadP2(raiz->izq, edad, cont);

}

int buscarEdadA(struct nodo *raiz, int edad){
    if(raiz==NULL){
        return 0;
    }
    int cont = 0;
    struct elemento *inicio=NULL, *fin=NULL;
    struct nodo *aux;
    
    insertarCola(&inicio, &fin, raiz);
    while(!vacia(inicio)){
        aux=eliminarCola(&inicio, &fin);
        if(aux -> dato.edad == edad){
            cont++;
            imprimirPersona(aux -> dato);
        }
        if(aux-> izq != NULL){
            insertarCola(&inicio, &fin, aux->izq);
        }
        if(aux-> der != NULL){
            insertarCola(&inicio, &fin, aux->der);
        }
    }
    return cont;
    
}

struct Persona eliminar(struct nodo **raiz, struct Persona datoB){
    if(*raiz==NULL){
        struct Persona datoElim={""};
        return datoElim;
    }
    if(strcmp((*raiz) -> dato.nombre, datoB.nombre) == 0){
        struct nodo *nodoElim = *raiz, *aux, *aux2;
        struct Persona datoElim = nodoElim -> dato;
        if((*raiz) -> izq == NULL && (*raiz) -> der == NULL){
            //Este caso es para cuando es una hoja.
            *raiz = NULL;
        }else{
            if((*raiz) -> der == NULL){
                //Tiene un hijo izquierdo
                *raiz = (*raiz) -> izq;
            }else{
                if((*raiz) -> izq == NULL){
                    //Tiene un hijo derecho
                    *raiz = (*raiz) -> der;
                }else{
                    aux2=*raiz;
                    aux = (*raiz) -> izq; // Se va solo una vez a la izquierda
                    while(aux -> der != NULL){
                        aux2=aux;
                        aux = aux -> der;//Después de ir a la izquierda, se va todo a la derecha
                        // esto permite encontrar el mayor en la
                    }
                    aux2 -> der = aux -> izq;//
                    aux -> der = (*raiz) -> der;
                    aux -> izq = (*raiz) -> izq;
                    *raiz = aux;
                }
            }
        }
        free(nodoElim);
        return datoElim;
    }
    if(strcmp((*raiz) -> dato.nombre, datoB.nombre) > 0){
        return eliminar(&((*raiz) -> izq), datoB);
    }else{
        return eliminar(&((*raiz) -> der), datoB);
    }
}

//Captura y MENUUUUUUUUU
void capturarPersona(struct Persona *datoPersona){
    printf("\nNombre de la persona: ");
    scanf("%[^\n]%*c",datoPersona->nombre);
    printf("\nEdad de la persona: ");
    scanf("%d%*c",&datoPersona->edad);
    datoPersona -> inicio = NULL;
    datoPersona -> fin = NULL;

}

void imprimirPersona(struct Persona persona){
    if(strcmp(persona.nombre, "") != 0){
        printf("\nNombre: %s",persona.nombre);
        printf("\nEdad: %d",persona.edad);
    }else{
        printf("\nPersona no encontrada!");
    }
}

int insertarInicio(struct listaMediciones **inicio, struct listaMediciones **fin, struct medicion datoNuevo){
    struct listaMediciones *nuevo;
    nuevo = (struct listaMediciones*)malloc(sizeof(struct listaMediciones));
    nuevo->datoM=datoNuevo;
    nuevo->sig=*inicio;
    nuevo->ant=NULL;
    if(*inicio == NULL){
        (*fin)=nuevo;
        }
    else{
        (*inicio)->ant = nuevo;
        }
    *inicio = nuevo;
    return 1;
}

int insertarFin(struct listaMediciones **inicio, struct listaMediciones **fin, struct medicion datoNuevo){
    struct listaMediciones *nuevo;
    nuevo=(struct listaMediciones*)malloc(sizeof(struct listaMediciones));
    nuevo->datoM=datoNuevo;
    nuevo->sig=NULL;
    nuevo->ant=*fin;
    if(*fin==NULL){
        *inicio=nuevo;
    }else{
        (*fin)->sig=nuevo;
    }
    *fin=nuevo;
    return 1;
}

int insertarDespues(struct listaMediciones *anterior, struct medicion datoNuevo){
    struct listaMediciones *nuevo;
    nuevo=(struct listaMediciones*)malloc(sizeof(struct listaMediciones));
    nuevo->datoM=datoNuevo;
    nuevo->ant=anterior;
    nuevo->sig=anterior->sig;
    (anterior->sig)->ant=nuevo;
    anterior->sig=nuevo;
}

int insertarOdenado(struct listaMediciones **inicio, struct listaMediciones **fin, struct medicion datoNuevo){
    struct listaMediciones *aux;
    aux=*inicio;
    while(aux!=NULL)
    {
        if(aux->datoM.estatura>datoNuevo.estatura)
        {
            if(aux->ant==NULL)
            {
                return insertarFin(inicio, fin, datoNuevo);
            }
            else
            {
                return insertarDespues(aux->ant, datoNuevo);
            }
        }
        aux=aux->sig;
    }
    return insertarFin(inicio, fin, datoNuevo);
}

/*void imprimirLista(struct listaMediciones *inicio){
    printf("\n");
    while(inicio!=NULL){
       printf("%d->", inicio->datoM);
       inicio=inicio->sig;
    }
    printf("NULL \n");
}*/

int agregarMedPersona(struct nodo *raiz, struct Persona datoB, struct medicion nuevaM){
    if(raiz==NULL){
        return 0;
    }
    if(strcmp(raiz -> dato.nombre, datoB.nombre) == 0){
        return insertarOdenado(&(raiz->dato.inicio),&(raiz->dato.fin),nuevaM);
    }
    if(strcmp(raiz -> dato.nombre, datoB.nombre) > 0){
        return agregarMedPersona(raiz -> izq, datoB, nuevaM);
    } else{
        return agregarMedPersona(raiz -> der, datoB, nuevaM);
    }
}

