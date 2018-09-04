#include "Date.h"
#include "Debug.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std ;

bool is_valid_date (int y, int m, int d) ;

Date::Date() {
    if (DEBUG)
        cout << "... calling default constructor for Date..." << endl ;
    year = 1900; month = 1; day = 1;
}

Date::Date(int y, int m, int d) {
    if (DEBUG)
        cout << "... calling parameterize constructor for Date..." << endl ;

    //assert ( y >= 1900 )
    //assert ( 0 <= m && m <= 12 )
    //assert ( 0 <= d && d <= 31 )

    year = y; month = m; day = d;
}

Date::~Date() {
    if (DEBUG)
        cout << "... calling destructor for Date \""
             << show() << "\" ..." << endl ;
}

Date Date::copy() const {
  Date myDateCopy(year,month,day);
  return myDateCopy;
}

bool Date::equals(const Date &d) const {
    assert ( d.year >= 1900 )
    assert ( 0 <= d.month && d.month <= 12 )
    assert ( 0 <= d.day && d.day <= 31 )

    return year == d.year && month == d.month &&
           day == d.day ;
}

string Date::show() const {
    ostringstream s ;

    switch (month) {
    case  1 : s << "January"  ; break;
    case  2 : s << "February" ; break;
    case  3 : s << "March"    ; break;
    case  4 : s << "April"    ; break;
    case  5 : s << "May"      ; break;
    case  6 : s << "June"     ; break;
    case  7 : s << "July"     ; break;
    case  8 : s << "August"   ; break;
    case  9 : s << "September"; break;
    case 10 : s << "October"  ; break;
    case 11 : s << "November" ; break;
    case 12 : s << "December" ; break;
    default : s << "ERROR: invalid month" ;
    }

    s << " " << day << ", " << year ;

    return s.str() ;
}




bool is_valid_date (int y, int m, int d) {
    int month_length[] = { 0,
                           31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31 } ;

    if ( y >= 1900 &&
         m >= 1 &&
         m <= 12 &&
         d >= 1 &&
         d <= month_length[m] ) {
        return true ;
    }
    else{
        return false ;
    }
}

// assert (is_valid_date (d.year, d.month, d.day))





void Date::day_inc(int n) {
    int month_length[] = { 31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31 } ;

    assert (n >= 0) ;

    if (n + day > month_length[month]) {
        ++ month ;
        day = 1 ;
        n = n - (month_length[month] - day) ;
    }

    while (n > month_length[month]) {
        ++ month ;
        n = n - month_length[month] ;
    }
    day = day + n ;

    assert (is_valid_date(year, month, day) ) ;
}



// Is this date "before" the parameter Date d ?
bool Date::before(const Date &d) const {

    if ( ! is_valid_date(d.year, d.month, d.day) )
        throw InvalidData ("Invalid Date passed to Date::before.") ;

    if (year < d.year)
        return true ;
    else
    if (year > d.year)
        return false ;
    else
        if (month < d.month)
            return true ;
        else
        if (month > d.month)
            return false ;
        else
            return day < d.day ;
}



// Factories for Date

Date mkDate(int y, int m, int d) {
    if (DEBUG)
        cout << "... calling mkDate to create Date ..." << endl ;

    if ( ! is_valid_date(y, m, d) )
        throw InvalidData ("Invalid Date passed to Date::before.") ;

    Date date(y,m,d) ;

    return  date ;
}

Date * mkDate_ptr(int y, int m, int d) {
    if (DEBUG)
        cout << "... calling mkDate to create Date ..." << endl ;

    if ( ! is_valid_date(y, m, d) )
        throw InvalidData ("Invalid Date passed to Date::before.") ;

    Date *date = new Date (y,m,d) ;

    return  date ;
}
