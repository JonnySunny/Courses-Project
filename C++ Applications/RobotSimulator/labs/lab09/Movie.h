// Movie.h
#ifndef MOVIE_H
#define MOVIE_H
#include <string>

class Movie {
public:
  static const int CHILDRENS   = 2;
  static const int REGULAR     = 0;
  static const int NEW_RELEASE = 1;

  Movie( const std::string& title, int priceCode = REGULAR );

  int getPriceCode() const;
  void setPriceCode( int arg );
  std::string getTitle() const;

private:
  std::string _title;
  int _priceCode;
};

inline Movie::
Movie( const std::string& title, int priceCode )
  : _title( title )
  , _priceCode( priceCode )
{}

inline int Movie::
getPriceCode() const { return _priceCode; }

inline void Movie::
setPriceCode( int arg ) { _priceCode = arg; }

inline std::string Movie::
getTitle() const { return _title; }

#endif // MOVIE_H
