#include "srvfile.h"

void main()
{

    signalHandler();

    int i, server_fifo_fd, client_fifo_fd, status, pid = getpid(), idsem = -1;
    struct t_request req;

    char client_fifo[MAX_FILE];

    idsem = sem_criar(IPC_PRIVATE, PERMISSION, 1);

    /*Elimina no caso de existir*/
    unlink(SERVER_FIFO_NAME);
    unlink(CLIENT_FIFO_NAME);

    /*Cria FIFO SERVER*/
    i = mkfifo(SERVER_FIFO_NAME, PERMISSION);
    exit_on_error(i, "Erro a criar o FIFO");
    /*Abre FIFO SERVER*/
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDWR);
    exit_on_error(server_fifo_fd, "Erro na abertura do FIFO");

    int read_res;
    do
    {
        read_res = read(server_fifo_fd, &req, sizeof(struct t_request));
        if (read_res > 0)
        {

            if (fork())
            {
                wait(&status);
            }
            else
            {

                sem_operacao(idsem, -1);

                sprintf(client_fifo, "%s_%d", CLIENT_FIFO_NAME, req.pid);
                client_fifo_fd = open(client_fifo, O_WRONLY);

                printf("PID:%d File:%s\n", req.pid, req.n_file);

                FILE *fp;
                char *line = NULL;
                ssize_t n = 0;

                if ((fp = fopen(req.n_file, "r")) == NULL)
                {

                    // Termina cliente -- Melhorar
                    kill(req.pid, SIGKILL);
                    unlink(client_fifo);

                    sem_operacao(idsem, 1);
                    close(client_fifo_fd);
                    exit(EXIT_FAILURE);
                }
                while ((n = getline(&line, &n, fp)) != -1)
                {
                    write(client_fifo_fd, line, n);
                }

                free(line);

                fclose(fp);

                close(client_fifo_fd);

                sem_operacao(idsem, 1);

                exit(0);
            }
        }
    } while (read_res > 0);

    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
    /* O FIFO resposta deve ser eliminado pelo processo client*/

    sem_remover(idsem);
    kill(getpid(), SIGKILL);
}
