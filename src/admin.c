#include <stdio.h>
#include <stdlib.h>
#include "../include/admin.h"

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
            printf("Viewing appointment trends...\n");
            break;
        case 5:
            printf("Managing inventory...\n");
            break;
        case 6:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            break;
        }
    } while (choice == -1);
}

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