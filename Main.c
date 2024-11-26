#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096

bool parse_int(char *str, int *integer);

int main() {

    bool parsed_correct = true;
    int integer = 0;
    FILE *Xfile;
    Xfile=fopen("agenda.cf","r+");


    if(Xfile==NULL) {
        printf("Error opening file");

    } else {
        printf("correctly opened file");
    }

    do {
        printf("\nMenu de opciones");
        printf("\n1.- Agregar contacto");
        printf("\n2.- Buscar contacto");
        printf("\n3.- Editar contacto");
        printf("\n4.- Eliminar contacto");
        printf("\n5.- Listar contactos");
        printf("\n6.- Salir");
        printf("\n\nIngrese la opcion deseada: ");

        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);

        parsed_correct = parse_int(buffer, &integer);

        if(!parsed_correct)
            printf("Favor de ingresar el valor correcto de la opcion deseada\n");

    }while(!parsed_correct);

    printf("Opcion seleccionada: %d\n", integer);

}

//funcion que regresa un entero si el numero ingresado es entero.
bool parse_int(char *str, int *intx) {
    int i = 0;

    while (isspace(str[i])) i++;

    int length = strlen(str);

    if (length == i) return false;

    char int_buffer[BUFFER_SIZE];
    int int_chars = 0;

    while (i < length && !isspace(str[i])) {

        if (!isdigit(str[i])) return false;

        int_buffer[int_chars] = str[i];
        int_chars++;
        i++;
    }

    int_buffer[int_chars] = '\0';
    while (isspace(str[i])) i++;
    if (str[i] != '\0') return false;
    *intx = atoi(int_buffer);

    return true;

}