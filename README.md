# AddressBook (C++)

Simple console address book written in C++.
Allows managing contacts (name + phone) with file persistence.

## Features

* Add or update contacts
* Find contacts by name
* Delete contacts
* Delete all contacts
* Save contacts to file
* Table view of contacts

## C++ & STL Used

- **C++17**
- OOP: classes (`Contact`, `AddressBook`, `GUI`)
- `std::vector`, `std::string`
- Algorithms:
  - `std::find_if`
  - `std::remove_if`
  - `std::sort`
- File I/O: `std::ifstream`, `std::ofstream`
- Formatting: `std::setw`, `std::left`
- Lambda expressions
- Clean CLI logic (`switch`, `loop`)

## Project structure

```
AddressBook
│
├── include
│   ├── AddressBook.hpp
│   ├── Contact.hpp
│   └── GUI.hpp
│
├── src
│   ├── AddressBook.cpp
│   ├── Contact.cpp
│   ├── GUI.cpp
│   └── main.cpp
│
├── contacts.txt
├── CMakeLists.txt
└── README.md
```

## Build

```
mkdir build
cd build
cmake ..
make
```

## Run

```
./contact
```

## Requirements

* C++17
* CMake 3.16+

## About contacts.txt

- `contacts.txt` in the root folder: template / initial data  
- `build/contacts.txt`: used by the program during runtime

