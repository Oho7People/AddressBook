    #include "Contact.hpp"    
    
    Contact::Contact(const std::string& name, const std::string& phone) : name_(name), phone_(phone){
    }

    const std::string& Contact::GetName() const {
        return name_;
    }

    const std::string& Contact::GetPhone() const {
        return phone_;
    }

    void Contact::SetPhone(const std::string& new_phone) {
        phone_ = new_phone;
    }

    bool Contact::operator<(const Contact& other) const {
        return name_ < other.name_;
    }