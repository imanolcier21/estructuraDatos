#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//structs para guardar los datos de los doctores en el arbol binario y los de pacientes en lista doblemente enlazada

struct Paciente{
    char nombrePaciente[100];
    char curp[100];
    int diaNacimientoPaciente;
    int mesNacimientoPaciente;
    int anioNacimientoPaciente;
    int diaCita;
    int mesCita;
    int horaCita;
    char telefonoP[100];
    char correoP[100];
};

struct ListaPaciente{
    struct Paciente paciente;
    struct ListaPaciente *siguiente;
    struct ListaPaciente *anterior;
};

struct Doctor{
    char clave[100];
    char nombre[100];
    int horaInicio;
    int horaFin;
    int numeroConsultorio;
    char especialidad[100];
    char universidad[100];
    char direccion[100];
    char telefono[100];
    char correo[100];
    struct listaPaciente *inicio;
    struct listaPaciente *fin;
};

struct nodo{
    struct Doctor doctor;
    struct nodo *izquierda;
    struct nodo *derecha;
};

struct elemento{
   struct nodo *nodo;
   struct elemento *siguiente;
};

//funciones de cola
int insertarCola(struct elemento **inicio, struct elemento **fin, struct nodo *nodo);
struct nodo *eliminarCola(struct elemento **inicio, struct elemento **fin);
int vaciaCola(struct elemento *inicio);
struct nodo *verPrimero(struct elemento *inicio);

//funciones de arbol
int insertar(struct nodo **raiz, struct Doctor doctor);
void preOrden(struct nodo *raiz);
void inOrden(struct nodo *raiz);
void postOrden(struct nodo *raiz);
void recorridoAmplitud(struct nodo *raiz);
int buscar(struct nodo *raiz, struct Doctor doctor);
struct Doctor buscarDoctor(struct nodo *raiz, struct Doctor doctor);
struct Doctor eliminar(struct nodo **raiz, struct Doctor doctor);

//menu, busqueda y captura de datos
int menu();
void imprimirDoctor(struct Doctor doctor);
void imprimirPaciente(struct Paciente paciente);
int capturarDoctor(struct Doctor *doctor);
int capturarPaciente(struct Paciente *paciente);
int buscarDoctorPorClave(struct nodo *raiz, struct Doctor doctor);
int buscarPacientePorCurp(struct nodo *raiz);
int buscarPacientePorNombre(struct nodo *raiz, struct Paciente paciente);
int buscarDoctorPorNombre(struct nodo *raiz, struct Doctor doctor);

//funciones de lista doblemente enlazada
int insertarInicio(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente);
int insertarFinal(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente);
int insertarDespues(struct listaPaciente *anterior,  struct Paciente paciente);
int insertarOrdenado(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente);
void imprimirLista(struct listaPaciente *inicio);
int agregarPaciente(struct nodo *raiz, struct Doctor doctor, struct Paciente paciente);


void inicializar(struct nodo **raiz);


int main(){
    
}
  

int menu(){
    int opcion;
    printf("1. Agregar doctor\n");
    printf("2. Agregar paciente a medico\n");
    printf("3. Consultar pacientes de un medico\n");
    printf("4. Consultar doctor/medico por campo en especifico\n");
    printf("5. Modificar datos de un doctor/paciente\n");
    printf("6. Eliminar un medico\n");
    printf("7. Eliminar un paciente\n");
    printf("8. Salir\n");
    printf("Opcion: ");
    scanf("%d%*c", &opcion);
    return opcion;
}

int insertarCola(struct elemento **inicio, struct elemento **fin, struct nodo *nodo){
    struct elemento *nuevo;
    nuevo = (struct elemento *)malloc(sizeof(struct elemento));
    if(nuevo == NULL){
        return 0;
    }
    nuevo->nodo = nodo;
    nuevo->siguiente = NULL;
    if(*inicio == NULL && *fin == NULL){
        *inicio = nuevo;
    }else{
        (*fin)->siguiente = nuevo;
    }
    *fin = nuevo;
    return 1;
}

struct nodo* eliminarCola(struct elemento **inicio, struct elemento **fin){
    struct nodo *datoElim= NULL;
    if(*inicio == NULL){
        return datoElim;
    }
    struct elemento *nodoElim = *inicio;
    datoElim = nodoElim->nodo;
    *inicio = nodoElim->siguiente;
    if(*inicio == NULL){
        *fin = NULL;
    }
    free(nodoElim);
    return datoElim;
}

int vaciaCola(struct elemento *inicio){
    if(inicio == NULL){
        return 1;
    }
    return 0;
}

struct nodo *verPrimero(struct elemento *inicio){
    if(inicio == NULL){
        return NULL;
    }
    return inicio->nodo;
}

