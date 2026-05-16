#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the record
typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

// Function prototypes
void storeRecords(const char *filename, int n);
void getRecord(const char *filename, int m);
void deleteRecord(const char *filename, int m);
void displayAllRecords(const char *filename);

int main() {
    const char *filename = "students.dat";
    int n, m, choice;

    printf("How many records do you want to enter? ");
    if (scanf("%d", &n) != 1) return 1;

    // 1. Store n records
    storeRecords(filename, n);
    displayAllRecords(filename);

    // 2. Fetch the m-th record using fseek
    printf("\nEnter the record number you want to fetch: ");
    scanf("%d", &m);
    getRecord(filename, m);

    // 3. Delete a record
    printf("\nEnter the record number you want to delete: ");
    scanf("%d", &m);
    deleteRecord(filename, m);

    // Display final file contents to verify deletion
    printf("\n--- File Contents After Deletion ---\n");
    displayAllRecords(filename);

    return 0;
}

// Function to write N records into the binary file
void storeRecords(const char *filename, int n) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        exit(1);
    }

    Student s[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Record %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &s[i].id);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("GPA: ");
        scanf("%f", &s[i].gpa);
    }
    fwrite(&s, sizeof(Student), n, file);
    fclose(file);
    printf("\nSuccessfully stored %d records.\n", n);
}

// Function to fetch and display the m-th record using fseek
void getRecord(const char *filename, int m) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    Student s;
    // Calculate byte offset: (m - 1) * size of one structure
    long offset = (long)(m - 1) * sizeof(Student);

    // Using fseek to jump directly to the target location
    if (fseek(file, offset, SEEK_SET) != 0) {
        printf("Error: Could not seek to record %d (it might be out of bounds).\n", m);
        fclose(file);
        return;
    }

    // Read the single record at this position
    if (fread(&s, sizeof(Student), 1, file) == 1) {
        printf("\n[Record %d Found]\n", m);
        printf("ID: %d\nName: %s\nGPA: %.2f\n", s.id, s.name, s.gpa);
    } 
    else {
        printf("Error: Record %d does not exist.\n", m);
    }

    fclose(file);
}

// Function to physically delete the m-th record using a temporary file
void deleteRecord(const char *filename, int m) {
    FILE *file = fopen(filename, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!file) {
        perror("Error opening original file for deletion");
        if (temp) fclose(temp);
        return;
    }
    if (!temp) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    Student s;
    int currentRecord = 1;
    int found = 0;

    // Read sequentially through the file
    while (fread(&s, sizeof(Student), 1, file) == 1) {
        // If it's NOT the m-th record, copy it to the temp file
        if (currentRecord != m) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1; // Mark that we successfully skipped (deleted) it
        }
        currentRecord++;
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(filename);          // Delete old file
        rename("temp.dat", filename); // Rename temp file to original name
        printf("Record %d successfully deleted.\n", m);
    } else {
        remove("temp.dat"); // Clean up temp file if m was out of bounds
        printf("Deletion failed: Record %d was not found.\n", m);
    }
}

// Helper function to print out everything currently in the file
void displayAllRecords(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;

    Student s;
    int count = 1;
    printf("\n--- Current Binary File Content ---\n");
    while (fread(&s, sizeof(Student), 1, file) == 1) {
        printf("[%d] ID: %d | Name: %s | GPA: %.2f\n", count++, s.id, s.name, s.gpa);
    }
    fclose(file);
}