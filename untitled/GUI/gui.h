//
// Created by anton on 24/05/2024.
//

#ifndef UNTITLED_GUI_H
#define UNTITLED_GUI_H

#include <QWidget>
#include <QMessageBox>
#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Controller controller, QWidget *parent = nullptr);
    ~GUI() override;

    void populateList();
    void populateListPaid();
    void populateListUnPaid();

private:
    Ui::GUI *ui;
    Controller controller;
};


#endif //UNTITLED_GUI_H
