/*
 * Implementación de un Intérprete de Máquinas de Turing
 * Implementar un programa en C que, dada una máquina de Turing M =< Q, Σ, δ, q 0 , 6 b, F > y una cadena α
 * sobre el alfabeto Σ simule la ejecución de M sobre una cinta que inicialmente contiene a
 */

/* 
 * File:   main.c
 * Author: Ismael Ignacio Morinigo
 * Created on 11 de junio de 2018, 19:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * 
 */
void gui(char message[]){
    printf("======== TURING MACHINE SIMULATOR ========\n\n");
    printf("%s", message);
    printf("\n\n==========================================\n\n");
}
/* n tuplas de la forma (s, x, t, y, m) que representan las transiciones de la máquina de Turing. Donde s, t
 * corresponden al estado de inicio y fin de la transición, respectivamente; x es el sı́mbolo corriente en la
 * cinta; y es el sı́mbolo que se escribe en la cinta; y m la dirección en que se mueve el cabezal que lee la cinta.
 */
typedef struct{
    int inicio,   //s
        mover,    //m  derecha -> 0 | izquierda -> 1
        fin;      //t
    char escibir, //y  
         leer;    //x
}turing;

/* Utilice un arreglo de 50 elementos para representar la cinta. Ubique el primer elemento de la entrada en
 * la posición 20. Asuma que la entrada no podra tener una longitud mayor a 30 caracteres.
 */
typedef struct {
    char contenido[51];
    int  inicio,
         fin;
}tape;
    
// METODOS DE MAQUINA

/*
 * Lee las transiciones de la máquina tal como se describió previamente, almace-
 * nando toda la información necesaria para luego ejecutar la máquina. 
 */
void definirMaquina(turing (*maquina)[]){
    for(int i=0; i<4; i++){
        switch(i){
            case 0:
                (*maquina)[i].leer = '1';
                (*maquina)[i].mover = 0; 
                break;
            case 1:
                (*maquina)[i].leer = '2';
                (*maquina)[i].mover = 1; 
                break;
            case 2:
                (*maquina)[i].leer = '3';
                (*maquina)[i].mover = 0; 
                break;
            case 3:
                (*maquina)[i].leer = '4';
                (*maquina)[i].mover = 1; 
                break;   
        }
        (*maquina)[i].escibir = '0';
        (*maquina)[i].inicio  = i;
        (*maquina)[i].fin     = i+1;   
   }
    gui(">> Maquina Cargada");
    sleep(3);
}

/* 
 * Imprime toda la información almacenada sobre esta
 */
void imprimirMaquina(turing maquina[]){
    printf("======== TURING MACHINE SIMULATOR ========\n\n");
    printf(" S | T | X | Y | M \n");
               
    for(int i=0; i<4; i++){
        printf(" %i | %i | %c | %c | %i "
               "\n",maquina[i].inicio, maquina[i].fin ,maquina[i].leer, maquina[i].escibir,maquina[i].mover);
    }
    printf("\n REFERENCIAS\nS -> Estado Actual\nT -> Siguiente Estado\nX -> Leo\nY -> Escribo\nM -> Muevo\n ");
    printf("\n\n==========================================\n\n");
}

/*
 * Borra la información de la máquina.
*/
void borrarMaquina(turing maquina[]){
    for(int i=0; i<4; i++){
        maquina[i].escibir = ' ';
        maquina[i].leer    = ' ';
        maquina[i].mover   = -1;
        maquina[i].inicio  = -1;
        maquina[i].fin     = -1;
    }
    gui(">> La maquina ha sido borrada");
    sleep(3);
} 


// METODOS DE CINTA

/*
 * Se mueve en la cinta una posición a la izquierda.
 */
void movIzq(tape *cinta){
    if(cinta->inicio > 0)
        cinta->inicio--;  
}

/*
 * Se mueve en la cinta una posición a la derecha.
 */
void movDer(tape *cinta){
    if(cinta->inicio < 50)
        cinta->inicio++;   
}

/*
 * Corre la máquina con la cinta corriente e informa si la acepta o la rechaza.
 */
