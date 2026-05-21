#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

// Define the structure
typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

// Function Prototypes
void storeASCII(const char *filename, Student arr[], int n);
int createIndex(const char *filename, long positions[], int max_size);
void displayRecordAtPosition(const char *filename, long pos);

int main() {
    const char *filename = "students.txt";
    Student students[MAX_RECORDS];
    int n;

    // Get the number of records from the user
    printf("How many student records do you want to enter? (Max %d): ", MAX_RECORDS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_RECORDS) {
        printf("Invalid number of records.\n");
        return 1;
    }

    // Loop to collect user input for the array of structures
    for (int i = 0; i < n; i++) {
        printf("\n--- Enter Details for Student %d ---\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        
        printf("Name: ");
        scanf("%s", students[i].name);
        
        printf("GPA: ");
        scanf("%f", &students[i].gpa);
    }

    printf("\nAll data collected. Writing to file...\n");

    // 1. Store the user-inputted array of structures in ASCII format
    storeASCII(filename, students, n);

    // 2. Build the array of seek positions dynamically based on file contents
    long seekPositions[MAX_RECORDS];
    int recordCount = createIndex(filename, seekPositions, MAX_RECORDS);

    printf("\nSuccessfully indexed %d records from the ASCII file.\n", recordCount);

    // Display the generated index map for visualization
    printf("\n--- Generated Index Map (Byte Offsets) ---\n");
    for (int i = 0; i < recordCount; i++) {
        printf("Record %d starts at byte offset: %ld\n", i + 1, seekPositions[i]);
    }
    printf("------------------------------------------\n");

    // 3. Prompt user to jump to a specific record using the index map
    int targetRecord;
    printf("\nEnter a record number to fetch (1 to %d) or 0 to exit: ", recordCount);
    while (scanf("%d", &targetRecord) == 1 && targetRecord != 0) {
        if (targetRecord > 0 && targetRecord <= recordCount) {
            printf("Jumping to Record %d using fseek...\n", targetRecord);
            // Indexing is 0-based, so we look up targetRecord - 1
            displayRecordAtPosition(filename, seekPositions[targetRecord - 1]);
        } else {
            printf("Invalid record number. Try again.\n");
        }
        printf("\nEnter a record number to fetch (1 to %d) or 0 to exit: ", recordCount);
    }

    printf("Exiting program.\n");
    return 0;
}

// Function to store the array of structures as a formatted text file (ASCII)
void storeASCII(const char *filename, Student arr[], int n) {
    FILE *file = fopen(filename, "w"); // 'w' opens the file for text writing
    if (!file) {
        perror("Error opening file for writing");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        // Each record is written as a single line
        fprintf(file, "%d %s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }

    fclose(file);
    printf("ASCII File '%s' successfully created/updated.\n", filename);
}

// Function to generate an array containing the starting byte offset of each record
int createIndex(const char *filename, long positions[], int max_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for indexing");
        return 0;
    }

    int count = 0;
    long current_pos;
    char buffer[256];

    // Read line by line. Track the position *before* reading the line.
    while (count < max_size) {
        current_pos = ftell(file); // Capture the byte position right before reading the line
        
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            break; // End of file reached
        }
        
        positions[count] = current_pos;
        count++;
    }

    fclose(file);
    return count; // Returns total records found and indexed
}

// Function to jump to a specific byte offset and print the ASCII record
void displayRecordAtPosition(const char *filename, long pos) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading record");
        return;
    }

    // Use fseek to skip directly to the mapped byte position
    if (fseek(file, pos, SEEK_SET) != 0) {
        printf("Error running fseek to target position.\n");
        fclose(file);
        return;
    }

    Student s;
    // Parse the ASCII string back into our structure format
    if (fscanf(file, "%d %s %f", &s.id, s.name, &s.gpa) == 3) {
        printf(" -> [Found] ID: %d | Name: %s | GPA: %.2f\n", s.id, s.name, s.gpa);
    } else {
        printf(" -> Error: Failed to parse data at position %ld\n", pos);
    }

    fclose(file);
}