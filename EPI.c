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

struct listaPaciente{
    struct Paciente paciente;
    struct listaPaciente *siguiente;
    struct listaPaciente *anterior;
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
struct Doctor buscar(struct nodo *raiz, struct Doctor doctor, char clave[100]);
struct Doctor buscarDoctor(struct nodo *raiz, struct Doctor doctor);
struct Doctor eliminar(struct nodo **raiz, struct Doctor doctor);
//funcion para imprimir un doctor que esta en el arbol

//menu, busqueda y captura de datos
int menu();
void imprimirDoctor(struct Doctor doctor);
void imprimirPaciente(struct Paciente paciente);
int capturarDoctor(struct Doctor *doctor);
int capturarPaciente(struct Paciente *paciente);
struct Paciente buscarPacientePorCurp(struct nodo *raiz, struct Paciente paciente);
int buscarPacientePorNombre(struct nodo *raiz, struct Paciente paciente);
int buscarDoctorPorNombre(struct nodo *raiz, struct Doctor doctor);

//funciones de lista doblemente enlazada
int insertarInicio(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente);
int insertarFinal(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente);
int insertarDespues(struct listaPaciente *anterior,  struct Paciente paciente);
int insertarOrdenado(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente);
void imprimirLista(struct listaPaciente *inicio);
int agregarPaciente(struct nodo *raiz,struct Doctor doctor, struct Paciente paciente);


void inicializar(struct nodo **raiz);


int main(){
    struct nodo *raiz=NULL;
    struct Doctor doctor;
    struct Paciente paciente;
    struct listaPaciente listaPaciente;
    char clave[100];
    int opcion;
    int opc1;
    int opc2, opc3;
    //fucion de inicializar
    do{
        opcion = menu();
        switch(opcion){
            case 1:
                if(capturarDoctor(&doctor)==1){
                    if(insertar(&raiz,doctor)){
                        printf("Doctor agregado correctamente\n");
                    }else{
                        printf("No se pudo agregar el doctor\n");
                    }
                }else{
                    printf("No se pudo capturar el doctor\n");
                }
                break;
            case 2:
            printf("Ingrese la clave del doctor: ");
            scanf("%[^\n]%*c", clave);
            doctor = buscar(raiz, doctor, clave);
            //if(doctor.inicio==NULL){
              //  printf("No se encontro el doctor\n");
            //}else{
                agregarPaciente(raiz, doctor, paciente);
           // }
                break;
            case 3:
            //preguntar la clave del doctor y mostrar la lista de pacientes
            printf("Ingrese la clave del doctor: ");
            scanf("%[^\n]%*c", clave);
            doctor = buscar(raiz, doctor, clave);
            //if(doctor.inicio==NULL){
              //  printf("No se econtro el doctor\n");
           // }else{
                imprimirLista(doctor.inicio);
            //}
                break;
            case 4:
            printf("Ingrese la clave del doctor: ");
            scanf("%[^\n]%*c", clave);
            doctor = buscar(raiz, doctor, clave);
            if(doctor.inicio==NULL){
                printf("No se encontro el doctor\n");
            }else{
                imprimirDoctor(doctor);
            }
                break;
            case 5:
            //preguntar si se quiere modificar un doctor o un paciente y preguntar el campo a modificar y modificarlo
            printf("1. Modificar doctor \n");
            printf("2. Modificar paciente \n");
            scanf("%d%*c", &opc1);
            //modificar doctor, preguntando el campo a modificar y modificandolo y preguntar si se quiere modificar otro campo
            switch(opc1){
        case 1:
            printf("Ingrese el nombre del doctor: ");
            scanf("%[^\n]%*c", doctor.nombre);
            doctor = buscarDoctor(raiz, doctor);
            printf("1. Modificar clave\n");
            printf("2. Modificar hora de inicio\n");
            printf("3. Modificar hora de fin\n");
            printf("4. Modificar numero de consultorio\n");
            printf("5. Modificar especialidad\n");
            printf("6. Modificar universidad\n");
            printf("7. Modificar direccion\n");
            printf("8. Modificar telefono\n");
            printf("9. Modificar correo\n");
            scanf("%d%*c", &opc2);
            switch(opc2){
            case 1:
                printf("Ingrese la nueva clave: ");
                scanf("%[^\n]%*c", doctor.clave);
                break;
            case 2:
                printf("Ingrese la nueva hora de inicio: ");
                scanf("%[^\n]%*c", doctor.horaInicio);
                break;
            case 3:
                printf("Ingrese la nueva hora de fin: ");
                scanf("%[^\n]%*c", doctor.horaFin);
                break;
            case 4:
                printf("Ingrese el nuevo numero de consultorio: ");
                scanf("%d%*c", &doctor.numeroConsultorio);
                break;
            case 5:
                printf("Ingrese la nueva especialidad: ");
                scanf("%[^\n]%*c", doctor.especialidad);
                break;
            case 6:
                printf("Ingrese la nueva universidad: ");
                scanf("%[^\n]%*c", doctor.universidad);
                break;
            case 7:
                printf("Ingrese la nueva direccion: ");
                scanf("%[^\n]%*c", doctor.direccion);
                break;
            case 8:
                printf("Ingrese el nuevo telefono: ");
                scanf("%[^\n]%*c", doctor.telefono);
                break;
            case 9:
                printf("Ingrese el nuevo correo: ");
                scanf("%[^\n]%*c", doctor.correo);
                break;
            default:
                printf("Opcion no valida\n");
                break;
            }
            break;
        case 2:
            printf("Ingrese la curp del paciente: ");
            scanf("%[^\n]%*c", paciente.curp);
            paciente = buscarPacientePorCurp(raiz, paciente);
            printf("1. Modificar curp\n");
            printf("2. Modificar dia de nacimiento\n");
            printf("3. Modificar mes de nacimiento\n");
            printf("4. Modificar anio de nacimiento\n");
            printf("5. Modificar dia de cita\n");
            printf("6. Modificar mes de cita\n");
            printf("7. Modificar hora de cita\n");
            printf("8. Modificar telefono\n");
            printf("9. Modificar correo\n");
            scanf("%d%*c", &opc3);
            switch(opc3){
            case 1:
                printf("Ingrese la nueva curp: ");
                scanf("%[^\n]%*c", paciente.curp);
                break;
            case 2:
                printf("Ingrese el nuevo dia de nacimiento: ");
                scanf("%d%*c", &paciente.diaNacimientoPaciente);
                break;
            case 3:
                printf("Ingrese el nuevo mes de nacimiento: ");
                scanf("%d%*c", &paciente.mesNacimientoPaciente);
                break;
            case 4:
                printf("Ingrese el nuevo anio de nacimiento: ");
                scanf("%d%*c", &paciente.anioNacimientoPaciente);
                break;
            case 5:
                printf("Ingrese el nuevo dia de cita: ");
                scanf("%d%*c", &paciente.diaCita);
                break;
            case 6:
                printf("Ingrese el nuevo mes de cita: ");
                scanf("%d%*c", &paciente.mesCita);
                break;
            case 7:
                printf("Ingrese la nueva hora de cita: ");
                scanf("%[^\n]%*c", paciente.horaCita);
                break;
            case 8:
                printf("Ingrese el nuevo telefono: ");
                scanf("%[^\n]%*c", paciente.telefonoP);
                break;
            case 9:
                printf("Ingrese el nuevo correo: ");
                scanf("%[^\n]%*c", paciente.correoP);
                break;
                default:
                printf("Opcion no valida\n");
                break;
            }
            break;
        }
        break;
    case 6:
        printf("Ingrese la clave del medico: ");
        scanf("%[^\n]%*c", doctor.clave);
        doctor = eliminar(&raiz, doctor);
        printf("Medico eliminado\n");
        break;
        }   
    }while(opcion!=8); 
}
  

int menu(){
    int opcion;
    printf("1. Agregar doctor\n");
    printf("2. Agregar paciente a medico\n");
    printf("3. Consultar pacientes de un medico\n");
    printf("4. Consultar doctor por clave\n");
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
struct Doctor buscar(struct nodo *raiz, struct Doctor doctor, char clave[100]){
    if(raiz == NULL){
        doctor.inicio = NULL;
        return doctor;
    }
    if(strcmp(clave, raiz->doctor.clave) < 0){
        return buscar(raiz->izquierda, doctor, clave);
    }
    if(strcmp(clave, raiz->doctor.clave) > 0){
        return buscar(raiz->derecha, doctor, clave);
    }
    if(strcmp(clave, raiz->doctor.clave) == 0){
        return raiz->doctor;
    }
}

struct Doctor buscarDoctor(struct nodo *raiz, struct Doctor doctor){
    if(raiz == NULL){
        doctor.inicio = NULL;
        return doctor;
    }
     if(strcmp(doctor.nombre, raiz->doctor.nombre) == 0){
        return raiz->doctor;
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) < 0){
        return buscarDoctor(raiz->izquierda, doctor);
    }
    if(strcmp(doctor.nombre, raiz->doctor.nombre) > 0){
        return buscarDoctor(raiz->derecha, doctor);
    }
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
    printf("Nombre: %s \n", doctor.nombre);
    printf("Clave: %s \n", doctor.clave);
    printf("Hora de inicio de la consulta: %d \n", doctor.horaInicio);
    printf("Hora de fin de la consulta: %d \n", doctor.horaFin);
    printf("Numero de consultorio: %d \n", doctor.numeroConsultorio);
    printf("Especialidad: %s \n", doctor.especialidad);
    printf("Universidad: %s \n", doctor.universidad);
    printf("Telefono: %s \n", doctor.telefono);
    printf("Correo: %s \n", doctor.correo);
}

//funcion para imprimir un paciente en pantalla
void imprimirPaciente(struct Paciente paciente){
    printf("Nombre: %s \n", paciente.nombrePaciente);
    printf("Curp: %s \n", paciente.curp);
    printf("Fecha de nacimiento: %d/%d/%d \n", paciente.diaNacimientoPaciente, paciente.mesNacimientoPaciente, paciente.anioNacimientoPaciente);
    printf("Fecha de la cita: %d/%d \n", paciente.diaCita, paciente.mesCita);
    printf("Hora de la cita: %d \n", paciente.horaCita);
    printf("Telefono: %s \n", paciente.telefonoP);
    printf("Correo: %s \n", paciente.correoP);
    printf(" \n");
}

int capturarDoctor(struct Doctor *doctor){
    printf("Nombre: ");
    scanf("%[^\n]%*c", doctor->nombre);
    printf("Clave: ");
    scanf("%[^\n]%*c", doctor->clave);
    printf("Hora de inicio de consulta: ");
    scanf("%d%*c", &doctor->horaInicio);
    printf("Hora de fin de consulta: ");
    scanf("%d%*c", &doctor->horaFin);
    printf("Numero de consultorio: ");
    scanf("%d%*c", &doctor->numeroConsultorio);
    printf("Especialidad: ");
    scanf("%[^\n]%*c", doctor->especialidad);
    printf("Universidad: ");
    scanf("%[^\n]%*c", doctor->universidad);
    printf("Direccion: ");
    scanf("%[^\n]%*c", doctor->direccion);
    printf("Telefono: ");
    scanf("%[^\n]%*c", doctor->telefono);
    printf("Correo: ");
    scanf("%[^\n]%*c", doctor->correo);
    doctor -> inicio = NULL;
    doctor -> fin = NULL;
    return 1;
}

int capturarPaciente(struct Paciente *paciente){
    printf("Nombre: ");
    scanf("%[^\n]%*c", paciente->nombrePaciente);
    printf("Curp: ");
    scanf("%[^\n]%*c", paciente->curp);
    printf("Dia de nacimiento: ");
    scanf("%d%*c", &paciente->diaNacimientoPaciente);
    printf("Mes de nacimiento: ");
    scanf("%d%*c", &paciente->mesNacimientoPaciente);
    printf("Anio de nacimiento: ");
    scanf("%d%*c", &paciente->anioNacimientoPaciente);
    printf("Dia de la cita: ");
    scanf("%d%*c", &paciente->diaCita);
    printf("Mes de la cita: ");
    scanf("%d%*c", &paciente->mesCita);
    printf("Hora de la cita: ");
    scanf("%d%*c", &paciente->horaCita);
    printf("Telefono: ");
    scanf("%[^\n]%*c", paciente->telefonoP);
    printf("Correo: ");
    scanf("%[^\n]%*c", paciente->correoP);
}

//funcion que busque en el arbol de doctores un paciente por su curp
struct Paciente buscarPacientePorCurp(struct nodo *raiz, struct Paciente paciente){
    if(raiz != NULL){
        if(strcmp(raiz->doctor.nombre, paciente.curp) == 0){
            return paciente;
        }else if(strcmp(raiz->doctor.nombre, paciente.curp) > 0){
            return buscarPacientePorCurp(raiz->izquierda, paciente);
        }else{
            return buscarPacientePorCurp(raiz->derecha, paciente);
        }
    }
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

int insertarInicio(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente){
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
}

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

int insertarDespues(struct listaPaciente *anterior,  struct Paciente paciente){
    struct listaPaciente *nuevo;
    nuevo = (struct listaPaciente*)malloc(sizeof(struct listaPaciente));
    nuevo->paciente = paciente;
    nuevo->siguiente = anterior->siguiente;
    (anterior->siguiente)->anterior = nuevo;
    anterior->siguiente = nuevo;
}

int insertarOrdenado(struct listaPaciente **inicio, struct listaPaciente **fin, struct Paciente paciente){
    struct listaPaciente *aux;
    aux=*inicio;
    while(aux!=NULL){
        if(strcmp(aux->paciente.nombrePaciente, paciente.nombrePaciente)){
            if(aux->anterior == NULL){
                return insertarFinal(inicio, fin, paciente);
            }
            else{
                return insertarDespues(aux->anterior, paciente);
            }
        }
        aux=aux->siguiente;
    }
    return insertarFinal(inicio, fin, paciente);
}

