#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; // -1 indicates that the memory is unallocated
    }
}

// Function to display memory status
void displayMemory() {
    int i = 0;
    int count = 0;

    printf("Memory Status:\n");
    while (i < MAX_MEMORY) {
        if (memory[i] == -1) {
            int start = i;
            while (i < MAX_MEMORY && memory[i] == -1) {
                i++;
            }
            printf("Free memory block %d - %d\n", start, i - 1);
            count++;
        } else {
            i++;
        }
    }

    if (count == 0) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using best-fit algorithm
void allocateMemory(int processId, int size) {
    int bestStart = -1;
    int bestSize = MAX_MEMORY + 1;

    int i = 0;
    while (i < MAX_MEMORY) {
        if (memory[i] == -1) {
            int start = i;
            int blockSize = 0;
            while (i < MAX_MEMORY && memory[i] == -1) {
                blockSize++;
                i++;
            }

            if (blockSize >= size && blockSize < bestSize) {
                bestSize = blockSize;
                bestStart = start;
            }
        } else {
            i++;
        }
    }

    if (bestStart != -1) {
        for (int j = bestStart; j < bestStart + size; j++) {
            memory[j] = processId;
        }
        printf("Allocated memory block %d - %d to Process %d\n", bestStart, bestStart + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
        }
    }
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory();
    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}
