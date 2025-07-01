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
    int i, j;
    int count = 0;

    printf("\nMemory Status:\n");

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            count++;
            j = i;
            while (j < MAX_MEMORY && memory[j] == -1) {
                j++;
            }
            printf("Free memory block %d-%d (Size: %d)\n", i, j - 1, j - i);
            i = j - 1;
        }
    }

    if (count == 0) {
        printf("No free memory available.\n");
    }
}

// Function to allocate memory using Worst-Fit algorithm
void allocateMemory(int processId, int size) {
    int bestStart = -1;
    int bestSize = -1;

    for (int i = 0; i < MAX_MEMORY;) {
        if (memory[i] == -1) {
            int start = i;
            int blockSize = 0;

            while (i < MAX_MEMORY && memory[i] == -1) {
                blockSize++;
                i++;
            }

            if (blockSize >= size && blockSize > bestSize) {
                bestStart = start;
                bestSize = blockSize;
            }
        } else {
            i++;
        }
    }

    if (bestStart != -1) {
        for (int i = bestStart; i < bestStart + size; i++) {
            memory[i] = processId;
        }
        printf("Allocated memory block %d-%d to Process %d\n", bestStart, bestStart + size - 1, processId);
    } else {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
    }
}

// Function to deallocate memory
void deallocateMemory(int processId) {
    int released = 0;
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
            released = 1;
        }
    }

    if (released) {
        printf("Memory released by Process %d\n", processId);
    } else {
        printf("No memory found for Process %d\n", processId);
    }
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
