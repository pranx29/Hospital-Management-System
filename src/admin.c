#include <stdio.h>
#include <stdlib.h>
#include "../include/admin.h"

void registerPatient()
{
    Patient patient;
    printf("\n------------- Register Patient -------------\n");
    getPatientData(&patient);

    if (addPatient(&patient))
    {
        printf("Patient registered successfully!\n");
        return;
    }
    else
    {
        printf("Failed to register patient. Please try again.\n");
    }
}

void registerDoctor()
{
    Doctor doctor;
    printf("\n------------- Register Doctor -------------\n");
    getDoctorData(&doctor);

    if (addDoctor(&doctor))
    {
        printf("Doctor registered successfully!\n");
        return;
    }
    else
    {
        printf("Failed to register doctor. Please try again.\n");
    }
}

void registerStaff()
{
    Staff staff;
    printf("\n------------- Register Staff -------------\n");
    getStaffData(&staff);

    if (addStaff(&staff))
    {
        printf("Staff registered successfully!\n");
        return;
    }
    else
    {
        printf("Failed to register staff. Please try again.\n");
    }
}

// Function to view appointment trends
void viewAppointmentTrends()
{
    printf("\n------------- Appointment Trends -------------\n");
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    printf("Total Appointments: %d\n\n", appointmentCount);

    // Initialize counters for statuses and types
    int scheduledAppointments = 0;
    int cancelledAppointments = 0;
    int checkupAppointments = 0;
    int consultationAppointments = 0;
    int procedureAppointments = 0;
    int followupAppointments = 0;

    for (int i = 0; i < appointmentCount; i++)
    {
        switch (appointments[i].status)
        {
        case SCHEDULED:
            scheduledAppointments++;
            break;
        case CANCELLED:
            cancelledAppointments++;
            break;
        default:
            // Handle unexpected status
            break;
        }

        switch (appointments[i].appointmentType)
        {
        case CHECKUP:
            checkupAppointments++;
            break;
        case CONSULTATION:
            consultationAppointments++;
            break;
        case PROCEDURE:
            procedureAppointments++;
            break;
        case FOLLOWUP:
            followupAppointments++;
            break;
        default:
            // Handle unexpected appointment type
            break;
        }
    }

    printf("Appointments by Status:\n");
    printf("Scheduled: %d\n", scheduledAppointments);
    printf("Cancelled: %d\n\n", cancelledAppointments);

    printf("Appointments by Type:\n");
    printf("Checkup: %d\n", checkupAppointments);
    printf("Consultation: %d\n", consultationAppointments);
    printf("Procedure: %d\n", procedureAppointments);
    printf("Follow-up: %d\n", followupAppointments);
}


// Function to display options in manage inventory
void manageInventory()
{
    int choice;
    do
    {
        printf("\n---------------- Manage Inventory ---------------\n");
        printf("1. View Inventory\n");
        printf("2. Search Inventory\n");
        printf("3. Go back\n");

        choice = getUserChoice(1, 3);

        switch (choice)
        {
        case 1:
            viewInventory();
            break;
        case 2:
            searchInventory();
            break;
        case 3:
            return;
        }
    } while (1);
}

// Function to display the admin menu
void adminMenu()
{
    int choice;
    do
    {
        printf("\n---------------- Admin Panel ---------------\n");
        printf("1. Register Patient\n");
        printf("2. Register Doctor\n");
        printf("3. Register Staff\n");
        printf("4. View appointment trends\n");
        printf("5. Manage inventory\n");
        printf("6. Logout\n");

        choice = getUserChoice(1, 6);

        switch (choice)
        {
        case 1:
            registerPatient();
            break;
        case 2:
            registerDoctor();
            break;
        case 3:
            registerStaff();
            break;
        case 4:
            viewAppointmentTrends();
            break;
        case 5:
            manageInventory();
            break;
        case 6:
            printf("Logging out...\n");
            return;
        }
    } while (1);
}
