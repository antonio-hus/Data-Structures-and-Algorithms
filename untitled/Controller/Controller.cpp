#include "Controller.h"

vector<string> Controller::tokenize(const string &str, char delimiter) {
    vector <string> result;
    stringstream ss{str};
    string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

Controller::Controller() {
    this->readBills();
}

void Controller::readBills() {
    ifstream in{"db.txt"};

    string line;
    while(getline(in, line)){
        vector<string> tokens = Controller::tokenize(line, ';');
        string company = tokens[0];
        string serial = tokens[1];
        int sum = stoi(tokens[2]);

        string payment = tokens[3];
        bool isPaid= false;
        if(payment=="true") isPaid = true;

        this->bills.emplace_back(company, serial, sum, isPaid);
    }
}

vector<Bill> Controller::billsByCompany() {
    for(int i=0; i<this->bills.size()-1; ++i){
        for(int j=i; j<this->bills.size(); ++j){
            if(this->bills[i].getCompanyName() > this->bills[i].getCompanyName())
                swap(bills[i], bills[j]);
        }
    }
    return this->bills;
}

vector<Bill> Controller::billsPaid() {
    vector<Bill> paidBills;
    for(auto& bill:this->billsByCompany()){
        if(bill.getPaymentStatus() == true)
            paidBills.push_back(bill);
    }
    return paidBills;
}

vector<Bill> Controller::billsUnPaid() {
    vector<Bill> unpaidBills;
    for(auto& bill:this->billsByCompany()){
        if(bill.getPaymentStatus() == false)
            unpaidBills.push_back(bill);
    }
    return unpaidBills;
}

int Controller::getBillsByCompany(const std::string& company) {
    int sum = 0;
    for(auto& bill:this->bills){
        if(bill.getCompanyName() == company && bill.getPaymentStatus() == false)
            sum += bill.getSum();
    }
    return sum;
}