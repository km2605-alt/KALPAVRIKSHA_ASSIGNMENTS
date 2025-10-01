#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "users.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} 
User;


void createUser();
void readUsers();
void updateUser();
void deleteUser();
void ensureFileExists();

int main() {
    int option;
    ensureFileExists();  

    while (1) {
        printf("\n Welcome to the User Management System where you can perform CRUD operations, Below is the following List of the operations. \n");
        printf("1. Create User\n");
        printf("2. Read Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice from 1 to 5: ");
        scanf("%d", &option);

        switch (option) {
            case 1: createUser(); 
            break;
            case 2: readUsers(); 
            break;
            case 3: updateUser();
            break;
            case 4: deleteUser();
             break;
            case 5: exit(0);

            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void ensureFileExists() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(fp);
}


void createUser() {
    User user;
    FILE *fp = fopen(FILE_NAME, "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &user.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", user.name);  
    printf("Enter Age: ");
    scanf("%d", &user.age);

    fprintf(fp, "%d %s %d\n", user.id, user.name, user.age);
    fclose(fp);
    printf("User added successfully!\n");
}


void readUsers() {
    User user;
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n User Records \n");
    while (fscanf(fp, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        printf("ID: %d | Name: %s | Age: %d\n", user.id, user.name, user.age);
    }
    fclose(fp);
}


void updateUser() {
    User user;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID of user to update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf(" %[^\n]", user.name);
            printf("Enter new Age: ");
            scanf("%d", &user.age);
        }
        fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("User updated successfully!\n");
    else
        printf("User with ID %d not found!\n", id);
}


void deleteUser() {
    User user;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID of user to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &user.id, user.name, &user.age) != EOF) {
        if (user.id == id) {
            found = 1;
            continue; 
        }
        fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("User deleted successfully!\n");
    else
        printf("User with ID %d not found!\n", id);
}