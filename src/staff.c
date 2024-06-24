#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/staff.h"

// Function to read staff from file to array
int readStaffFromFile(Staff staff[]) {
    FILE *file = fopen(STAFF_FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int staffCount = 0;
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &staff[staffCount].staffId, &staff[staffCount].userId,
                  staff[staffCount].firstName, staff[staffCount].lastName,
                  staff[staffCount].role, staff[staffCount].contactNumber,
                  staff[staffCount].email) == 7) {
        staffCount++;
        if (staffCount >= MAX_STAFF) {
            printf("Maximum staff limit reached. Increase MAX_STAFF if needed.\n");
            break;
        }
    }

    fclose(file);
    return staffCount;
}

// Function to save staff from array to file
int saveStaffToFile(Staff staff[], int staffCount) {
    FILE *file = fopen(STAFF_FILE_PATH, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < staffCount; i++) {
        fprintf(file, "%d,%d,%s,%s,%s,%s,%s\n", staff[i].staffId, staff[i].userId,
                staff[i].firstName, staff[i].lastName, staff[i].role,
                staff[i].contactNumber, staff[i].email);
    }

    fclose(file);
    return 1;
}

// Function to search for staff by ID
Staff *searchStaffById(int staffId) {
    static Staff staff[MAX_STAFF]; // Static array to hold staff data
    int staffCount = readStaffFromFile(staff);

    for (int i = 0; i < staffCount; i++) {
        if (staff[i].staffId == staffId) {
            return &staff[i];
        }
    }
    return NULL; // Return NULL if staff with given ID is not found
}

// Function to get new staff data from user input
Staff getStaffData() {
    Staff staff;

    printf("First Name: ");
    scanf("%s", staff.firstName);

    printf("Last Name: ");
    scanf("%s", staff.lastName);

    printf("Role: ");
    scanf("%s", staff.role);

    printf("Contact Number: ");
    scanf("%s", staff.contactNumber);

    printf("Email: ");
    scanf("%s", staff.email);

    // Assuming user ID is generated or assigned elsewhere in the system
    staff.userId = 0; // Initialize or generate user ID as needed

    return staff;
}

// Function to add new staff
void addStaff(Staff newStaff) {
    Staff staff[MAX_STAFF];
    int staffCount = readStaffFromFile(staff);

    if (staffCount >= MAX_STAFF) {
        printf("Maximum staff limit reached. Cannot add more staff.\n");
        return;
    }

    newStaff.staffId = staffCount + 1;
    staff[staffCount] = newStaff;
    staffCount++;

    if (saveStaffToFile(staff, staffCount) == 0) {
        printf("Failed to add staff.\n");
        return;
    } else {
        printf("Staff added successfully.\n");
    }
}


