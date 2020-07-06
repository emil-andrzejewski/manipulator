#include "lista_przeszkod.hh"

using namespace std;

/*  DODAJ WIELOBOK

    Funkcja pozwala na wczytanie przeszkody do programu poprzez podanie nazwy
    pliku z danymi przeszkody  
    Parametry:
      Lacze Do GnuPlota
    Zwraca wartosci:
      true - poprawnie dodano plik
      false - anulowano dodawanie pliku             
*/
bool ListaPrzeszkod::DodajWielobok(PzG::LaczeDoGNUPlota &Lacze) {
  char Nazwa[100];
  fstream Plik;
  Wielobok *Pom = new Wielobok;
  do {
    cout << "Podaj nazwe pliku z przeszkoda: ";
    cin >> Nazwa;
    if (!strcmp(Nazwa,"r")) return false;
    Plik.open(Nazwa,fstream::in);
    if (!Plik.is_open()) {
      cout<<"Blad: Nie podano uchwytu do pliku."<<endl;
      cout<<"Podaj nazwe pliku jeszcze raz lub aby anulowac dodawanie ";
      cout<<"pliku wcisnij r."<<endl;
    }

  } while (!Plik.is_open()); 
  Plik.close();
  Pom->WczytajPrzeszkode(Nazwa);
  push_back(Pom);
  Lacze.WczytajDoGnuPlota(*this);

  return true;
}


/*  DODAJ OKRAG

    Metoda pozwala na wczytanie okregu do programu z pliku.
    Parametry:
      Lacze do Gnuplota
    Zwraca wartosci:
      true - poprawnie dodano plik
      false - anulowano dodawanie pliku    
    UWAGA!!!
    Plik musi byc zapisany tak jak bedzie odczytywany przez Gnuplota do 
    wyswietlania. Czyli w formie 73 punktow przyblizajacych obraz okregu.
*/
bool ListaPrzeszkod::DodajOkrag(PzG::LaczeDoGNUPlota &Lacze) {
  char Nazwa[100];
  fstream Plik;
  Okrag *Pom = new Okrag;
  do {
    cout <<"UWAGA!!!"<<endl<<"Podany plik musi byc zapisany w takiej formie";
    cout <<" jak bedzie wczytywany do gnuplota."<<endl;
    cout<<"Czyli w formie 73 punktow."<<endl<<endl;
    cout << "Podaj nazwe pliku z przeszkoda - okregiem: ";
    cin >> Nazwa;
    if (!strcmp(Nazwa,"r")) return false;
    Plik.open(Nazwa,fstream::in);
    if (!Plik.is_open()) {
      cout<<"Blad: Nie podano uchwytu do pliku."<<endl;
      cout<<"Podaj nazwe pliku jeszcze raz lub aby anulowac dodawanie ";
      cout<<"pliku wcisnij r."<<endl;
    }

  } while (!Plik.is_open()); 
  Plik.close();
  Pom->WczytajPrzeszkode(Nazwa);
  push_back(Pom);
  Lacze.WczytajDoGnuPlota(*this);

  return true;
}




/*  WCZYTAJ WIELOBOK RECZNIE

    Funkcja pozwala na reczne podanie nazwy oraz wierzcholkow przeszkody   
    Parametry:
      Lacze do Gnuplota 
*/
void ListaPrzeszkod::WczytajWielobokRecznie(PzG::LaczeDoGNUPlota &Lacze) {
  char Nazwa[100];
  int LBokow=3, i;
  Wielobok *NowaPrzeszkoda = new Wielobok;
  vector<Wektor> Nowa;
  Wektor A;
  ostringstream Strm;
  string Linijka;
  fstream Plik;

// Wczytywanie danych
  cout << "Podaj nazwe tworzonej przeszkody: ";
  cin >> Nazwa;
  do {
    cout << "Podaj liczbe bokow przeszkody: ";
    cin >> LBokow;
    if (LBokow<3) 
      cout<< "Niepoprawna liczba bokow. Wprowadz liczbe jeszcze raz."<<endl;
  } while (LBokow<3);

  cout<< "Wierzcholki podawaj jako dwie wartosci oddzielone spacja."<<endl;
  for (i=0;i<LBokow;i++) {
    cout<<"Podaj wierzcholek nr "<<i<<": ";
    cin >> A;
    Nowa.push_back(A);
  }
  A = Nowa.front();
  Nowa.push_back(A);  
// Zapisywanie danych do pliku

  for (i=0;i<=LBokow;i++) {
    Strm << Nowa[i].x() << " " << Nowa[i].y()<< "\n";
  }

  Linijka += Strm.str();        // komenda zapisana w Linijce
  Plik.open(Nazwa,fstream::out);
  Plik.write(Linijka.data(),Linijka.size());
  Plik.close();        //zamykanie pliku

// Wczytanie pliku do programu
  push_back(NowaPrzeszkoda->WczytajPrzeszkode(Nazwa));
  Lacze.WczytajDoGnuPlota(*this);
}


/*  WCZYTAJ OKRAG RECZNIE

    Metoda pozwala na wczytanie okregu do programu. Uzytkownik podaje srodek
    okregu oraz dlugosc promiania
    Parametry:
      Lacze do Gnuplota
*/
void ListaPrzeszkod::WczytajOkragRecznie(PzG::LaczeDoGNUPlota &Lacze) {
  Okrag *O = new Okrag;
  float Pr;
  char Nazwa[100];
  cout <<"Podaj nazwe tworzonej przeszkody: ";
  cin >> Nazwa;
  cout <<"Podaj srodek okregu (jako dwie wartosci oddzielone spacja): ";
  cin >> O->Srodek;
  cout <<"Podaj dlugosc promienia: ";
  cin >> Pr;
  O->ZmienPromien(Pr);
  O->ZapiszDoPliku(Nazwa);
  push_back(O);
  Lacze.WczytajDoGnuPlota(*this);
}


/*  USUN PRZESZKODE

    Funkcja pozwala na usuniecie podanej przeszkody z programu.
    Parametr:
      Lacze Do GnuPlota               
*/
void ListaPrzeszkod::UsunPrzeszkode(PzG::LaczeDoGNUPlota &Lacze) {
  unsigned int NrPrzeszkody, i;
  do {
    for(i=0;i<=size()-2;i++)
      cout <<"   "<<i<<". - "<< at(i+1)->_NazwaPliku<<endl;
    cout <<endl<< "Podaj numer przeszkody: ";
    cin >> NrPrzeszkody;
    if (NrPrzeszkody > (size()-2) )
      cout <<"Nieprawidlowy nr przeszkody. Sprobuj jeszcze raz."<<endl;
  } while (NrPrzeszkody > size()-2 );
  erase(begin()+NrPrzeszkody+1);
//  Lacze.UsunNazwePliku(NrPrzeszkody+1); //(+1)-uwzgledniamy pliki manipulatora
  Lacze.WczytajDoGnuPlota(*this);
}




