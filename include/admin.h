#ifndef ADMIN_H
#define ADMIN_H

#include <stdio.h>
#include "common.h"
#include "user.h"
#include "patient.h"
#include "doctor.h"
#include "staff.h"

void adminMenu();
void registerPatient();
void registerDoctor();
void registerStaff();

#endif