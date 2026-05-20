#include "Slot.h"

//default constructor
Slot::Slot()
{
    slotID = -1;
    latestID = -1;
    time = "";
    isAvailable = false;
}

//parameterized constructor
Slot::Slot(int slotID, int latestID, string time, bool isAvailable) {
    this->slotID = slotID;
    this->latestID = latestID;
    this->time = time;
    this->isAvailable = isAvailable;
}

//destructor
Slot::~Slot()
{

}

//setters
void Slot::setSlotID(int slotID)
{
    this->slotID = slotID;
}

void Slot::setLatestID(int latestID)
{
    this->latestID = latestID;
}

void Slot::setTime(const string& time)
{
    this->time = time;
}

void Slot::setIsAvailable(bool b)
{
    isAvailable = b;
}

//getters
int  Slot::getSlotID() const
{
    return slotID;
}


int  Slot::getLatestID() const
{
    return latestID;
}

string Slot::getTime() const               
{
    return time;
}

bool Slot::getIsAvailable() const
{
    return isAvailable;
}

//a function that loads the slot's details from a file
void Slot::loadFromFile(ifstream& in) {
    in >> slotID >> latestID;
    in.ignore();
    getline(in, time);
    in >> isAvailable;
}

//a function that saves the slot's details to a file
void Slot::saveToFile(ofstream& out) const {
    out << slotID      << "\n"
        << latestID    << "\n"
        << time        << "\n"
        << isAvailable << "\n";
}
