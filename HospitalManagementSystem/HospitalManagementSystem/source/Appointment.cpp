#include "Appointment.h"

//default constructor
Appointment::Appointment()
{
    id = 0;
    doctorId = 0;
    patientId = 0;
    slotId = -1;
    date = "";
}

//parameterized constructo
Appointment::Appointment(int id, int doctorId, int patientId,
                         int slotId, string date) 
{
    this->id = id;
    this->doctorId = doctorId;
    this->patientId = patientId;
    this->slotId = slotId;
    this->date = date;
}

//convenience constructor where id and date are set later making this constructor useful when creating a new appointment before saving it (constructor overloading)
Appointment::Appointment(int pId, int dId, int sId)
{
    this->patientId = pId;
    this->doctorId = dId;
    this->slotId = sId;
    this->id = 0;
    this->date = "";
}

//destructor
Appointment::~Appointment()
{

}

//setters
void Appointment::setId(int id)              
{
    this->id = id;
}

void Appointment::setDoctorId(int doctorId)  
{
    this->doctorId = doctorId;
}

void Appointment::setPatientId(int patientId)
{
    this->patientId = patientId;
}

void Appointment::setSlotId(int slotId)
{
    this->slotId = slotId;
}

void Appointment::setDate(const string& date)
{
    this->date = date;
}

//getters
int Appointment::getId() const
{
    return id;
}

int Appointment::getDoctorId() const
{
    return doctorId;
}

int Appointment::getPatientId() const
{
    return patientId;
}

int Appointment::getSlotId() const
{
    return slotId;
}

string Appointment::getDate() const
{
    return date;
}

//a function that displays the appointment info
void Appointment::displayAppointmentInfo() const
{
    cout << "------------------------------\n";
    cout << "Appointment ID : " << id        << "\n";
    cout << "Date           : " << (date.empty() ? "N/A" : date) << "\n";
    cout << "Doctor ID      : " << doctorId  << "\n";
    cout << "Patient ID     : " << patientId << "\n";
    cout << "Slot ID        : " << slotId    << "\n";
    cout << "------------------------------\n";
}

//a function that loads the appointment details from a file
void Appointment::loadFromFile(ifstream& in)
{
    in >> id >> doctorId >> patientId >> slotId;
    in.ignore();
    getline(in, date);
}

//a function that saves the appointment details to a file
void Appointment::saveToFile(ofstream& out) const
{
    out << id        << "\n"
        << doctorId  << "\n"
        << patientId << "\n"
        << slotId    << "\n"
        << date      << "\n";
}
