#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/common.h"
#include "../include/user.h"
#include "../include/admin.h"
#include "../include/patient.h"
#include "../include/doctor.h"

// Function to verify login
int verifyLogin(char *username, char *password, User *user)
{
    User users[MAX_USERS];
    int userCount = readUsersFromFile(users);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            *user = users[i];
            return users[i].userId;
        }
    }

    return -1;
}

// Function to login to the system
void loginMenu()
{
    int userId;
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    User user;
    int attempts = 0;

    printf("\n---------------- Login ---------------\n");

    do
    {
        attempts++;
        if (attempts > 3)
        {
            printf("Maximum login attempts reached. Exiting...\n");
            exit(0);
        }

        strcpy(username, getText("username", MAX_NAME_LENGTH));
        strcpy(password, getPassword());

        userId = verifyLogin(username, password, &user);

        if (userId != -1)
        {
            if (strcmp(user.role, "admin") == 0)
            {
                adminMenu();
            }
            else if (strcmp(user.role, "doctor") == 0)
            {
                doctorMenu(userId);
            }
            else if (strcmp(user.role, "manager") == 0 || strcmp(user.role, "nurse") == 0 || strcmp(user.role, "receptionist") == 0)
            {
                staffMenu(userId);
            }
            else if (strcmp(user.role, "patient") == 0)
            {
                patientMenu(userId);
            }
            break;
        }
        else
        {
            printf("Invalid username or password\n");
        }
    } while (1);
}

// Function to display main menu of hospital management system. It shows login and exit
int main()
{
    int choice;
    do
    {
        printf("\n---------------- Main Menu ---------------\n");
        printf("1. Login\n");
        printf("2. Exit\n");

        choice = getUserChoice(1, 2);

        switch (choice)
        {
        case 1:
            loginMenu();
            break;
        case 2:
            printf("Exiting...\n");
            exit(0);
        }
    } while (1);

    return 0;
}
