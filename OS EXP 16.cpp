#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;

    // Try to open the file for reading and writing in binary mode
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        // If file doesn't exist, create it
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);

                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);

                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                fflush(filePtr); // Ensure write is committed
                printf("Employee details added successfully.\n");
                break;

            case 2:
                printf("Enter Employee ID to display: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1) {
                    printf("Employee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                } else {
                    printf("Employee not found.\n");
                }
                break;

            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp.empId);

                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1) {
                    printf("Enter New Employee Name: ");
                    scanf("%s", emp.empName);

                    printf("Enter New Employee Salary: ");
                    scanf("%f", &emp.empSalary);

                    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                    fflush(filePtr); // Save changes
                    printf("Employee details updated successfully.\n");
                } else {
                    printf("Employee not found.\n");
                }
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    fclose(filePtr);
    return 0;
}
