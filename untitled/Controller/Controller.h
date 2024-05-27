#ifndef UNTITLED_CONTROLLER_H
#define UNTITLED_CONTROLLER_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include "../Domain/Bill.h"
using namespace std;

class Controller {
private:
    vector<Bill> bills;
    vector<string> tokenize(const string &str, char delimiter);
public:

    Controller();
    void readBills();
    vector<Bill> billsByCompany();
    vector<Bill> billsPaid();
    vector<Bill> billsUnPaid();
    int getBillsByCompany(const string& company);

};


#endif //UNTITLED_CONTROLLER_H
