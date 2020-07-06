#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH
#include <iostream>
#include <string>
#include "manipulator.hh"

class Przeszkoda {
  public: 
    std::string _NazwaPliku ;
    virtual ~Przeszkoda() { _NazwaPliku.clear(); } 
    virtual bool CzyPunktWspolny(const Manipulator &Segment) const = 0 ;
    virtual void WyswPrzeszkode() const = 0;

    /*  DAJ NAZWE PLIKU
        Metoda pozwala na odczytanie nazwy pliku, w ktorym znajduja sie 
        informacje o przeszkodzie                       */
    std::string DajNazwePliku() const { return _NazwaPliku; } ;

};

#endif
