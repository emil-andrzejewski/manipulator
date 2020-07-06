#ifndef WIELOBOK_HH
#define WIELOBOK_HH

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
class Wielobok;
#include "wektor.hh"
#include "manipulator.hh"
#include "lacze_do_gnuplota.hh"
#include "przeszkoda.hh"




/*  Niniejsza klasa modeluje WIELOBOK
    
    Klasa bedzie przechowywac informacje o manipulatorze:
      NazwaPliku - Nazwa pliku, w ktorym przechowywane sa wspolrzedne 
                wierzcholkow
      Wierzcholki - zawiera informacje o wszystkich wierzcholkach oraz katach
                przy tych wierzcholkach. Jest zawsze LBokow +1 wierzcholkow,
                bo pierwszy wierzcholek jest powtorzony na ostatnim miejscu 
*/
            


class Wielobok: public Przeszkoda {
  public:

    std::vector<Wektor> Wierzcholki;   // wierzcholki wieloboku
    Wielobok(): Wierzcholki(4)  { };   //konstruktor
//    ~Wielobok() { Wierzcholki.clear(); }

//    std::vector<Wektor> operator [ ] ( unsigned int ind ) const ;
    
    virtual bool CzyPunktWspolny(const Manipulator &Segment) const;
    Wielobok * WczytajPrzeszkode(std::string NazwaPliku);
    virtual void WyswPrzeszkode() const;

   
};

std::istream & operator >> (std::istream & StrmWej, Wielobok & StrmWyj);
std::ostream & operator << (std::ostream & StrmWyj,const Wielobok & Wyczyt);


#endif
