#include "manipulator.hh"

using namespace std;

/*  ZMIANA KATA

    Metoda wprowadza podany przez uzytkownika kat do danego przegubu
    Uwaga!! 
    Nowy Kat zostaje zapisany w Kacie Pomocniczym 
    Stary Kat ciagle pozostaje niezmieniony  */
void Manipulator::ZmianaKata() {
  cout << "Wprowadz q"<< NrPrzegubu<<": ";
  cin >>KatPom;
}


/*  ZMIANA KATA

    Metoda pozwala na zmiane kat przy danym przegubie
    Parametry:
      NumerPrzegubu - nr przegubu, przy ktorym zmieniamy kat
      NowyKat - po prostu nowy kat :)           */
void Manipulator::ZmianaKata(float NowyKat) {
  Katy[NrPrzegubu]=NowyKat;
}

/*  LICZBA SEGMENTOW

    Funkcja pozwala na wczytanie liczby segmentow do programu 
    oraz zmiana rozmiaru wektora zachowujacego liczbe przegubow      */
void Manipulator::LSegmentow() {
  cout << "Wprowadz ilosc segmentow (od 0 do 10): ";
  cin >> LPrzegubow;
  while (LPrzegubow < 0 || LPrzegubow> 10) {
    cout <<" Niepoprawna liczba segmentow. Wprowadz liczbe jeszcze raz"<<endl;
    cout << "Wprowadz ilosc segmentow (od 0 do 10): ";
    cin >> LPrzegubow;
  }
  Segment.resize(LPrzegubow);
  Katy.resize(LPrzegubow);
}



/*  ZMIEN DLUGOSC SEGMENTOW

    Metoda pozwala na zmiane dlugosci segmentow w manipulatorze.
    Moze przyjmowac tylko dodanie wartosci*/
void Manipulator::ZmienDlSegm() {
  cout<<"Podaj dlugosc segmentu: ";
  cin>> DlSegm;
  while (DlSegm<0) {
    cout<<"Blad: Ujemna wartosc dlugosci segmentu. Ponow probe"<<endl;
    cout<<"Podaj dlugosc segmentu: ";
    cin>> DlSegm;
  }
}


/*  ZMIEN DLUGOSC SEGMENTU

    Metoda pozwala na zmiane dlugosci segmentow manipulatora.
    Parametrem jest nowa wartosc dlugosci segmentow             */
void Manipulator::ZmienDlSegm(float DlugoscSegmentu) {
  if (DlugoscSegmentu<0) {
    cerr<<"Blad: Ujemna wartosc dlugosci segmentu."<<endl;
    cerr<<"Brak zmian w manipulatorze.";
  }
  else DlSegm=DlugoscSegmentu;
}


/*  DAJ LICZBE SEGMENTOW

    Metoda pozwala na odczytanie liczby segmentow manipulatora  
    Zwraca ilosc segmentow manipulatora    */
int Manipulator::DajLSegmentow() const { 
  return LPrzegubow; 
}

/*  ZMIEN NUMER PRZEGUBU

    Metoda pozwala na zmiane aktualnie ustawionego przegubu na aktualnie
    potrzebny. Jako parametr podaje sie numer przegubu, na ktorym chcemy
    aktualnie dzialac. Wartosci od 0 do 10                              */
void Manipulator::ZmienNrPrzegubu(const int NumerPrzegubu){
  NrPrzegubu=NumerPrzegubu;
}

/*  DAJ DLUGOSC SEGMENTU

    Metoda pozwala na odczytanie dlugosci segmentu manipulatora.     
    Zwraca dlugosc segmentow                                        */
float Manipulator::DajDlSegm() const { 
  return DlSegm; 
} 

/*  DAJ NUMER PRZEGUBU

    Metoda pozwala na odczytanie aktualnego numeru przegubu   
    Zwraca numer przegubu, ktory jest aktualnie ustawiony  */
int Manipulator::DajNrPrzegubu() const {
  return NrPrzegubu;
}

/*  ZMIEN KAT POMOCNICZY

    Metoda pozwala na ustawienie pomocniczego kata, ktorego uzywam przy 
    plynnym przewijaniu wykresu w GnuPlocie. Parametr:
      float Pom - ustawia wartosc tego kata (podany w stopniach)    */
void Manipulator::ZmienKatPom(float Pom) {
  KatPom=Pom;
}
/*  DAJ KAT POMOCNICZY

    Metoda pozwala na odczytanie wartosci pomocniczego kata 
    Zwraca pomocnicza wartosc kata (w stopniach)    */
float Manipulator::DajKatPom() const {
  return KatPom;
}



/*  R(qi) RAZY FLOATVECTOR    ( R(qi)*FLOATVECTOR )

    Metoda pozwala na pomnozenie macierzy obrotu przez podany wektor 
    Parametry:
      Nr Przeg - numer przegubu, z ktorego kata chcemy korzystac do wyznaczenia
                 macierzy obrotu   
      Pkt  - Wspolrzedne punktu, z ktorym dokonujemy mnozenia*/
