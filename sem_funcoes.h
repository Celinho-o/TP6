#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

/* Modulo de funcoes de semaforos*/
/* Este modulo nao pretende conter todas as "combinacoes" possiveis;
apenas algumas das funcoes mais utilizadas nos exercicios estudados*/
union semun
{                          /* codigo copiado da manpage da semctl: */
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* array for GETALL, SETALL */
    /* Linux specific part: */
    struct seminfo *__buf; /* buffer for IPC_INFO */
};
int sem_criar_n(int chave, int numero_de_semaforos, int permissoes);
void sem_ini_var_n(int id, int indice_do_semaforo, int valor);
int sem_criar(int chave, int permissoes, int valor);
int sem_id(int chave);
void sem_remover(int id);
void sem_operacao_n(int id, int indice_do_semaforo, int operacao);
void sem_operacao(int id, int operacao);
int sem_valor_n(int id, int indice_do_semaforo);
int sem_valor(int id);
void sem_esperar(int id);
void sem_assinalar(int id);
void sem_wait40(int id);
