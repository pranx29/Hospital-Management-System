#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ehr.h"

// Function to read EHR records from file to array
int readEHRsFromFile(EHR ehrs[])
{
    FILE *file = fopen(EHR_FILE_PATH, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int ehrCount = 0;
    while (fscanf(file, "%d,%d,%d,%10[^,],%255[^,],%255[^\n]\n",
                  &ehrs[ehrCount].recordId, &ehrs[ehrCount].patient.patientId, &ehrs[ehrCount].doctor.doctorId,
                  ehrs[ehrCount].visitDate, ehrs[ehrCount].diagnosis, ehrs[ehrCount].treatment) == 6)
    {
        ehrCount++;
        if (ehrCount >= MAX_EHRS)
        {
            printf("Maximum EHR limit reached. Increase MAX_EHRS if needed.\n");
            break;
        }
    }

    fclose(file);
    return ehrCount;
}

// Function to save EHR records from array to file
int saveEHRsToFile(EHR ehrs[], int ehrCount)
{
    FILE *file = fopen(EHR_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < ehrCount; i++)
    {
        fprintf(file, "%d,%d,%d,%s,%s,%s\n", ehrs[i].recordId, ehrs[i].patient.patientId, ehrs[i].doctor.doctorId,
                ehrs[i].visitDate, ehrs[i].diagnosis, ehrs[i].treatment);
    }

    fclose(file);
    return 1;
}

// Function to search for EHR records by patient ID
void searchEHRByPatientId(int patient_id, EHR *ehr)
{
    EHR ehrs[MAX_EHRS];
    int ehrCount = readEHRsFromFile(ehrs);

    for (int i = 0; i < ehrCount; i++)
    {
        if (ehrs[i].patient.patientId == patient_id)
        {
            ehr = &ehrs[i];
            return;
        }
    }
    printf("No EHR record found for patient ID: %d\n", patient_id);
}

// Function to search for EHR records by doctor ID
void searchEHRByDoctorId(int doctor_id)
{
    EHR ehrs[MAX_EHRS];
    int ehrCount = readEHRsFromFile(ehrs);

    for (int i = 0; i < ehrCount; i++)
    {
        if (ehrs[i].doctor.doctorId == doctor_id)
        {
            printf("Record ID: %d\nPatient ID: %d\nDoctor ID: %d\nDate: %s\nDiagnosis: %s\nTreatment: %s\n\n",
                   ehrs[i].recordId, ehrs[i].patient.patientId, ehrs[i].doctor.doctorId,
                   ehrs[i].visitDate, ehrs[i].diagnosis, ehrs[i].treatment);
        }
    }
}

// Function to get EHR data
void getEHRData(EHR *ehr, int doctorId)
{
    ehr->patient.patientId = getValidPatientId();
    ehr->doctor.doctorId = doctorId;
    strcpy(ehr->visitDate, getCurrentDate());
    strcpy(ehr->diagnosis, getText("Diagnosis", MAX_DIAGNOSIS_LENGTH));
    strcpy(ehr->treatment, getText("Treatment", MAX_TREATMENT_LENGTH));
}

// Function to add a new EHR record
void addEHR(EHR newRecord)
{
    EHR ehrs[MAX_EHRS];
    int ehrCount = readEHRsFromFile(ehrs);

    newRecord.recordId = ehrCount + 1;
    ehrs[ehrCount] = newRecord;
    ehrCount++;

    if (saveEHRsToFile(ehrs, ehrCount))
    {
        printf("EHR record added successfully.\n");
    }
    else
    {
        printf("Error saving EHR record.\n");
    }
}
