#include "srvfile.h"

void writeFIFO(int request, struct t_request req, int pid, char *file)
{
    req.pid = pid;
    strcpy(req.n_file, file);

    if (write(request, &req, sizeof(req)) < 0) /*Escreve no FIFO*/
    {
        exit_on_error(request, "Não escrever no FIFO.");
    }
}

void main()
{
    signalHandler();

    int server_fifo_fd,
        pid = getpid();

    struct t_request req;
    char client_fifo[MAX_FILE];
    char fileName[MAX_FILE];

    /*É suposto o servidor já estar a correr e ter criado os FIFO*/
    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    exit_on_error(server_fifo_fd, "Servidor não se encontra a correr.");

    sprintf(client_fifo, "%s_%d", CLIENT_FIFO_NAME, pid);
    // printf("-> [%s]\n", client_fifo);

    if (mkfifo(client_fifo, PERMISSION) == -1)
    {
        exit_on_error(stderr, "Erro a criar o FIFO");
    }

    printf("File?");
    scanf("%s", fileName);

    writeFIFO(server_fifo_fd, req, getpid(), fileName);
    close(server_fifo_fd);

    FILE *fp = fopen(client_fifo, "r");
    char *line = 0;
    size_t n = 0;
    while (getline(&line, &n, fp) != EOF)
    {
        if (strlen(line) <= 0)
            break;
        printf("%s", line);
    }
    free(line);
    fclose(fp);
    
    unlink(client_fifo);
}
