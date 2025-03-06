#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include "data_structures.h"
#include "git_commands.h"

#define PORT 4242
#define BUFFER_LENGTH 4096
#define TABLE_SIZE 1427

int main(void) {
    // Initialize data structures
    Branch *branches = NULL;
    Branch *current_branch = NULL;
    Hash *ha = criaHash(TABLE_SIZE);

    // Initialize the master branch and create the first commit
    git_branch(&branches, "master", &current_branch);
    current_branch = branches;
    git_commit(current_branch, "First commit");
    insereHash_EnderAberto(ha, current_branch);

    char vetor[100];
    printf("Abrindo socket do servidor...\n");

    // Socket structures
    struct sockaddr_in server, client;
    int serverfd, clientfd;
    char buffer[BUFFER_LENGTH];

    while (1) {
        printf("---------------------------------------------\n");
        printf("Iniciando o Servidor\n");

        // Create a TCP socket
        serverfd = socket(AF_INET, SOCK_STREAM, 0);
        if (serverfd == -1) {
            perror("Não foi possível criar o soquete do servidor:");
            return EXIT_FAILURE;
        }
        fprintf(stdout, "Soquete do servidor criado com fd: %d\n", serverfd);

        // Configure server socket
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = INADDR_ANY; // Accept connections on any interface
        memset(server.sin_zero, 0x0, 8);

        // Allow reuse of the port
        int yes = 1;
        if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("Erro nas opções do soquete:");
            close(serverfd);
            return EXIT_FAILURE;
        }

        // Bind the socket to the port
        if (bind(serverfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
            perror("Erro ao associar o soquete:");
            close(serverfd);
            return EXIT_FAILURE;
        }

        // Listen for incoming connections
        if (listen(serverfd, 1) == -1) {
            perror("Erro na espera de conexões:");
            close(serverfd);
            return EXIT_FAILURE;
        }
        fprintf(stdout, "Ouvindo na porta %d\n", PORT);

        // Accept a client connection
        socklen_t client_len = sizeof(client);
        clientfd = accept(serverfd, (struct sockaddr *)&client, &client_len);
        if (clientfd == -1) {
            perror("Erro ao aceitar conexão do cliente:");
            close(serverfd);
            return EXIT_FAILURE;
        }

        // Send welcome message to the client
        strcpy(buffer, "Olá, cliente!\n$\n$\0");
        if (send(clientfd, buffer, strlen(buffer), 0)) {
            fprintf(stdout, "Cliente conectado.\nAguardando mensagem do cliente ...\n");
            fprintf(stdout, "\n\nServer:\n");
            git_log(current_branch);

            // Handle client communication
            do {
                memset(buffer, 0x0, BUFFER_LENGTH);
                int received_bytes = recv(clientfd, buffer, BUFFER_LENGTH, 0);

                if (received_bytes == -1) {
                    perror("Falha ao receber dados do cliente");
                    break;
                }

                if (received_bytes == 0) {
                    fprintf(stdout, "Cliente desconectado.\n");
                    break;
                }

                if (strcmp(buffer, "exit") == 0) {
                    send(clientfd, "exit", 4, 0);
                    break;
                }

                printf("---------------------------------------------\n");
                printf("Pedido: %s\n", buffer);

                // Handle "Git pull" request
                if (strcmp(buffer, "Git pull") == 0) {
                    memset(buffer, 0x0, BUFFER_LENGTH);
                    send(clientfd, current_branch->name, BUFFER_LENGTH, 0);
                    recv(clientfd, buffer, 2, 0);

                    int aux3 = numCommits(current_branch);
                    char aux5[BUFFER_LENGTH];
                    sprintf(aux5, "%d", aux3);

                    memset(buffer, 0x0, BUFFER_LENGTH);
                    send(clientfd, aux5, BUFFER_LENGTH, 0);
                    recv(clientfd, buffer, 16, 0);

                    Commit *current = current_branch->commits;
                    while (current != NULL) {
                        memset(buffer, 0x0, BUFFER_LENGTH);
                        strcpy(vetor, current->message);
                        send(clientfd, vetor, 100, 0);
                        recv(clientfd, buffer, 15, 0);
                        current = current->next;
                    }

                    printf("\nBRANCH ENVIADO: %s\n", current_branch->name);
                    git_log(current_branch);
                    printf("\n\n");
                }

                // Handle "Git push" request
                if (strcmp(buffer, "Git push") == 0) {
                    send(clientfd, "Ok", 2, 0);

                    // Auxiliary branches
                    Branch *branches2 = NULL;
                    Branch *current_branch2 = NULL;
                    Hash *ha2 = criaHash(TABLE_SIZE);

                    Branch *branches3 = NULL;
                    Branch *current_branch3 = NULL;
                    Hash *ha3 = criaHash(TABLE_SIZE);

                    memset(buffer, 0x0, BUFFER_LENGTH);
                    recv(clientfd, buffer, BUFFER_LENGTH, 0);
                    printf("\nNome do branch recebido: %s\n", buffer);
                    char nome_branch[strlen(buffer)];
                    strcpy(nome_branch, buffer);

                    git_branch(&branches2, nome_branch, &current_branch2);
                    current_branch2 = branches2;
                    git_branch(&branches3, nome_branch, &current_branch3);
                    current_branch3 = branches3;

                    send(clientfd, "Branch recebido", 16, 0);

                    memset(buffer, 0x0, BUFFER_LENGTH);
                    recv(clientfd, buffer, BUFFER_LENGTH, 0);
                    printf("Numero de commits recebidos: %s\n", buffer);
                    send(clientfd, "numero de commits recebido", 27, 0);
                    int d = atoi(buffer);

                    memset(buffer, 0x0, BUFFER_LENGTH);
                    for (int i = 0; i < d; i++) {
                        memset(buffer, 0x0, BUFFER_LENGTH);
                        recv(clientfd, buffer, BUFFER_LENGTH, 0);
                        send(clientfd, "commit recebido", 15, 0);
                        git_commit(current_branch2, buffer);
                        insereHash_EnderAberto(ha2, current_branch2);
                    }

                    Commit *current_commit2 = current_branch2->commits;
                    while (current_commit2) {
                        memset(buffer, 0x0, BUFFER_LENGTH);
                        git_commit(current_branch3, current_commit2->message);
                        insereHash_EnderAberto(ha3, current_branch3);
                        current_commit2 = current_commit2->next;
                    }

                    free_branches(branches2);
                    git_merge(current_branch, branches3, nome_branch);
                    git_log(current_branch);
                    printf("\n");
                }

            } while (strcmp(buffer, "bye"));
        }

        // Close client and server sockets
        close(clientfd);
        close(serverfd);
        printf("Conexão fechada\n\n");
    }

    return EXIT_SUCCESS;
}