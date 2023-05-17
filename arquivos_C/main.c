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
    double **A, *x, *b_i, *b_j; // Matrizes A, x, b (loop externo i), b (loop externo j)
    int i, j, k, n;             // Contadores de loop
    double start, end, elapsed; // Variáveis para medir o tempo de execução

    // Alocando memória para as matrizes A, x e b
    A = (double **)malloc(n_max * sizeof(double *));
    for (i = 0; i < n_max; i++)
    {
        A[i] = (double *)malloc(n_max * sizeof(double));
    }
    x = (double *)malloc(n_max * sizeof(double));
    b_i = (double *)malloc(n_max * sizeof(double));
    b_j = (double *)malloc(n_max * sizeof(double));

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

    // Loop para aumentar o tamanho do problema e medir o tempo de execução
    FILE *file = fopen("tempo_execucao.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    for (n = n_min; n <= n_max; n += n_step)
    {
        // Preenchimento das matrizes b_i e b_j com zeros
        for (i = 0; i < n; i++)
        {
            b_i[i] = 0.0;
            b_j[i] = 0.0;
        }

        // Medição do tempo de execução para o loop externo i
        struct timespec start_time, end_time;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

        // Cálculo do produto matriz-vetor (loop externo i)
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                b_i[i] += A[i][j] * x[j];
            }
        }

        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
        elapsed = get_execution_time(start_time, end_time);

        // Impressão do tempo de execução no arquivo para o loop externo i
        fprintf(file, "%d %f ", n, elapsed);

        // Medição do tempo de execução para o loop externo j
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);

        // Reinicialização da matriz b_j para zeros
        for (i = 0; i < n; i++)
        {
            b_j[i] = 0.0;
        }

        // Cálculo do produto matriz-vetor (loop externo j)
        for (j = 0; j < n; j++)
        {
            for (i = 0; i < n; i++)
            {
                b_j[i] += A[i][j] * x[j];
            }
        }

        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
        elapsed = get_execution_time(start_time, end_time);

        // Impressão do tempo de execução no arquivo para o loop externo j
        fprintf(file, "%f\n", elapsed);

        // Impressão do tempo de execução no terminal
        printf("Tempo de execução para n = %d (i no loop externo): %f segundos\n", n, elapsed);

        // Impressão do tempo de execução no terminal
        printf("Tempo de execução para n = %d (j no loop externo): %f segundos\n", n, elapsed);
    }

    // Liberação da memória alocada
    for (i = 0; i < n_max; i++)
    {
        free(A[i]);
    }
    free(A);
    free(x);
    free(b_i);
    free(b_j);
    // Fechamento do arquivo
    fclose(file);

    return 0;
}
