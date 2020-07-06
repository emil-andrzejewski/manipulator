#ifndef LISTA_PRZESZKOD_HH
#define LISTA_PRZESZKOD_HH
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
class ListaPrzeszkod;
#include "przeszkoda.hh"
#include "okrag.hh"
#include "wielobok.hh"
#include "lacze_do_gnuplota.hh"

class ListaPrzeszkod: public std::vector<Przeszkoda*> {
  public:
    ~ListaPrzeszkod() { clear(); }
    ListaPrzeszkod()  { resize(1); }


    bool DodajWielobok(PzG::LaczeDoGNUPlota &Lacze);
    bool DodajOkrag(PzG::LaczeDoGNUPlota &Lacze);
    void WczytajWielobokRecznie(PzG::LaczeDoGNUPlota &Lacze);
    void WczytajOkragRecznie(PzG::LaczeDoGNUPlota &Lacze);
    void UsunPrzeszkode(PzG::LaczeDoGNUPlota &Lacze);

};

#endif
