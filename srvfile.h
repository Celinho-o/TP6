#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "sem_funcoes.h"

#define exit_on_error(s, m) \
    if (s < 0)              \
    {                       \
        printf("%s\n", m);  \
        exit(EXIT_FAILURE); \
    }
#define exit_on_null(s)     \
    if (s == NULL)          \
    {                       \
        exit(EXIT_FAILURE); \
    }

/*Nome do FIFO*/
#define SERVER_FIFO_NAME "./FIFO/SRV_FIFO"
#define CLIENT_FIFO_NAME "./FIFO/CLI_FIFO"
// #define n_fifosrv 101010

/*Tam. Máximo para nome de ficheiro*/
#define MAX_FILE 50

/*Tam. do buffer*/
#define MAX_BUFFER 4096

/*Permissões*/
#define PERMISSION 0666

/*Estrutura de dados para pedido ao servidor*/
struct t_request
{
    int pid;
    char n_file[MAX_FILE];
};

void trataSIGINT(int sinal)
{
}

void signalHandler()
{
    struct sigaction sa;
    sa.sa_handler = trataSIGINT;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;              /* POSIX */
    sigaction(SIGINT, &sa, NULL); /* trata SIGINT*/
}
