#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 206

//propiedades que cada contacto debe tener.
typedef struct {
    char nombre[50];
    char telefono[15];
    char correo[50];
    char direccion[100];
} Contacto;

//validamos que el valor sea un numero entero positivo
bool parse_int(char *str, int *integer);

void agregarContacto(Contacto *contacto);

void eliminarContacto(const char *nombreEiminar);

void editarContacto(const char *nombreEditar);

int validarCorreo(char *correo);

int validarNombre(char *nombre);

void listarContactos();

void buscarContacto();

void Menu();

//funcion principal donde se ejecutara todo el programa
int main() {

    bool parsed_correct = true;
    int integer;
    bool optionCheck = false;
    bool avanzar = true;
    char nombre[BUFFER_SIZE];
    int validar;
    Contacto c;

    //Repetimos el menu de forma infinita hasta que escojan la opcion 6 de salir
    do
    {
        //se imprime el menu de opciones
        Menu();

        //se solicita al usuario ingresar una de las opciones del menu
        do {
            char buffer[BUFFER_SIZE];
            //almacenamos los datos proporcionados por el usuario
            fgets(buffer, BUFFER_SIZE, stdin);
            //verificamos si los datos proporcionados son un entero positivo o no
            parsed_correct = parse_int(buffer, &integer);
            //Validamos si el numero es entre el 1 al 6
            if ((integer < 7) && (integer > 0)) optionCheck = true;
            //se valida que se haya escogido de forma correcta una de las opciones proporcionadas.
            if(!parsed_correct || (!optionCheck)){
                printf("\nFavor de ingresar el valor correcto de la opcion deseada: ");
            }else{
                avanzar = false;
            }
        }while(avanzar);

        //reseteamos las variables para futuras validaciones
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
                    // Elimina el salto de línea
                    c.nombre[strcspn(c.nombre, "\n")] = '\0';
                    //obtenemos 1 si el formato del nombre es valido o un 0 si es invaldo
                    validar = validarNombre(c.nombre);

                    if (validar == 1)
                    {
                        avanzar = false;
                    }else{
                        printf("\nFavor de ingresar un valor\n");
                    }
                    
                } while (avanzar);
                avanzar = true;
                validar = 0;

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
                    c.correo[strcspn(c.correo, "\n")] = '\0';
                    validar = validarCorreo(c.correo);
                    if (validar == 1)
                    {
                        avanzar = false;
                    }else{
                        printf("\nFavor de ingresar un correo valido: ");
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
                //se realiza la busqueda y se imprime los datos del contacto solicitado
                buscarContacto();
                break;

            case 3:
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                printf("\n*-*-*-*-*-*Editar contacto-*-*-*-*-*-*");
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                printf("\n\nIngrese el nombre del contacto a editar: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                //se hace la busqueda y solicitar los nuevos datos a editar del contacto solicitado
                editarContacto(nombre);
                break;

            case 4:
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                printf("\n*-*-*-*-*-*Eliminar contacto-*-*-*-*-*");
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                printf("\n\nIngrese el nombre del contacto a eliminar: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0'; 
                //se hace la busqueda y eliminacion del contacto solicitado
                eliminarContacto(nombre);
                break;

            case 5:
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                printf("\n*-*-*-*-*-Agenda de contactos*-*-*-*-*");
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                //imprimimos todos los contactos registrador
                listarContactos();
                break;

            case 6:
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                printf("\n*-*-*-*-*-*-*-*-*Salir-*-*-*-*-*-*-*-*");
                printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
                //salimos del programa
                exit(0);
                break;
        }
        char bucle[BUFFER_SIZE];
        printf("\nPresione Enter para regresar al menu\n");
        fgets(bucle, BUFFER_SIZE, stdin);
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

//funcion para agregar un nuevo contacto a la lista.
void agregarContacto(Contacto *contacto) {
    //abrimos el archivo y verificamos si esta nulo
    FILE *archivo = fopen("agenda.dat", "ab");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    //escribimos en el archivo los datos del contacto obtenido
    fwrite(contacto, sizeof(Contacto), 1, archivo);
    fclose(archivo);
}

//funcion para eliminar un contacto con el nombre exacto en la lista existente
void eliminarContacto(const char *nombreEiminar){
    FILE *archivo = fopen("agenda.dat", "rb"); 
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    //Creamos un archivo temporal donde se almacenara los datos cambiados de la lista
    FILE *archivoTemporal = fopen("temp.dat", "wb");
    if (archivoTemporal == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Contacto contacto;
    int encontrado = 0;

    //se realiza la busqueda del usuario a borrar
    while (fread(&contacto, sizeof(Contacto), 1, archivo)) {
        ///si se encuentra se imprime los datos del usuario a eliminar y no se agrega a la lista modificada
        if (strcmp(contacto.nombre, nombreEiminar) == 0) {
            encontrado = 1;
            printf("\nContacto eliminado:\n");
            printf("Nombre: %s\n", contacto.nombre);
            printf("Teléfono: %s\n", contacto.telefono);
            printf("Correo: %s\n", contacto.correo);
            printf("Dirección: %s\n", contacto.direccion);
            printf("-------------------------------------\n");
        } else {
            //si el usuario no es el que se solicita eliminar, se agrega al archivo temporal
            fwrite(&contacto, sizeof(Contacto), 1, archivoTemporal);
        }
    }

    fclose(archivo);
    fclose(archivoTemporal);

    //se eliminar la agenda y se remplaza por la lista modiificada
    if (encontrado) {
        remove("agenda.dat");
        rename("temp.dat", "agenda.dat");
        printf("\nEl contacto ha sido eliminado exitosamente.\n");
    } else {
        printf("\nNo se encontró un contacto con el nombre: %s\n", nombreEiminar);
        remove("temp.dat");
    }
}

//funcion para editar el contacto con el nombre exacto de la lista existente
void editarContacto(const char *nombreEditar){
FILE *archivo = fopen("agenda.dat", "rb"); 

    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }
    //se genera archivo temporal
    FILE *archivoTemporal = fopen("temp.dat", "wb");
    if (archivoTemporal == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    Contacto contacto;
    Contacto NewContacto;
    int encontrado;
    int numero;
    
    while (fread(&contacto, sizeof(Contacto), 1, archivo)) {
        int validarCambio;
        bool NumeroValido = false;
        //al encontrar el usuario a modificar se imprimen los datos de dicho usuario y solicita los nuevos para sobreescribir los datos con los nuevos.
        if (strcmp(contacto.nombre, nombreEditar) == 0) {
            encontrado = 1;
            bool repetir = true;
            

            printf("\nContacto encontrado:\n");
            printf("Nombre: %s\n", contacto.nombre);
            printf("Teléfono: %s\n", contacto.telefono);
            printf("Correo: %s\n", contacto.correo);
            printf("Dirección: %s\n", contacto.direccion);
            printf("-------------------------------------\n");
            printf("\nIngrese los nuevos datos (deje el campo vacio para no modificar)\n");
                
            do
            {
                printf("\nNuevo nombre: ");
                fgets(NewContacto.nombre, sizeof(NewContacto.nombre), stdin);
                //si el valor esta vacio los datos se quedan igual sin modificaciones
                if (NewContacto.nombre[0] != '\n')
                {
                    // Elimina el salto de línea
                    NewContacto.nombre[strcspn(NewContacto.nombre, "\n")] = '\0';
                    validarCambio = validarNombre(&NewContacto.nombre);

                    if (validarCambio == 1)
                    {
                        strcpy(contacto.nombre, NewContacto.nombre);
                        validarCambio = 0;
                        repetir = false;
                    }else{
                        printf("\nFavor de ingresar un nombre valido: \n");
                    }
                }else{
                    //no se realiza ningun cambio
                    repetir = false;
                }
            } while (repetir);

            //reseteamos el valor de la variable
            repetir = true;

            do
            {
                
                printf("\nNuevo teléfono: ");
                fgets(NewContacto.telefono, sizeof(NewContacto.telefono), stdin);
                if (NewContacto.telefono[0] != '\n')
                {
                    NumeroValido = parse_int(NewContacto.telefono, &numero);
                    if (NumeroValido)
                    {
                        NewContacto.telefono[strcspn(NewContacto.telefono, "\n")] = '\0';
                        strcpy(contacto.telefono, NewContacto.telefono);
                        repetir = false;
                    }else{
                        printf("\nFavor de agregar un valor numerico\n");
                    }
                }else{
                    repetir = false;
                }
            } while (repetir);
            
            repetir = true;

            do
                {
                    printf("\nNuevo correo: ");
                    fgets(NewContacto.correo, sizeof(NewContacto.correo), stdin);

                    if (NewContacto.correo[0] != '\n')
                    {
                        NewContacto.correo[strcspn(NewContacto.correo, "\n")] = '\0';
                        validarCambio = validarCorreo(&NewContacto.correo);
                        if (validarCambio == 1)
                        {
                            strcpy(contacto.correo, NewContacto.correo);
                            repetir = false;
                            validarCambio = 0;
                        }else{
                            printf("\nFavor de ingresar un correo valido: \n");
                        }
                    }else{
                        repetir = false;
                    }
            } while (repetir);
                
            printf("\nNueva dirección: ");
            fgets(NewContacto.direccion, sizeof(NewContacto.direccion), stdin);
            if (NewContacto.direccion[0] != '\n')
            {
                NewContacto.direccion[strcspn(NewContacto.direccion, "\n")] = '\0';
                strcpy(contacto.direccion, NewContacto.direccion);
            }
        }
        fwrite(&contacto, sizeof(Contacto), 1, archivoTemporal);
    }

    fclose(archivo);
    fclose(archivoTemporal);

    //se remplaza la anterior lista con la modificada
    if (encontrado) {
        remove("agenda.dat");
        rename("temp.dat", "agenda.dat");
        printf("\nEl contacto ha sido editado exitosamente.\n");
    } else {
        printf("\nNo se encontró un contacto con el nombre: %s\n", nombreEditar);
        remove("temp.dat");
    }
}

//funcion para validar que el formato del correo sea correcto
int validarCorreo(char *correo){
    int posArroba = -1; //indice de la posicion del arroba
    int pospunto = -1; //indice de la posicion del punto

    int longitudCorreo = strlen(correo);

    if (longitudCorreo < 5){ //si el correo es menor a 5 caracteres regresamos un 0
        return 0; //el cero significa que el formato del correo es invalido
    }
    
    for (int i = 0; i < longitudCorreo; i++)
    {
        if (correo[i] == '@') { //Verificamos que el correo tenga una arroba

            if (pospunto == i -1){ //si hay un punto anterior al arroba regresamos un cero
                return 0;
            }
            
            if (posArroba != -1){ //si el correo tiene mas de un arroba regresamos un cero
                return 0; 
            }

            posArroba = i;
        }else if (correo[i] == '.'){ //verificamos que el correo tenga algun punto
            pospunto = i;
        }
    }
    
    if (posArroba == -1 || pospunto == -1){
        return 0; //El correo debe contener el arroba y punto
    }

    if (posArroba == 0 || posArroba == longitudCorreo -1){
        return 0; //el arroba no puede estar al inicio o al final
    }
    
    if (pospunto < posArroba + 2 || pospunto == longitudCorreo -1){
        return 0; //el punto debe estar despues del arroba y no puede estar al final
    }
    
    return 1; //se valida que el formato del correo es valido.
}

//funcion para validar que el formato del nombre sea correcto
int validarNombre(char *nombre){
    for (int i = 0; i < nombre[i] != '\0'; i++){
        //permitimos solo letras y espacios
        if (!isalpha(nombre[i]) && nombre[i] != ' ')
        {
            return 0; //Nombre invalido si contiene otro caracter
        }
    }
    return 1; //el formato del nombre es valido
}

//funcion para listar todos los contactos existentes
void listarContactos() {
    //abrimos el archivo y verificamos si esta nulo
    FILE *archivo = fopen("agenda.dat", "rb");
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    Contacto contacto;
    //se imprime en el siguiente formato los contactos almacenados en la lista
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

//funcion para buscar un contacto por su nombre
void buscarContacto(){
    FILE *archivo = fopen("agenda.dat", "rb");
    Contacto c;
    int encontrado = 0;
    if (archivo == NULL) {
        printf("\nNo hay contactos registrados.\n");
        return;
    }

    //se solicta el nombre del contacto a buscar
    printf("\nIngrese el nombre del contacto a buscar: ");
    fgets(c.nombre, sizeof(c.nombre), stdin);
    //eliminamos el "\n" que se genera al ingresar un dato
    c.nombre[strcspn(c.nombre, "\n")] = '\0'; 
    Contacto contacto;
    printf("\nLista de contactos:\n");
    //se busca al contacto otorgado por el usuario
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

//funcion el cual tenemos la impresion del menu en pantalla
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
