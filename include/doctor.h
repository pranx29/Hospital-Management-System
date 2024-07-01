#ifndef DOCTOR_H
#define DOCTOR_H

#define MAX_SPECIALIZATION_LENGTH 50
#define MAX_DOCTORS 100
#define DOCTORS_FILE_PATH "data/doctors.csv"

#include "common.h"
#include "user.h"

typedef struct
{
    int doctorId;
    User user;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char specialization[MAX_SPECIALIZATION_LENGTH];
    char contactNumber[MAX_CONTACT_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Doctor;

int readDoctorsFromFile(Doctor doctors[]);
int saveDoctorsToFile(Doctor doctors[], int doctorCount);
void searchDoctorById(int doctorId, Doctor *doctor);
int getValidDoctorId();
void getDoctorData(Doctor *doctor);
int addDoctor(Doctor *newDoctor);
void viewAppointmentsByDoctorID(int doctorId);
void doctorMenu(int userId);
#endif /* DOCTOR_H */
