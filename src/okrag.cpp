#include "okrag.hh"

using namespace std;


/*  CZY PUNKT WSPOLNY

    Metoda sprawdza czy nastepuje przeciecie manipulatora z okregiem.
    Parametry:
      Segment - jeden z segmentow manipulator podany jako wspolrzedne koncow
        segmentu

    Mamy rownania parametryczne segmentu manipulatora:
    segment P:  x = P0x + Dx*t                       
                y = P0y + Dy*t
    gdzie Ax = P1x-P0x   ,  Dy = P1y-P0y   i D=[Dx, Dy]
         oraz konce boku: P0=[P0x,P0y] , P1=[P1x,P1y]       

    oraz rownanie okregu o srodku w punkcie S=[Sx,Sy] i promieniu r
            (x-Sx)^2 + (y-Sy)^2 = r^2

    wstawiajac rownanie odcinka do rownania okregu otrzymuje rownianie 
    kwadratowe:
        (Dx^2+Dy^2)t^2    + 
     +  2[Dx(P0x-Sx)+Dy(P0y-Sy)]t    +
     +  [(P0x-Sx)^2 +(P0y-Sy)^2 -r^2]    =   0
    upraszczajac mam: At^2 + Bt + C = 0
*/
bool Okrag::CzyPunktWspolny(const Manipulator &Manip) const {
  Wektor S = Srodek, P0, P1;
  Wektor D;
  float r = Promien;
  float Delta, A,B,C,t1, t2;
  int j;
 
  for (j=0;j<Manip.DajLSegmentow();j++) {
    if (Manip[j].empty() == 1 ) { 
      cerr << "Brak segmentu manipulatora. Nastapi zakonczenie dzialania";
      cerr << " programu."<< endl;
      exit(1);
    }
    P0 = Manip[j][0];
    P1 = Manip[j][1];
    D = Wektor(P1[0]-P0[0],P1[1]-P0[1]);
    A = pow(D[0],2)  +  pow(D[1],2);
    B = 2.0f*( (D[0] * (P0[0] - S[0])   +   D[1] * (P0[1] - S[1]) ) );
    C = pow(P0[0]-S[0],2) + pow(P0[1]-S[1],2) - pow(r,2);
    Delta = pow(B,2) - 4.0f*A*C;
    if (!(Delta < 0)) {         // wykonaj gdy delta dodatnia
      t1 = (-B - sqrt(Delta))/(2.0f*A);
      t2 = (-B + sqrt(Delta))/(2.0f*A);
      if (!(t1<0 || t1>1) || !(t2<0 || t2>1)) return true;
    }
  }
  return false;
}


/*  ZAPISZ DO PLIKU

    Metoda pozwala na zapisanie okregu w postaci 73 punktow co pozwoli 
    Laczu Do Gnuplota narysowac go w przyblizeniu 
*/
void Okrag::ZapiszDoPliku(const char* NazwaPliku) {
  Wektor A;
  ostringstream Strm;
  string Linijka;
  fstream Plik;
  _NazwaPliku = NazwaPliku;

  // Zapisywanie danych do pliku
  float x, y, r = Promien;
  float fi;  // kat  w stopniach
  float KatPom;
  Srodek.Odczyt(&x,&y); // odczytanie wartosci srodka okregu 
  for (fi=0;fi<=360;fi+=5) {
    KatPom = (fi*3.14159)/180;      // kat w radianach
    Strm << x+r*cos(KatPom) << " " << y+r*sin(KatPom) << endl;
  }
//  Strm << *this;

  Linijka += Strm.str();        // komenda zapisana w Nazwa
  Plik.open(NazwaPliku,fstream::out);
  Plik.write(Linijka.data(),Linijka.size());
  Plik.close();        //zamykanie pliku

// Wczytanie pliku do programu
//  Lacze.DodajNazwePliku(_NazwaPliku.data(),PzG::RR_Ciagly,5);
//  Lacze.WczytajDoGnuPlota(Przeszkody);
}





