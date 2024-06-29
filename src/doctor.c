#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/doctor.h"
#include "../include/appointment.h"
#include "../include/ehr.h"

// Below are the functions defined for doctor management in doctor.h

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
                  &doctors[doctorCount].doctorId, &doctors[doctorCount].user.userId,
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
        fprintf(file, "%d,%d,%s,%s,%s,%s,%s\n", doctors[i].doctorId, doctors[i].user.userId,
                doctors[i].firstName, doctors[i].lastName, doctors[i].specialization,
                doctors[i].contactNumber, doctors[i].email);
    }

    fclose(file);
    return 1;
}

// Function to search for a doctor by ID
void searchDoctorById(int doctorId, Doctor *doctor)
{
    Doctor doctors[MAX_DOCTORS];
    int doctorCount = readDoctorsFromFile(doctors);

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == doctorId)
        {
            *doctor = doctors[i];
            return;
        }
    }
    printf("Doctor with ID %d not found.\n", doctorId);
}

// Function to get a valid doctor ID from user input
int getValidDoctorId()
{
    int doctorId;
    int isValid = 0;
    Doctor doctor;

    do
    {
        printf("Doctor ID: ");
        scanf("%d", &doctorId);
        searchDoctorById(doctorId, &doctor);

        if (doctor.doctorId == doctorId)
        {
            isValid = 1;
        }

    } while (!isValid);
    return doctorId;
}

// Function to get new doctor data from user input
void getDoctorData(Doctor *doctor)
{
    doctor->user.userId = generateUserId();
    strcpy(doctor->user.role, "doctor");
    strcpy(doctor->firstName, getText("First Name", MAX_NAME_LENGTH));
    strcpy(doctor->lastName, getText("Last Name", MAX_NAME_LENGTH));
    strcpy(doctor->specialization, getText("Specialization", MAX_SPECIALIZATION_LENGTH));
    strcpy(doctor->contactNumber, getContactNumber());
    strcpy(doctor->email, getEmail());

    // Ask for login information
    printf("\nPlease enter login information:\n");
    getUserCredentials(&doctor->user);
}

// Function to add a new doctor
int addDoctor(Doctor *newDoctor)
{
    Doctor doctors[MAX_DOCTORS];
    int doctorCount = readDoctorsFromFile(doctors);

    if (doctorCount >= MAX_DOCTORS)
    {
        printf("Maximum doctor limit reached. Cannot add more doctors.\n");
        return 0;
    }

    newDoctor->doctorId = doctorCount + 1;
    doctors[doctorCount] = *newDoctor;
    doctorCount++;

    if (saveDoctorsToFile(doctors, doctorCount) == 0 || addUser(&newDoctor->user) == 0)
    {
        printf("Error saving doctor to file.\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

// Function to get doctor data by userid
void getDoctorByUserId(int userId, Doctor *doctor)
{
    Doctor doctors[MAX_DOCTORS];
    int doctorCount = readDoctorsFromFile(doctors);

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].user.userId == userId)
        {
            *doctor = doctors[i];
            return;
        }
    }
    printf("Doctor with user ID %d not found.\n", userId);
}

// Below are the functions defined for doctor operations in doctor.c

// Function to view appointments of a doctor
void viewAppointmentsOfDoctor(int doctorId)
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount;
    searchAppointmentsByDoctorId(doctorId, appointments, &appointmentCount);

    printf("\n---------------- Appointments ---------------\n");

    if (appointmentCount == 0)
    {
        printf("No appointments found for doctor with ID %d.\n", doctorId);
        return;
    }

    printf("Appointment ID\tPatient Name\tAppointment Date\tAppointment Time\tStatus\n");
    for (int i = 0; i < appointmentCount; i++)
    {
        searchPatientById(appointments[i].patient.patientId, &appointments[i].patient);
        printf("%d\t\t%s %s\t%s\t\t%s\t\t\t%s\n", appointments[i].appointmentId,
               appointments[i].patient.firstName, appointments[i].patient.lastName,
               appointments[i].appointmentDate, appointments[i].appointmentTime,
               statusToString(appointments[i].status));
    }
}

// Function to view EHR of a patient for a doctor
void viewDoctorEHR(int doctorId)
{
    int patientId = getValidPatientId();

    EHR ehrs[MAX_EHRS];
    int ehrCount = readEHRsFromFile(ehrs);

    printf("\n---------------- Health Records ---------------\n");

    if (ehrCount == 0)
    {
        printf("No EHR records found.\n");
        return;
    }

    printf("Record ID\\tVisit Date\t\tDiagnosis\tTreatment\n");
    for (int i = 0; i < ehrCount; i++)
    {
        if (ehrs[i].patient.patientId == patientId && ehrs[i].doctor.doctorId == doctorId)
        {
            printf("%d\t\t%s\t%s\t%s\n", ehrs[i].recordId, ehrs[i].visitDate, ehrs[i].diagnosis, ehrs[i].treatment);
        }
    }
}

// Function to add EHR record for a patient
void addEHRRecord(int doctorId)
{
    EHR ehr;
    getEHRData(&ehr, doctorId);
    addEHR(ehr);
}

// Function to display doctor main menu: Check appointments, view EHR of a patient, add ehr
void doctorMenu(int UserId)
{
    Doctor doctor;
    getDoctorByUserId(UserId, &doctor);
    if (doctor.doctorId == -1)
    {
        printf("Error logging in to your account.\n");
        return;
    }

    int choice;
    do
    {
        printf("\n---------------- Doctor Menu ---------------\n");
        printf("Welcome Dr. %s %s\n", doctor.firstName, doctor.lastName);
        printf("1. View Appointments\n");
        printf("2. View EHR\n");
        printf("3. Add EHR\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");

        choice = getUserChoice(1, 4);

        switch (choice)
        {
        case 1:
            viewAppointmentsOfDoctor(doctor.doctorId);
            break;
        case 2:
            viewDoctorEHR(doctor.doctorId);
            break;
        case 3:
            addEHRRecord(doctor.doctorId);
            break;
        case 4:
            printf("Logging out...\n");
            break;
        }
    } while (1);
}