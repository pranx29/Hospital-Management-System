#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/patient.h"

// Function to read patients from file to array
int readPatientsFromFile(Patient patients[])
{
    FILE *file = fopen(PATIENTS_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int patientCount = 0;
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &patients[patientCount].patientId, &patients[patientCount].userId,
                  patients[patientCount].firstName, patients[patientCount].lastName,
                  patients[patientCount].dateOfBirth, patients[patientCount].gender,
                  patients[patientCount].contactNumber, patients[patientCount].email,
                  patients[patientCount].city) == 9)
    {
        patientCount++;
        if (patientCount >= MAX_PATIENTS)
        {
            printf("Maximum patient limit reached. Increase MAX_PATIENTS if needed.\n");
            break;
        }
    }

    fclose(file);
    return patientCount;
}

// Function to save patients from array to file
int savePatientsToFile(Patient patients[], int patientCount)
{
    FILE *file = fopen(PATIENTS_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < patientCount; i++)
    {
        fprintf(file, "%d,%d,%s,%s,%s,%s,%s,%s,%s\n", patients[i].patientId, patients[i].userId,
                patients[i].firstName, patients[i].lastName, patients[i].dateOfBirth,
                patients[i].gender, patients[i].contactNumber, patients[i].email,
                patients[i].city);
    }

    fclose(file);
    return 1;
}
// Function to search patient by ID
Patient *searchPatientById(int patientId)
{
    static Patient patients[MAX_PATIENTS];
    int patientCount = readPatientsFromFile(patients);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patientId == patientId)
        {
            return &patients[i];
        }
    }
    return NULL; // Return NULL if patient with given ID is not found
}

Patient getPatientData()
{
    Patient patient;
    patient.userId = generateUserId();

    printf("First Name: ");
    scanf("%s", patient.firstName);

    printf("Last Name: ");
    scanf("%s", patient.lastName);

    do
    {
        printf("Date of Birth (YYYY-MM-DD): ");
        scanf("%s", patient.dateOfBirth);
        if (!isValidDate(patient.dateOfBirth))
        {
            printf("Invalid date format. Please enter in YYYY-MM-DD format.\n");
        }
    } while (!isValidDate(patient.dateOfBirth));

    do
    {
        printf("Gender (Male/Female/Other): ");
        scanf("%s", patient.gender);
        if (!isValidGender(patient.gender))
        {
            printf("Invalid gender. Please enter 'Male', 'Female', or 'Other'.\n");
        }
    } while (!isValidGender(patient.gender));

    do
    {
        printf("Contact Number: ");
        scanf("%s", patient.contactNumber);
        if (!isValidContactNumber(patient.contactNumber))
        {
            printf("Invalid contact number. Please enter only digits and ensure it is not empty.\n");
        }
    } while (!isValidContactNumber(patient.contactNumber));

    do
    {
        printf("Email: ");
        scanf("%s", patient.email);
        if (!isValidEmail(patient.email))
        {
            printf("Invalid email format. Please enter a valid email city.\n");
        }
    } while (!isValidEmail(patient.email));

    printf("City: ");
    scanf("%s", patient.city);

    return patient;
}

// Function to add a new patient
void addPatient(Patient newPatient)
{
    Patient patients[MAX_PATIENTS];

    int patientCount = readPatientsFromFile(patients);

    if (patientCount >= MAX_PATIENTS)
    {
        printf("Maximum patient limit reached. Cannot add more patients.\n");
        return;
    }

    newPatient.patientId = patientCount + 1;
    patients[patientCount] = newPatient;
    patientCount++;

    if (savePatientsToFile(patients, patientCount) == 0)
    {
        printf("Failed to add patient.\n");
        return;
    }
    else
    {
        printf("Patient added successfully.\n");
    }
}