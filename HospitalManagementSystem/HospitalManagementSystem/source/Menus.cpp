#include "Menus.h"
#include <iostream>
#include <fstream>
using namespace std;

//a function that clears invalid input state and removes leftover characters from input buffer
void clearInput() 
{
    cin.clear();
    cin.ignore(1000, '\n');
}

//a function that loads the appointments details from the appointments.txt file
void loadAppointments(Appointment* appts, int& count, int& nextId)
{
    ifstream in("data/appointments.txt");
    if (!in.is_open())
        return;
    in >> count >> nextId;
    for (int i = 0; i < count; i++)
        appts[i].loadFromFile(in);
    in.close();
}

//a function that saves the appointments details to the appointments.txt file
void saveAppointments(Appointment* appts, int count, int nextId)
{
    ofstream out("data/appointments.txt");
    if (!out.is_open())
    {
        cout << "Warning: could not open appointments.txt for writing.\n";
        return;
    }
    out << count  << "\n"
        << nextId << "\n";
    for (int i = 0; i < count; i++)
        appts[i].saveToFile(out);
    out.close();
    cout << "Appointments saved.\n";
}

//a function that computes the next safe slot id from all of the loaded doctors
int computeNextSlotId(Admin& admin)
{
    int maxId = 0;
    Doctor* docs = admin.getDoctors();
    for (int i = 0; i < admin.getDoctorCount(); i++)
    {
        Slot* slots = docs[i].getSlots();
        for (int j = 0; j < docs[i].getSlotCount(); j++)
        {
            if (slots[j].getSlotID() > maxId)
                maxId = slots[j].getSlotID();
        }
    }
    return maxId + 1;
}

// ================================================================
//  SPECIALTY SEARCH + GUIDED BOOKING
// ================================================================
void searchAndBook(Admin& admin, Patient* patient,
                   Appointment* appts, int& apptCount, int& nextApptId) {

    if (apptCount >= MAX_APPOINTMENTS) {
        cout << "Error: maximum appointments reached.\n";
        return;
    }

    string specialty;
    cout << "Enter specialty to search (e.g. Cardiology): ";
    cin.ignore(1000, '\n');
    getline(cin, specialty);

    cout << "\n--- Doctors with specialty: " << specialty << " ---\n";
    bool    anyFound = false;
    Doctor* docs     = admin.getDoctors();
    int     dc       = admin.getDoctorCount();
    for (int i = 0; i < dc; i++) {
        if (docs[i].getSpecialization() == specialty) {
            cout << "  ID: " << docs[i].getID()
                 << "  Name: " << docs[i].getName()
                 << " (" << docs[i].getUsername() << ")"
                 << (docs[i].hasAvailableSlots() ? "  [slots available]"
                                                 : "  [no slots]") << "\n";
            anyFound = true;
        }
    }
    if (!anyFound) { cout << "No doctors found with that specialty.\n"; return; }

    int docId;
    cout << "Enter doctor ID: ";
    cin >> docId;
    Doctor* doc = admin.findDoctorByID(docId);
    if (!doc || doc->getSpecialization() != specialty) {
        cout << "Error: doctor not found or wrong specialty.\n";
        return;
    }

    doc->displayAvailableSlots();
    if (!doc->hasAvailableSlots()) { cout << "No available slots.\n"; return; }

    int slotId;
    cout << "Enter Slot ID to book: ";
    cin >> slotId;

    try {
        Slot* s = doc->findSlotByID(slotId);
        if (!s)                   throw "Slot ID not found.";
        if (!s->getIsAvailable()) throw "Slot is already booked.";

        bool ok = patient->makeAppointment(*doc, *s);
        if (!ok) throw "Booking failed.";

        s->setLatestID(nextApptId);
        appts[apptCount] = Appointment(nextApptId, docId,
                                       patient->getID(), slotId, "");
        patient->setCurrentAppointment(&appts[apptCount]);

        cout << "Appointment booked! ID = " << nextApptId << "\n";
        nextApptId++;
        apptCount++;
    }
    catch (const char* msg) 
    {
        cout << "Error: " << msg << "\n"; 
    }
}