//funcion de insertar en el arbol binario de doctores ordenando por nombre de doctor menores a la izquierda y mayores a la derecha y no permitir duplicados
int insertar(struct nodo **raiz, struct Doctor doctor){
    if(*raiz == NULL){
        *raiz = (struct nodo *)malloc(sizeof(struct nodo));
        (*raiz)->doctor = doctor;
        (*raiz)->izquierda = NULL;
        (*raiz)->derecha = NULL;
        return 1;
    }
    if(strcmp(doctor.nombre, (*raiz)->doctor.nombre) < 0){
        return insertar(&(*raiz)->izquierda, doctor);
    }
    if(strcmp(doctor.nombre, (*raiz)->doctor.nombre) > 0){
        return insertar(&(*raiz)->derecha, doctor);
    }
    if(strcmp(doctor.nombre, (*raiz)->doctor.nombre) == 0){
        return 0;
    }
    return 0;
}

void preOrden(struct nodo *raiz){
    if(raiz != NULL){
        imprimirDoctor(raiz->doctor);
        preOrden(raiz->izquierda);
        preOrden(raiz->derecha);
    }
}

void inOrden(struct nodo *raiz){
    if(raiz != NULL){
        inOrden(raiz->izquierda);
        imprimirDoctor(raiz->doctor);
        inOrden(raiz->derecha);
    }
}

void postOrden(struct nodo *raiz){
    if(raiz != NULL){
        postOrden(raiz->izquierda);
        postOrden(raiz->derecha);
        imprimirDoctor(raiz->doctor);
    }
}

void recorridoAmplitud(struct nodo *raiz){
    struct elemento *inicio = NULL;
    struct elemento *fin = NULL;
    struct nodo *nodo;
    if(raiz == NULL){
        return;
    }
    insertarCola(&inicio, &fin, raiz);
    while(!vaciaCola(inicio)){
        nodo = eliminarCola(&inicio, &fin);
        imprimirDoctor(nodo->doctor);
        if(nodo->izquierda != NULL){
            insertarCola(&inicio, &fin, nodo->izquierda);
        }
        if(nodo->derecha != NULL){
            insertarCola(&inicio, &fin, nodo->derecha);
        }
    }
}

//funcion para buscar un doctor en el arbol binario de doctores
int buscar(struct nodo *raiz, struct Doctor doctor){
    if(raiz == NULL){
        return 0;
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) < 0){
        return buscar(raiz->izquierda, doctor);
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) > 0){
        return buscar(raiz->derecha, doctor);
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) == 0){
        return 1;
    }
    return 0;
}

struct Doctor buscarDoctor(struct nodo *raiz, struct Doctor doctor){
    if(raiz == NULL){
        return doctor;
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) < 0){
        return buscarDoctor(raiz->izquierda, doctor);
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) > 0){
        return buscarDoctor(raiz->derecha, doctor);
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) == 0){
        return raiz->doctor;
    }
    return doctor;
}

struct Doctor eliminar(struct nodo **raiz, struct Doctor doctor){
    struct Doctor doctorElim;
    if(*raiz == NULL){
        return doctorElim;
    }
    if(strcmp(doctor.nombre, (*raiz)->doctor.nombre) < 0){
        return eliminar(&(*raiz)->izquierda, doctor);
    }
    if(strcmp(doctor.nombre, (*raiz)->doctor.nombre) > 0){
        return eliminar(&(*raiz)->derecha, doctor);
    }
    if(strcmp(doctor.nombre, (*raiz)->doctor.nombre) == 0){
        doctorElim = (*raiz)->doctor;
        if((*raiz)->izquierda == NULL && (*raiz)->derecha == NULL){
            free(*raiz);
            *raiz = NULL;
        }else if((*raiz)->izquierda == NULL){
            struct nodo *aux = *raiz;
            *raiz = (*raiz)->derecha;
            free(aux);
        }else if((*raiz)->derecha == NULL){
            struct nodo *aux = *raiz;
            *raiz = (*raiz)->izquierda;
            free(aux);
        }else{
            struct nodo *aux = (*raiz)->izquierda;
            while(aux->derecha != NULL){
                aux = aux->derecha;
            }
            (*raiz)->doctor = aux->doctor;
            aux->doctor = doctor;
            return eliminar(&(*raiz)->izquierda, doctor);
        }
        return doctorElim;
    }
    return doctorElim;
}

//funcion para imprimir un doctor en pantalla 
void imprimirDoctor(struct Doctor doctor){
    printf("Nombre: %s \t", doctor.nombre);
    printf("Clave: %s \t", doctor.clave);
    printf("Hora de inicio de consulta: %d \t", doctor.horaInicio);
    printf("Hora de fin de consulta: %d \t", doctor.horaFin);
    printf("Numero de consultorio: %d \t", doctor.numeroConsultorio);
    printf("Especialidad: %s \t", doctor.especialidad);
    printf("Universidad: %s \t", doctor.universidad);
    printf("Direccion: %s \t", doctor.direccion);
    printf("Telefono: %s \t", doctor.telefono);
    printf(" Correo: %s \t", doctor.correo);
    printf(" \n");
}

