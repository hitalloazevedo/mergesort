void tasks_distributor(int tasks, int executors, int distribution[]);

// Extrai apenas os nomes dos arquivos de entradas da lista de argumentos
// E guarda no vetor de strings filenames
// char ** filenames: Vetor de strings onde será guardado o nome dos arquivos
// char ** argv: Vetor de strings com os argumentos do programa
// int argc: quantidade de argumentos do vetor argv
void extract_file_names_from_argv(char ** filenames, char ** argv, int argc);