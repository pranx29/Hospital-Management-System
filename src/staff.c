#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/staff.h"
#include "../include/appointment.h"
#include "../include/inventory.h"

// Function to read staff from file to array
int readStaffFromFile(Staff staff[])
{
    FILE *file = fopen(STAFF_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int staffCount = 0;
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &staff[staffCount].staffId, &staff[staffCount].user.userId,
                  staff[staffCount].firstName, staff[staffCount].lastName,
                  staff[staffCount].role, staff[staffCount].contactNumber,
                  staff[staffCount].email) == 7)
    {
        staffCount++;
        if (staffCount >= MAX_STAFF)
        {
            printf("Maximum staff limit reached. Increase MAX_STAFF if needed.\n");
            break;
        }
    }

    fclose(file);
    return staffCount;
}

// Function to save staff from array to file
int saveStaffToFile(Staff staff[], int staffCount)
{
    FILE *file = fopen(STAFF_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < staffCount; i++)
    {
        fprintf(file, "%d,%d,%s,%s,%s,%s,%s\n", staff[i].staffId, staff[i].user.userId,
                staff[i].firstName, staff[i].lastName, staff[i].role,
                staff[i].contactNumber, staff[i].email);
    }

    fclose(file);
    return 1;
}

// Function to search for staff by ID
void searchStaffById(int staffId, Staff *staff)
{
    Staff staffs[MAX_STAFF];
    int staffCount = readStaffFromFile(staffs);

    for (int i = 0; i < staffCount; i++)
    {
        printf("%d\n", staffs[i].staffId);
        if (staffs[i].staffId == staffId)
        {
            *staff = staffs[i];
            return;
        }
    }
    printf("Staff not found.\n");
}

void getStaffByUserId(int userId, Staff *staff)
{
    Staff staffs[MAX_STAFF];
    int staffCount = readStaffFromFile(staffs);

    for (int i = 0; i < staffCount; i++)
    {
        if (staffs[i].user.userId == userId)
        {
            *staff = staffs[i];
            return;
        }
    }
    printf("Staff not found.\n");
}

int getValidStaffId(const char *type)
{
    int staffId;
    int isValid = 0;
    Staff staff;

    do
    {
        printf("Staff ID (%s): ", type);
        scanf("%d", &staffId);
        searchStaffById(staffId, &staff);

        if (staff.staffId == staffId)
        {
            isValid = 1;
        }

    } while (!isValid);
    return staffId;
}

// Function to get new staff data from user input
void getStaffData(Staff *staff)
{

    staff->user.userId = generateUserId();
    strcpy(staff->user.role, "staff");
    strcpy(staff->firstName, getText("First Name", MAX_NAME_LENGTH));
    strcpy(staff->lastName, getText("Last Name", MAX_NAME_LENGTH));
    strcpy(staff->role, getText("Role", MAX_ROLE_LENGTH));
    strcpy(staff->contactNumber, getContactNumber());
    strcpy(staff->email, getEmail());

    // Ask for login information
    printf("\nPlease enter login information:\n");
    getUserCredentials(&staff->user);
}

// Function to add new staff
int addStaff(Staff *newStaff)
{
    Staff staff[MAX_STAFF];
    int staffCount = readStaffFromFile(staff);

    if (staffCount >= MAX_STAFF)
    {
        printf("Maximum staff limit reached. Cannot add more staff.\n");
        return 0;
    }

    newStaff->staffId = staffCount + 1;
    staff[staffCount] = *newStaff;
    staffCount++;

    if (saveStaffToFile(staff, staffCount) == 0 || addUser(&newStaff->user) == 0)
    {
        printf("Error saving staff to file.\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

// Create staff main menu: Create appoinment, view appoinment, update appoinment, view inventory, update inventory supplies make all staff don't have access to every menu:

void createAppointment()
{
    printf("Appointment Details:\n");
    Appointment appointment;

    getAppointmentData(&appointment);

    if (addAppointment(&appointment) == 1)
    {
        printf("Appointment added successfully.\n");
    }
    else
    {
        printf("Error adding appointment.\n");
    }
}

void viewAppointmentsByStaffId(int staffId)
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    if (appointmentCount == 0)
    {
        printf("No appointments found.\n");
        return;
    }

    printf("\nID\tDate\t\tTime\tType\n");
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].nurse.staffId == staffId && appointments[i].status == SCHEDULED)
        {
            printf("%d\t%s\t%s\t%s\n", appointments[i].appointmentId, appointments[i].appointmentDate,
                   appointments[i].appointmentTime, appointmentTypeToString(appointments[i].appointmentType));
        }
    }
}

