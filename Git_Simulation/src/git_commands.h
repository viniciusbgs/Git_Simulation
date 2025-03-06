#ifndef GIT_COMMANDS_H
#define GIT_COMMANDS_H

#include "data_structures.h"

void git_commit(Branch *current_branch, char *message);
void git_branch(Branch **branches, char *name, Branch *current_branch);
int git_checkout(Branch **current_branch, Commit **current_commit, Branch *branches, char *name, Hash *ha);
void git_merge(Branch *current_branch, Branch *branches, char *name);
void git_log(Branch *current_branch);
void git_log_commit(Branch *current_commit);
void  git_push_branch(Branch *branches, Branch_Commit *new_branch_commit , int sockfd, char *message);
int numCommits(Branch *branches);

#endif