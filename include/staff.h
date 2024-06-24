#ifndef STAFF_H
#define STAFF_H

#define MAX_STAFF 100  // Define your maximum staff limit as needed
#define STAFF_FILE_PATH "../data/staffs.csv"  // Define your staff data file path

#include "common.h"
#include "user.h"

typedef struct {
    int staffId;
    int userId;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char role[MAX_ROLE_LENGTH];
    char contactNumber[MAX_CONTACT_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} Staff;

// Function prototypes
int readStaffFromFile(Staff staff[]);
int saveStaffToFile(Staff staff[], int staffCount);
Staff *searchStaffById(int staffId);
Staff getStaffData();
void addStaff(Staff newStaff);

#endif /* STAFF_H */
