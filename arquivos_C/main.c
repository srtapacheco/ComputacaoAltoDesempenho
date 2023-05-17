#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para medir o tempo de execução
double get_execution_time(struct timespec start, struct timespec end)
{
    double t;

    t = (end.tv_sec - start.tv_sec) * 1e9;
    t += (end.tv_nsec - start.tv_nsec);

    return t / 1e9;
}

int main()
{
    // Inicialização de variáveis
    int n_min = 0;              // Tamanho mínimo do problema
    int n_max = 40000;          // Tamanho máximo do problema
    int n_step = 10000;         // Tamanho do passo para aumentar o tamanho do problema
    double **A, *x, *b;         // Matrizes A, x e b
    int i, j, k, n;             // Contadores de loop
    double start, end, elapsed; // Variáveis para medir o tempo de execucao

    // Alocando memória para as matrizes A, x e b
    A = (double **)malloc(n_max * sizeof(double *));
    for (i = 0; i < n_max; i++)
    {
        A[i] = (double *)malloc(n_max * sizeof(double));
    }
    x = (double *)malloc(n_max * sizeof(double));
    b = (double *)malloc(n_max * sizeof(double));

    // Preenchimento das matrizes A e x com números aleatórios
    srand(time(NULL));
    for (i = 0; i < n_max; i++)
    {
        x[i] = (double)rand() / (double)RAND_MAX;
        for (j = 0; j < n_max; j++)
        {
            A[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }

    // Loop para aumentar o tamanho do problema e medir o tempo de execucao
    FILE *file = fopen("tempo_execucao.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    for (n = n_min; n <= n_max; n += n_step)
    {
        // Preenchimento da matriz b com zeros
        for (i = 0; i < n; i++)
        {
            b[i] = 0.0;
        }

        // Medição do tempo de execucao
        struct timespec start_time, end_time;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

        // Cálculo do produto matriz-vetor
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                b[i] += A[i][j] * x[j];
            }
        }

        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
        elapsed = get_execution_time(start_time, end_time);

        // Impressão do tempo de execucao no arquivo
        fprintf(file, "%d %f\n", n, elapsed);

        // Impressão do tempo de execucao no terminal
        printf("Tempo de execução para n = %d: %f segundos\n", n, elapsed);
    }

    // Liberação da memória alocada
    for (i = 0; i < n_max; i++)
    {
        free(A[i]);
    }
    free(A);
    free(x);
    free(b);
    // Fechamento do arquivo
    fclose(file);

    return 0;
}
