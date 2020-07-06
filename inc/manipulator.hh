#ifndef MANIPULATOR_HH
#define MANIPULATOR_HH

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include "wektor.hh"


/*  Niniejsza klasa modeluje MANIPULATOR
    
    Klasa bedzie przechowywac informacje o manipulatorze:
      LPrzegubow - liczba przegubow manipulatora (maksymalnie 10)
      NrPrzegubu - numer przegubu, na ktorym aktualnie dzialamy
      DlSegm - Dlugosc segmentow manipulatora 
      KatPom - Pomocniczy kat potrzebny przy plynnym przewijaniu 
               wykresu w GnuPlocie
      Katy - zawiera wartosci kotow przy danych przegubach. Max rozmiar to 10
      Efektor - Wspolrzedne efektora. 
      Wektor - zawiera informacje o wszystkich przegubach oraz katach przy
               tych przegubach. Max rozmiar to 10                         */


class Manipulator {
  private:
    int LPrzegubow;
    int NrPrzegubu;    // Nr aktualnie uzywanego do obliczen przegubu 
    float DlSegm;
    float KatPom;     // Kat pomocniczy uzyty przy plynnym przewijaniu wykresu
  public:
    std::vector<float> Katy;
    Wektor Efektor;
    std::vector<Wektor> Segment;


    Manipulator(): LPrzegubow(3), NrPrzegubu(0), DlSegm(10), Katy(3),
                              Segment(3)  { };   //konstruktor

    void ZmianaKata();
    void ZmianaKata(float NowyKat);

    void LSegmentow();
    int DajLSegmentow() const ;

    void ZmienDlSegm();
    void ZmienDlSegm(float DlugoscSegmentu);
    float DajDlSegm() const; 

    void ZmienNrPrzegubu(const int NumerPrzegubu);
    int DajNrPrzegubu() const ;

    void ZmienKatPom(float Pom);
    float DajKatPom() const;

    Wektor RqRazyWektor(const int & NrPrzegubu,
                                         const Wektor & Pkt) const;

    std::vector<Wektor> operator [ ] ( unsigned int i ) const ;
    Manipulator & operator = (const Manipulator & M);
    Wektor Oblicz(int i=0);
    int ZapiszDoPliku() const ;
    void Menu() const;
};


#endif