//ADMIN MENU
void adminMenu(Admin& admin, Appointment* appts,
               int& apptCount, int& nextSlotId) {

    int  choice;
    bool inMenu = true;

    while (inMenu) 
    {
        cout << "\n====== Admin Menu ======\n";
        cout << "1. Add Doctor\n";
        cout << "2. Remove Doctor\n";
        cout << "3. Add Patient\n";
        cout << "4. Remove Patient\n";
        cout << "5. View All Doctors\n";
        cout << "6. View All Patients\n";
        cout << "7. View My Details\n";
        cout << "8. Update My Details\n";
        cout << "9. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (cin.fail()) 
        { 
            clearInput(); cout << "Invalid input.\n"; continue;
        }

        try 
        {
            switch (choice) 
            {

            case 1: //add doctor
            {
                string uname, pass, spec, univ, gender, name;
                int    age;
                cout << "Name          : "; cin.ignore(); getline(cin, name);
                cout << "Username      : "; getline(cin, uname);
                cout << "Password      : "; getline(cin, pass);
                cout << "Age           : "; cin >> age;
                cout << "Specialization: "; cin.ignore(); getline(cin, spec);
                cout << "University    : "; getline(cin, univ);
                cout << "Gender        : "; getline(cin, gender);

                int newId = admin.getNextDoctorId();
                Slot emptySlots[12];
                Doctor d(newId, uname, pass, age, spec, univ, emptySlots, gender, name);
                admin.addDoctor(d);
                admin.setNextDoctorId(newId + 1);
                cout << "Doctor added. ID = " << newId << "\n";
                break;
            }

            case 2: //remove doctor
            {
                int id;
                cout << "Doctor ID to remove: "; cin >> id;
                for (int i = 0; i < apptCount; i++)
                {
                    if (appts[i].getDoctorId() == id) 
                    {
                        for (int j = i; j < apptCount - 1; j++)
                            appts[j] = appts[j + 1];
                        apptCount--; i--;
                    }
                }
                admin.removeDoctor(id);
                cout << "Doctor removed.\n";
                break;
            }

            case 3: //add patient
            {
                string uname, pass, gender, blood, disease;
                int    age, contact;
                cout << "Username   : "; cin.ignore(); getline(cin, uname);
                cout << "Password   : "; getline(cin, pass);
                cout << "Age        : "; cin >> age;
                cout << "Gender     : "; cin.ignore(); getline(cin, gender);
                cout << "Blood type : "; getline(cin, blood);
                cout << "Disease    : "; getline(cin, disease);
                cout << "Contact #  : "; cin >> contact;

                int newId = admin.getNextPatientId();
                Patient p(newId, uname, pass, age, gender, blood, disease, contact, nullptr);
                admin.addPatient(p);
                admin.setNextPatientId(newId + 1);
                cout << "Patient added. ID = " << newId << "\n";
                break;
            }

            case 4: //remove patient
            {
                int id;
                cout << "Patient ID to remove: "; cin >> id;
                for (int i = 0; i < apptCount; i++) 
                {
                    if (appts[i].getPatientId() == id) 
                    {
                        Doctor* doc = admin.findDoctorByID(appts[i].getDoctorId());
                        if (doc) 
                            doc->freeSlotByID(appts[i].getSlotId());
                        for (int j = i; j < apptCount - 1; j++)
                            appts[j] = appts[j + 1];
                        apptCount--; i--;
                    }
                }
                admin.removePatient(id);
                cout << "Patient removed.\n";
                break;
            }

            case 5: //view all doctors
            {
                if (admin.getDoctorCount() == 0) 
                {
                    cout << "No doctors registered.\n";
                } 
                else 
                {
                    cout << "\n--- All Doctors ---\n";
                    Doctor* docs = admin.getDoctors();
                    for (int i = 0; i < admin.getDoctorCount(); i++)
                        docs[i].getDetails();
                }
                break;
            }

            case 6: //view all patients
            {
                if (admin.getPatientCount() == 0) 
                {
                    cout << "No patients registered.\n";
                } else 
                {
                    cout << "\n--- All Patients ---\n";
                    Patient* pats = admin.getPatients();
                    for (int i = 0; i < admin.getPatientCount(); i++)
                        pats[i].getDetails();
                }
                break;
            }

            case 7:  admin.getDetails(); //get admin and some system details
                break;
            case 8:  admin.updateDetails(); //update admin details
                break;
            case 9:  inMenu = false; //exit
                break;
            default: cout << "Invalid choice.\n";
            }
        }
        catch (const char* msg)
        {
            cout << "Error: " << msg << "\n";
        }
    }
}

