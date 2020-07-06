#include "wielobok.hh"	
#define PARAM 1

using namespace std;


/*  OPERATOR [ ]

    Pozwala na odczytanie ind-tego boku przeszkody. Jako parametr podaje się nr
    boku oznaczany od 0 do n-1 bokow. Metoda zawiera rowniez sprawdzanie 
    poprawnosci indeksu				*/
/*std::vector<Wektor> Wielobok::operator [ ] (unsigned int ind ) const { 
  if (ind> Wierzcholki.size()-2) {
    cerr << "Niepoprawny indeks boku"<<endl;
    exit(1);
  }
  std::vector<Wektor>  Bok_Lok(2);
  Bok_Lok[0]=Wierzcholki[ind];
  Bok_Lok[1]=Wierzcholki[ind+1];
  return Bok_Lok;
}   */



/*  CZY PUNKT WSPOLNY

    Metoda sprawdza, czy wszystkie boki wieloboku maja punkt wspolny 
    z jednym z segmentow manipulatora 
    Jako parametr podaje sie 
    
    Mamy rownania parametryczne boku przeszkody:
    bok P:  x = P0x + Ax*Tp                       
            y = P0y + Ay*Tp       
         
         gdzie Ax = P1x-P0x   ,  Ay = P1y-P0y   i A=[Ax, Ay]
         oraz konce boku: P0=[P0x,P0y] , P1=[P1x,P1y]

    segment manipulatora S:
            x = S0x + (S1x-S0x)*Ts                       
            y = S0y + (S1y-S0y)*Ts        

         gdzie Bx = S1x-S0x   ,  By = S1y-S0y   i B=[Bx, By]
         oraz konce segmentu: S0=[S0x,S0y] , S1=[S1x,S1y]

    T=[Ta,Ts]                   */

        
bool Wielobok::CzyPunktWspolny(const Manipulator &Manip) const {
  unsigned int i; 
  int j;
  Wektor P0,P1;
  for (j=0;j<Manip.DajLSegmentow();j++) {
    if (Manip[j].empty() == 1 ) { 
      cerr << "Brak segmentu manipulatora. Nastapi zakonczenie dzialania";
      cerr << " programu."<< endl;
      exit(1);
    }
    Wektor S0 = Manip[j][0], S1= Manip[j][1];
    Wektor A,B;
    float Wyznacznik, WyznP, WyznS;
    float Tp, Ts;
    B = S1-S0;  
    for (i=0;i<Wierzcholki.size()-1;i++) {  // sprawdzenie dla bokow figury
      P0 = Wierzcholki[i];
      P1 = Wierzcholki[i+1];
      A = P1-P0;
      Wyznacznik = B[0]*A[1]-B[1]*A[0];  // wyznacznik glowny
      if (abs(Wyznacznik) > 0.001) { // gdy wyznacznik != 0
        WyznP = (S0[0]-P0[0])*(-1)*B[1] - (S0[1]-P0[1])*(-1)*B[0];
        WyznS = A[0]*(S0[1]-P0[1]) - A[1]*(S0[0]-P0[0]);
        Tp = WyznP/Wyznacznik;
        Ts = WyznS/Wyznacznik;
        if (Tp>=0 && Tp<=1 && Ts<=1 && Ts>=0) { return true;}
      }
    }
  }
  return false;
}



/*  WCZYTAJ PRZESZKODE

    Metoda pozwala na wczytanie przeszkody do klasy WIELOBOK 
    Parametry:
      LaczeDoGnuplota Lacze - Stamtad brane sa nazwy plikow. 
      i - numer przeszkody ktory chcemy wczytac. i oznacza n+1
          plik z nazw plikow wczytanych do GNUPlota, gdyz poprzednie nazwy to 
          nazwy plikow manipulatora    */ 
Wielobok * Wielobok::WczytajPrzeszkode(string NazwaPliku) {
  fstream Plik;
  _NazwaPliku = NazwaPliku;
  ifstream Strm(NazwaPliku.data());
  Plik.open(NazwaPliku.data(),fstream::in);
  /*sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (Plik==NULL) {
    cerr<<"Blad: Nie podano uchwytu do pliku"<<endl;;
    exit(1);
  }
  Strm >> *this;
  Plik.close();        //zamykanie pliku
  return this;
}


/*  WYSWIETL PRZESZKODE

    Metoda pozwala na wyswietlenie wspolrzednych wierzcholkow wieloboku    */
void Wielobok::WyswPrzeszkode() const {
  unsigned int i;
  cout <<endl<<"     "<<_NazwaPliku<<endl<<endl;
  for(i=0;i<Wierzcholki.size()-1;i++) {
    cout<<"     Wierzcholek_"<<i<<": ("<<Wierzcholki[i][0]<<", ";
    cout <<Wierzcholki[i][1]<<")"<<endl;
  }
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
istream & operator >> (istream & StrmWej, Wielobok & StrmWyj) {
  Wektor Pom;
  StrmWej >> Pom;
  StrmWyj.Wierzcholki.clear();
  StrmWyj.Wierzcholki.push_back(Pom);

  do {
    StrmWej >> Pom;
    StrmWyj.Wierzcholki.push_back(Pom);
  } while ( Pom != StrmWyj.Wierzcholki[0] ) ;
  return StrmWej;
}



/* Umozliwia wypisanie symbolu do strumienia wyjscia.

	Parametry:
  	  StrmWyj - Strumien wyjsciowy, do ktorego ma byc wyczytany wektor
	  Wyczyt - z niej ma byc czytany wektor do strumienia wyjsciowego

	Zwracane wartosci:
	  Refernecja do strumienia, na ktorym wykonana zostala
	  operacja wypisu symobolu
*/
ostream & operator << (ostream & StrmWyj,const Wielobok & Wyczyt) {
  float x, y;
  unsigned int i;
  for (i=0;i<Wyczyt.Wierzcholki.size()-1;i++) {
    Wyczyt.Wierzcholki[i].Odczyt(&x,&y); // odczytanie wartosci wektora
    cout << x << " " << y << endl;
  }
  return StrmWyj;
}

