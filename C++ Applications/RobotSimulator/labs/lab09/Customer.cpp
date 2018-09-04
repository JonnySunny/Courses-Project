// Customer.cpp
#include <sstream>
#include <vector>
#include "Customer.h"

using std::ostringstream;
using std::vector;

std::string Customer::statement()
{
  double totalAmount = 0;
  int frequentRenterPoints = 0;
  vector< Rental >::iterator iter = _rentals.begin();
  vector< Rental >::iterator iter_end = _rentals.end();
  ostringstream result;
  result << "Rental Record for " << getName() << "\n";
  for ( ; iter != iter_end; ++iter ) {
    double thisAmount = 0;
    Rental each = *iter;

    thisAmount = amountFor( each );

    // add frequent renter points
    frequentRenterPoints++;
    // add bonus for a two day new release rental
    if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
         && each.getDaysRented() > 1 ) frequentRenterPoints++;

    // show figures for this rental
    result << "\t" << each.getMovie().getTitle() << "\t"
           << thisAmount << "\n";
    totalAmount += thisAmount;
  }
  // add footer lines
  result << "Amount owed is " << totalAmount << "\n";
  result << "You earned " << frequentRenterPoints
         << " frequent renter points";
  return result.str();
}


double Customer::
amountFor( const Rental& aRental ) const
{
  return aRental.getCharge();
}

// double Customer::amountFor( const Rental& aRental ) const
// {
//   double result = 0;
//   switch ( aRental.getMovie().getPriceCode() ) {
//     case Movie::REGULAR:
//       result += 2;
//       if ( aRental.getDaysRented() > 2 )
//         result += ( aRental.getDaysRented() - 2 ) * 1.5;
//       break;
//     case Movie::NEW_RELEASE:
//       result += aRental.getDaysRented() * 3;
//       break;
//     case Movie::CHILDRENS:
//       result += 1.5;
//       if ( aRental.getDaysRented() > 3 )
//         result += ( aRental.getDaysRented() - 3 ) * 1.5;
//       break;
//   }
//   return result;
// }
