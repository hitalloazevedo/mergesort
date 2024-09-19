// Para T threads e A arquivos, retorna um vetor com a distribuição das tarefas
// int tasks: quantidade total de arquivos a serem lidos
// int executors: quantidade de threads disponibilizadas
// int distribution[]: vetor de inteiros que armazenará a distribuição
// Exemplo: T=4 A=3 distribution=[1, 1, 1, 0]
// Exemplo: T=4 A=5 distribution=[2, 1, 1, 1]
void tasks_distributor(int tasks, int executors, int distribution[]);

// Extrai apenas os nomes dos arquivos de entradas da lista de argumentos
// E guarda no vetor de strings filenames
// char ** filenames: Vetor de strings onde será guardado o nome dos arquivos
// char ** argv: Vetor de strings com os argumentos do programa
// int argc: quantidade de argumentos do vetor argv
void extract_file_names_from_argv(char ** filenames, char ** argv, int argc);