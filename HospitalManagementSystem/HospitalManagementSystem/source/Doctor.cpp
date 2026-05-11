#include "Doctor.h"

//default constructor
Doctor::Doctor() : User() //calling the base class's (user) default constructor to initialize id, username and password
{
    age = 0;
    specialization = "";
    university = "";
    gender = "";
    name = "";
    slotCount = 0;
    //slots[] are default constructed where all slot ids = -1
}

//parameterized constructor
Doctor::Doctor(int id, string user, string pass, int age,
               string specialization, string university,
               Slot inSlots[12], string gender, string name)
    : User(id, user, pass) //calling the base class (user) parameterized constructor to construct the id, username and password for a doctor
{
    this->age = age;
    this->specialization = specialization;
    this->university = university;
    this->gender = gender;
    this->name = name;
    slotCount = 0;
    for (int i = 0; i < MAX_SLOTS; i++) 
    {
        this->slots[i] = inSlots[i];
        if (inSlots[i].getSlotID() >= 0)
            slotCount++; //increments the slot counter if a slot with an id >= 0 is found
    }
}

//destructor
Doctor::~Doctor()
{

}

//setters
void Doctor::setAge(int age)
{
    this->age = age;
}

void Doctor::setSpecialization(const string& s)
{
    specialization = s;
}

void Doctor::setUniversity(const string& u)
{
    university = u;
}

void Doctor::setSlots(Slot inSlots[12]) 
{
    slotCount = 0;
    for (int i = 0; i < MAX_SLOTS; i++) 
    {
        slots[i] = inSlots[i];
        if (inSlots[i].getSlotID() >= 0)
            slotCount++; //increments the slot counter if a slot with an id >= 0 is found
    }
}

void   Doctor::setGender(const string& g) 
{
    gender = g;
}

void   Doctor::setName(const string& n)
{
    name = n;
}

//getters
int  Doctor::getAge() const
{
    return age;
}

string Doctor::getSpecialization() const
{
    return specialization;
}

string Doctor::getUniversity() const  {
    return university;
}

Slot* Doctor::getSlots()
{
    return slots;
}

string Doctor::getGender() const
{
    return gender;
}

string Doctor::getName() const
{
    return name;
}

int Doctor::getSlotCount() const
{
    return slotCount;
}

//a function that lets the doctor add a slot
int Doctor::addSlot(Slot slot) 
{
    if (slotCount >= MAX_SLOTS)
        return -1; //returns -1 if the array of slots is full
    else
        slots[slotCount] = slot;
        slotCount++; //increments the slot count
        return slot.getSlotID(); //returns the slot id if the slot is added
}

//a function that lets the doctor remove a slot from the slots array by its id
void Doctor::removeSlot(int id) 
{
    int index = -1;
    for (int i = 0; i < slotCount; i++)
    {
        if (slots[i].getSlotID() == id) 
        { 
            index = i; 
            break; 
        }
    }
    if (index == -1) 
        throw "Slot ID not found.";

    for (int i = index; i < slotCount - 1; i++)
        slots[i] = slots[i + 1]; //moves every element after the deleted one one step backward
    slots[slotCount - 1] = Slot(); //clears the empty last position
    slotCount--; //decrements the slot count
}

//a function that displays the available slots of a doctor
void Doctor::displayAvailableSlots() const 
{
    bool found = false;
    cout << "Available slots for Dr. " << (name.empty() ? username : name) << ":\n";
    for (int i = 0; i < slotCount; i++)
    {
        if (slots[i].getIsAvailable())
        {
            cout << "  [Slot ID: " << slots[i].getSlotID() << "]  "
                 << slots[i].getTime() << "\n";
            found = true;
        }
    }
    if (!found) 
        cout << "  No available slots.\n";
}

//a function that checks if a doctor has available slots
bool Doctor::hasAvailableSlots() const
{
    for (int i = 0; i < slotCount; i++)
        if (slots[i].getIsAvailable()) 
            return true;
    return false;
}

//a function that finds the slot by its assigned id
Slot* Doctor::findSlotByID(int slotId) {
    for (int i = 0; i < slotCount; i++)
        if (slots[i].getSlotID() == slotId)
            return &slots[i]; //returns the address of the slot found
    return nullptr;
}

//a function that lets a patient book a slot by its id
void Doctor::bookSlotByID(int slotId)
{
    Slot* s = findSlotByID(slotId);
    if (!s)                  
        throw "Slot ID not found.";
    if (!s->getIsAvailable()) 
        throw "Slot is already booked.";
    s->setIsAvailable(false);
}
//a function that makes a slot available again using its id after cancellation
void Doctor::freeSlotByID(int slotId) {
    Slot* s = findSlotByID(slotId);
    if (!s) 
        return;          // slot may have been removed
    s->setIsAvailable(true);
}

//an overriden function that displays the doctor's details
void Doctor::getDetails() const 
{
    cout << "------------------------------\n";
    cout << "Role          : Doctor\n";
    cout << "ID            : " << id << "\n";
    cout << "Name          : " << name << "\n";
    cout << "Username      : " << username << "\n";
    cout << "Age           : " << age << "\n";
    cout << "Gender        : " << gender << "\n";
    cout << "Specialization: " << specialization << "\n";
    cout << "University    : " << university << "\n";
    cout << "Slots (" << slotCount << "/" << MAX_SLOTS << "):\n";
    for (int i = 0; i < slotCount; i++) 
    {
        cout << "  [ID:" << slots[i].getSlotID() << "] "
             << slots[i].getTime()
             << (slots[i].getIsAvailable() ? "  (Available)" : "  (Booked)") << "\n";
    }
    cout << "------------------------------\n";
}

//an overriden function that lets the doctor update his details
void Doctor::updateDetails()
{
    string input;
    int num;

    cout << "\n--- Update Doctor Details ---\n";

    cout << "Current name: " << name << "\n";
    cout << "New name (Press Enter to keep): ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) 
        name = input;

    cout << "Current username: " << username << "\n";
    cout << "New username (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        username = input;

    cout << "Current specialization: " << specialization << "\n";
    cout << "New specialization (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        specialization = input;

    cout << "Current university: " << university << "\n";
    cout << "New university (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        university = input;

    cout << "Current gender: " << gender << "\n";
    cout << "New gender (Press Enter to keep): ";
    getline(cin, input);
    if (!input.empty()) 
        gender = input;

    cout << "Current age: " << age << "\n";
    cout << "New age (Press 0 to keep): ";
    cin >> num;
    if (num > 0) 
        age = num;

    cout << "New password (Press Enter to keep): ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) 
        password = input;

    cout << "Details updated successfully!\n";
}

//an overriden function that loads the doctor's details from a file
void Doctor::loadFromFile(ifstream& in)
{
    User::loadFromFile(in);          //to load id, username and password
    in >> age;
    in.ignore();
    getline(in, specialization);
    getline(in, university);
    getline(in, gender);
    getline(in, name);
    in >> slotCount;
    for (int i = 0; i < slotCount; i++)
        slots[i].loadFromFile(in);
}

//an overriden function that saves the doctor's details to a file
void Doctor::saveToFile(ofstream& out) const {
    User::saveToFile(out);           //to save id, username and password
    out << age            << "\n"
        << specialization << "\n"
        << university     << "\n"
        << gender         << "\n"
        << name           << "\n"
        << slotCount      << "\n";
    for (int i = 0; i < slotCount; i++)
        slots[i].saveToFile(out);
}
