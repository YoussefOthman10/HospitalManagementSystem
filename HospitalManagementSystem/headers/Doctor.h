#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"
#include "Slot.h"

//a derived class that inherits the base class (user)
class Doctor : public User
{
private:
    int age;
    string specialization;
    string university;
    Slot slots[12];       //a fixed array of slot objects
    string gender;
    string name;
    int slotCount;       //a counter that tracks how many of the 12 slots are in use making them unavailable
    static const int MAX_SLOTS = 12;

public:
    //default constructor
    Doctor();

    //parameterized constructor
    Doctor(int id, string user, string pass, int age, string specialization,
           string university, Slot inSlots[12], string gender, string name);
    
    //destructor
    ~Doctor();

    //setters
    void setAge(int age);
    void setSpecialization(const string& specialization);
    void setUniversity(const string& university);
    void setSlots(Slot inSlots[12]);
    void setGender(const string& gender);
    void setName(const string& name);

    //getters
    int  getAge() const;
    string getSpecialization() const;
    string getUniversity() const;
    Slot* getSlots();          //returns a pointer to the first element of the slots array declared as a member variable in the slots class
    string getGender() const;
    string getName() const;
    int getSlotCount() const; //gets the number of slots that are currently in use

    //a function that lets the doctor add a slot
    int  addSlot(Slot slot);

    //a function that lets the doctor remove a slot by the slot's id
    void removeSlot(int id);
    
    //a function that displays the available slots
    void displayAvailableSlots() const;

    //a function that checks whether the doctor has available slots
    bool hasAvailableSlots() const;
    
    //a function that finds a slot by its id
    Slot* findSlotByID(int slotId);
    
    //a function that lets the patient book a slot by its id
    void  bookSlotByID(int slotId);
    
    //a function that makes a slot available again using its id after cancellation
    void  freeSlotByID(int slotId);

    //overriden functions that display and update the doctor's details
    void getDetails() const override;
    void updateDetails() override;

    //overriden functions that load and save the doctor's details from a file
    void loadFromFile(ifstream& in) override;
    void saveToFile(ofstream& out) const override;
};

#endif
