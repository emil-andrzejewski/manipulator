#include "wektor.hh"
using namespace std;



/*	ODCZYT

	Umozliwia odczytanie wartosci wektora		*/
void Wektor::Odczyt(float *x,float *y) const {
  *x=(_x);
  *y=(_y);
}


/*      ==

    Metoda sprawdza czy 2 wektory sa sobie rowne. Zwraca:
    1 - gdy sa rowne
    0 - gdy nie sa rowne         */
bool Wektor::operator == (const Wektor& Arg2) const {
  return (abs(_x-Arg2._x)<=0.001 && abs(_y-Arg2._y)<=0.001);
}



/*      !=

    Metoda sprawdza czy 2 wektory sa sobie rowne. Zwraca:
    1 - gdy sa rozne
    0 - gdy sa rowne         */
bool Wektor::operator != (const Wektor& Arg2) const {
  return (abs(_x-Arg2._x)>0.001 || abs(_y-Arg2._y)>0.001);
}


/*	Umozliwia wczytanie wektora ze strumienia wejscia
	
	Parametry:
	  StrmWej - strumien wejsciowy, z ktorego bedzie wczytany wektor
	  StrmWyj - do niego bedzie wczytany wektor ze strumienia wejsciowego
	
	Warunki koncowe:
	  StrmWyj - zawiera wczytany wektor pod warunkiem,ze ze strumienia zostaly
		wczytane trzy liczby typu float, jak np.: (1.2 22 -3.4). W przeciwnym
		wypadku dzialanie programu zostanie przerwane z komunikatem bledu

	Zwracane wartosci:
	  Referencja do strumienia, na ktorym zostala wykonana operacja odczytu
	  wektora.
*/
istream & operator >> (istream & StrmWej, Wektor & StrmWyj) {
  float x, y;
  StrmWej >> x;
  StrmWej >> y;
  StrmWyj = Wektor(x,y);
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
ostream & operator << (ostream & StrmWyj,const Wektor & Wyczyt) {
  float x, y;
  Wyczyt.Odczyt(&x,&y); // odczytanie wartosci wektora
  cout << x << " " << y << endl;
  return StrmWyj;
}
