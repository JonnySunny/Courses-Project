#ifndef DATE_H
#define DATE_H

#include "Exceptions.h"

#include <string>

class Date {
public:
    Date() ;
    Date(int, int, int) ;
    ~Date() ;



    std::string show() const ;

    bool equals(const Date &) const ;

    bool before(const Date &) const ;

    void day_inc(int) ;

    Date copy() const;

private:
    int year, month, day ;
};


















Date mkDate(int y, int m, int d) ;
Date * mkDate_ptr(int y, int m, int d) ;



#endif
