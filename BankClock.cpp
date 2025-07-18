#include "BankClock.h"

BankClock::BankClock() : observerCount(0) {}

void BankClock::registerObserver(MonthlyObserver* obs) {
    if (observerCount < 100) {
        observers[observerCount++] = obs;
    }
}

void BankClock::notifyAll() {
    for (int i = 0; i < observerCount; ++i) {
        if (observers[i]) observers[i]->onMonthPassed();
    }
} 