#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "git_commands.h"

void git_branch(Branch **branches, char *name, Branch *current_branch) {
    add_branch(branches, name, current_branch);
}

void git_commit(Branch *current_branch, char *message) {
    add_commit(current_branch, message);
}

int git_checkout(Branch **current_branch, Commit **current_commit, Branch *branches, char *name, Hash *ha) {
        
    int i, pos, newPos, nome = atoi(name);
    pos = chaveDivisao(nome, ha->TABLE_SIZE);

    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, mat, i, ha->TABLE_SIZE);


        if (ha->itens[newPos] == NULL) {
            break;      
            }
        if(valorString(ha->itens[newPos]->commits->message) == nome)
        {
            *current_branch = ha->itens[newPos];
            return 1;
        }
    }
        Branch *found_branch = find_branch(branches, name);
        if (found_branch) 
        {
        *current_branch = found_branch;
        return 0;
        }
        else {
        printf("Branch not found.\n");
        return 0;
        }
    }



void git_merge(Branch *current_branch, Branch *branches, char *name) {
    Branch *found_branch = find_branch(branches, name);

    int aux = 0;
    if (found_branch) {

        Branch *current_inverte = NULL;
        Branch *inverte = NULL;
        git_branch(&inverte, name, &current_inverte);
        current_inverte = inverte;
        git_commit(current_inverte, "First commit");

        Commit *inverte_commit = found_branch->commits;
        int cont = 0, aux2 = 0;

        while (inverte_commit) 
        {   
            cont++;
            if (strcmp(inverte_commit->message, "First commit") == 0 && inverte_commit->next == NULL) 
            
            {
            inverte_commit = inverte_commit->next;
            continue;
            }

        add_commit(current_inverte, inverte_commit->message);
        inverte_commit = inverte_commit->next;

        }




        Commit *current = inverte->commits;

        while (aux2 < cont) 
        {
            Commit *branch_aux = current_branch->commits;


            while(branch_aux)
            {

                if(strcmp(branch_aux->message, current->message) == 0)
                {
                    aux = 1;
                    break;
                }
                branch_aux = branch_aux->next;
            }

            if(aux == 0)
            {
                add_commit(current_branch, current->message);
            }
            aux = 0;
            current = current->next;
            aux2++;
            
            }
        }
    else{
        printf("Branch not found.\n");

    }
}

void git_log(Branch *current_branch) {
    print_branch_commits(current_branch);
}

void git_log_commit(Branch *current_commit) {
    print_commits(current_commit);
}
int numCommits(Branch *branches){

    Commit *current = branches->commits;

    int numCommits = 0;

    while(current != NULL)
 {
    numCommits++;
    current = current->next;
 }
    return numCommits;
}

void  git_push_branch(Branch *branches, Branch_Commit *new_branch_commit , int sockfd, char *message){

 // compute the length of the linked list we want to send
 
}