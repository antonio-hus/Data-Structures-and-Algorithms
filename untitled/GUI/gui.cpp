#include "gui.h"

#include <utility>
#include "ui_GUI.h"


GUI::GUI(Controller controller, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI) {

    this->controller = std::move(controller);
    ui->setupUi(this);

    connect(ui->allBox, &QCheckBox::clicked, [&]{
       if(ui->allBox->isChecked()) {
           ui->paidBox->setChecked(false);
           ui->unpaidBox->setChecked(false);
           populateList();
       }
       else ui->listWidget->clear();
    });

    connect(ui->paidBox, &QCheckBox::clicked, [&]{
        if(ui->paidBox->isChecked()) {
            ui->allBox->setChecked(false);
            ui->unpaidBox->setChecked(false);
            populateListPaid();
        }
        else ui->listWidget->clear();
    });

    connect(ui->unpaidBox, &QCheckBox::clicked, [&]{
        if(ui->unpaidBox->isChecked()) {
            ui->paidBox->setChecked(false);
            ui->allBox->setChecked(false);
            populateListUnPaid();
        }
        else ui->listWidget->clear();
    });

    connect(ui->getTotalButton, &QPushButton::clicked, [&]{
       std::string company = ui->companySearch->text().toStdString();
       int sum = this->controller.getBillsByCompany(company);
       if(sum == 0){
           QMessageBox::warning(this, "Error - Not Found", "No bills found for the given company");
       }
       else ui->totalSumLabel->setText(QString::fromStdString(to_string(sum)));
    });
}

GUI::~GUI() {
    delete ui;
}

void GUI::populateList() {
    ui->listWidget->clear();
    for(auto& bill:this->controller.billsByCompany()){
        auto* item = new QListWidgetItem(QString::fromStdString(bill.getCompanyName() + " " + to_string(bill.getSum())));
        if(bill.getPaymentStatus() == false) item->setBackground(QBrush(Qt::red));
        ui->listWidget->addItem(item);
    }
}

void GUI::populateListPaid() {
    ui->listWidget->clear();
    for(auto& bill:this->controller.billsPaid()){
        auto* item = new QListWidgetItem(QString::fromStdString(bill.getCompanyName() + " " + to_string(bill.getSum())));
        ui->listWidget->addItem(item);
    }
}

void GUI::populateListUnPaid() {
    ui->listWidget->clear();
    for(auto& bill:this->controller.billsUnPaid()){
        auto* item = new QListWidgetItem(QString::fromStdString(bill.getCompanyName() + " " + to_string(bill.getSum())));
        item->setBackground(QBrush(Qt::red));
        ui->listWidget->addItem(item);
    }
}