#ifndef MONTHLYOBSERVER_H
#define MONTHLYOBSERVER_H

class MonthlyObserver {
public:
    virtual void onMonthPassed() = 0;
    virtual ~MonthlyObserver() {}
};

#endif // MONTHLYOBSERVER_H 