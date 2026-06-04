#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
void computeLPSArray(const char* pattern, int M, int* lps);
int KMPSearch(const char* text, const char* pattern);

int main() {
    char text[1000];
    char pattern[256];

    printf("Enter the main text string: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    // Remove trailing newline character from fgets
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the substring pattern to find: ");
    if (fgets(pattern, sizeof(pattern), stdin) == NULL) return 1;
    pattern[strcspn(pattern, "\n")] = '\0';

    printf("\nSearching for \"%s\" inside \"%s\"...\n", pattern, text);
    
    int index = KMPSearch(text, pattern);

    if (index != -1) {
        printf("Success! Pattern found starting at index: %d\n", index);
    } else {
        printf("Pattern not found in the given text.\n");
    }

    return 0;
}

// Function to perform the KMP string matching algorithm
int KMPSearch(const char* text, const char* pattern) {
    int N = strlen(text);
    int M = strlen(pattern);

    // Edge case: An empty pattern matches at the very beginning
    if (M == 0) return 0; 

    // Create a dynamic array to hold the longest prefix-suffix values
    int* lps = (int*)malloc(M * sizeof(int));
    if (lps == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    // Step 1: Precompute the LPS array
    computeLPSArray(pattern, M, lps);

    int i = 0; // Index pointer for text[]
    int j = 0; // Index pointer for pattern[]
    int foundIndex = -1;

    // Step 2: Scan the text
    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            // Match found! Calculate the starting index
            foundIndex = i - j;
            break; // Stop at first match. (Remove break if you want all matches)
        }
        // Mismatch occurred after j matches
        else if (i < N && pattern[j] != text[i]) {
            // Do not match lps[0..lps[j-1]] characters, they will match anyway
            if (j != 0) {
                j = lps[j - 1]; // Fallback smoothly using our precomputed jumps
            } else {
                i++; // If no characters matched yet, just move to the next text character
            }
        }
    }

    free(lps); // Clean up allocated memory
    return foundIndex;
}

// Helper function to populate the LPS (Longest Proper Prefix which is also Suffix) table
void computeLPSArray(const char* pattern, int M, int* lps) {
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            // Mismatch sequence path
            if (len != 0) {
                len = lps[len - 1]; // Fallback to previous structural state
                // Note: We do NOT increment i here
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}