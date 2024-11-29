#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 512

bool parse_int(char *str, int *integer);

//propiedades que cada contacto debe tener.
typedef struct {
    char nombre[50];
    char telefono[15];
    char correo[50];
    char direccion[100];
} Contacto;

void AgregarContacto(Contacto *contacto) {
    FILE *archivo = fopen("agenda.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(contacto, sizeof(Contacto), 1, archivo);
    fclose(archivo);
}

void listarContactos() {
    FILE *archivo = fopen("agenda.dat", "rb");
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    Contacto contacto;
    printf("\nLista de contactos:\n");
    while (fread(&contacto, sizeof(Contacto), 1, archivo)) {
        printf("Nombre: %s\n", contacto.nombre);
        printf("Teléfono: %s\n", contacto.telefono);
        printf("Correo: %s\n", contacto.correo);
        printf("Dirección: %s\n", contacto.direccion);
        printf("---------------------------\n");
    }
    fclose(archivo);
}

void Menu(){
    printf("\n*-*-*-*-*-*Menu de opciones*-*-*-*-*-*");
    printf("\n1.- Agregar contacto");
    printf("\n2.- Buscar contacto");
    printf("\n3.- Editar contacto");
    printf("\n4.- Eliminar contacto");
    printf("\n5.- Listar contactos");
    printf("\n6.- Salir");
    printf("\n\nIngrese la opcion deseada: ");
}


int main() {
    bool parsed_correct = true;
    int integer;
    bool opcion = false;
    bool avanzar = false;
    FILE *Xfile;

    //se imprime el menu de opciones
    Menu();

    do {
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        //getchar();
        parsed_correct = parse_int(buffer, &integer);

        if ((integer < 7) && (integer > 0)) opcion = true;

        if(!parsed_correct || (!opcion)){
            printf("\nFavor de ingresar el valor correcto de la opcion deseada: ");
            avanzar = true;
        }else{
            avanzar = false;
        }

    }while(avanzar);

    //printf("Opcion seleccionada: %d\n", integer);

    switch (integer)
    {
    case 1:
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
        printf("\n*-*-*-*-*-*Agregar contacto*-*-*-*-*-*");
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
        Contacto c;
        printf("\nIngrese el nombre: ");
        fgets(c.nombre, sizeof(c.nombre), stdin);
        // Elimina el salto de línea
        c.nombre[strcspn(c.nombre, "\n")] = '\0'; 
        printf("\nIngrese el teléfono: ");
        fgets(c.telefono, sizeof(c.telefono), stdin);
        c.telefono[strcspn(c.telefono, "\n")] = '\0';
        printf("\nIngrese el correo: ");
        fgets(c.correo, sizeof(c.correo), stdin);
        c.correo[strcspn(c.correo, "\n")] = '\0';
        printf("\nIngrese la dirección: ");
        fgets(c.direccion, sizeof(c.direccion), stdin);
        c.direccion[strcspn(c.direccion, "\n")] = '\0';

        //le damos a la funcion los datos del contacto para que los agregue al archivo
        AgregarContacto(&c); 
        printf("\n¡Contacto añadido con éxito!\n");
        break;

    case 2:
        printf("\n*-*-*-*-*-*Buscar contacto-*-*-*-*-*-*");
        printf("\n*-*-*-*-*-*Work in progress*-*-*-*-*-*");
        break;

    case 3:
        printf("\n*-*-*-*-*-*Editar contacto-*-*-*-*-*-*");
        printf("\n*-*-*-*-*-*Work in progress*-*-*-*-*-*");
        break;

    case 4:
        printf("\n*-*-*-*-*-*Eliminar contacto-*-*-*-*-*");
        printf("\n*-*-*-*-*-*Work in progress*-*-*-*-*-*");
        break;

    case 5:
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
        printf("\n*-*-*-*-*-Agenda de contactos*-*-*-*-*");
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
        listarContactos();
        break;

    case 6:
        printf("\n*-*-*-*-*-*-*-*-*Salir-*-*-*-*-*-*-*-*");
        exit(0);
        break;
    }

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