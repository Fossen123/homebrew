#pragma once
#include <QObject>
#include <iostream>

class ScriptedClass : public QObject{
    Q_OBJECT
public slots:
    void method(){
        std::cout << "METHOD CALLED BY THE SCRIPT!" << std::endl;
    }
};
