#ifndef OKRAG_HH
#define OKRAG_HH
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
class Okrag;
#include "przeszkoda.hh"
#include "wektor.hh"
#include "manipulator.hh"
#include "lacze_do_gnuplota.hh"


class Okrag: public Przeszkoda {
    float Promien;
  public: 
    Wektor  Srodek;

    Okrag(): Promien(10), Srodek(-10,-10) {}
    Okrag(float x,float y) { Srodek=Wektor(x,y); }
//    ~Okrag() { }

    void ZmienPromien(float Pr) {Promien = Pr; }
    float DajPromien() const { return Promien; }

//    void ZmienSrodek(const Wektor & W) { Srodek = W; }
  //  Wektor DajSrodek() { return Srodek; }

    virtual bool CzyPunktWspolny(const Manipulator &Manip) const;
    void ZapiszDoPliku(const char * NazwaPliku);
    virtual void WyswPrzeszkode() const;
    Okrag * WczytajPrzeszkode(const char * NazwaPliku);

};

std::ostream & operator << (std::ostream & StrmWyj,const Okrag & Wyczyt);

#endif
