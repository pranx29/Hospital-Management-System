#ifndef USER_H
#define USER_H

#include "common.h"

#define MAX_USERNAME_LENGTH 50
#define MIN_USERNAME_LENGTH 5
#define MAX_PASSWORD_LENGTH 50
#define MIN_PASSWORD_LENGTH 8
#define MAX_ROLE_LENGTH 20
#define USERS_FILE_PATH "data/users.csv"
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
int saveUsersToFile(User users[], int userCount);
int addUser(User *newUser);
User *getUserByUsername(const char *username);
int isUsernameExists(const char *username);
int authenticateUser(const char *username, const char *password, const char *role);
int generateUserId();
void getUserCredentials(User *user);

#endif // USER_H
