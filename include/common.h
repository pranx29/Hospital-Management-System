#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include "user.h"

#define MAX_NAME_LENGTH 50
#define MAX_CONTACT_LENGTH 10
#define MAX_EMAIL_LENGTH 50
#define MAX_CITY_LENGTH 50
#define MAX_DATE_LENGTH 12

// Validation function declarations
int isValidText(const char *name, int maxTextLength);
char *getText(const char *type, int maxTextLength);
int isValidDate(const char *date);
char *getDate(const char *text);
int isValidGender(const char *gender);
char *getGender();
int isValidContactNumber(const char *contactNumber);
char *getContactNumber();
int isValidEmail(const char *email);
char *getEmail();
int isValidUsername(const char *username);
int isValidPassword(const char *password);
char *getPassword();
int getUserChoice(int min, int max);
int getNumber(const char *input);
char *getTime();
char *getCurrentDate();
#endif // COMMON_H
