#include "classification.h"
#include <stdlib.h>

void mergesort(int *v, int n) {
  int *c = malloc(sizeof(int) * n);
  sort(v, c, 0, n - 1);
  free(c);
}

/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(int *v, int *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (v[m] <= v[m + 1]) return;

  merge(v, c, i, m, f);
}


/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(int *v, int *c, int i, int m, int f) {
  int z,
      iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv] <= c[ic]) v[z++] = c[iv++];
    else v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}
























// #include <stdio.h>
// #include <stdlib.h>

// // Função para mesclar duas metades
// void merge(int arr[], int left, int mid, int right) {
//     int i, j, k;
//     int n1 = mid - left + 1;  // Tamanho da primeira metade
//     int n2 = right - mid;     // Tamanho da segunda metade

//     // Vetores temporários
//     int *L = (int*) malloc(n1 * sizeof(int));
//     int *R = (int*) malloc(n2 * sizeof(int));

//     // Copiar os dados para os vetores temporários L[] e R[]
//     for (i = 0; i < n1; i++)
//         L[i] = arr[left + i];
//     for (j = 0; j < n2; j++)
//         R[j] = arr[mid + 1 + j];

//     // Mesclar os vetores temporários de volta no arr[]
//     i = 0; // Índice inicial do primeiro subvetor (L)
//     j = 0; // Índice inicial do segundo subvetor (R)
//     k = left; // Índice inicial do vetor mesclado

//     while (i < n1 && j < n2) {
//         if (L[i] <= R[j]) {
//             arr[k] = L[i];
//             i++;
//         } else {
//             arr[k] = R[j];
//             j++;
//         }
//         k++;
//     }

//     // Copiar os elementos restantes de L[], se houver
//     while (i < n1) {
//         arr[k] = L[i];
//         i++;
//         k++;
//     }

//     // Copiar os elementos restantes de R[], se houver
//     while (j < n2) {
//         arr[k] = R[j];
//         j++;
//         k++;
//     }

//     // Liberar a memória alocada
//     free(L);
//     free(R);
// }

// // Função recursiva para o Merge Sort
// void mergeSort(int arr[], int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;

//         // Ordena a primeira e a segunda metades
//         mergeSort(arr, left, mid);
//         mergeSort(arr, mid + 1, right);

//         // Mescla as duas metades ordenadas
//         merge(arr, left, mid, right);
//     }
// }

// // Função para imprimir o array
// void printArray(int arr[], int size) {
//     for (int i = 0; i < size; i++)
//         printf("%d ", arr[i]);
//     printf("\n");
// }

// // Programa principal
// // int main() {
// //     int arr[] = {12, 11, 13, 5, 6, 7};
// //     int arr_size = sizeof(arr) / sizeof(arr[0]);

// //     printf("Array original: \n");
// //     printArray(arr, arr_size);

// //     mergeSort(arr, 0, arr_size - 1);

// //     printf("\nArray ordenado: \n");
// //     printArray(arr, arr_size);

// //     return 0;
// // }
