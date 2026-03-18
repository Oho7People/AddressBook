#pragma once

#include <vector>
#include <iostream>
#include "Contact.hpp"

class AddressBook {
    std::vector<Contact> book_;
    std::string filename_;
    bool is_dirty_ = false;

   public:

    explicit AddressBook(const std::string& file);

    void AddContact(const std::string& name, const std::string& phone);
    void FindName(const std::string& name);
    void Remove(const std::string& name);
    void RemoveAll();

    size_t Size() const;
    void Print();
    bool LoadFromFile(const std::string& filename);
    bool SaveToFile();

    ~AddressBook();
};