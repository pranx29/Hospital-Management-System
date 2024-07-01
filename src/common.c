#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/common.h"

int isValidText(const char *text, int maxTextLength)
{
    int len = strlen(text);
    if (len == 0 || len > maxTextLength)
        return 0;
    for (int i = 0; i < len; ++i)
    {
        if (!isalpha(text[i]) && !isspace(text[i]))
            return 0;
    }
    return 1;
}

char *getText(const char *type, int maxTextLength)
{
    static char text[1000]; // Static array to hold the text
    int valid = 0;
    do
    {
        printf("%s: ", type);
        scanf("%s", text);
        if (!isValidText(text, maxTextLength))
        {
            printf("Invalid %s. Only alphabetic characters are allowed.\n", type);
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return text;
}

char *getDate(const char *text)
{
    static char date[11]; // Static array to hold the date
    int valid = 0;
    do
    {
        printf("%s: ", text);
        scanf("%s", date);
        if (!isValidDate(date))
        {
            printf("Invalid date format. Please enter in YYYY-MM-DD format.\n");
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return date;
}

int isValidDate(const char *date)
{

    if (strlen(date) != 10)
        return 0;

    // Check format
    if (date[4] != '-' || date[7] != '-')
        return 0;

    // Check each character
    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }
        if (!isdigit(date[i]))
        {
            return 0;
        }
    }

    // Extract year, month, day
    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        return 0;
    }

    // Check year range
    if (year < 1900 || year > 2100)
    {
        return 0; // Year out of range
    }

    // Check month range
    if (month < 1 || month > 12)
    {
        return 0; // Month out of range
    }

    // Check day range
    if (day < 1 || day > 31)
    {
        return 0;
    }

    return 1;
}

int isValidGender(const char *gender)
{
    return strcmp(gender, "Male") == 0 || strcmp(gender, "Female") == 0 || strcmp(gender, "Other") == 0;
}

char *getGender()
{
    static char gender[10]; // Static array to hold the gender
    int valid = 0;
    do
    {
        printf("Gender (Male/Female/Other): ");
        scanf("%s", gender);
        if (!isValidGender(gender))
        {
            printf("Invalid gender. Please enter either Male, Female, or Other.\n");
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return gender;
}

int isValidContactNumber(const char *contactNumber)
{
    int len = strlen(contactNumber);
    if (len == 0 || len != MAX_CONTACT_LENGTH)
        return 0;
    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(contactNumber[i]))
            return 0;
    }
    return 1;
}

char *getContactNumber()
{
    static char contactNumber[MAX_CONTACT_LENGTH + 1];
    int valid = 0;
    do
    {
        printf("Contact Number: ");
        scanf("%s", contactNumber);
        if (!isValidContactNumber(contactNumber))
        {
            printf("Invalid contact number.\n");
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return contactNumber;
}

int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (at == NULL || at == email || strchr(at, '.') == NULL)
        return 0;
    return 1;
}

char *getEmail()
{
    static char email[100]; // Static array to hold the email address
    int valid = 0;
    do
    {
        printf("Email Address: ");
        scanf("%s", email);
        if (!isValidEmail(email))
        {
            printf("Invalid email address. Please enter a valid email address.\n");
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return email;
}

int isValidUsername(const char *username)
{
    int len = strlen(username);
    if (len < MIN_USERNAME_LENGTH || len > MAX_USERNAME_LENGTH)
        return 0;
    for (int i = 0; i < len; ++i)
    {
        if (!isalnum(username[i]) && username[i] != '_')
            return 0;
    }
    return 1;
}

int isValidPassword(const char *password)
{
    int len = strlen(password);
    return len >= MIN_PASSWORD_LENGTH && len <= MAX_PASSWORD_LENGTH;
}

// Function to get a valid password from user input
char *getPassword()
{
    static char password[MAX_PASSWORD_LENGTH + 1]; // Static array to hold the password
    int valid = 0;
    do
    {
        printf("Password: ");
        scanf("%s", password);
        if (!isValidPassword(password))
        {
            printf("Invalid password. Password must be between %d and %d characters.\n", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return password;
}

int getUserChoice(int min, int max)
{
    int choice;
    printf("Enter your choice [%d-%d]: ", min, max);
    if (scanf("%d", &choice) != 1 || choice < min || choice > max)
    {
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        while (getchar() != '\n')
            ;      // Clear input buffer
        return -1; // Return -1 to indicate failure
    }
    return choice;
}

// Function to get a valid positive number from user input
int getNumber(const char *input)
{
    int number;
    int isValid = 0;
    do
    {
        printf("%s: ", input);
        if (scanf("%d", &number) != 1)
        {
            printf("Invalid %s.\n", input);
            while (getchar() != '\n')
                ; // Clear input buffer
        }
        else if (number < 0)
        {
            printf("Invalid %s. \n", input);
        }
        else
        {
            isValid = 1;
        }
    } while (!isValid);
    return number;
}

// Function to valid time in HH:MM format
int isValidTime(const char *time)
{
    if (strlen(time) != 5)
        return 0;

    if (time[2] != ':')
        return 0;

    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return 0;

    return 1;
}

// Function to get time in HH:MM format
char *getTime()
{
    static char time[6]; // Static array to hold the time
    int valid = 0;
    do
    {
        printf("Time (HH:MM): ");
        scanf("%s", time);
        if (!isValidTime(time))
        {
            printf("Invalid time format. Please enter in HH:MM format.\n");
        }
        else
        {
            valid = 1;
        }
    } while (!valid);
    return time;
}

// Function to get current data in YYYY-MM-DD format
char *getCurrentDate()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char date[11];
    sprintf(date, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return date;
}