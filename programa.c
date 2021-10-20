#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TAMANHO 100000

// Quick Sort
void QuickSort(int *v, int tam) {
    int j = tam, k;
    if (tam <= 1) {
        return;
    }
    else {
        int x = v[0];
        int a = 1;
        int b = tam - 1;
        do {
            while ((a < tam) && (v[a] <= x)) {
                a++;
            }
            while (v[b] > x) {
                b--;
            }
            if (a < b) {
                int temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++;
                b--;
            }
        } while (a <= b);
        v[0] = v[b];
        v[b] = x;
        QuickSort(v, b);
        QuickSort(&v[a], tam - a);
    }
}

// Insertion Sort
void InsertionSort(int *v, int tam) {
    int i, j, k, chave;
    for (j = 1; j < tam; j++) {
        chave = v[j];
        i = j - 1;
        while ((i >= 0) && (v[i] > chave)) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = chave;
    }
}

// Selection Sort
void SelectionSort(int *v, int tam) {
    int i, j, k, min;
    for (i = 0; i < (tam - 1); i++) {
        min = i;
        for (j = (i + 1); j < tam; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (i != min) {
            int swap = v[i];
            v[i] = v[min];
            v[min] = swap;
        }
    }
}

// Bubble Sort
void BubbleSort(int *v, int tam) {
    int i, j = tam, k;
    int trocou;
    do {
        tam--;
        trocou = 0;
        for (i = 0; i < tam; i++) {
            if (v[i] > v[i + 1]) {
                int aux = 0;
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                trocou = 1;
            }
        }
    } while (trocou);
}

// Heap Sort
void PercorreArvore(int *v, int raiz, int folha) {
    int percorreu, maxfolhas, temp, k;
    percorreu = 0;
    while ((raiz * 2 <= folha) && (!percorreu)) {
        if (raiz * 2 == folha) {
            maxfolhas = raiz * 2;
        }
        else if (v[raiz * 2] > v[raiz * 2 + 1]) {
            maxfolhas = raiz * 2;
        }
        else {
            maxfolhas = raiz * 2 + 1;
        }
        if (v[raiz] < v[maxfolhas]) {
            temp = v[raiz];
            v[raiz] = v[maxfolhas];
            v[maxfolhas] = temp;
            raiz = maxfolhas;
        }
        else {
            percorreu = 1;
        }
    }
}

void HeapSort(int *v, int tam) {
    int i, k, temp;
    for (i = (tam / 2); i >= 0; i--) {
        PercorreArvore(v, i, tam - 1);
    }
    for (i = tam - 1; i >= 1; i--) {
        temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        PercorreArvore(v, 0, i - 1);
    }
}

// Merge Sort
void MergeSort(int *v, int inicio, int fim) {
    int i, j, k, meio, *t, z;
    if (inicio == fim) {
        return;
    }
    meio = (inicio + fim) / 2;
    MergeSort(v, inicio, meio);
    MergeSort(v, meio + 1, fim);
    i = inicio;
    j = meio + 1;
    k = 0;
    t = (int*)malloc(sizeof(int) * (fim - inicio + 1));
    while (i < meio + 1 || j < fim + 1) {
        if (i == meio + 1) {
            t[k] = v[j];
            j++; k++;
        }
        else if (j == fim + 1) {
            t[k] = v[i];
            i++; k++;
        }
        else if (v[i] < v[j]) {
            t[k] = v[i];
            i++; k++;
        }
        else {
            t[k] = v[j];
            j++; k++;
        }
    }
    for (i = inicio; i <= fim; i++) {
        v[i] = t[i - inicio];
    }
    free(t);
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Uso: ./programa [algoritmo] [caminho]\n");
        return 1;
    }

    if (realpath(argv[2], NULL) == NULL) {
        printf("O caminho passado não foi encontrado.\n");
        return 1;
    }

    FILE *arq;
    int tamanho;

    char temp[] = "";
    for (int i = 0; i < strlen(argv[2]); i++) {
        if ((int) argv[2][i] < 48 || (int) argv[2][i] > 57) {
            break;
        }
        temp[i] += argv[2][i];
    }
    if (strcmp(temp, "") == 0) {
        printf("Não foi possível alocar o tamanho do vetor.\n");
        return 1;
    }
    tamanho = atoi(temp);

    char valor[tamanho];

    if (strcmp(argv[1], "quick") == 0) {
        arq = fopen(realpath(argv[2], NULL), "r");
        if (arq == NULL) {
            printf("Arquivo não encontrado.");
            return 1;
        }
        while (!feof(arq))
        {
            fgets(valor, tamanho, arq);
            printf("%s", valor);
        }
    }
    // else if (strcmp(tolower(argv[1]), "insertion")) {
        
    // }
    // else if (strcmp(tolower(argv[1]), "selection")) {
        
    // }
    // else if (strcmp(tolower(argv[1]), "bubble")) {

    // }
    // else if (strcmp(tolower(argv[1]), "heap")) {

    // }
    // else if (strcmp(tolower(argv[1]), "merge")) {

    // }
    // else {
    //     printf("Algoritmo inexistente.");
    //     return 1;
    // }
    
    // SelectionSort(vqs, TAMANHO);
    return 0;
}
