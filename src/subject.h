#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "chess.h"
#include "observer.h"
#include <iostream>


class Subject {
    std::vector<Observer*> observers;
public:
    virtual ~Subject() = 0;
    
    void attach(Observer* os);
    void detach(Observer* os);
    void notifyObservers();
};
#endif