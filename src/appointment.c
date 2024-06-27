#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/appointment.h"

// Function to enum to string
char *statusToString(enum Status status)
{
    switch (status)
    {
    case SCHEDULED:
        return "Scheduled";
    case CANCELLED:
        return "Cancelled";
    default:
        return "Invalid";
    }
}

// Function to enum to appointment type
char *appointmentTypeToString(enum AppointmentType appointmentType)
{
    switch (appointmentType)
    {
    case CHECKUP:
        return "Checkup";
    case CONSULTATION:
        return "Consultation";
    case PROCEDURE:
        return "Procedure";
    case FOLLOWUP:
        return "Follow-up";
    default:
        return "Invalid";
    }
}

// Function to read appointments from file to array
int readAppointmentsFromFile(Appointment appointments[])
{
    FILE *file = fopen(APPOINTMENT_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int appointmentCount = 0;

    while (fscanf(file, "%d,%d,%d,%d,%u,%[^,],%[^,],%u,%[^\n]\n",
                  &appointments[appointmentCount].appointmentId, &appointments[appointmentCount].patient.patientId,
                  &appointments[appointmentCount].doctor.doctorId, &appointments[appointmentCount].nurse.staffId,
                  &appointments[appointmentCount].appointmentType, appointments[appointmentCount].appointmentDate,
                  appointments[appointmentCount].appointmentTime, &appointments[appointmentCount].status,
                  appointments[appointmentCount].comments) == 9)
    {

        appointmentCount++;
        if (appointmentCount >= MAX_APPOINTMENTS)
        {
            printf("Maximum appointments limit reached. Increase MAX_APPOINTMENTS if needed.\n");
            break;
        }
    }

    fclose(file);
    return appointmentCount;
}

// Function to save appointments from array to file
int saveAppointmentsToFile(Appointment appointments[], int appointmentCount)
{
    FILE *file = fopen(APPOINTMENT_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < appointmentCount; i++)
    {
        fprintf(file, "%d,%d,%d,%d,%d,%s,%s,%d,%s\n",
                appointments[i].appointmentId, appointments[i].patient.patientId,
                appointments[i].doctor.doctorId, appointments[i].nurse.staffId,
                appointments[i].appointmentType, appointments[i].appointmentDate,
                appointments[i].appointmentTime, appointments[i].status,
                appointments[i].comments);
    }

    fclose(file);
    return 1;
}

// Function to search for appointment by ID
Appointment *searchAppointmentById(int appointmentId)
{
    static Appointment appointments[MAX_APPOINTMENTS]; // Static array to hold appointment data
    int appointmentCount = readAppointmentsFromFile(appointments);

    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].appointmentId == appointmentId)
        {
            return &appointments[i];
        }
    }
    return NULL; // Return NULL if appointment with given ID is not found
}

// Function to get new appointment data from user input
void getAppointmentData(Appointment *appointment)
{
    // Get patient, doctor, and nurse data
    printf("Enter Patient Details:\n");
    printf("Patient ID: ");
    scanf("%d", &appointment->patient.patientId);

    printf("Enter Doctor Details:\n");
    printf("Doctor ID: ");
    scanf("%d", &appointment->doctor.doctorId);

    printf("Enter Nurse Details:\n");
    printf("Nurse ID: ");
    scanf("%d", &appointment->nurse.staffId);

    printf("Enter Appointment Details:\n");
    printf("Appointment Type: ");

    printf("Appointment Date (YYYY-MM-DD): ");
    scanf(" %s", appointment->appointmentDate);
    printf("Appointment Time (HH:MM): ");
    scanf(" %s", appointment->appointmentTime);
    printf("Status: ");

    printf("Comments: ");
    scanf(" %s", appointment->comments);
}

// Function to add a new appointment
int addAppointment(Appointment *newAppointment)
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    if (appointmentCount >= MAX_APPOINTMENTS)
    {
        printf("Maximum appointments limit reached. Cannot add more appointments.\n");
        return 0;
    }

    newAppointment->appointmentId = appointmentCount + 1;
    appointments[appointmentCount] = *newAppointment;
    appointmentCount++;

    if (saveAppointmentsToFile(appointments, appointmentCount) == 0)
    {
        printf("Error saving appointment to file.\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
