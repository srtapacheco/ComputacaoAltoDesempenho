#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define ELEMENT_SIZE_BYTES sizeof(double)

int main() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    long mem_capacity_bytes = pages * page_size;

    int n_max = (int)(sqrt(mem_capacity_bytes / (3 * ELEMENT_SIZE_BYTES)));

    printf("Valor máximo de n_max: %d\n", n_max);

    return 0;
}
