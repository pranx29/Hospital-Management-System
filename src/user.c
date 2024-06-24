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
