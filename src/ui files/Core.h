#ifndef MEGA_CALCAPP_CORE_H
#define MEGA_CALCAPP_CORE_H


#include "iostream"
#include "QObject"
#include "QString"
#include "unistd.h"

class Core : public QObject {
Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr) : QObject(parent) {}

signals:

    void send_ans(QString msg);

public slots:

    void recieve_str(QString m) {
        std::string msg = m.toStdString();
        std::cout << msg << std::endl;
        emit send_ans(QString("123"));
    };

};

#endif //MEGA_CALCAPP_CORE_H
