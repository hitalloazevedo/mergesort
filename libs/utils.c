#include "utils.h"

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