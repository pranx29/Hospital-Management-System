#ifndef PATIENT_H
#define PATIENT_H

#define MAX_PATIENTS 100
#define PATIENTS_FILE_PATH "data/patients.csv"

#include "user.h"
#include "common.h"

typedef struct
{
    int patientId;
    User user;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char dateOfBirth[MAX_DATE_LENGTH];
    char gender[10];
    char contactNumber[MAX_CONTACT_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char city[MAX_CITY_LENGTH];
} Patient;

int readPatientsFromFile(Patient patients[]);
int savePatientsToFile(Patient patients[], int patientCount);
void searchPatientById(int patientId, Patient *patient);
int getValidPatientId();
void getPatientData(Patient *patient);
int addPatient(Patient *newPatient);

#endif 
