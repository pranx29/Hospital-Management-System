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
void searchAppointmentById(int appointmentId, Appointment *appointment)
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].appointmentId == appointmentId)
        {
            *appointment = appointments[i];
            return;
        }
    }
    printf("Appointment with ID %d not found.\n", appointmentId);
}

// Function to search for appointments by patient ID
void searchAppointmentsByPatientId(int patientId, Appointment *appointments, int *count)
{
    Appointment allAppointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(allAppointments);
    int index = 0;

    for (int i = 0; i < appointmentCount; i++)
    {
        if (allAppointments[i].patient.patientId == patientId)
        {
            appointments[index] = allAppointments[i];
            index++;
        }
    }

    *count = index;

    if (index == 0)
    {
        printf("No appointments found for patient with ID %d.\n", patientId);
    }
}

// Function to search appointments by doctor ID
void searchAppointmentsByDoctorId(int doctorId, Appointment *appointments, int *count)
{
    Appointment allAppointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(allAppointments);
    int index = 0;

    for (int i = 0; i < appointmentCount; i++)
    {
        if (allAppointments[i].doctor.doctorId == doctorId)
        {
            appointments[index] = allAppointments[i];
            index++;
        }
    }

    *count = index;

    if (index == 0)
    {
        printf("No appointments found for doctor with ID %d.\n", doctorId);
    }
}

// Function to get appointment type from user input
enum AppointmentType getAppointmentType()
{
    int appointmentType;
    printf("Enter Appointment Type (0 for Checkup, 1 for Consultation, 2 for Procedure, 3 for Follow-up): ");
    scanf("%d", &appointmentType);

    while (appointmentType < 0 || appointmentType > 3)
    {
        printf("Invalid appointment type. Please enter a valid appointment type: ");
        scanf("%d", &appointmentType);
    }

    return (enum AppointmentType)appointmentType;
}

// Function to get new appointment data from user input
void getAppointmentData(Appointment *appointment)
{
    appointment->patient.patientId = getValidPatientId();

    appointment->doctor.doctorId = getValidDoctorId();

    appointment->nurse.staffId = getValidStaffId("Nurse");

    printf("Enter Appointment Details:\n");

    appointment->appointmentType = getAppointmentType();
    strcpy(appointment->appointmentDate, getDate());

    strcpy(appointment->appointmentTime, getTime());

    strcpy(appointment->comments, getText("Comments", MAX_COMMENTS_LENGTH));
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