#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/patient.h"
#include "../include/user.h"
#include "../include/common.h"

#define MAX_PATIENTS 100
#define MAX_LINE_LENGTH 1024
#define PATIENTS_FILE_PATH "../data/patients.csv"

static Patient patients[MAX_PATIENTS];
static int numPatients = 0;

void loadPatientsFromFile()
{
    FILE *patientsFile = fopen(PATIENTS_FILE_PATH, "r");
    if (patientsFile == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", PATIENTS_FILE_PATH);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int row = 0;

    while (fgets(line, sizeof(line), patientsFile))
    {
        if (row == 0)
        {
            // Skip the header line
            row++;
            continue;
        }

        // Split the line by commas
        char *value = strtok(line, ",");
        int column = 0;

        while (value != NULL)
        {
            switch (column)
            {
                removeNewline(value);
                case 0: // patientId
                    patients[numPatients].patientId = atoi(value);
                    break;
                case 1: // userId
                    patients[numPatients].userId = atoi(value);
                    break;
                case 2: // firstName
                    snprintf(patients[numPatients].firstName, sizeof(patients[numPatients].firstName), "%s", value);
                    break;
                case 3: // lastName
                    snprintf(patients[numPatients].lastName, sizeof(patients[numPatients].lastName), "%s", value);
                    break;
                case 4: // dateOfBirth
                    snprintf(patients[numPatients].dateOfBirth, sizeof(patients[numPatients].dateOfBirth), "%s", value);
                    break;
                case 5: // gender
                    snprintf(patients[numPatients].gender, sizeof(patients[numPatients].gender), "%s", value);
                    break;
                case 6: // contactNumber
                    snprintf(patients[numPatients].contactNumber, sizeof(patients[numPatients].contactNumber), "%s", value);
                    break;
                case 7: // email
                    snprintf(patients[numPatients].email, sizeof(patients[numPatients].email), "%s", value);
                    break;
                case 8: // address
                    snprintf(patients[numPatients].address, sizeof(patients[numPatients].address), "%s", value);
                    break;
            }
            value = strtok(NULL, ",");
            column++;
        }

        numPatients++;
        row++;
    }

    fclose(patientsFile);
}

Patient getPatientData()
{
    Patient patient;

    patient.patientId = generatePatientId();
    patient.userId = generateUserId();

    printf("Enter First Name: ");
    scanf("%s", patient.firstName);

    printf("Enter Last Name: ");
    scanf("%s", patient.lastName);

    do
    {
        printf("Enter Date of Birth (YYYY-MM-DD): ");
        scanf("%s", patient.dateOfBirth);
        if (!isValidDate(patient.dateOfBirth))
        {
            printf("Invalid date format. Please enter in YYYY-MM-DD format.\n");
        }
    } while (!isValidDate(patient.dateOfBirth));

    do
    {
        printf("Enter Gender (Male/Female/Other): ");
        scanf("%s", patient.gender);
        if (!isValidGender(patient.gender))
        {
            printf("Invalid gender. Please enter 'Male', 'Female', or 'Other'.\n");
        }
    } while (!isValidGender(patient.gender));

    do
    {
        printf("Enter Contact Number: ");
        scanf("%s", patient.contactNumber);
        if (!isValidContactNumber(patient.contactNumber))
        {
            printf("Invalid contact number. Please enter only digits and ensure it is not empty.\n");
        }
    } while (!isValidContactNumber(patient.contactNumber));

    do
    {
        printf("Enter Email: ");
        scanf("%s", patient.email);
        if (!isValidEmail(patient.email))
        {
            printf("Invalid email format. Please enter a valid email address.\n");
        }
    } while (!isValidEmail(patient.email));

    printf("Enter Address: ");
    scanf("%[^\n]%*c", patient.address);

    return patient;
}

int generatePatientId()
{
    int maxId = 0;
    // Find the maximum patientId in the existing patients
    for (int i = 0; i < numPatients; ++i)
    {
        if (patients[i].patientId > maxId)
        {
            maxId = patients[i].patientId;
        }
    }

    // Return the next unique patientId (maxId + 1)
    return maxId + 1;
}

int addPatientToFile(Patient patient)
{
    FILE *patientsFile = fopen(PATIENTS_FILE_PATH, "a");
    if (patientsFile == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", PATIENTS_FILE_PATH);
        return -1;
    }

    fprintf(patientsFile, "%d,%d,%s,%s,%s,%s,%s,%s,%s\n",
            patient.patientId,
            patient.userId,
            patient.firstName,
            patient.lastName,
            patient.dateOfBirth,
            patient.gender,
            patient.contactNumber,
            patient.email,
            patient.address);

    fclose(patientsFile);
    return 0;
}

int updatePatientFile()
{
    FILE *patientsFile = fopen(PATIENTS_FILE_PATH, "w");
    if (patientsFile == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", PATIENTS_FILE_PATH);
        return -1;
    }

    for (int i = 0; i < numPatients; i++)
    {
        fprintf(patientsFile, "%d,%d,%s,%s,%s,%s,%s,%s,%s\n",
                patients[i].patientId,
                patients[i].userId,
                patients[i].firstName,
                patients[i].lastName,
                patients[i].dateOfBirth,
                patients[i].gender,
                patients[i].contactNumber,
                patients[i].email,
                patients[i].address);
    }

    fclose(patientsFile);
    return 0;
}

Patient *getPatientById(const int id)
{
    for (int i = 0; i < numPatients; ++i)
    {
        if (patients[i].patientId == id)
        {
            return &patients[i];
        }
        printf("Patient ID: %d\n", patients[i].patientId);
    }
    return NULL;
}

void patientLogin(const char *username, const char *password)
{
    int userId = authenticateUser(username, password, "patient");
    if (userId != -1)
    {
        printf("Patient logged in successfully with ID: %d\n", userId);
        // Additional admin-specific logic here
    }
    else
    {
        printf("Invalid username, password\n");
    }
}

int main()
{
    patientLogin("patientbob", "patientpass");
}