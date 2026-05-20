#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//a class that deals with the appointments and their booking by the patient
class Appointment
{
private:
    int id; //the appointment's id
    string date; //the booking date
    int doctorId; //the doctor's id
    int patientId; //the patient's id
    int slotId; //the slot's id

public:
    //default constructor
    Appointment();

    //parameterized constructor
    Appointment(int id, int doctorId, int patientId, int slotId, string date);

    //convenience constructor
    Appointment(int pId, int dId, int sId);
    
    //destructor
    ~Appointment();

    //setters
    void setId(int id);
    void setDoctorId(int doctorId);
    void setPatientId(int patientId);
    void setSlotId(int slotId);
    void setDate(const string& date);

    //getters
    int    getId()       const;
    int    getDoctorId() const;
    int    getPatientId()const;
    int    getSlotId()   const;
    string getDate()     const;

    //a function that displays the appointment's info
    void displayAppointmentInfo() const;

    //functions to load and save appointment details from files
    void loadFromFile(ifstream& in);
    void saveToFile(ofstream& out) const;
};

#endif
