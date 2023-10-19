#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define USER_FILE "users.txt"

struct Donor {
    char username[MAX_SIZE];
    char password[MAX_SIZE];
    char fullName[MAX_SIZE];
    char bloodType[MAX_SIZE];
    char contactNumber[MAX_SIZE];
    int donations;
    int bloodTypeRegistered;
// 0 if not registered, 1 if registered
};

void displayError(const char *message) {
    printf("Error: %s\n", message);
}

int registerDonor(struct Donor *donors, int *donorCount) {
    FILE *file = fopen(USER_FILE, "a");
    if (!file) {
        displayError("Unable to open user file.");
        return -1;
    }

    struct Donor newDonor;
    printf("Enter username: ");
    scanf("%s", newDonor.username);
    printf("Enter password: ");
    scanf("%s", newDonor.password);
    printf("Enter full name (No whitespace): ");
    scanf("%s", newDonor.fullName);
    printf("Enter blood type (In Capital): ");
    scanf("%s", newDonor.bloodType);
    printf("Enter contact number: ");
    scanf("%s", newDonor.contactNumber);

    newDonor.donations = 0;
    newDonor.bloodTypeRegistered = 1; 
    // Indicates that the blood type is registered

    fprintf(file, "%s %s %s %s %s %d %d\n", newDonor.username, newDonor.password, newDonor.fullName, newDonor.bloodType, newDonor.contactNumber, newDonor.donations, newDonor.bloodTypeRegistered);
    fclose(file);

    donors[*donorCount] = newDonor;
    (*donorCount)++;

    printf("Registration successful!\n");
    return 0;
}

int login(const struct Donor *donors, int donorCount) {
    char username[MAX_SIZE];
    char password[MAX_SIZE];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < donorCount; i++) {
        if (strcmp(username, donors[i].username) == 0 && strcmp(password, donors[i].password) == 0) {
            printf("Welcome Mr. %s!\n", donors[i].fullName);
            printf("Blood group is %s\n",donors[i].bloodType);
            printf("The number is %s\n",donors[i].contactNumber);
            printf("Login successful!\n");
            return i; 
            // Return the index of the logged-in user
        }
    }

    displayError("Login failed. Invalid credentials.");
    return -1;
     // Invalid login
}


void changePassword(struct Donor *donors, int userIndex) {
    if (userIndex >= 0) {
        printf("Enter new password: ");
        scanf("%s", donors[userIndex].password);
        printf("Password changed successfully!\n");
    } else {
        displayError("Invalid user index.");
    }
}

void changeNumber(struct Donor *donors, int userIndex) {
    if (userIndex >= 0) {
        printf("Enter new contact number: ");
        scanf("%s", donors[userIndex].contactNumber);
        printf("Contact number changed successfully!\n");
    } else {
        displayError("Invalid user index.");
    }
}

int searchBloodType(const struct Donor *donors, int donorCount) {
    char bloodType[MAX_SIZE];

    printf("Enter Blood Type (In Capital): ");
    scanf("%s", bloodType);

    for (int i = 0; i < donorCount; i++) {
        if (strcmp(bloodType, donors[i].bloodType) == 0 && donors[i].bloodTypeRegistered == 1) {
            printf("Blood Group available!\n");
            printf("Name of donor is %s\n",donors[i].fullName);
            printf("The number is %s",donors[i].contactNumber);
            return i; 
            // Return the index of the found donor
        }
    }

    displayError("Sorry, Blood Group not available!");
    return -1; 
    // Blood group not found
}

int main() {
    int choice, donorIndex = -1;
    int donorCount = 0;
    struct Donor *donors = malloc(MAX_SIZE * sizeof(struct Donor));

    // Check if the user file exists and create it if it doesn't
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        file = fopen(USER_FILE, "w");
        if (!file) {
            displayError("Unable to create user file.");
            return -1;
        }
        fclose(file);
    } else {
        fclose(file);
    }

    do {
        printf("\nMenu:\n");
        printf("1. Register as Donor\n");
        printf("2. Login\n");
        printf("3. Change Contact Number\n");
        printf("4. Change Password\n");
        printf("5. Search Blood Group\n");
        printf("6. Logout\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (donorCount < MAX_SIZE) {
                    registerDonor(donors, &donorCount);
                } else {
                    displayError("Maximum donor count reached.");
                }
                break;
            case 2:
                donorIndex = login(donors, donorCount);
                break;
            case 3:
                changeNumber(donors, donorIndex);
                break;
            case 4:
                changePassword(donors, donorIndex);
                break;
            case 5:
                searchBloodType(donors, donorCount);
                break;
            case 6:
                donorIndex = -1;
                 // Logout
                printf("Logged out successfully.\n");
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                displayError("Invalid choice. Please try again.");
        }
    } while (choice != 7);

    free(donors); 
    // Free allocated memory
    return 0;
    }