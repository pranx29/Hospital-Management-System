#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/patient.h"
#include "../include/appointment.h"

int patientId = 1;

// Below are the functions defined for patient management in patient.h

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
void searchPatientById(int patientId, Patient *patient)
{
    Patient patients[MAX_PATIENTS];
    int patientCount = readPatientsFromFile(patients);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patientId == patientId)
        {
            *patient = patients[i];
            return;
        }
    }
    printf("Patient with ID %d not found.\n", patientId);
}
// Function to get a valid id patient id from user it should check patient file
int getValidPatientId()
{
    int patientId;
    int isValid = 0;
    Patient patient;

    do
    {
        printf("Patient ID: ");
        scanf("%d", &patientId);
        searchPatientById(patientId, &patient);

        if (patient.patientId == patientId)
        {
            isValid = 1;
        }

    } while (!isValid);
    return patientId;
}

// Function to get patient data
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

// Below are the functions used only by patient

// Patient Appointment Management:
// Function to show patient appointment management menu
void manageAppointments()
{
    int choice;
    do
    {
        printf("\n---------------- Manage Inventory ---------------\n");
        printf("1. View Appointments\n");
        printf("2. Reschedule Appointments\n");
        printf("3. Cancel Appointments\n");
        printf("4. Go back\n");

        choice = getUserChoice(1, 4);

        switch (choice)
        {
        case 1:
            viewAppointments();
            break;
        case 2:
            rescheduleAppointment();
            break;
        case 3:
            cancelAppointment();
            break;
        case 4:
            return;
        }
    } while (1);
}

// Function to view appointments of patient
void viewAppointments()
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount;
    searchAppointmentsByPatientId(patientId, appointments, &appointmentCount);

    printf("\n---------------- Appointments ---------------\n");

    if (appointmentCount == 0)
    {
        printf("No appointments found.\n");
        return;
    }

    printf("Appointment ID\tDoctor Name\tDate\t\tTime\tStatus\n");
    for (int i = 0; i < appointmentCount; i++)
    {
        searchDoctorById(appointments[i].doctor.doctorId, &appointments[i].doctor);

        printf("%d\t%s %s\t%s\t%s\t%s\n", appointments[i].appointmentId,
               appointments[i].doctor.firstName, appointments[i].doctor.lastName,
               appointments[i].appointmentDate, appointments[i].appointmentTime,
               statusToString(appointments[i].status));
    }
}

// Function to display scheduled appointments
void displayScheduledAppointments()
{

    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount;
    searchAppointmentsByPatientId(patientId, appointments, &appointmentCount);

     if (appointmentCount == 0)
    {
        printf("No appointments found.\n");
        return;
    }

    printf("Current Appointment Details:\n");
    printf("\nID\tDate\t\tTime\tType\n");

    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].patient.patientId == patientId && appointments[i].status == SCHEDULED)
        {
            printf("%d\t%s\t%s\t%s\n", appointments[i].appointmentId, appointments[i].appointmentDate,
                   appointments[i].appointmentTime, appointmentTypeToString(appointments[i].appointmentType));
        }
    }
}

// Function to get valid appointment ID from patient
int getValidAppointmentId(int patientId)
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount;
    searchAppointmentsByPatientId(patientId, appointments, &appointmentCount);

    int appointmentId;
    do
    {
        printf("Enter Appointment ID: ");
        scanf("%d", &appointmentId);

        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].appointmentId == appointmentId && appointments[i].patient.patientId == patientId && appointments[i].status == SCHEDULED)
            {
                return appointmentId;
            }
        }
        printf("Invalid Appointment ID. Please try again.\n");
    } while (1);
}

// Function to reschedule appointment
void rescheduleAppointment()
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);
    displayScheduledAppointments();

    int appointmentId = getValidAppointmentId(patientId);

    // Change appointment date and time
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].appointmentId == appointmentId)
        {
            printf("Enter new date (YYYY-MM-DD): ");
            scanf("%s", appointments[i].appointmentDate);
            printf("Enter new time (HH:MM): ");
            scanf("%s", appointments[i].appointmentTime);
            printf("Appointment rescheduled successfully.\n");
            break;
        }
    }
    saveAppointmentsToFile(appointments, appointmentCount);
}

// Function to cancel appointment
void cancelAppointment()
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    displayScheduledAppointments();

    int appointmentId = getValidAppointmentId(patientId);

    // Change appointment status to cancelled
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].appointmentId == appointmentId)
        {
            appointments[i].status = CANCELLED;
            printf("Appointment cancelled successfully.\n");
            break;
        }
    }
    saveAppointmentsToFile(appointments, appointmentCount);
}