//  DOCTOR MENU
void doctorMenu(Admin& admin, Doctor* doctor,
                Appointment* appts, int& apptCount, int& nextSlotId) 
{
    int  choice;
    bool inMenu = true;
    while (inMenu) 
    {
        cout << "\n====== Doctor Menu (" << doctor->getUsername() << ") ======\n";
        cout << "1. View Details\n";
        cout << "2. Update Details\n";
        cout << "3. Add Slot\n";
        cout << "4. Remove Slot\n";
        cout << "5. View Available Slots\n";
        cout << "6. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (cin.fail()) 
        {
            clearInput(); cout << "Invalid input.\n";
            continue;
        }
        try 
        {
            switch (choice)
            {

            case 1:  doctor->getDetails(); //get the doctor's details
                break;
            case 2:  doctor->updateDetails(); //update the doctor's details
                break;

            case 3: //add slot
            {
                string slotTime;
                cout << "Enter slot time (ex. 09:00 AM): ";
                cin.ignore();
                getline(cin, slotTime);

                Slot newSlot(nextSlotId, -1, slotTime, true);
                int result = doctor->addSlot(newSlot);
                if (result == -1) 
                    throw "Cannot add slot: 12-slot maximum reached.";
                cout << "Slot added. Slot ID = " << result << "\n";
                nextSlotId++;
                break;
            }

            case 4: //remove slot
            {
                doctor->getDetails();
                int slotId;
                cout << "Enter Slot ID to remove: "; 
                cin >> slotId;
                if (cin.fail()) 
                {
                    clearInput(); throw "Invalid input.";
                }

                for (int i = 0; i < apptCount; i++)
                {
                    if (appts[i].getDoctorId() == doctor->getID() &&
                        appts[i].getSlotId()   == slotId)
                    {
                        for (int j = i; j < apptCount - 1; j++)
                            appts[j] = appts[j + 1];
                        apptCount--; i--;
                    }
                }
                doctor->removeSlot(slotId);
                cout << "Slot removed.\n";
                break;
            }

            case 5:  doctor->displayAvailableSlots(); //display the slots
                break;
            case 6:  inMenu = false; //exit                  
                break;
            default: cout << "Invalid choice.\n";
            }
        }
        catch (const char* msg)
        {
            cout << "Error: " << msg << "\n";
        }
    }
}

