# Hospital Management System (HMS)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)

## Introduction

This Hospital Management System (HMS) is a console application developed in C as a college assignment. It aims to streamline essential hospital functionalities to improve efficiency and patient care. The system caters to the needs of hospital administrators, patients, doctors, and staff nurses, providing them with various features to manage appointments, access electronic health records (EHR), handle inventory, and generate reports.

## Features

### Hospital Administrator

- Login and logout from the system
- Register new users (patients, doctors, and staff nurses) into the system
- Identify appointment trends and adjust staffing or clinic hours accordingly
- Manage inventory (view and search), track hospital supplies and medications, ensuring timely restocking and preventing shortages

### Patient

- Login and logout from the system
- Appointment management: View, reschedule, and cancel appointments electronically
- Electronic Health Records (EHR) access (view only): Secure access to a portion of their medical history, prescriptions, appointment history, and billing information
- Billing management (view and search): View billing details and manage insurance claims

### Doctor

- Login and logout from the system
- Doctor scheduler: Manage schedules and availability for appointments, allowing patients to book slots conveniently and reducing wait times
- Secure EHR access (view only): Provide doctors with secure access to complete patient Electronic Health Records (EHR)
- Reporting and analytics (view and search): Generate reports on patients or specific conditions to track treatment trends and measure outcomes

### Staff Nurse

- Login and logout from the system
- Doctor scheduler: Access doctor schedules and availability for appointments
- Inventory management: Access and manage supplies and medications at the nurse's station directly through the HMS
- Reporting and analytics (view and search): Generate reports on patients or specific units to identify trends and areas for improvement in care delivery

## Usage

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/pranx29/hospital-management-system.git
   ```
2. Compile the C code using a C compiler.
3. Run the compiled executable file to launch the HMS console application.
4. Follow the on-screen prompts to navigate through different functionalities as a hospital administrator, patient, doctor, or staff nurse.
