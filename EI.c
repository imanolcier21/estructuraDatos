#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structs para pacientes y doctores con arboles binarios con listas doblemente enlazadas

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
};

struct Pacientes{
    struct Doctor datoD;
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
    struct listaDoctor *inicio;
    struct listaDoctor *fin;
};

struct listaDoctor{
    struct Doctor datoD;
    struct Pacientes dato;
    struct listaDoctor *sig;
    struct listaDoctor *ant;
};


struct nodo{
    struct Pacientes dato;
    struct Doctor datoD;
    struct nodo *izq;
    struct nodo *der;
};

struct elemento{
    struct nodo *datoN;
    struct elemento *sig;
};





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


//funcion para inicializar el arbol binario de doctores y pacientes con listas doblemente enlazadas 
void inicializar(struct nodo **raiz){
    struct Doctor doct1={"12345234", "Juan Perez", 8, 18, 1, "Cardiologia", "UNAM", "Av. Universidad 1000", "5548234869"};
    struct Doctor doct2={"35843285", "Maria Lopez", 9, 15, 2, "Ginecologia", "IPN", "Av. Universidad 1000", "5541284723"};
    struct Doctor doct3={"75832347", "Mauricio Paulin", 8, 18, 1, "Gastroentorologia", "UAEM", "Av. Universidad 1000", "5598423457"};
    struct Pacientes paci1={"Javier Lopez", "LOPJ980101HDFRDF", 1, 1, 1998, 9, 1, 1, "5548234869", "javier@gmail.com"};
    struct Pacientes paci2={"Karla Garcia", "GAKL980101HDFRDF", }
}

