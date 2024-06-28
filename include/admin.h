#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include "common.h"
#include "user.h"
#include "patient.h"
#include "doctor.h"
#include "staff.h"
#include "appointment.h"
#include "inventory.h"

void adminMenu();
void registerPatient();
void registerDoctor();
void registerStaff();
void viewAppointmentTrends();
void manageInventory();
void viewInventory();
void searchInventory();

#endif