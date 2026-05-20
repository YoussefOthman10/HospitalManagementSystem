#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"

//default constructor
Patient::Patient() : User() //calling the base class's (user) default constructor to initialize id, username and password
{
    age = 0;
    patientGender = "";
    bloodType = "";
    disease = "";
    contactNumber = 0;
    currentAppointment = nullptr;
}

//parameterized constructor
Patient::Patient(int id, string user, string pass, int age, string gender,
                 string blood, string disease, int contact, Appointment* app)
    : User(id, user, pass) //calling the base class (user) parameterized constructor to construct the id, username and password for a patient
{
    this->age                = age;
    this->patientGender      = gender;
    this->bloodType          = blood;
    this->disease            = disease;
    this->contactNumber      = contact;
    this->currentAppointment = app;
}

//destructor
Patient::~Patient() //currentAppointment is non owning so it is not deleted here
{

}

//setters
void Patient::setAge(int age)
{
    this->age = age;
}

void Patient::setGender(const string& g) 
{
    patientGender = g;
}

void Patient::setBloodType(const string& b)
{
    bloodType = b;
}

void Patient::setDisease(const string& d)
{ 
    disease = d;
}

void Patient::setContactNumber(int c)
{
    contactNumber = c;
}

void Patient::setCurrentAppointment(Appointment* app)
{
    currentAppointment = app;
}

//getters
int  Patient::getAge() const
{
    return age;
}

string Patient::getGender() const
{
    return patientGender;
}

string Patient::getBloodType() const  
{
    return bloodType;
}


string Patient::getDisease() const
{
    return disease;
}

int  Patient::getContactNumber() const
{
    return contactNumber;
}

Appointment* Patient::getCurrentAppointment() const
{
    return currentAppointment;
}

//a function that marks the availability of a slot where it returns true if a slot is available
//creating the appointment record is handled in the main
bool Patient::makeAppointment(Doctor& d, Slot& s) 
{
    if (!s.getIsAvailable())
        return false;
    s.setIsAvailable(false);
    return true;
}

//a function that cancels the appointment where it clears current and sets it to a null pointer if id matches
//removing the appointment record is handled in the main
void Patient::cancelAppointment(int appointmentId) {
    if (currentAppointment != nullptr &&
        currentAppointment->getId() == appointmentId)
    {
        currentAppointment = nullptr;
    }
}

//a function that lets the patient view his current appointment
void Patient::viewAppointments() const
{
    if (currentAppointment != nullptr)
    {
        cout << "--- Current Appointment ---\n";
        currentAppointment->displayAppointmentInfo();
    } 
    else
    {
        cout << "No current appointment on record.\n";
    }
}

//an overriden function that displays the patient's details
void Patient::getDetails() const
{
    cout << "------------------------------\n";
    cout << "Role        : Patient\n";
    cout << "ID          : " << id             << "\n";
    cout << "Username    : " << username       << "\n";
    cout << "Age         : " << age            << "\n";
    cout << "Gender      : " << patientGender  << "\n";
    cout << "Blood Type  : " << bloodType      << "\n";
    cout << "Disease     : " << disease        << "\n";
    cout << "Contact     : " << contactNumber  << "\n";
    cout << "------------------------------\n";
}

//an overriden function that lets the patient update his details
void Patient::updateDetails()
{
    string input;
    int    num;

    cout << "\n--- Update Patient Details ---\n";

    cout << "Current username: " << username << "\n";
    cout << "New username (Press Enter to keep): ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) 
        username = input;

    cout << "Current disease: " << disease << "\n";
    cout << "New disease (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        disease = input;

    cout << "Current blood type: " << bloodType << "\n";
    cout << "New blood type (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        bloodType = input;

    cout << "Current gender: " << patientGender << "\n";
    cout << "New gender (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        patientGender = input;

    cout << "Current age: " << age << "\n";
    cout << "New age (Press 0 to keep): ";
    cin >> num;
    if (num > 0) 
        age = num;

    cout << "Current contact: " << contactNumber << "\n";
    cout << "New contact (Press 0 to keep): ";
    cin >> num;
    if (num > 0) 
        contactNumber = num;

    cout << "New password (Press Enter to keep): ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) 
        password = input;

    cout << "Details updated successfully!\n";
}

//current appointment is a runtime pointer so it is not persisted in the loading and saving
//an overriden function that loads the doctor's details from a file
void Patient::loadFromFile(ifstream& in) {
    User::loadFromFile(in);         //to load id, username and password
    in >> age;
    in.ignore();
    getline(in, patientGender);
    getline(in, bloodType);
    getline(in, disease);
    in >> contactNumber;
    currentAppointment = nullptr;   //restablished at runtime if needed
}

//an overriden function that saves the patient's details from a file
void Patient::saveToFile(ofstream& out) const {
    User::saveToFile(out);          //to save id, username and password
    out << age << "\n"
        << patientGender << "\n"
        << bloodType << "\n"
        << disease << "\n"
        << contactNumber << "\n";
}
