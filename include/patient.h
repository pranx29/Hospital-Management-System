#ifndef PATIENT_H
#define PATIENT_H

#include "../include/patient.h"
#include "../include/user.h"
#include "../include/common.h"

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
    char address[MAX_ADDRESS_LENGTH];
} Patient;

// Function declaration
void loadPatientsFromFile();
Patient getPatientData();
int addPatientToFile(Patient patient);
int generatePatientId();
Patient *getPatientById(const int id);
#endif // PATIENT_H
