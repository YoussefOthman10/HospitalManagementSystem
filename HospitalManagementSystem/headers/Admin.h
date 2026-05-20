#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Doctor.h"
#include "Patient.h"

//a derived class that inherits the base class (user)
class Admin : public User 
{
private:
    Doctor* doctors;         //a dynamic array that carries doctor objects
    int doctorCount;
    int doctorCapacity;
    int nextDoctorId;
    Patient* patients;       //a dynamic array that carries patient objetcs
    int patientCount;
    int patientCapacity;
    int nextPatientId;
    static const int INITIAL_CAPACITY = 50;

public:
    //default constructor
    Admin();

    //parameterized constructor
    Admin(int id, string user, string pass);

    //destructor
    ~Admin();

    //setters
    void setNextDoctorId(int id);
    void setNextPatientId(int id);

    //getters
    Doctor* getDoctors() const;
    Patient* getPatients() const;
    int getDoctorCount() const;
    int getPatientCount() const;
    int getNextDoctorId() const;
    int getNextPatientId() const;

    //a function that lets the admin add a doctor to the system
    void addDoctor(Doctor d);

    //a function that lets the admin remove a doctor from the system
    void removeDoctor(int id);

    //a function that lets the admin add a patient to the system
    void addPatient(Patient p);

    //a function that lets the admin remove a patient from the system
    void removePatient(int id);

    //a function that finds a doctor by his id
    Doctor*  findDoctorByID(int id);

    //a function that finds a patient by his id
    Patient* findPatientByID(int id);

    //functions that load and save the doctor count and the next doctor id using files
    void loadDoctors(const string& filename);
    void saveDoctors(const string& filename)  const;
    
    //functions that load and save the patient count and the next patient id using files
    void loadPatients(const string& filename);
    void savePatients(const string& filename) const;
    

    //overriden functions that prints out the admin and sonme of the system details and updates them
    void getDetails()    const override;
    void updateDetails()       override;
};

#endif
