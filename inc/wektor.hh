#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <cstdlib>
#include <cmath>




class Wektor {
    float _x, _y;
  public :
    Wektor( ) { _x = _y = 0; } ;
    Wektor( float x, float y ) { _x = x;  _y = y; } ;

    float x( ) const { return _x; } ;
    float y( ) const { return _y; } ;
                                          
    Wektor Zmien( float x, float y ) { _x = x; _y = y; return Wektor(x,y) ; };
    Wektor & operator += ( const Wektor &W ) {_x += W._x;_y+=W._y;
                                                                return *this;};
    Wektor operator + ( Wektor W ) const { return Wektor( _x+W._x, _y+W._y); };

    Wektor & operator -= ( const Wektor &W ) { _x -= W._x; _y -= W._y; 
                                                              return *this;} ;
    Wektor operator - ( Wektor W ) const { return Wektor( _x-W._x, _y-W._y); };

    float operator * ( Wektor W ) const { return _x*W._y - _y*W._x; } ;
    Wektor operator * ( float L ) const { return Wektor( _x*L , _y*L); };

    Wektor & operator = (Wektor W) { _x=W._x; _y=W._y; return *this; } ;
    float operator [ ] (unsigned int i) const { return (i==0 ? _x : _y); } 
    float & operator [ ] (unsigned int i) { return (i==0 ? _x : _y); }

    bool operator == (const Wektor& Arg2) const;
    bool operator != (const Wektor& Arg2) const;

    void Odczyt(float *x,float *y) const;
};

std::istream & operator >> (std::istream & StrmWej, Wektor & StrmWyj);
std::ostream & operator << (std::ostream & StrmWyj,const Wektor & Wyczyt);

#endif 
