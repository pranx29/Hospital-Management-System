#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/common.h"

int isValidDate(const char *date)
{
    // Basic validation for date format YYYY-MM-DD
    if (strlen(date) != 10)
        return 0;
    if (date[4] != '-' || date[7] != '-')
        return 0;

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return 0;
    }
    return 1;
}

int isValidGender(const char *gender)
{
    return strcmp(gender, "Male") == 0 || strcmp(gender, "Female") == 0 || strcmp(gender, "Other") == 0;
}

int isValidContactNumber(const char *contactNumber)
{
    int len = strlen(contactNumber);
    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(contactNumber[i]))
            return 0;
    }
    return len > 0 && len <= MAX_CONTACT_LENGTH;
}

int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (at == NULL || at == email || strchr(at, '.') == NULL)
        return 0;
    return 1;
}