  void imprimirLista(struct listaPaciente *inicio){
    struct listaPaciente *aux;
    aux = inicio;
    while(aux != NULL){
        printf("Nombre: %s\n", aux->paciente.nombrePaciente);
        printf("Curp: %s\n", aux->paciente.curp);
        printf("Fecha de nacimiento: %d/%d/%d\n", aux->paciente.diaNacimientoPaciente, aux->paciente.mesNacimientoPaciente, aux->paciente.anioNacimientoPaciente);
        printf("Fecha cita: %d/%d\n", aux->paciente.diaCita, aux->paciente.mesCita);
        printf("Hora cita %d\n", aux->paciente.horaCita);
        printf("Telefono %s\n", aux->paciente.telefonoP);
        printf("Correo %s\n", aux->paciente.correoP);
        aux=aux->siguiente;
  }
  printf("\n");
}

int agregarPaciente(struct nodo *raiz, struct Doctor doctor, struct Paciente paciente){
    if(raiz != NULL){
        if(strcmp(raiz->doctor.nombre, doctor.nombre) == 0){
            insertarOrdenado(&raiz->doctor.inicio, &raiz->doctor.fin, paciente);
            return 1;
        }else if(strcmp(raiz->doctor.nombre, doctor.nombre) > 0){
            return agregarPaciente(raiz->izquierda, doctor, paciente);
        }else{
            return agregarPaciente(raiz->derecha, doctor, paciente);
        }
    }
    return 0;
}

//funcion para inicializar el arbol binario de doctores y pacientes con listas doblemente enlazadas 
/*void inicializar(struct nodo **raiz){
    struct Doctor doct1={"12345234", "Juan Perez", 8, 18, 1, "Cardiologia", "UNAM", "Av. Universidad 1000", "5548234869"};
    struct Doctor doct2={"35843285", "Maria Lopez", 9, 15, 2, "Ginecologia", "IPN", "Av. Universidad 1000", "5541284723"};
    struct Doctor doct3={"75832347", "Mauricio Paulin", 8, 18, 1, "Gastroentorologia", "UAEM", "Av. Universidad 1000", "5598423457"};
}*/