//funcion para imprimir un paciente en pantalla
void imprimirPaciente(struct Paciente paciente){
    printf("Nombre: %s \t", paciente.nombrePaciente);
    printf("Curp: %s \t", paciente.curp);
    printf("Fecha de nacimiento: %d/%d/%d \t", paciente.diaNacimientoPaciente, paciente.mesNacimientoPaciente, paciente.anioNacimientoPaciente);
    printf("Fecha de la cita: %d/%d \t", paciente.diaCita, paciente.mesCita);
    printf("Hora de la cita: %d \t", paciente.horaCita);
    printf("Telefono: %s \t", paciente.telefonoP);
    printf("Correo: %s \t", paciente.correoP);
    printf(" \n");
}

int capturarDoctor(struct Doctor *doctor){
    printf("Nombre: ");
    scanf("%s", doctor->nombre);
    printf("Clave: ");
    scanf("%s", doctor->clave);
    printf("Hora de inicio de consulta: ");
    scanf("%d", &doctor->horaInicio);
    printf("Hora de fin de consulta: ");
    scanf("%d", &doctor->horaFin);
    printf("Numero de consultorio: ");
    scanf("%d", &doctor->numeroConsultorio);
    printf("Especialidad: ");
    scanf("%s", doctor->especialidad);
    printf("Universidad: ");
    scanf("%s", doctor->universidad);
    printf("Direccion: ");
    scanf("%s", doctor->direccion);
    printf("Telefono: ");
    scanf("%s", doctor->telefono);
    printf("Correo: ");
    scanf("%s", doctor->correo);
    doctor -> inicio = NULL;
    doctor -> fin = NULL;
}

int capturarPaciente(struct Paciente *paciente){
    printf("Nombre: ");
    scanf("%s", paciente->nombrePaciente);
    printf("Curp: ");
    scanf("%s", paciente->curp);
    printf("Fecha de nacimiento: ");
    scanf("%d/%d/%d", &paciente->diaNacimientoPaciente, &paciente->mesNacimientoPaciente, &paciente->anioNacimientoPaciente);
    printf("Fecha de la cita: ");
    scanf("%d/%d", &paciente->diaCita, &paciente->mesCita);
    printf("Hora de la cita: ");
    scanf("%d", &paciente->horaCita);
    printf("Telefono: ");
    scanf("%s", paciente->telefonoP);
    printf("Correo: ");
    scanf("%s", paciente->correoP);
}

int buscarDoctorPorClave(struct nodo *raiz, struct Doctor doctor){
    if(raiz != NULL){
        if(strcmp(raiz->doctor.clave, doctor.clave) == 0){
            return 1;
        }else if(strcmp(raiz->doctor.clave, doctor.clave) > 0){
            return buscarDoctorPorClave(raiz->izquierda, doctor);
        }else{
            return buscarDoctorPorClave(raiz->derecha, doctor);
        }
    }
    return 0;
}

int buscarPacientePorNombre(struct nodo *raiz, struct Paciente paciente){
    if(raiz != NULL){
        if(strcmp(raiz->doctor.nombre, paciente.nombrePaciente) == 0){
            return 1;
        }else if(strcmp(raiz->doctor.nombre, paciente.nombrePaciente) > 0){
            return buscarPacientePorNombre(raiz->izquierda, paciente);
        }else{
            return buscarPacientePorNombre(raiz->derecha, paciente);
        }
    }
    return 0;
}

int buscarDoctorPorNombre(struct nodo *raiz, struct Doctor doctor){
    if(raiz != NULL){
        if(strcmp(raiz->doctor.nombre, doctor.nombre) == 0){
            return 1;
        }else if(strcmp(raiz->doctor.nombre, doctor.nombre) > 0){
            return buscarDoctorPorNombre(raiz->izquierda, doctor);
        }else{
            return buscarDoctorPorNombre(raiz->derecha, doctor);
        }
    }
    return 0;
}

/*int insertarInicio(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente){
    struct listaPaciente *nuevo;
    nuevo = (struct listaPaciente*)malloc(sizeof(struct listaPaciente));
    nuevo->paciente = paciente;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    if(*fin==NULL){
        *inicio=nuevo;
    }else{
        (*fin)->siguiente = nuevo;
    }
    *fin = nuevo;
    return 1;
}*/

int insertarFinal(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente){
    struct listaPaciente *nuevo;
    nuevo = (struct listaPaciente*)malloc(sizeof(struct listaPaciente));
    nuevo->paciente = paciente;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    if(*fin==NULL){
        *inicio=nuevo;
    }else{
        (*fin)->siguiente = nuevo;
        nuevo->anterior = *fin;
    }
    *fin = nuevo;
    return 1;
}




//funcion para inicializar el arbol binario de doctores y pacientes con listas doblemente enlazadas 
/*void inicializar(struct nodo **raiz){
    struct Doctor doct1={"12345234", "Juan Perez", 8, 18, 1, "Cardiologia", "UNAM", "Av. Universidad 1000", "5548234869"};
    struct Doctor doct2={"35843285", "Maria Lopez", 9, 15, 2, "Ginecologia", "IPN", "Av. Universidad 1000", "5541284723"};
    struct Doctor doct3={"75832347", "Mauricio Paulin", 8, 18, 1, "Gastroentorologia", "UAEM", "Av. Universidad 1000", "5598423457"};
}*/



