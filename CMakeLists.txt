cmake_minimum_required(VERSION 3.10)

project(AddressBook VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(contact
    src/main.cpp
    src/Contact.cpp
    src/AddressBook.cpp
    src/GUI.cpp
)

target_include_directories(contact PRIVATE include)

configure_file(contacts.txt contacts.txt COPYONLY)