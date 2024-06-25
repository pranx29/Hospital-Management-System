#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"

// Function to read users from file to array
int readUsersFromFile(User users[])
{
    FILE *file = fopen(USERS_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int userCount = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^\n]\n",
                  &users[userCount].userId,
                  users[userCount].username,
                  users[userCount].password,
                  users[userCount].role) == 4)
    {
        userCount++;
        if (userCount >= MAX_USERS)
        {
            printf("Maximum user limit reached. Increase MAX_PATIENTS if needed.\n");
            break;
        }
    }

    fclose(file);
    return userCount;
}
// Function to save patients from array to file
int saveUsersToFile(User users[], int userCount)
{
    FILE *file = fopen(USERS_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%d,%s,%s,%s\n", users[i].userId, users[i].username, users[i].password, users[i].role);
    }

    fclose(file);
    return 1;
}

// Function to add user
void addUser(User *newUser)
{
    User users[MAX_USERS];
    int userCount = readUsersFromFile(users);

    if (userCount >= MAX_USERS)
    {
        printf("Maximum user limit reached. Cannot add more users.\n");
        return;
    }

    newUser->userId = userCount + 1;
    users[userCount] = *newUser;
    userCount++;

    if (saveUsersToFile(users, userCount) == 0)
    {
        printf("Failed to add user.\n");
        return;
    }
    else
    {
        printf("User added successfully.\n");
    }
}

User *getUserByUsername(const char *username)
{
    static User users[MAX_USERS];
    int userCount = readUsersFromFile(users);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return &users[i];
        }
    }
    return NULL; // Return NULL if user with given username is not found
}

// Function to check whether username exists
int isUsernameExists(const char *username)
{
    User *user = getUserByUsername(username);
    return user != NULL;
}

int authenticateUser(const char *username, const char *password, const char *role)
{
    User *user = getUserByUsername(username);

    if (user != NULL && strcmp(user->password, password) == 0 && strcmp(user->role, role) == 0)
    {
        return user->userId; // Return user id or some identifier to signify successful login
    }
    return -1; // Invalid credentials
}

int generateUserId()
{
    static User users[MAX_USERS];
    int userCount = readUsersFromFile(users);
    return users[userCount - 1].userId + 1;
}

void getUserCredentials(User *user)
{
    do
    {
        printf("Username: ");
        scanf("%s", user->username);
        if (isUsernameExists(user->username))
        {
            printf("Username already exists. Please choose a different username.\n");
        }
    } while (isUsernameExists(user->username));

    do
    {
        printf("Password: ");
        scanf("%s", user->password);
        if (!isValidPassword(user->password))
        {
            printf("Password must be at least 8 characters long.\n");
        }
    } while (!isValidPassword(user->password));

    char confirmPassword[MAX_PASSWORD_LENGTH];

    do
    {
        printf("Confirm Password: ");
        scanf("%s", confirmPassword);
        if (strcmp(user->password, confirmPassword) != 0)
        {
            printf("Passwords do not match. Please try again.\n");
        }
    } while (strcmp(user->password, confirmPassword) != 0);
}

