/* Exceptions.cpp

   Author: Eric Van Wyk
   Date: Oct 20, 2009.
*/

#include "Exceptions.h"

#include <string>

using namespace std ;

InvalidData::InvalidData(string _msg) {
    msg = _msg ;
}

InvalidData::~InvalidData() {
}

string InvalidData::get_msg() {
    return msg ;
}
