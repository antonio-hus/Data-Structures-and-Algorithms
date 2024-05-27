#ifndef UNTITLED_BILL_H
#define UNTITLED_BILL_H

#include <string>

class Bill {
private:
    std::string company;
    std::string serialNumber;
    int sum;
    bool isPaid;

public:
    Bill(std::string company, std::string serialNumber, int sum, bool isPaid);

    std::string getCompanyName();
    std::string getSerialNumber();
    int getSum();
    int getPaymentStatus();

};


#endif
