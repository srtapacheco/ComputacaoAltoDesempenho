#include <stdio.h>
#include <math.h>

int main() {
    double GB_to_bytes = 1024 * 1024 * 1024;
    double mem_capacity_GB = 16.0;
    double mem_capacity_bytes = mem_capacity_GB * GB_to_bytes;

    double element_size_bytes = sizeof(double);

    int n_max = (int) (sqrt(mem_capacity_bytes / (3 * element_size_bytes)));

    printf("Valor máximo de n_max: %d\n", n_max);

    return 0;
}
