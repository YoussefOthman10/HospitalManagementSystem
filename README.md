# 🏥 Hospital Management System

A console-based **Hospital Management System** built using **C++** and core **Object-Oriented Programming (OOP)** concepts.

This project simulates a real hospital workflow with separate interfaces for **Admins**, **Doctors**, and **Patients**, allowing appointment booking and management with persistent file storage.

---

# ✨ Features

## 👨‍💼 Admin Features
- ➕ Add doctors
- ❌ Remove doctors
- ➕ Add patients
- ❌ Remove patients
- 📋 View all doctors
- 📋 View all patients

---

## 👨‍⚕️ Doctor Features
- ➕ Add appointment slots
- ❌ Remove slots
- 👀 View slot availability
- ✏️ Update personal details

---

## 🧑‍🦱 Patient Features
- 🔍 Search doctors by specialty
- 📅 View available slots
- ✅ Book appointments
- ❌ Cancel appointments
- 📋 View personal appointments
- ✏️ Update personal details

---

# 🧠 OOP Concepts Used

| Concept | How It Was Used |
|---|---|
| 🔒 Encapsulation | Private/protected members with getters & setters |
| 🧬 Inheritance | `Doctor`, `Patient`, and `Admin` inherit from `User` |
| 🎭 Polymorphism | Virtual functions like `displayInfo()` |
| 🧱 Abstraction | Pure virtual methods in `User` |
| 🏗️ Constructor Overloading | Multiple constructors in classes |
| 💾 File Handling | Persistent storage using text files |
| ⚠️ Exception Handling | `try-catch` and `throw` statements |
| 🧹 Dynamic Memory | Arrays allocated using `new[]` and `delete[]` |

---

# 🏗️ Class Overview

## 👤 User (Abstract Base Class)

The base class for all users in the system.

### Stores:
- ID
- Username
- Password

### Provides:
- Authentication
- File handling
- Virtual methods for polymorphism

---

## 👨‍💼 Admin

Derived from `User`.

### Responsibilities:
- Managing doctors
- Managing patients
- Viewing records

---

## 👨‍⚕️ Doctor

Derived from `User`.

### Additional Data:
- Specialization
- Appointment slots
- Slot availability

### Responsibilities:
- Managing slots
- Updating details
- Viewing appointments

---

## 🧑‍🦱 Patient

Derived from `User`.

### Additional Data:
- Disease/complaint
- Age

### Responsibilities:
- Searching doctors
- Booking appointments
- Cancelling appointments

---

## 📅 Appointment

Represents a booked appointment between a doctor and a patient.

### Stores:
- Appointment ID
- Doctor ID
- Patient ID
- Slot index

---

# 💾 File Persistence

The system automatically saves and loads data using text files.

| File | Purpose |
|---|---|
| `doctors.txt` | Stores doctor records |
| `patients.txt` | Stores patient records |
| `appointments.txt` | Stores appointment records |

### ✅ Data is:
- Loaded automatically at startup
- Saved automatically before exit

---

# 🔐 Authentication System

## 👨‍💼 Admin Login

```text
Username: admin
Password: admin123
```

---

## 👨‍⚕️ Doctor Login
Doctors login using:
- Doctor ID
- Password

---

## 🧑‍🦱 Patient Login
Patients login using:
- Patient ID
- Password

---

# 🚀 How To Run

## 💻 Using Visual Studio

1. Open the `.sln` file
2. Build the project
3. Run using:

```bash
Ctrl + F5
```

---

## ⚙️ Using g++

```bash
g++ main.cpp User.cpp Admin.cpp Doctor.cpp Patient.cpp Appointment.cpp -o hospital
./hospital
```

---

# 🔄 Example Workflow

## 👨‍💼 Admin
1. Login as admin
2. Add doctors and patients

## 👨‍⚕️ Doctor
1. Login using doctor ID
2. Add appointment slots

## 🧑‍🦱 Patient
1. Login using patient ID
2. Search doctors by specialty
3. Book an available appointment

---

# 🌟 Technical Highlights

- ✅ Uses OOP principles extensively
- ✅ Uses polymorphism and abstraction
- ✅ Prevents double-booking slots
- ✅ Automatically frees slots after cancellation
- ✅ Handles invalid input safely
- ✅ Persistent file storage
- ✅ Modular and maintainable code design

---

# 📊 Sample Data Included

The repository already contains sample:
- Doctors
- Patients
- Appointments

for easy testing and demonstration.

---

# 🔮 Future Improvements

Possible future enhancements:
- 🖥️ GUI/Desktop Interface
- 🗄️ Database Integration
- 📆 Appointment scheduling by date
- 🔐 Password encryption
- 📱 Mobile or Web version
- 📊 Admin dashboards
- 💳 Billing system

---

# 🛠️ Technologies Used

- 💻 C++
- 🧠 Object-Oriented Programming
- 💾 File Handling
- ⚙️ Dynamic Memory Allocation
- 🪟 Visual Studio

---

# 👨‍💻 Authors

| Name | ID |
|---|---|
| Abdelrahman Nader | 25-105217 |
| Yassin Tamer | 25-103804 |
| Youssef Mohamed | 25-101800 |
| Seif El Sayed | 25-103665 |
| Abdelrahman Shady | 25-100322 |

🔗 GitHub Profile:  
https://github.com/YoussefOthman10

📂 Project Repository:  
https://github.com/YoussefOthman10/HospitalManagementSystem
