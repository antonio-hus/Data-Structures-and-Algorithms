#include "Bill.h"

#include <utility>

Bill::Bill(std::string company, std::string serialNumber, int sum, bool isPaid) {
    this->company=std::move(company);
    this->serialNumber=std::move(serialNumber);
    this->sum=sum;
    this->isPaid=isPaid;
}

std::string Bill::getCompanyName() {
    return this->company;
}

std::string Bill::getSerialNumber() {
    return this->serialNumber;
}

int Bill::getSum() {
    return this->sum;
}

int Bill::getPaymentStatus() {
    return this->isPaid;
}