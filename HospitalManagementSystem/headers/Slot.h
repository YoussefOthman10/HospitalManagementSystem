#ifndef SLOT_H
#define SLOT_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//a class that organizes and deals with the slots created by doctors and booked by patients
class Slot
{
private:
    int slotID;
    int latestID;   //the id of the most recent appointment that used this slot
    string time;
    bool isAvailable;

public:
    //default constructor
    Slot();

    //parameterized constructor
    Slot(int slotID, int latestID, string time, bool isAvailable);

    //destructor
    ~Slot();

    //setters
    void setSlotID(int slotID);
    void setLatestID(int latestID);
    void setTime(const string& time);
    void setIsAvailable(bool isAvailable);

    //getters
    int  getSlotID() const;
    int  getLatestID() const;
    string getTime() const;
    bool getIsAvailable() const;

    //a function that loads the slot's details from a file
    void loadFromFile(ifstream& in);

    //a function that saves the slot's details to a file
    void saveToFile(ofstream& out) const;
};

#endif