void viewAppointments(int staffId)
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    if (appointmentCount == 0)
    {
        printf("No appointments found.\n");
        return;
    }

    // Ask for filter
    int choice;
    printf("Filter appointments by:\n");
    printf("1. Patient ID\n");
    printf("2. Doctor ID\n");
    printf("3. Nurse ID\n");

    printf("Enter your choice: ");
    choice = getUserChoice(1, 3);

    if (choice == 1)
    {
        int patientId = getValidPatientId();
        viewAppointmentsByPatientID(patientId);
    }
    else if (choice == 2)
    {
        int doctorId = getValidDoctorId();
        viewAppointmentsByDoctorID(doctorId);
    }
    else if (choice == 3)
    {
        viewAppointmentsByStaffId(staffId);
    }
}

void updateAppointment()
{
    Appointment appointments[MAX_APPOINTMENTS];
    int appointmentCount = readAppointmentsFromFile(appointments);

    if (appointmentCount == 0)
    {
        printf("No appointments found.\n");
        return;
    }

    int appointmentId = getValidAppointmentId();
    Appointment appointment;
    searchAppointmentById(appointmentId, &appointment);

    printf("Current Appointment Details:\n");
    printf("\nID\tDate\t\tTime\tType\n");
    printf("%d\t%s\t%s\t%s\n", appointment.appointmentId, appointment.appointmentDate,
           appointment.appointmentTime, appointmentTypeToString(appointment.appointmentType));

    printf("Update Appointment:\n");

    // Change appointment date and time
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].appointmentId == appointmentId)
        {
            strcpy(appointments[i].appointmentDate, getDate("Appointment Date (YYYY-MM-DD)"));
            strcpy(appointments[i].appointmentTime, getTime());
            appointments[i].status = getNumber("Status (0: Scheduled, 1: Cancelled):");
            printf("Appointment rescheduled successfully.\n");
            break;
        }
    }
    if (saveAppointmentsToFile(appointments, appointmentCount))
    {
        printf("Appointment updated successfully.\n");
    }
    else
    {
        printf("Error updating appointment.\n");
    }
}

void receptionistMenu(int staffId)
{
    int choice;
    do
    {
        printf("\n------------- Receptionist Main Menu -------------\n");
        printf("1. Create Appointment\n");
        printf("2. View Appointment\n");
        printf("3. Update Appointment\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        choice = getUserChoice(1, 4);

        switch (choice)
        {
        case 1:
            createAppointment();
            break;
        case 2:
            viewAppointments(staffId);
            break;
        case 3:
            updateAppointment();
            break;
        case 4:
            printf("Logging out...\n");
            return;
        }

    } while (1);
}

void nurseMenu(int staffId)
{
    int choice;
    do
    {
        printf("\n------------- Nurse Main Menu -------------\n");
        printf("1. View Appointment\n");
        printf("2. Update Appointment\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        choice = getUserChoice(1, 3);

        switch (choice)
        {
        case 1:
            viewAppointmentsByStaffId(staffId);
            break;
        case 2:
            updateAppointment();
            break;
        case 3:
            printf("Logging out...\n");
            return;
        }

    } while (1);
}

void managerMenu()
{
    int choice;
    do
    {
        printf("\n------------- Manager Main Menu -------------\n");
        printf("1. View Inventory\n");
        printf("2. Search Inventory\n");
        printf("3. Update Inventory Supplies\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
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
            updateInventory();
            break;
        case 4:
            printf("Logging out...\n");
            return;
        }

    } while (1);
}

void staffMenu(int userId)
{
    Staff staff;
    getStaffByUserId(userId, &staff);

    printf("Welcome %s %s\n", staff.firstName, staff.lastName);

    if (strcmp(staff.role, "receptionist") == 0)
    {
        receptionistMenu(staff.staffId);
    }
    else if (strcmp(staff.role, "nurse") == 0)
    {
        nurseMenu(staff.staffId);
    }
    else if (strcmp(staff.role, "manager") == 0)
    {
        managerMenu();
    }
}
