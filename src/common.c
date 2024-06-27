#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

char *getDate()
{
    static char date[11]; // Static array to hold the date
    int valid = 0;
    do
    {
        printf("Date of Birth (YYYY-MM-DD): ");
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