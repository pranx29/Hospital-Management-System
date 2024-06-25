#ifndef PATIENT_H
#define PATIENT_H

#define MAX_PATIENTS 100
#define PATIENTS_FILE_PATH "../data/patients.csv"

#include "user.h"
#include "common.h"

typedef struct
{
    int patientId;
    int userId;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char dateOfBirth[12];
    char gender[10];
    char contactNumber[MAX_CONTACT_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char city[MAX_CITY_LENGTH];
} Patient;

// Function declaration
int readPatientsFromFile(Patient patients[]);
int savePatientsToFile(Patient patients[], int patientCount);
Patient *searchPatientById(int patientId);
void getPatientData(Patient *patient, User *user);
void addPatient(Patient *newPatient);
#endif // PATIENT_H