//PATIENT MENU
void patientMenu(Admin& admin, Patient* patient,
                 Appointment* appts, int& apptCount, int& nextApptId) 
{
    int  choice;
    bool inMenu = true;
    while (inMenu) 
    {
        cout << "\n====== Patient Menu (" << patient->getUsername() << ") ======\n";
        cout << "1. View Details\n";
        cout << "2. Update Details\n";
        cout << "3. Search Doctors by Specialty & Book\n";
        cout << "4. View Available Slots of a Doctor\n";
        cout << "5. Make Appointment\n";
        cout << "6. Cancel Appointment\n";
        cout << "7. View My Appointments\n";
        cout << "8. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (cin.fail())
        {
            clearInput(); cout << "Invalid input.\n"; 
            continue;
        }
        try
        {
            switch (choice)
            {

            case 1:  patient->getDetails(); //get patient details  
                break;
            case 2:  patient->updateDetails(); //update patient details 
                break;
            case 3: //SEARCH FOR A DOCTOR BY SPECIALITY
                searchAndBook(admin, patient, appts, apptCount, nextApptId);
                break;
            case 4: //view available slots
            {
                int docId;
                cout << "Enter doctor ID: "; 
                cin >> docId;
                if (cin.fail())
                {
                    clearInput();
                    throw "Invalid input.";
                }
                Doctor* doc = admin.findDoctorByID(docId);
                if (!doc) 
                    throw "Doctor not found.";
                doc->displayAvailableSlots();
                break;
            }

            case 5: //make an appointment
            {
                if (apptCount >= MAX_APPOINTMENTS)
                    throw "Maximum appointments reached.";
                int docId, slotId;
                cout << "Enter doctor ID : "; cin >> docId;
                if (cin.fail())
                {
                    clearInput(); 
                    throw "Invalid input.";
                }
                Doctor* doc = admin.findDoctorByID(docId);
                if (!doc) 
                    throw "Doctor not found.";
                doc->displayAvailableSlots();
                cout << "Enter Slot ID   : "; cin >> slotId;
                if (cin.fail())
                {
                    clearInput(); 
                    throw "Invalid input.";
                }

                Slot* s = doc->findSlotByID(slotId);
                if (!s)                   
                    throw "Slot ID not found.";
                if (!s->getIsAvailable()) 
                    throw "That slot is not available.";

                bool ok = patient->makeAppointment(*doc, *s);
                if (!ok) 
                    throw "Booking failed.";

                s->setLatestID(nextApptId);
                appts[apptCount] = Appointment(nextApptId, docId,
                                               patient->getID(), slotId, "");
                patient->setCurrentAppointment(&appts[apptCount]);

                cout << "Appointment booked! ID = " << nextApptId << "\n";
                nextApptId++;
                apptCount++;
                break;
            }

            case 6: //cancel appointment
            {
                int apptId;
                cout << "Enter appointment ID to cancel: "; 
                cin >> apptId;
                if (cin.fail()) 
                {
                    clearInput();
                    throw "Invalid input.";
                }

                int index = -1;
                for (int i = 0; i < apptCount; i++)
                {
                    if (appts[i].getId()        == apptId &&
                        appts[i].getPatientId() == patient->getID())
                    {
                        index = i;
                        break;
                    }
                }
                if (index == -1) 
                    throw "Appointment not found (or not your appointment).";

                Doctor* doc = admin.findDoctorByID(appts[index].getDoctorId());
                if (doc) 
                    doc->freeSlotByID(appts[index].getSlotId());

                patient->cancelAppointment(apptId);

                for (int i = index; i < apptCount - 1; i++)
                    appts[i] = appts[i + 1];
                apptCount--;
                cout << "Appointment cancelled.\n";
                break;
            }

            case 7: //view appointments
            {
                patient->viewAppointments();
                bool found = false;
                cout << "\n--- Full Appointment History ---\n";
                for (int i = 0; i < apptCount; i++) 
                {
                    if (appts[i].getPatientId() == patient->getID()) 
                    {
                        appts[i].displayAppointmentInfo();
                        Doctor* doc = admin.findDoctorByID(appts[i].getDoctorId());
                        if (doc) 
                        {
                            Slot* s = doc->findSlotByID(appts[i].getSlotId());
                            cout << "Doctor : " << doc->getName()
                                 << " (" << doc->getSpecialization() << ")\n";
                            if (s) 
                                cout << "Time   : " << s->getTime() << "\n";
                        }
                        found = true;
                    }
                }
                if (!found) 
                    cout << "No appointment history found.\n";
                break;
            }
            case 8:  inMenu = false; 
                break;
            default: cout << "Invalid choice.\n";
            }
        }
        catch (const char* msg)
        {
            cout << "Error: " << msg << "\n";
        }
    }
}
