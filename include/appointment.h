#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "staff.h"
#include "common.h"
#include "time.h"
#include "patient.h"

#define MAX_APPOINTMENT_TYPE_LENGTH 50
#define MAX_TIME_LENGTH 10
#define MAX_STATUS_LENGTH 20
#define MAX_COMMENTS_LENGTH 200
#define MAX_APPOINTMENTS 100
#define APPOINTMENT_FILE_PATH "data/appointments.csv"

enum Status
{
    SCHEDULED,
    CANCELLED
};
enum AppointmentType
{
    CHECKUP,
    CONSULTATION,
    PROCEDURE,
    FOLLOWUP
};

typedef struct
{
    int appointmentId;
    Patient patient;
    Doctor doctor;
    Staff nurse;
    enum AppointmentType appointmentType;
    char appointmentDate[MAX_DATE_LENGTH];
    char appointmentTime[MAX_TIME_LENGTH];
    enum Status status;
    char comments[200];
} Appointment;

// Function prototypes
char *statusToString(enum Status status);
char *appointmentTypeToString(enum AppointmentType appointmentType);
int readAppointmentsFromFile(Appointment appointments[]);
int saveAppointmentsToFile(Appointment appointments[], int appointmentCount);
void searchAppointmentById(int appointmentId, Appointment *appointment);
void searchAppointmentsByPatientId(int patientId, Appointment *appointments, int *count);
void getAppointmentData(Appointment *appointment);
int addAppointment(Appointment *newAppointment);

#endif /* APPOINTMENT_H */