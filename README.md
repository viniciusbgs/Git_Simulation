Git Simulation 
==============

This project is a simulation of a version control system similar to Git, implemented in C. It includes basic functionalities such as creating branches, making commits, merging branches, checking out branches, pulling changes, and pushing changes. The project consists of a server and a client that communicate via sockets.


Features
--------

-   **Branch Creation**: Create new branches to work on different versions of the project.

-   **Commits**: Save changes to a specific branch.

-   **Merge**: Combine changes from two branches.

-   **Checkout**: Switch between existing branches.

-   **Pull**: Synchronize the local branch with the remote branch.

-   **Push**: Send local changes to the remote branch.

-   **Log**: View the commit history of the current branch.



Project Structure
-----------------

-   **`server.c`**: Implementation of the server that manages branches and commits.

-   **`client.c`**: Implementation of the client that interacts with the server.

-   **`data_structures.h` and `data_structures.c`**: Definition and implementation of the data structures used in the project (branches, commits, etc.).

-   **`git_commands.h` and `git_commands.c`**: Implementation of Git functionalities (branch, commit, merge, etc.).

-   **`tabelahash.c`**: Implementation of a hash table to store branches.

How to Run
----------

### Prerequisites

-   C compiler (e.g., `gcc`).

-   Unix-like operating system (Linux, macOS, etc.).

### Step-by-Step Guide

#### 1\. **Clone the Repository**

First, clone the project repository to your local environment:

```bash
git clone https://github.com/viniciusbgs/Git_Simulation.git
```

#### 2\. **Navigate to the Project Folder**

After cloning the repository, navigate to the project folder:

```bash
cd Git_Simulation/src
```


#### 3\. **Compile the Project**

Compile the project using `make` or manually with `gcc`:

**Option 1: Using `make` (if a Makefile is available):**

```bash
make
```

**Option 2: Manual compilation with `gcc`:**

```bash

gcc -o server server.c data_structures.c git_commands.c tabelahash.c
gcc -o client client.c data_structures.c git_commands.c tabelahash.c
```

This will generate two executables: `server` and `client`.



### Execution

1.  Start the server:

    ```bash
    ./server

2.  In another terminal, start the client:

    ```bash
    ./client

3.  Use the available commands in the client to interact with the server.

Available Commands in the Client
--------------------------------

-   **`git branch <name>`**: Create a new branch.

-   **`git commit <message>`**: Create a commit in the current branch.

-   **`git merge <branch>`**: Merge the current branch with the specified branch.

-   **`git checkout <branch>`**: Switch to the specified branch.

-   **`git pull`**: Synchronize the local branch with the remote branch.

-   **`git push`**: Send local changes to the remote branch.

-   **`git log`**: View the commit history of the current branch.



-   **`exit`**: Exit the client.

Example Usage
-------------

1.  Create a branch:

    ```bash
    $ git branch feature

2.  Switch to the new branch:
   
   ```bash
   $ git checkout feature
   ```
 
2.  Make a commit:

    ```bash
    $ git commit "Add new feature"

3.  Switch to another branch:

   ```bash
    $ git checkout master
```
4.  Merge branches:

    ```bash
    $ git merge feature

5.  Synchronize with the server:

    ```bash
    $ git pull

6.  Send changes to the server:

    ```bash
    $ git push

7. View log

    ```bash
    $ git log
    
