#ifndef BANKCLOCK_H
#define BANKCLOCK_H

#include "MonthlyObserver.h"

class BankClock {
private:
    MonthlyObserver* observers[100];
    int observerCount;
public:
    BankClock();
    void registerObserver(MonthlyObserver* obs);
    void notifyAll();
};

#endif // BANKCLOCK_H 