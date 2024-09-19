#include "utils.h"
#include <string.h>

void tasks_distributor(int tasks, int executors, int distribution[]) {
    int q = tasks / executors;  // Calcula o quociente
    int r = tasks % executors;  // Calcula o resto

    // Distribui as tarefas
    for (int i = 0; i < executors; i++) {
        if (i < r) {
            distribution[i] = q + 1;  // Os primeiros 'r' executores recebem uma tarefa extra
        } else {
            distribution[i] = q;  // Os restantes recebem 'q' tarefas
        }
    }
}

void extract_file_names_from_argv(char ** filesnames, char ** argv, int argc){
    for (int i = 0; i < argc; i++){
        if (i > 1 && i < argc - 2){
            strcpy(filesnames[i - 2], argv[i]);
        }
    }
}