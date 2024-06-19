#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user.h"
#include "../include/common.h"

#define MAX_USERS 100
#define MAX_LINE_LENGTH 256
#define USERS_FILE_PATH "../data/users.csv"

static User users[MAX_USERS];
static int numUsers = 0;

void loadUsersFromFile()
{
    FILE *usersFile = fopen(USERS_FILE_PATH, "r");
    if (usersFile == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", USERS_FILE_PATH);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int row = 0;
    while (fgets(line, sizeof(line), usersFile))
    {

        // Skip the first row if it contains column headers
        if (row == 0)
        {
            row++;
            continue;
        }

        // Split the line by commas
        char *value = strtok(line, ",");
        int column = 0;

        while (value != NULL)
        {
            removeNewline(value);
            switch (column)
            {
            case 0: // ID
                users[numUsers].userId = atoi(value);
                break;
            case 1: // Username
                snprintf(users[numUsers].username, sizeof(users[numUsers].username), "%s", value);
                break;
            case 2: // Password
                snprintf(users[numUsers].password, sizeof(users[numUsers].password), "%s", value);
                break;
            case 3: // Role
                
                snprintf(users[numUsers].role, sizeof(users[numUsers].role), "%s", value);
                break;
            }
            value = strtok(NULL, ",");
            column++;
        }
        numUsers++;
    }
    fclose(usersFile);
}

User *getUserByUsername(const char *username)
{
    loadUsersFromFile();
    for (int i = 0; i < numUsers; ++i)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return &users[i];
        }
    }
    return NULL;
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
    loadUsersFromFile();
    int maxId = 0;

    // Find the maximum patientId in the existing patients
    for (int i = 0; i < numUsers; ++i)
    {
        if (users[i].userId > maxId)
        {
            maxId = users[i].userId;
        }
    }
    // Return the next unique patientId (maxId + 1)
    return maxId + 1;
}
