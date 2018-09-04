#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

/* Author: Eric Van Wyk
   Date created: October 20, 2009.
 */

#include <string>

class InvalidData {
public:
    InvalidData (std::string) ;
    ~InvalidData () ;

    std::string get_msg() ;

private:
    std::string msg ;
} ;

#endif /* EXCEPTIONS_H */