void evaluarCinta(turing maquina[], tape *cinta){
    int result;
    printf("======== TURING MACHINE SIMULATOR ========\n\n");
    printf("Evaluando Cinta\n");
    printf("%s",cinta->contenido);
    sleep(2);
    for(int i=0; i<4; i++){
        for(int j=0; j<cinta->fin; j++){
            if(maquina[i].leer == cinta->contenido[cinta->inicio]){
                cinta->contenido[cinta->inicio] = '0';
            }
            switch(i){
                case 0:
                case 2:
                    movDer(*&cinta);
                    break;
                case 1:
                case 3:
                    movIzq(*&cinta);
                    break;
            }
        }
    }
    for(int i=cinta->inicio; i<cinta->fin; i++){
        if(cinta->contenido[i] == '0'){
            result = 0;
        }
        else{
            result=1;
        } 
    }
    if(result == 0){
        printf("\nCinta valida. Solo valores: 1-2-3-4\n");
    }
    else{
        printf("\nCinta no valida\n");
    }    
    printf("\n\n==========================================\n\n");
    sleep(5);
}

/*
 * Borra todos los elementos de la cinta (deja solo blancos, –).
 */
void borrarCinta(tape *cinta){
    for(int i=0; i<=50; i++){
        cinta->contenido[i]= '0';
    }
    cinta->inicio = 20;
    cinta->fin = 20;  
} 

/*
 * Carga y corre una máquina previamente definida como ejemplo
 */
void correrEjemplo(turing (*maquina)[], tape *cinta){
    borrarCinta(*&cinta);
    definirMaquina(*&maquina);
    cinta->contenido[20] = '2';
    cinta->contenido[21] = '4';
    cinta->contenido[22] = '1';
    cinta->contenido[23] = '3';
    cinta->contenido[24] = '2';
    cinta->fin = 25;
    
    evaluarCinta(*maquina, *&cinta);
    
    
}

/*
 * almacenar en la cinta los caracteres de entrada (a partir de la posición 20 del
arreglo)
 */
void cargarCinta(tape *cinta){
    system("clear");
    char aux;
    if(cinta->inicio == cinta->fin)
        borrarCinta(*&cinta);
    
    if(cinta->fin >= 29){
        gui("La cinta esta llena");
        sleep(3);
    }
    else{
        gui("[>] Ingrese valores validos [0..9]\n[S] Para terminar\n");
        for(int i = cinta->inicio; i < 30; i++){
            scanf("%c", &aux);
            switch(aux){
                case 's':
                case 'S':
                    cinta->fin = i;
                    i = 32;
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    cinta->contenido[i] = aux;
                    break;
                default: 
                    i--;
                    break;
            }
        }  
    }
}

/*
 * Retorna el caracter en la posición corriente en que se encuentra la cinta.
 */
char caracterCorriente(tape cinta){
    return cinta.contenido[cinta.fin];
}

/*
 * Imprime los valores almacenados en la cinta
 */
void imprimirCinta(tape cinta){
    system("clear");
    gui(cinta.contenido);
}

/*
 * Posiciona el caracter corriente en el primer elemento de la cinta (en la posición 20 del arreglo).
 * void inicCinta(); //No es necesaria
 */


/*
 * MENU DE OPCIONES
 */
void menu(){
    int option = -1;
    tape cinta; 
    turing maquina[4];
    
    while(option != 0){
        system("clear");
        gui("  [1] Definir Maquina\n  [2] Imprimir Maquina\n  [3] Borrar Maquina \n"
                "  [4] Cargar Cinta\n  [5] Mostrar Cinta\n  [6] Borrar Cinta\n  [7] Evaluar Cinta\n  [8]  Ejecutar Ejemplo\n  [0] Salir");
        printf("Ingrese Opcion : ");
        scanf("%i",&option);
        system("clear");
        switch(option){
            case 0:
                break;
            case 1:
                definirMaquina(&maquina);
                break;
           case 2:
                if(maquina[0].inicio == -1){
                    gui("La maquina no esta cargada");
                }
                else{
                    imprimirMaquina(maquina);
                }
                sleep(5);
                break;
           case 3:
                borrarMaquina(maquina);
                break;
           case 4:
                cargarCinta(&cinta);
                break;
            case 5:
                if(cinta.inicio == cinta.fin){
                    gui("La cinta esta vacia");
                }
                else{
                    imprimirCinta(cinta);
                }
                
                printf("\nvalor de la cabeza %i\n", cinta.fin);
                sleep(5);
                break;
            case 6:
                borrarCinta(&cinta);
                gui(">> La cinta ha sido borrada");
                sleep(3);
                break;
            case 7:
                 if(cinta.inicio == cinta.fin){
                    gui("La cinta esta vacia");
                    sleep(3);
                }
                else{
                    evaluarCinta(maquina,&cinta);
                }
                break;
            case 8:
                correrEjemplo(&maquina, &cinta);
            default:
                break;
        }
    }
}
int main(int argc, char** argv) {
    menu();
    return (EXIT_SUCCESS);
}
