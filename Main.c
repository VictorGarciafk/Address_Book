#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 206

bool parse_int(char *str, int *integer);

//propiedades que cada contacto debe tener.
typedef struct {
    char nombre[50];
    char telefono[15];
    char correo[50];
    char direccion[100];
} Contacto;

void agregarContacto(Contacto *contacto) {
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

void buscarContacto(){
    FILE *archivo = fopen("agenda.dat", "rb");
    Contacto c;
    int encontrado = 0;
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    printf("\nIngrese el nombre del contacto a buscar: ");
    fgets(c.nombre, sizeof(c.nombre), stdin);
    c.nombre[strcspn(c.nombre, "\n")] = '\0'; 
    Contacto contacto;
    printf("\nLista de contactos:\n");
    while (fread(&contacto, sizeof(Contacto), 1, archivo)) {
        
        if (strstr(contacto.nombre, c.nombre))
        {
        printf("Nombre: %s\n", contacto.nombre);
        printf("Teléfono: %s\n", contacto.telefono);
        printf("Correo: %s\n", contacto.correo);
        printf("Dirección: %s\n", contacto.direccion);
        printf("---------------------------\n");
        encontrado++;
        }
        
    }
    fclose(archivo);

    if(encontrado == 1){
        printf("se encontraron %d contacto\n", encontrado);
    }else{
        printf("se encontraron %d contactos\n", encontrado);
    }
    
}

void eliminarContacto(const char *nombreEiminar){
    FILE *archivo = fopen("agenda.dat", "rb"); 
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    FILE *archivoTemporal = fopen("temp.dat", "wb");
    if (archivoTemporal == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Contacto contacto;
    int encontrado = 0;

    while (fread(&contacto, sizeof(Contacto), 1, archivo)) {
        if (strcmp(contacto.nombre, nombreEiminar) == 0) {
            encontrado = 1;
            printf("\nContacto eliminado:\n");
            printf("Nombre: %s\n", contacto.nombre);
            printf("Teléfono: %s\n", contacto.telefono);
            printf("Correo: %s\n", contacto.correo);
            printf("Dirección: %s\n", contacto.direccion);
            printf("-------------------------------------\n");
        } else {
            fwrite(&contacto, sizeof(Contacto), 1, archivoTemporal);
        }
    }

    fclose(archivo);
    fclose(archivoTemporal);

    if (encontrado) {
        remove("agenda.dat");
        rename("temp.dat", "agenda.dat");
        printf("\nEl contacto ha sido eliminado exitosamente.\n");
    } else {
        printf("\nNo se encontró un contacto con el nombre: %s\n", nombreEiminar);
        remove("temp.dat");
    }
}

void editarContacto(const char *nombreEditar){
FILE *archivo = fopen("agenda.dat", "rb"); 
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    FILE *archivoTemporal = fopen("temp.dat", "wb");
    if (archivoTemporal == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

Contacto contacto;
int encontrado;

while (fread(&contacto, sizeof(Contacto), 1, archivo)) {
        if (strcmp(contacto.nombre, nombreEditar) == 0) {
            encontrado = 1;
            char input[BUFFER_SIZE];

            printf("\nContacto encontrado:\n");
            printf("Nombre: %s\n", contacto.nombre);
            printf("Teléfono: %s\n", contacto.telefono);
            printf("Correo: %s\n", contacto.correo);
            printf("Dirección: %s\n", contacto.direccion);
            printf("-------------------------------------\n");
            printf("\nIngrese los nuevos datos (deje el campo vacio para no modificar)\n");
            
            printf("\nNuevo nombre: ");
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n')
            {
                // Elimina el salto de línea
                input[strcspn(input, "\n")] = '\0';
                strcpy(contacto.nombre, input);
            }
            
            printf("\nNuevo teléfono: ");
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n')
            {
                input[strcspn(input, "\n")] = '\0';
                strcpy(contacto.telefono, input);
            }
            
            printf("\nNuevo correo: ");
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n')
            {
                input[strcspn(input, "\n")] = '\0';
                strcpy(contacto.correo, input);
            }
            
            printf("\nNueva dirección: ");
            fgets(input, sizeof(input), stdin);
            if (input[0] != '\n')
            {
                input[strcspn(input, "\n")] = '\0';
                strcpy(contacto.direccion, input);
            }
        }
            fwrite(&contacto, sizeof(Contacto), 1, archivoTemporal);
    }

    fclose(archivo);
    fclose(archivoTemporal);

    if (encontrado) {
        remove("agenda.dat");
        rename("temp.dat", "agenda.dat");
        printf("\nEl contacto ha sido editado exitosamente.\n");
    } else {
        printf("\nNo se encontró un contacto con el nombre: %s\n", nombreEditar);
        remove("temp.dat");
    }
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
    bool optionCheck = false;
    bool avanzar = true;
    char nombre[BUFFER_SIZE];
    Contacto c;

    do
    {
        //se imprime el menu de opciones
        Menu();

        do {
            char buffer[BUFFER_SIZE];
            fgets(buffer, BUFFER_SIZE, stdin);
            parsed_correct = parse_int(buffer, &integer);
            if ((integer < 7) && (integer > 0)) optionCheck = true;

            if(!parsed_correct || (!optionCheck)){
                printf("\nFavor de ingresar el valor correcto de la opcion deseada: ");
            }else{
                avanzar = false;
            }
        }while(avanzar);

        parsed_correct = true;
        optionCheck = false;
        avanzar = true;

        switch (integer)
        {
        case 1:
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n*-*-*-*-*-*Agregar contacto*-*-*-*-*-*");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            
            do
            {
                printf("\nIngrese el nombre: ");
                fgets(c.nombre, sizeof(c.nombre), stdin);
                if (c.nombre[0] != '\n')
                {
                    // Elimina el salto de línea
                    c.nombre[strcspn(c.nombre, "\n")] = '\0';
                    avanzar = false;
                }else{
                    printf("\nFavor de ingresar un valor\n");
                }
                
            } while (avanzar);
            avanzar = true;

            do
            {
                printf("\nIngrese el teléfono: ");
                fgets(c.telefono, sizeof(c.telefono), stdin);
                parsed_correct = parse_int(c.telefono, &integer);

                if (parsed_correct)
                {
                    c.telefono[strcspn(c.telefono, "\n")] = '\0';
                    avanzar = false;
                }else{
                    printf("\nFavor de ingresar un valor numerico");
                }
            } while (avanzar);
            parsed_correct = true;
            avanzar = true;

            do
            {
                printf("\nIngrese el correo: ");
                fgets(c.correo, sizeof(c.correo), stdin);
                if (c.correo[0] != '\n')
                {
                    c.correo[strcspn(c.correo, "\n")] = '\0';
                    avanzar = false;
                }else{
                    printf("\nFavor de ingresar un valor: ");
                }
            } while (avanzar);
            avanzar = true;

            do
            {
                printf("\nIngrese la dirección: ");
                fgets(c.direccion, sizeof(c.direccion), stdin);
                if (c.direccion[0] != '\n')
                {
                    c.direccion[strcspn(c.direccion, "\n")] = '\0';
                    avanzar = false;
                }else{
                    printf("\nFavor de ingresar un valor: ");
                }
                
            } while (avanzar);
            avanzar = true;

            //le damos a la funcion los datos del contacto para que los agregue al archivo
            agregarContacto(&c); 
            printf("\n¡Contacto añadido con éxito!\n");
            break;

        case 2:
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n*-*-*-*-*-*Buscar contacto-*-*-*-*-*-*");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            buscarContacto();
            break;

        case 3:
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n*-*-*-*-*-*Editar contacto-*-*-*-*-*-*");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n\nIngrese el nombre del contacto a editar: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0'; 
            editarContacto(nombre);
            break;

        case 4:
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n*-*-*-*-*-*Eliminar contacto-*-*-*-*-*");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n\nIngrese el nombre del contacto a eliminar: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0'; 
            eliminarContacto(nombre);
            break;

        case 5:
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n*-*-*-*-*-Agenda de contactos*-*-*-*-*");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            listarContactos();
            break;

        case 6:
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            printf("\n*-*-*-*-*-*-*-*-*Salir-*-*-*-*-*-*-*-*");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
            exit(0);
            break;
        }

        printf("-------------------------------------------------------------");
    } while (true);
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