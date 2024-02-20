#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

#define MAX_LENGTH 8

void sigint_handler(int sig) {
    // Manejar la señal SIGINT (Ctrl + C)
    // Mostrar estadísticas antes de salir
    // Cerrar el archivo "syscalls.log" y liberar recursos
    exit(0);
}

int main() {
    // Configurar el manejador de señales para SIGINT
    signal(SIGINT, sigint_handler);

    // Abrir el archivo "syscalls.log"
    FILE *logfile = fopen("syscalls.log", "w");
    if (logfile == NULL) {
        perror("Error al abrir el archivo syscalls.log");
        return 1;
    }

    // Abrir el archivo "practica1.txt"
    int fd = open("practica1.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error al abrir o crear el archivo practica1.txt");
        fclose(logfile);
        return 1;
    }

    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    // Crear dos procesos hijo
    pid_t child1_pid = fork();
    if (child1_pid == 0) {
        // Código del primer hijo
        while (1) {
            // Generar un número aleatorio entre 1 y 3 para el tiempo de espera
            int random_time = rand() % 3 + 1;

            // Esperar el tiempo aleatorio
            sleep(random_time);

            // Generar un número aleatorio entre 0 y 2 para seleccionar la llamada de sistema
            int syscall_choice = rand() % 3;

            // Realizar llamadas de sistema seleccionadas
            switch (syscall_choice) {
                case 0:
                    // Write: Escribir una línea de texto con 8 caracteres alfanuméricos aleatorios
                    {
                        char buffer[MAX_LENGTH + 1]; // +1 para el carácter nulo
                        for (int i = 0; i < MAX_LENGTH; i++) {
                            buffer[i] = 'A' + rand() % 26; // Caracteres aleatorios de A a Z
                        }
                        buffer[MAX_LENGTH] = '\0'; // Agregar el carácter nulo al final del buffer
                        write(fd, buffer, MAX_LENGTH);
                        // Escribir una línea en el archivo de registro (opcional)
                        //fprintf(logfile, "Proceso %d: Write (%s)\n", getpid(), buffer);
                    }
                    break;
                case 1:
                    // Read: Leer 8 caracteres
                    {
                        char buffer[MAX_LENGTH + 1]; // +1 para el carácter nulo
                        read(fd, buffer, MAX_LENGTH);
                        buffer[MAX_LENGTH] = '\0'; // Agregar el carácter nulo al final del buffer
                        // Escribir una línea en el archivo de registro (opcional)
                        //fprintf(logfile, "Proceso %d: Read (%s)\n", getpid(), buffer);
                    }
                    break;
                case 2:
                    // Seek: Reposicionar el puntero de lectura y escritura al inicio del archivo
                    lseek(fd, 0, SEEK_SET);
                    // Escribir una línea en el archivo de registro (opcional)
                    //fprintf(logfile, "Proceso %d: Seek\n", getpid());
                    break;
            }
        }
    } else if (child1_pid < 0) {
        perror("Error al crear el primer proceso hijo");
        fclose(logfile);
        close(fd);
        return 1;
    }

    pid_t child2_pid = fork();
    if (child2_pid == 0) {
        // Código del segundo hijo
        // Mismo código que el primer hijo, puedes dejarlo igual o modularizarlo más.
        // Aquí he copiado el mismo código para simplificar.
        while (1) {
            // Generar un número aleatorio entre 1 y 3 para el tiempo de espera
            int random_time = rand() % 3 + 1;

            // Esperar el tiempo aleatorio
            sleep(random_time);

            // Generar un número aleatorio entre 0 y 2 para seleccionar la llamada de sistema
            int syscall_choice = rand() % 3;

            // Realizar llamadas de sistema seleccionadas
            switch (syscall_choice) {
                case 0:
                    // Write: Escribir una línea de texto con 8 caracteres alfanuméricos aleatorios
                    {
                        char buffer[MAX_LENGTH + 1]; // +1 para el carácter nulo
                        for (int i = 0; i < MAX_LENGTH; i++) {
                            buffer[i] = 'A' + rand() % 26; // Caracteres aleatorios de A a Z
                        }
                        buffer[MAX_LENGTH] = '\0'; // Agregar el carácter nulo al final del buffer
                        write(fd, buffer, MAX_LENGTH);
                        // Escribir una línea en el archivo de registro (opcional)
                        //fprintf(logfile, "Proceso %d: Write (%s)\n", getpid(), buffer);
                    }
                    break;
                case 1:
                    // Read: Leer 8 caracteres
                    {
                        char buffer[MAX_LENGTH + 1]; // +1 para el carácter nulo
                        read(fd, buffer, MAX_LENGTH);
                        buffer[MAX_LENGTH] = '\0'; // Agregar el carácter nulo al final del buffer
                        // Escribir una línea en el archivo de registro (opcional)
                        //fprintf(logfile, "Proceso %d: Read (%s)\n", getpid(), buffer);
                    }
                    break;
                case 2:
                    // Seek: Reposicionar el puntero de lectura y escritura al inicio del archivo
                    lseek(fd, 0, SEEK_SET);
                    // Escribir una línea en el archivo de registro (opcional)
                    //fprintf(logfile, "Proceso %d: Seek\n", getpid());
                    break;
            }
        }
    } else if (child2_pid < 0) {
        perror("Error al crear el segundo proceso hijo");
        fclose(logfile);
        close(fd);
        return 1;
    }

    // Monitorear las llamadas de sistema de los hijos y escribir en el archivo "syscalls.log"
    // Esto requerirá utilizar SystemTap o alguna otra herramienta de monitoreo de llamadas de sistema

    // Esperar la señal SIGINT para salir
    while(1) {
        // Esperar la señal SIGINT
    }

    // Cerrar el archivo "syscalls.log"
    fclose(logfile);

    // Cerrar el archivo "practica1.txt"
    close(fd);

    return 0;
}

