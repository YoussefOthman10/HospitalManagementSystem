#ifndef MENUS_H
#define MENUS_H

#include "Admin.h"
#include "Appointment.h"
//some golbal functions and the menus of the program used in the main function
//the maximum number of concurrent appointments stored in memory/a patient can make
const int MAX_APPOINTMENTS = 5;

//a function that clears invalid input state and removes leftover characters from input buffer
void clearInput();

//functions that load and save appointment details using files
void loadAppointments(Appointment* appts, int& count, int& nextId);
void saveAppointments(Appointment* appts, int count, int nextId);

//a function that computes the next safe slot id from all of the loaded doctors
int computeNextSlotId(Admin& admin);

//a function that lets the patient search for doctors by specialty and book an appointment
void searchAndBook(Admin& admin, Patient* patient,
                   Appointment* appts, int& apptCount, int& nextApptId);

//menus
void adminMenu  (Admin& admin, Appointment* appts,
                 int& apptCount, int& nextSlotId);
void doctorMenu (Admin& admin, Doctor*  doctor,
                 Appointment* appts, int& apptCount, int& nextSlotId);
void patientMenu(Admin& admin, Patient* patient,
                 Appointment* appts, int& apptCount, int& nextApptId);

#endif
