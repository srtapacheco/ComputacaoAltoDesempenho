#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long page_size = sysconf(_SC_PAGESIZE);  // Tamanho da página de memória em bytes
    long mem_size = sysconf(_SC_PHYS_PAGES) * page_size;  // Tamanho total da memória física em bytes

    // Estimativa do tamanho máximo dos arranjos
    long max_n = (mem_size * 0.8) / (3 * sizeof(double));

    printf("Tamanho máximo estimado dos arranjos: %ld\n", max_n);

    return 0;
}
