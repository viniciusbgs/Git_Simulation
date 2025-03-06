#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "data_structures.h"
#include "git_commands.h"


/* Define a porta do servidor */
#define PORT 4242


/* Tamanho dos buffers dos sockets */
#define LEN 4096


/* Endereço do servidor */
#define SERVER_ADDR "127.0.0.1"


#define TABLE_SIZE 1427


/*
 * Execução principal do programa cliente do nosso protocolo simples
 */
int
main(int argc, char *argv[]) {

    /* Socket do servidor */
    struct sockaddr_in server;
    /* Descritor de arquivo do cliente para o socket local */
    int sockfd;
    int len = sizeof(server);
    int slen;

    /* Buffer de recebimento */
    char buffer_in[LEN];
    /* Buffer de envio */
    char buffer_out[LEN];


    fprintf(stdout, "Iniciando Cliente ...\n");


    /*
     * Cria um socket para o cliente
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Erro na criação do socket do cliente:");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "Socket do cliente criado com fd: %d\n", sockfd);


    /* Define as propriedades da conexão */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    memset(server.sin_zero, 0x0, 8);


    /* Tenta se conectar ao servidor */
    if (connect(sockfd, (struct sockaddr*) &server, len) == -1) {
        perror("Não é possível conectar ao servidor");
        return EXIT_FAILURE;
    }


    /* Recebe a mensagem de apresentação do servidor */

        //recebe : ola cliente
    if ((slen = recv(sockfd, buffer_in, LEN, 0)) > 0)
     {
        buffer_in[slen + 1] = '\0';
        fprintf(stdout, "O servidor diz: %s\n", buffer_in);
     }


    Branch *branches = NULL;
    Branch *current_branch = NULL;  
    Commit *commits = NULL;
    Commit *current_commit = NULL;
    Hash *ha = criaHash(TABLE_SIZE);

    Branch_Commit *branch_commit = NULL;

  char vetor[LEN], vetor2[LEN], vetor3[LEN];


    // Inicializando o branch master e criando o primeiro commit
    git_branch(&branches, "master", &current_branch);
    current_branch = branches;
    git_commit(current_branch, "First commit");
    insereHash_EnderAberto(ha, current_branch);

int aux2 = 0, aux = 0;
while (aux2 == 0)
{
    char *comando = (char*) malloc(60 * sizeof(char));
    char *nome = (char*) malloc(strlen(comando) * sizeof(char));

    // git_log(current_branch);

    printf("$ ");
    fgets(buffer_out, LEN, stdin);


    int len = strlen(buffer_out);
    if (len > 0 && buffer_out[len-1] == '\n')
    { 
      buffer_out[len-1] = '\0';
    }

    strcpy(comando, buffer_out);
    if(strcmp(comando, "exit") == 0){
      aux2++;
      send(sockfd, comando, strlen(comando), 0);
      break;
    }

    int size = strlen(comando), p = 0;

      if(comando[0] == '\0'|| comando[0] == '\t'|| comando[0] == '\n')
      {
      continue;
      }



      //recebendo comando do usuario

        /* Limpa os buffers */
        memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);



//funcao para verificar o comando
//retorna um valor inteiro pra identificar o tipo

  p = verifica_git (branches, current_branch, comando, nome,  size);
  if(p == 0){
  printf("Comando Invalido!\n");
  }
  if(p == 1){
    if(aux == 0){
  git_log(current_branch);
    } 
    if(aux == 1){
  git_log_commit(current_branch);
    }
 }
  else if(p == 2){
  git_commit(current_branch, nome);
  insereHash_EnderAberto(ha, current_branch);
 }
  else if(p == 3){

  git_merge(current_branch, branches, nome);

 }
  else if(p == 4){
  git_branch(&branches, nome, current_branch);
 }
 else if(p == 5){
  aux = git_checkout(&current_branch, &current_commit, branches, nome, ha);
    }

  
  else if(p == 6)
  {
    //envia o comando:
      strcpy(buffer_in, "Git pull");
      send(sockfd, buffer_in, LEN, 0);

                  //branch auxiliar invertido
                    Branch *branches2 = NULL;
                    Branch *current_branch2 = NULL;  
                    Hash *ha2 = criaHash(TABLE_SIZE);

                    //branch auxiliar corrigido
                    Branch *branches3 = NULL;
                    Branch *current_branch3 = NULL;  
                    Hash *ha3 = criaHash(TABLE_SIZE);

                    //recebe o nome do branch:
                    recv(sockfd, buffer_in, LEN, 0);            
                    // printf("\n\nNome do branch recebido: %s\n", buffer_in);
                    char nome_branch[strlen(buffer_in)];
                    strcpy(nome_branch, buffer_in);
                    memset(buffer_in, 0x0, LEN);


                    // criando branch auxiliar 1
                    git_branch(&branches2, nome_branch, &current_branch2);
                    current_branch2 = branches2;
                    //criando branch auxiliar 2
                    git_branch(&branches3, nome_branch, &current_branch3);
                    current_branch3 = branches3;

                    //envia que recebeu o branch:
                    send(sockfd, "Ok", 2, 0);

                    // git_branch(&branches, buffer_in, &current_branch);
                    // git_checkout(&current_branch, &current_commit, branches, buffer_in, ha);
                    
                    //recebe o numero de commits: (3o recv)
                    recv(sockfd, buffer_in, LEN, 0);
                    //envia que recebeu o numero de commits:
                    send(sockfd, "recebi o numero", 16, 0);
                    printf("Numero de commits recebidos: %s\n$", buffer_in);

                    int d = atoi(buffer_in);

                    //recebe os commits: (4o recv)
                    for(int i = 0; i < d; i++) {
                        memset(buffer_in, 0x0, LEN);
                        recv(sockfd, buffer_in, 100, 0);
                        // printf("Mensagem recebida do cliente: %s\n", buffer_in);
                        send(sockfd, "commit recebido", 15, 0);
                        git_commit(current_branch2, buffer_in);
                        insereHash_EnderAberto(ha2, current_branch2);
                        }

                    // printf("\n\n");
                    // git_log(current_branch2);

                    Commit *current_commit2 = current_branch2->commits;
                    printf("\n");
                    while(current_commit2){
                        memset(buffer_in, 0x0, LEN);
                        git_commit(current_branch3, current_commit2->message);

                        insereHash_EnderAberto(ha3, current_branch3);
                        current_commit2 = current_commit2->next;
                    }
                    //  printf("\ncuurent branch 3:\n");
                    //  git_log(current_branch3);

                    //  printf("\ncuurent branch:\n");
                    // git_log(current_branch);

                    free_branches(branches2);
                    // git_merge(current_branch, branches3, nome_branch);


                    // printf("\nnome: %s\n", nome_branch);
                    //  current_branch->name = nome_branch;


                    // char *vetor9 = (char*) malloc(60 * sizeof(char));
                    // strcpy(vetor9, nome_branch);
                    // printf("\nnome: %s\n", vetor9);
                    // strcpy(current_branch->name, vetor9);
                    // git_log(current_branch);

  }
  else if(p == 7)
  {        
        memset(buffer_in, 0x0, LEN);
        memset(buffer_out, 0x0, LEN);

        Branch  *found_branch = find_branch(branches, nome);

        if (found_branch == NULL) 
        {
            printf("Branch not found.\n");
            continue;
        }
        else
        {
            //envia o comando:
            send(sockfd, "Git push", 8, 0);
            //recebe ok
            recv(sockfd, buffer_in, 2, 0);

            // envia o nome do branch:
            strcpy(vetor,found_branch->name);
            send(sockfd, vetor, LEN, 0);
            recv(sockfd, buffer_in, 16, 0);
        
            int aux3 = numCommits(found_branch);
            char aux5[LEN];
            sprintf(aux5, "%d", aux3);

            memset(buffer_in, 0x0, LEN);

            //envia o numero de commits:
            send(sockfd, aux5, LEN, 0);
            recv(sockfd, buffer_in, 27, 0);

            // envia os commits:

            Commit *current = found_branch->commits;
            while (current != NULL)
            {    

            memset(buffer_in, 0x0, LEN);

            strcpy(vetor, current->message);
            send(sockfd, vetor, LEN, 0);
            recv(sockfd, buffer_in, 15, 0);
            current = current->next;
            }
        }

  }  
  
    else { 
      continue;
       }
    }

  free_branches(branches);
  

    close(sockfd);

    fprintf(stdout, "\nConexão fechada\n\n");

    printf("Saindo...\n");

    return EXIT_SUCCESS;
}











/*

mandar char do commit 




*/