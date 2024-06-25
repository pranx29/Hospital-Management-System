#ifndef DOCTOR_H
#define DOCTOR_H

#define MAX_SPECIALIZATION_LENGTH 50
#define MAX_DOCTORS 100
#define DOCTORS_FILE_PATH "../data/doctors.csv"

#include "common.h"
#include "user.h"

typedef struct
{
    int doctorId;
    int userId;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char specialization[MAX_SPECIALIZATION_LENGTH];
    char contactNumber[MAX_CONTACT_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Doctor;

int readDoctorsFromFile(Doctor doctors[]);
int saveDoctorsToFile(Doctor doctors[], int doctorCount);
Doctor *searchDoctorById(int doctorId);
void getDoctorData(Doctor *doctor, User *user);
void addDoctor(Doctor *newDoctor);

#endif /* DOCTOR_H */