Wektor Manipulator::RqRazyWektor(const int & NrPrzeg,
                                      const Wektor & Pkt) const {
  Wektor Zm1, Zm2, Wynik;
  float Kat = Katy[NrPrzeg-1]*3.14159/180; //przeliczenie na radiany
  Zm1[0]=cos(Kat);
  Zm1[1]=0-sin(Kat);
  Zm2[0]=sin(Kat);
  Zm2[1]=cos(Kat);
  Wynik[0]=Zm1[0]*Pkt[0]+Zm1[1]*Pkt[1];
  Wynik[1]=Zm2[0]*Pkt[0]+Zm2[1]*Pkt[1];
  return Wynik;
}



/*  OPERATOR [ ]

    Pozwala na odczytanie ind-tego segmentu manipulatora. Jako parametr podaje 
    się nr segmentu oznaczany od 0 do n-1 segmentow. Metoda zawiera rowniez 
    sprawdzanie poprawnosci indeksu				*/
vector<Wektor> Manipulator::operator [ ] (unsigned int i ) const { 
  vector<Wektor>  Bok_Lok(2);
  if (i> Segment.size()-1) {
    cerr << "Niepoprawny indeks segmentu"<<endl;
    exit(1);
  }
  if (i == Segment.size()-1) { // dla ostatniego segmentu
    Bok_Lok[0]=Segment[i];
    Bok_Lok[1]=Efektor;

  }
  else {
    Bok_Lok[0]=Segment[i];
    Bok_Lok[1]=Segment[i+1];
  }
  return Bok_Lok;
}




/*  OPERATOR    =

    Metoda pozwala na przepisanie informacji z jednego manipulatora 
    do drugiego                     */
Manipulator & Manipulator::operator = (const Manipulator & M) {
  Katy=M.Katy;
  Efektor = M.Efektor;
  Segment = M.Segment;
  return *this;
}


/*  OBLICZ

    Pozwala na wyliczenie punktu na podstawie wspolrzednych.
    Liczenie jest rekurencyjne  
    Parametry:
      i - domyslnie wynosi 0, potem wzrasta co 1 do aktualnego NrPrzegubu+1. 
          Potrzebna do obliczenia wspolrzednych jednego punktu*/
Wektor Manipulator::Oblicz(int i) {
  Wektor Wynik, T;
  T[0]=DajDlSegm();

  if (i<=DajNrPrzegubu()) {
    Wynik=RqRazyWektor(i+1,Oblicz(i+1)+T);  // rekurencja
  }
  return Wynik;
}




/*  ZAPISZ DO PLIKU

    Implementacja zapisu wspolrzednych manipulatora do pliku manipulator.dat
    Jesli plik nie istnieje, to zostanie utworzony          */
int Manipulator::ZapiszDoPliku() const {
  int i;
  char Nazwa[]="manipulator.dat"; 	/*zapisywany nowy plik*/
  ostringstream Strm;
  string linijka;
  fstream Plik;

  Plik.open(Nazwa,fstream::out);
  /*sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (Plik==NULL) {
    cerr<<"Blad: Nie podano uchwytu do pliku"<<endl;;
    return 0;
  }
  for(i=0;i<DajLSegmentow();i++) {
    Strm << Segment[i].x() << " "<< Segment[i].y()<<"\n";

  }

  Strm << Efektor.x() <<" "<<Efektor.y()<<"\n";
  linijka += Strm.str();        // komenda zapisana w manipulator.dat
  Plik.write(linijka.data(),linijka.size());
//  fputs(linijka.c_str(),p);
  Plik.close();        //zamykanie pliku
  return 0;
}



/*	MENU

	Wypusuje menu, z ktorego bedzie mogl korzystac uzytkownik           */
void Manipulator::Menu() const {
  int i;

  cout << " Menu:"<< endl;
  cout << "  0 - Zmiana kata q0" << endl;
  for (i=1;i<DajLSegmentow();i++) {
      cout << "  "<<i<<" - Zmiana kata q"<<i<< endl;
  }
  cout << "  z - Zmiana ilosci segmentow" << endl;
  cout << "  l - Zmiana dlugosci segmentu" << endl;
  cout << "  p - Wyswietlenie informacji o przeszkodach" <<endl;
  cout << "  u - Usun dana przeszkode" << endl;
  cout << "  d - Dodaj przeszkode - wielobok z pliku"<<endl;
  cout << "  s - Dodaj przeszkode - okrag z pliku"<<endl;
  cout << "  w - Wczytaj przeszkode - wielobok recznie"<< endl;
  cout << "  o - Wczytaj przeszkode - okrag recznie"<< endl;
  cout << "  ? - Ponowne wyswietlenie menu" << endl;
  cout << "  k - Koniec programu" << endl;

}

