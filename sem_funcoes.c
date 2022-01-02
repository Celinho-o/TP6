#include "sem_funcoes.h"
/* Modulo de funções para manipular semáforos/
/* Este modulo nao pretende conter todas as "combinações" possíveis;
apenas algumas das funções mais utilizadas nos exercícios estudados*/

/* cria um conjunto de semáforos mas nao inicializa as respectivas
variáveis de controlo */
int sem_criar_n(int chave, int numero_de_semaforos, int permissoes)
{
    int id;
    id = semget(chave, numero_de_semaforos, IPC_CREAT | IPC_EXCL | permissoes);
    exit_on_error(id, "Erro ao criar semaforo");
    return id;
}
/* (re)inicializa o valor da variavel de controlo do semaforo */
void sem_ini_var_n(int id, int indice_do_semaforo, int valor)
{
    int r;
    union semun su;
    su.val = valor;
    r = semctl(id, indice_do_semaforo, SETVAL, su);
    exit_on_error(r, "Erro ao atribuir valor ao semaforo");
}
/* cria um semaforo e inicializa a respectiva variavel de controlo */
int sem_criar(int chave, int permissoes, int valor)
{
    int id = sem_criar_n(chave, 1, permissoes);
    sem_ini_var_n(id, 0, valor);
    return id;
}
/* obtem id do semaforo */
int sem_id(int chave)
{
    int id;
    id = semget(chave, 0, 0);
    exit_on_error(id, "Erro ao obter id do semaforo");
    return id;
}
/* remove semaforo */
void sem_remover(int id)
{
    semctl(id, 0, IPC_RMID);
}
/* executa uma operacao sobre o semaforo n do conjunto */
void sem_operacao_n(int id, int indice_do_semaforo, int operacao)
{
    int r;
    struct sembuf sb;
    sb.sem_num = indice_do_semaforo; /* Indice do semaforo no conjunto */
    sb.sem_op = operacao;
    sb.sem_flg = 0; /* flags */
    r = semop(id, &sb, 1);
    exit_on_error(r, "Erro ao realizar a operacao sobre o semaforo");
}
/* executa uma operacao sobre o semaforo 0(assumido)*/
void sem_operacao(int id, int operacao)
{
    sem_operacao_n(id, 0, operacao); /*Indice 0 assumido*/
}
/* devolve o valor da variavel de controlo do semaforo n do conjunto*/
int sem_valor_n(int id, int indice_do_semaforo)
{
    int r;
    r = semctl(id, indice_do_semaforo, GETVAL);
    exit_on_error(r, "Erro ao aceder ao semaforo");
    return r;
}
/* devolve o valor da variavel de controlo do semaforo 0 (assumido)*/
int sem_valor(int id)
{
    int r;
    r = sem_valor_n(id, 0); /*0 assumido*/
    return r;
}
/* realiza a operação -1 ("esperar") sobre o semáforo 0 do conjunto*/
void sem_esperar(int id)
{
    sem_operacao(id, -1); /* esperar*/
}
/* realiza a operação +1 ("assinalar") sobre o semáforo 0 do conjunto*/
void sem_assinalar(int id)
{
    sem_operacao(id, 1); /* assinalar */
}
/* realiza a operação 0 ("wait-for-zero") sobre o semáforo 0 do conjunto*/
void sem_wait40(int id) /* wait-for-zero*/
{
    sem_operacao(id, 0);
}