/*  WYSWIETL WIELOBOK

    Metoda pozwala na wyswietlenie wspolrzednych wierzcholkow wieloboku    */
void Okrag::WyswPrzeszkode() const {
  cout <<endl<<"     "<<_NazwaPliku<<endl<<endl;
  cout<<"     Srodek okregu: ("<<Srodek.x()<<", ";
  cout <<Srodek.y()<<")"<<endl;
  cout<<"     Promien okregu: "<<Promien<<endl;  
}





/*  WCZYTAJ PRZESZKODE

    Metoda pozwala na wczytanie przeszkody do klasy OKRAG 
    Parametry:
      LaczeDoGnuplota Lacze
      i - numer przeszkody ktory chcemy wczytac. i oznacza n+1
          plik z nazw plikow wczytanych do GNUPlota, gdyz poprzednie nazwy to 
          nazwy plikow manipulatora    */ 
Okrag * Okrag::WczytajPrzeszkode(const char* NazwaPliku) {
  fstream Plik;
  Wektor A, B;
  int i;
  _NazwaPliku = NazwaPliku;
  ifstream Strm(NazwaPliku);
  Plik.open(NazwaPliku,fstream::in);
  /*sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (Plik==NULL) {
    cerr<<"Blad: Nie podano uchwytu do pliku"<<endl;;
    exit(1);
  }
  Strm >> A;
  for(i=0;i<17;i++) Strm >> B;
  Strm >> B;
  Plik.close();        //zamykanie pliku
  Srodek = Wektor(B.x(),A.y());
  Promien = abs(A.x() - B.x());
  return this;

}


/*	Umozliwia wczytanie wieloboku ze strumienia wejscia
	
	Parametry:
	  StrmWej - strumien wejsciowy, z ktorego bedzie wczytany wielobok
	  StrmWyj - do niego bedzie wczytany wielobok ze strumienia wejsciowego
	
	Warunki koncowe:
	  StrmWyj - zawiera wczytany wielobok pod warunkiem,ze ze strumienia
        zostaly wczytane n wektorow oznaczajacych wierzcholki wieloboku.
        Warunkiem jest rowniez, ze ostatnie wprowadzony wierzcholek musi 
        pokrywac sie pierwszym wczytanym. W przeciwnym wypadku dzialanie 
        programu zostanie przerwane z komunikatem bledu. 

	Zwracane wartosci:
	  Referencja do strumienia, na ktorym zostala wykonana operacja odczytu
	  wektora.
*/
/*istream & operator >> (istream & StrmWej, Okrag & StrmWyj) {
  Wektor Srodek;
  float Promien;
  StrmWej >> Srodek;
  Strmwej >> Promien;

  StrmWyj.ZmienSrodek(Srodek);
  StrmWyj.ZmienPromien(Promien);
  return StrmWej;
}       */



/* Umozliwia wypisanie symbolu do strumienia wyjscia.

	Parametry:
  	  StrmWyj - Strumien wyjsciowy, do ktorego ma byc wyczytany wektor
	  Wyczyt - z niej ma byc czytany wektor do strumienia wyjsciowego

	Zwracane wartosci:
	  Refernecja do strumienia, na ktorym wykonana zostala
	  operacja wypisu symobolu
*/
ostream & operator << (ostream & StrmWyj,const Okrag & Wyczyt) {
  float x, y, r;
  float fi;  // kat  w stopniach
  float KatPom;
  Wyczyt.Srodek.Odczyt(&x,&y); // odczytanie wartosci srodka okregu 
  for (fi=0;fi<=360;fi+=5) {
    KatPom = (fi*3.14159)/180;      // kat w radianach
    cout << x+r*cos(KatPom) << " " << y+r*sin(KatPom) << endl;
  }
  return StrmWyj;
}

