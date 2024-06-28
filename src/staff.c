#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/staff.h"

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
        if (staffs[i].staffId == staffId)
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