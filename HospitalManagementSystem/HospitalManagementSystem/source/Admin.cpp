#include "Admin.h"

//default constructor
Admin::Admin() : User(0, "admin", "admin123") //calling the base class's (user) default constructor to set and initialize the admin's credentials (id, username and password)
{
    doctorCapacity = INITIAL_CAPACITY;
    doctors = new Doctor[doctorCapacity]; //dynamicllay allocating an array of doctors with the size of the initial capacity
    doctorCount = 0;
    nextDoctorId = 1;
    patientCapacity = INITIAL_CAPACITY;
    patients = new Patient[patientCapacity]; //dynamicllay allocating an array of patients with the size of the initial capacity
    patientCount = 0;
    nextPatientId = 1;
}

//parameterized constructor
Admin::Admin(int id, string user, string pass) : User(id, user, pass) {
    doctorCapacity  = INITIAL_CAPACITY;
    doctors = new Doctor[doctorCapacity]; //dynamicllay allocating an array of doctors with the size of the initial capacity
    doctorCount = 0;
    nextDoctorId = 1;
    patientCapacity = INITIAL_CAPACITY;
    patients = new Patient[patientCapacity]; //dynamicllay allocating an array of patients with the size of the initial capacity
    patientCount = 0;
    nextPatientId = 1;
}

//destructor
Admin::~Admin()
{
    delete[] doctors; //deleting the dynamically allocated array of doctors
    delete[] patients; //deleting the dynamically alloacted array of patients
}

//setters
Doctor* Admin::getDoctors() const
{
    return doctors;
}

Patient* Admin::getPatients() const
{
    return patients;
}

int Admin::getDoctorCount() const
{
    return doctorCount;
}

int Admin::getPatientCount() const
{
    return patientCount;
}

int Admin::getNextDoctorId() const
{
    return nextDoctorId;
}

int Admin::getNextPatientId() const
{
    return nextPatientId;
}

//setters
void Admin::setNextDoctorId(int id)
{
    nextDoctorId = id;
}

void Admin::setNextPatientId(int id)
{
    nextPatientId = id;
}

//a function that lets the admin add a doctor by adding a new doctor object into a dynamically allocated array of doctors
void Admin::addDoctor(Doctor d) 
{
    if (doctorCount >= doctorCapacity)
    {
        doctorCapacity *= 2; //doubling the array's capacity if it is full
        Doctor* grown = new Doctor[doctorCapacity]; //creating a new array with the new capacity
        for (int i = 0; i < doctorCount; i++)
            grown[i] = doctors[i];
        delete[] doctors; //deleting old array stored in memory
        doctors = grown;
    }
    doctors[doctorCount++] = d; //error: deep copy using a copy constructor is needed
}

//a function that lets the admin remove a doctor by his id where we shift the remaining elements in the array to the left after a doctor is removed
void Admin::removeDoctor(int id) 
{
    int index = -1;
    for (int i = 0; i < doctorCount; i++)
        if (doctors[i].getID() == id) 
        { 
            index = i;
            break;
        }
    if (index == -1) 
        throw "Doctor not found.";
    for (int i = index; i < doctorCount - 1; i++)
        doctors[i] = doctors[i + 1];
    doctorCount--; //decrementing the doctor's counter
}

//a function that lets the admin add a patient by adding a new patient object into a dynamically allocated array of patients
void Admin::addPatient(Patient p)
{
    if (patientCount >= patientCapacity)
    {
        patientCapacity *= 2; //doubling the array's capacity if it is full
        Patient* grown = new Patient[patientCapacity]; //creating a new array with the new capacity
        for (int i = 0; i < patientCount; i++)
            grown[i] = patients[i];
        delete[] patients; //deleting old array stored in memory
        patients = grown;
    }
    patients[patientCount++] = p; //error: deep copy using a copy constructor is needed
}

//a function that lets the admin remove a patient by his id where we shift the remaining elements in the array to the left after a patient is removed
void Admin::removePatient(int id)
{
    int index = -1;
    for (int i = 0; i < patientCount; i++)
        if (patients[i].getID() == id)
        {
            index = i;
            break;
        }
    if (index == -1)
        throw "Patient not found.";
    for (int i = index; i < patientCount - 1; i++)
        patients[i] = patients[i + 1];
    patientCount--; //decrementing the patient's counter
}

//a function that finds the doctor by id
Doctor* Admin::findDoctorByID(int id)
{
    for (int i = 0; i < doctorCount; i++)
        if (doctors[i].getID() == id)
            return &doctors[i]; //a pointer is returned to the element where the doctor id is found in the dynamic array
    return nullptr; //a null pointer is returned otherwise
}

//a function that finds the patient by id
Patient* Admin::findPatientByID(int id) 
{
    for (int i = 0; i < patientCount; i++)
        if (patients[i].getID() == id) 
            return &patients[i]; //a pointer is returned to the element where the patient id is found in the dynamic array
    return nullptr;
}

//a function that loads doctor count and the next doctor id from a file
void Admin::loadDoctors(const string& filename)
{
    ifstream in(filename);
    if (!in.is_open())
        return;   //there is no file yet here

    in >> doctorCount >> nextDoctorId;
    if (doctorCount > doctorCapacity)
    {
        delete[] doctors;
        doctorCapacity = doctorCount * 2;
        doctors = new Doctor[doctorCapacity];
    }
    for (int i = 0; i < doctorCount; i++)
        doctors[i].loadFromFile(in);
    in.close();
}

//a function that saves doctor count and the next doctor id to a file
void Admin::saveDoctors(const string& filename) const 
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cout << "Warning: could not open " << filename << " for writing.\n";
        return;
    }
    out << doctorCount  << "\n"
        << nextDoctorId << "\n";
    for (int i = 0; i < doctorCount; i++)
        doctors[i].saveToFile(out);
    out.close();
    cout << "Doctors saved.\n";
}

//a function that loads patient count and the next patient id from a file
void Admin::loadPatients(const string& filename)
{
    ifstream in(filename);
    if (!in.is_open())
        return;

    in >> patientCount >> nextPatientId;
    if (patientCount > patientCapacity)
    {
        delete[] patients;
        patientCapacity = patientCount * 2;
        patients = new Patient[patientCapacity];
    }
    for (int i = 0; i < patientCount; i++)
        patients[i].loadFromFile(in);
    in.close();
}

//a function that saves the patient count and the next patient id to a file
void Admin::savePatients(const string& filename) const
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cout << "Warning: could not open " << filename << " for writing.\n";
        return;
    }
    out << patientCount  << "\n"
        << nextPatientId << "\n";
    for (int i = 0; i < patientCount; i++)
        patients[i].saveToFile(out);
    out.close();
    cout << "Patients saved.\n";
}

//a function that prints out the admin and sonme of the system details
void Admin::getDetails() const 
{
    cout << "------------------------------\n";
    cout << "Role    : Admin\n";
    cout << "ID      : " << id       << "\n";
    cout << "Username: " << username << "\n";
    cout << "Doctors : " << doctorCount  << " registered\n";
    cout << "Patients: " << patientCount << " registered\n";
    cout << "------------------------------\n";
}

//a function that lets the admin update his details
void Admin::updateDetails()
{
    string input;
    cout << "\n--- Update Admin Details ---\n";

    cout << "Current username: " << username << "\n";
    cout << "New username (Press Enter to keep): ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) 
        username = input;

    cout << "New password (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        password = input;

    cout << "Details updated successfully!\n";
}
