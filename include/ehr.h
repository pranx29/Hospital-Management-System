#ifndef EHR_H
#define EHR_H

#define MAX_EHRS 100
#define MAX_DIAGNOSIS_LENGTH 250
#define MAX_TREATMENT_LENGTH 250
#define EHR_FILE_PATH "data/ehr.csv"

#include "common.h"
#include "patient.h"
#include "doctor.h"


typedef struct
{
    int recordId;
    Patient patient;
    Doctor doctor;
    char visitDate[MAX_DATE_LENGTH];
    char diagnosis[MAX_DIAGNOSIS_LENGTH];
    char treatment[MAX_TREATMENT_LENGTH];
} EHR;

// Function prototypes for EHR operations
int readEHRsFromFile(EHR ehrs[]);
int saveEHRsToFile(EHR ehrs[], int ehrCount);
void searchEHRByPatientId(int patient_id);
void searchEHRByDoctorId(int doctor_id);
void addEHRRecord(EHR new_record);

#endif // EHR_H
