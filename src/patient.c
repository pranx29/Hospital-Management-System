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
                  &patients[patientCount].patientId, &patients[patientCount].user.userId,
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
        fprintf(file, "%d,%d,%s,%s,%s,%s,%s,%s,%s\n", patients[i].patientId, patients[i].user.userId,
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

void getPatientData(Patient *patient)
{
    patient->user.userId = generateUserId();
    strcpy(patient->user.role, "patient");

    strcpy(patient->firstName, getText("First Name", MAX_NAME_LENGTH));
    strcpy(patient->lastName, getText("Last Name", MAX_NAME_LENGTH));
    strcpy(patient->dateOfBirth, getDate());
    strcpy(patient->gender, getGender());
    strcpy(patient->contactNumber, getContactNumber());
    strcpy(patient->email, getEmail());
    strcpy(patient->city, getText("City", MAX_CITY_LENGTH));

    // Ask for login information
    printf("\nPlease enter login information:\n");
    getUserCredentials(&patient->user);
}

// Function to add a new patient
int addPatient(Patient *newPatient)
{
    Patient patients[MAX_PATIENTS];

    int patientCount = readPatientsFromFile(patients);

    if (patientCount >= MAX_PATIENTS)
    {
        printf("Maximum patient limit reached. Cannot add more patients.\n");
        return 0;
    }

    newPatient->patientId = patientCount + 1;
    patients[patientCount] = *newPatient;
    patientCount++;

    if (savePatientsToFile(patients, patientCount) == 0 || addUser(&newPatient->user) == 0)
    {
        printf("Error saving patient to file.\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
