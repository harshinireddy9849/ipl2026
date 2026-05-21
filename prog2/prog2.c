#include <stdio.h>

// Function Prototypes
void printBits(int num);
int countOneBits(int num);

int main() {
    int num;

    printf("Enter an integer: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // 1. Display the bits
    printf("\nAnalyzing integer %d:\n", num);
    printBits(num);

    // 2. Count and display the number of set bits (1s)
    int totalOnes = countOneBits(num);
    printf("Total number of 1 bits: %d\n", totalOnes);

    return 0;
}

// Function to print all bits of an integer (from MSB to LSB)
void printBits(int num) {
    // Dynamically calculate total bits for an integer on the current system (usually 32 bits)
    int totalBits = sizeof(int) * 8; 
    
    printf("Binary Representation: ");
    for (int i = totalBits - 1; i >= 0; i--) {
        // Shift the bit at position 'i' to the 1st position and mask it with 1
        int bit = (num >> i) & 1;
        printf("%d", bit);
        
        // Add a formatting space after every byte (8 bits) for scannability
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

// Function to count the number of 1 bits in an integer
int countOneBits(int num) {
    int count = 0;
    
    // Cast to an unsigned int to ensure safe right-shifting behavior 
    // if the user passes a negative number.
    unsigned int uNum = (unsigned int)num;

    while (uNum > 0) {
        // Check if the lowest bit (LSB) is a 1
        if (uNum & 1) {
            count++;
        }
        // Shift all bits to the right by 1 position to inspect the next bit
        uNum >>= 1;
    }
    
    return count;
}