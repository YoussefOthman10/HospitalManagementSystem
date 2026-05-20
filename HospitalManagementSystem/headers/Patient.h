#ifndef PATIENT_H
#define PATIENT_H

#include "User.h"

//forward declarations to avoid infinite chain includes
//the full class definitions aren't needed here since we are dealing with pointers to these classes
#include "Doctor.h"
#include "Slot.h"
#include "Appointment.h"

//a derived class that inherits the base class (user)
class Patient : public User 
{
private:
    int age;
    string patientGender;
    string bloodType;
    string disease;
    int contactNumber;
    Appointment* currentAppointment;   //this is only a pointer so the full appointment class definition is not needed here

public:
    //default constructor
    Patient();

    //parameterized constructor
    Patient(int id, string user, string pass, int age, string gender,
            string blood, string disease, int contact, Appointment* app);

    //destructor
    ~Patient();

    //setters
    void setAge(int age);
    void setGender(const string& gender);
    void setBloodType(const string& bloodType);
    void setDisease(const string& disease);
    void setContactNumber(int contactNumber);
    void setCurrentAppointment(Appointment* appointment);

    //getters
    int getAge() const;
    string getGender() const;
    string getBloodType() const;
    string getDisease() const;
    int getContactNumber() const;
    Appointment* getCurrentAppointment() const;

    //a function that lets the patient make an appointment
    bool makeAppointment(Doctor& d, Slot& s);    //marks slot unavailable

    //a function that lets the patient cancel an appointment he/she made before
    void cancelAppointment(int appointmentId);   //clears current appointment if matched

    //a function that lets the patient view all of his appointments
    void viewAppointments() const;               //displays current appointment

    //overriden functions that display and update the patient's details
    void getDetails() const override;
    void updateDetails() override;

    //overriden functions that load and save the patient's details from a file
    void loadFromFile(ifstream& in) override;
    void saveToFile(ofstream& out) const override;
    
};

#endif
