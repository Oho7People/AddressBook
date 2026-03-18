#pragma once

#include <string>

class Contact {
    std::string name_;
    std::string phone_;

    public:
    Contact(const std::string& name, const std::string& phone);

    const std::string& GetName() const;
    const std::string& GetPhone() const;

    void SetPhone(const std::string& new_phone);

    bool operator<(const Contact& other) const;

};