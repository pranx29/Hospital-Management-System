#ifndef USER_H
#define USER_H

#include "common.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_ROLE_LENGTH 20
#define USERS_FILE_PATH "../data/users.csv"
#define MAX_USERS 100

typedef struct
{
    int userId;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char role[MAX_ROLE_LENGTH];
} User;

// Function declarations
int readUsersFromFile(User users[]);
User *getUserByUsername(const char *username);
int authenticateUser(const char *username, const char *password, const char *role);
int generateUserId();

#endif // USER_H
