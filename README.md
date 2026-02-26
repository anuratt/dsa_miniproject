# 🏥 Hospital Management System
### DSA Mini Project — Anurat Niraula 3rd Semester Computer Engineering

---

## 📋 Project Overview

A fully functional **Hospital Management System** built with **Qt GUI** and custom **Data Structure** implementations.

The system models a real hospital workflow:
- Patients arrive and are placed in a **triage priority queue**
- The most critical patients are admitted first
- Admitted patients are tracked in a **doubly linked list** registry
- Every doctor action is recorded in a **LIFO stack** audit log

---

## 🗂️ File Structure

```
HospitalManagementSystem/
│
├── main.cpp              
├── CMakeLists.txt        
│
├── patient.h             
│
├── queue.h               
├── queue.cpp            
│
├── patientrecord.h       
├── patientrecord.cpp     
│
├── doctor.h             
├── doctor.cpp            
│
├── hospital.h            
├── hospital.cpp          
│
├── mainwindow.h          
├── mainwindow.cpp        
└── mainwindow.ui         
```

---

## 🧠 Data Structures Used

### 1. 🔵 Priority Queue (Triage System)
**File:** `queue.h / queue.cpp`

A **singly linked list** sorted by patient severity. Implements the hospital triage model where `Critical` patients are always served before `Low` priority patients, regardless of arrival order.

| Severity  | Priority | Colour |
|-----------|----------|--------|
| Critical  | 1 (highest) | 🔴 Red |
| High      | 2 | 🟠 Orange |
| Medium    | 3 | 🟡 Yellow |
| Low       | 4 (lowest) | 🟢 Green |

**Complexity:**
- Enqueue: **O(n)** — finds sorted insertion point
- Dequeue: **O(1)** — removes front node
- Peek: **O(1)**

---

### 2. 🟢 Patient Records (Doubly Linked List)
**File:** `patientrecord.h / patientrecord.cpp`

A **doubly linked list** stores all patient records (admitted + discharged). Bidirectional pointers (`next` / `prev`) allow efficient traversal and deletion without needing to scan back.

**Operations:**
- Insert at head: **O(1)**
- Delete by ID: **O(n)**
- Search by name / doctor: **O(n)**
- Get all patients: **O(n)**

---

### 3. 🟡 Doctor Action Stack (LIFO)
**File:** `doctor.h / doctor.cpp`

Each doctor has their own **stack** that records every action they perform (Admitted / Discharged / Updated). The most recent action is always on top — this models an **audit log with undo capability**.

**Operations:**
- Push (log action): **O(1)**
- Pop: **O(1)**
- Peek (last action): **O(1)**
- View history: **O(n)**

---

## 🖥️ GUI Tabs

| Tab | Description |
|-----|-------------|
| 📊 Dashboard | Live stats: total patients, admitted, discharged, queue size, critical cases |
| 🚑 Triage Queue | Add patients by severity, admit next patient, view priority order |
| 🏥 Patients | Full patient registry, search, discharge, severity colour coding |
| 👨‍⚕️ Doctors | Add/remove doctors, view per-doctor action history (Stack viewer) |

---

## 🚀 How to Build and Run

### Prerequisites
- **Qt 6.x** (or Qt 5.12+) with Qt Widgets module
- **CMake 3.16+**
- **C++17** compatible compiler (GCC 9+, MSVC 2019+, Clang 10+)

### Build Steps

```bash
# 1. Clone / download the project
cd HospitalManagementSystem

# 2. Create a build directory
mkdir build && cd build

# 3. Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Debug

# 4. Build
cmake --build . --parallel

# 5. Run
./HospitalManagementSystem        # Linux / macOS
HospitalManagementSystem.exe      # Windows
```

### Building with Qt Creator (Recommended for Students)
1. Open **Qt Creator**
2. File → Open File or Project → select `CMakeLists.txt`
3. Configure the kit (Qt 6.x MinGW 64-bit or MSVC)
4. Click the green ▶ **Run** button

---

## 📸 Features Demo

On launch, the app loads **sample data** automatically:

**4 Doctors:**
- Dr. Sarah Ahmed — Cardiology
- Dr. Rahul Khan — Neurology
- Dr. Aisha Malik — Orthopedics
- Dr. James Cooper — General Surgery

**5 Admitted Patients** (in doubly linked list)

**4 Patients in Triage Queue** (priority sorted):
1. 🔴 Bilal Akhtar — Chest Pain (Critical)
2. 🟠 Tariq Mehmood — Food Poisoning (High)
3. 🟡 Sana Javed — Knee Pain (Medium)
4. 🟢 Nadia Hussain — Back Pain (Low)

---

## 🎓 DSA Concepts Demonstrated

| Concept | Where Used |
|---------|-----------|
| Singly Linked List | Priority Queue nodes |
| Doubly Linked List | Patient Records registry |
| Stack (LIFO) | Doctor action history |
| Priority Queue | Triage ordering by severity |
| Struct / OOP | Patient, Doctor, Edge data models |
| Enums | Severity levels (type-safe) |

---

## 👨‍💻 Author

**[Anurat Niraula]** — Roll No: [31]
3rd Semester, Computer Engineering
Subject: Data Structures and Algorithms
Academic Year: 2024
