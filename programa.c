#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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

// Obter o tamanho do vetor pelo total de valores dentro do arquivo
int GetTamanhoVetorArquivo(char *p) {
    FILE *arq = fopen(p, "r");
    if (arq == NULL) {
        printf("Arquivo não encontrado.\n");
        return 0;
    }
    char linha[128];
    int tam = -1;
    while (fscanf(arq, "%[^\n]", linha) != EOF) {
        fgetc(arq);
        tam++;
    }
    fclose(arq);
    return tam;
}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        printf("Uso [dados externos]: ./programa [type] [algoritmo] [caminho]\nUso [dados internos]: ./programa [type] [algoritmo] [tamanho]\n");
        return 1;
    }

    FILE *arquivo;
    int tamanho, *v;
    char algoritmo[100];

    strcpy(algoritmo, argv[2]);

    // Gerar dados externos (Arquivos de texto)
    if (strcmp(argv[1], "-e") == 0) {
        char *caminho = realpath(argv[3], NULL);
        if (caminho == NULL) {
            printf("O caminho passado não foi encontrado.\n");
            return 1;
        }
        tamanho = GetTamanhoVetorArquivo(caminho);
        v = malloc(tamanho * sizeof(int));
        if (tamanho > 0) {
            arquivo = fopen(caminho, "r");
            if (arquivo == NULL) {
                printf("Arquivo não encontrado.\n");
                return 1;
            }
            char linha[128];
            for (int i = 0; i < tamanho; i++) {
                fscanf(arquivo, "%[^\n]", linha);
                fgetc(arquivo);
                v[i] = atoi(linha);
            }
            fclose(arquivo);
        }
        else {
            printf("O arquivo está vazio.\n");
            return 1;
        }
    }
    // Gerar dados internos (Aleatórios)
    else if (strcmp(argv[1], "-i") == 0) {
        for (int i = 0; i < strlen(argv[3]); i++) {
            if (argv[3][i] < 48 || argv[3][i] > 57) {
                printf("Digite um número inteiro positivo válido\n");
                return 1;
            }
        }
        tamanho = atoi(argv[3]);
        v = malloc(tamanho * sizeof(int));
        srand(time(0));
        for (int i = 0; i < tamanho; i++) {
            v[i] = rand();
        }
    }
    else {
        printf("Escolha entre gerar dados externos [-e] ou internos [-i]\n");
        return 1;
    }

    // Copiar os dados dentro do vetor para uma variável temporária para guardar os dados não ordenados
    int *vtemp = malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) {
        vtemp[i] = v[i];
    }

    clock_t inicio, fim, total;

    inicio = clock();
    if (strcmp(algoritmo, "quick") == 0) {
        printf("Iniciando o algoritmo QuickSort... ");
        QuickSort(v, tamanho);
    }
    else if (strcmp(algoritmo, "insertion") == 0) {
        printf("Iniciando o algoritmo InsertionSort... ");
        InsertionSort(v, tamanho);
    }
    else if (strcmp(algoritmo, "selection") == 0) {
        printf("Iniciando o algoritmo SelectionSort... ");
        SelectionSort(v, tamanho);
    }
    else if (strcmp(algoritmo, "bubble") == 0) {
        printf("Iniciando o algoritmo BubbleSort... ");
        BubbleSort(v, tamanho);
    }
    else if (strcmp(algoritmo, "heap") == 0) {
        printf("Iniciando o algoritmo HeapSort... ");
        HeapSort(v, tamanho);
    }
    else if (strcmp(algoritmo, "merge") == 0) {
        printf("Iniciando o algoritmo MergeSort... ");
        MergeSort(v, 0, tamanho - 1);
    }
    else {
        printf("Algoritmo não encontrado.\n");
        return 1;
    }
    fim = clock();

    // CLOCKS_PER_SEC = 1.000.000
    total = (double) (fim - inicio) / CLOCKS_PER_SEC;

    // Gerar o benchmark
    arquivo = fopen("benchmark.txt", "w");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado.\n");
        return 1;
    }

    fprintf(arquivo, "Algoritmo: %s\n", algoritmo);

    fprintf(arquivo, "Dados: ");
    for (int k = 0; k < tamanho; k++) {
        fprintf(arquivo, "%d", vtemp[k]);
        if (k == tamanho - 1) {
            continue;
        }
        fprintf(arquivo, ", ");
    }

    fprintf(arquivo, "\nDados ordenados: ");
    for (int k = 0; k < tamanho; k++) {
        fprintf(arquivo, "%d", v[k]);
        if (k == tamanho - 1) {
            continue;
        }
        fprintf(arquivo, ", ");
    }

    fprintf(arquivo, "\n%s: %s\n", strcmp(argv[1], "-e") == 0 ? "Caminho" : "Tamanho", argv[3]);
    fprintf(arquivo, "\t-> Início: %ld ms\n\t-> Fim: %ld ms\n\t-> Total: %ld segundos\n\n", inicio / 1000, fim / 1000, total);
    fclose(arquivo);

    printf("Resultados gravados em benchmark.txt\n");

    free(vtemp);
    free(v);

    return 0;
}
