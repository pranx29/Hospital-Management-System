#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/doctor.h"

// Function to read doctors from file to array
int readDoctorsFromFile(Doctor doctors[])
{
    FILE *file = fopen(DOCTORS_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int doctorCount = 0;
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &doctors[doctorCount].doctorId, &doctors[doctorCount].userId,
                  doctors[doctorCount].firstName, doctors[doctorCount].lastName,
                  doctors[doctorCount].specialization, doctors[doctorCount].contactNumber,
                  doctors[doctorCount].email) == 7)
    {
        doctorCount++;
        if (doctorCount >= MAX_DOCTORS)
        {
            printf("Maximum doctor limit reached. Increase MAX_DOCTORS if needed.\n");
            break;
        }
    }

    fclose(file);
    return doctorCount;
}

// Function to save doctors from array to file
int saveDoctorsToFile(Doctor doctors[], int doctorCount)
{
    FILE *file = fopen(DOCTORS_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < doctorCount; i++)
    {
        fprintf(file, "%d,%d,%s,%s,%s,%s,%s\n", doctors[i].doctorId, doctors[i].userId,
                doctors[i].firstName, doctors[i].lastName, doctors[i].specialization,
                doctors[i].contactNumber, doctors[i].email);
    }

    fclose(file);
    return 1;
}

// Function to search for a doctor by ID
Doctor *searchDoctorById(int doctorId)
{
    static Doctor doctors[MAX_DOCTORS]; // Static array to hold doctors data
    int doctorCount = readDoctorsFromFile(doctors);

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == doctorId)
        {
            return &doctors[i];
        }
    }
    return NULL; // Return NULL if doctor with given ID is not found
}

// Function to get new doctor data from user input
Doctor getDoctorData()
{
    Doctor doctor;

    doctor.userId = generateUserId();

    printf("First Name: ");
    scanf("%s", doctor.firstName);

    printf("Last Name: ");
    scanf("%s", doctor.lastName);

    printf("Specialization: ");
    scanf("%s", doctor.specialization);

    printf("Contact Number: ");
    scanf("%s", doctor.contactNumber);

    printf("Email: ");
    scanf("%s", doctor.email);

    return doctor;
}

// Function to add a new doctor
void addDoctor(Doctor newDoctor)
{
    Doctor doctors[MAX_DOCTORS];
    int doctorCount = readDoctorsFromFile(doctors);

    if (doctorCount >= MAX_DOCTORS)
    {
        printf("Maximum doctor limit reached. Cannot add more doctors.\n");
        return;
    }

    newDoctor.doctorId = doctorCount + 1;
    doctors[doctorCount] = newDoctor;
    doctorCount++;

    if (saveDoctorsToFile(doctors, doctorCount) == 0)
    {
        printf("Failed to add doctor.\n");
        return;
    }
    else
    {
        printf("Doctor added successfully.\n");
    }
}
