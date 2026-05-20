#include <iostream>
#include <string>
#include "Menus.h"
using namespace std;

int main() {

    //the admin object is constructed at the beginning because it owns the dynamically allocated arrays of doctors and patients
    Admin admin(0, "admin", "admin123");

    //appointments are managed here
    Appointment* appts      = new Appointment[MAX_APPOINTMENTS]; //5
    int          apptCount  = 0;
    int          nextApptId = 1;

    //loading saved data from files
    try 
    {
        admin.loadDoctors("doctors.txt");
        admin.loadPatients("patients.txt");
        loadAppointments(appts, apptCount, nextApptId);
    }
    catch (...) 
    {
        cout << "Note: could not load some data — starting fresh.\n";
    }

    //deriving the next slot id from the loaded slots so the ids are never reused
    int nextSlotId = computeNextSlotId(admin);

    //the start of the program
    cout << "========================================\n";
    cout << "     El Mostashfa El Ma3lomateya\n";
    cout << "========================================\n";

    //the main menu
    int  choice;
    bool running = true;
    while (running) 
    {
        cout << "\n====== Main Menu ======\n";
        cout << "1. Admin\n";
        cout << "2. Doctor\n";
        cout << "3. Patient\n";
        cout << "4. Exit\n";
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

            case 1: //admin login
            {
                string uname, pass;
                cout << "Admin username: "; cin >> uname;
                cout << "Admin password: "; cin >> pass;
                if (admin.getUsername() != uname || !admin.checkPassword(pass))
                    cout << "Invalid credentials.\n";
                else 
                {
                    cout << "Admin login successful.\n";
                    adminMenu(admin, appts, apptCount, nextSlotId);
                }
                break;
            }

            case 2: //doctor login
            {
                int    id;
                string pass;
                cout << "Doctor ID : "; cin >> id;
                if (cin.fail()) 
                {
                    clearInput(); cout << "Invalid input.\n";
                    continue;
                }
                cout << "Password  : "; 
                cin >> pass;

                Doctor* doc = admin.findDoctorByID(id);
                if (!doc)
                    cout << "Doctor not found.\n";
                else if (!doc->checkPassword(pass))
                    cout << "Incorrect password.\n";
                else 
                {
                    cout << "Doctor login successful.\n";
                    doctorMenu(admin, doc, appts, apptCount, nextSlotId);
                }
                break;
            }

            case 3: //patient login
            {
                int    id;
                string pass;
                cout << "Patient ID: "; 
                cin >> id;
                if (cin.fail()) 
                {
                    clearInput(); cout << "Invalid input.\n"; 
                    continue;
                }
                cout << "Password  : "; 
                cin >> pass;
                Patient* pat = admin.findPatientByID(id);
                if (!pat)
                    cout << "Patient not found.\n";
                else if (!pat->checkPassword(pass))
                    cout << "Incorrect password.\n";
                else 
                {
                    cout << "Patient login successful.\n";
                    patientMenu(admin, pat, appts, apptCount, nextApptId);
                }
                break;
            }

            case 4: //save and exit
            {
                admin.saveDoctors("doctors.txt");
                admin.savePatients("patients.txt");
                saveAppointments(appts, apptCount, nextApptId);
                cout << "Goodbye!\n";
                running = false;
                break;
            }

            default: cout << "Invalid choice.\n";
            }
        }
        catch (const char* msg) 
        {
            cout << "Error: " << msg << "\n";
        }
    }
    delete[] appts; //needs delete since it is the only member variable declared as a pointer in the appointments class
    return 0;
}
