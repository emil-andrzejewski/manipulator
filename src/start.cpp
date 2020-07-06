#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "lacze_do_gnuplota.hh"
#include "manipulator.hh"
#include "wielobok.hh"
#include "okrag.hh"
#include "lista_przeszkod.hh"

#define ROZMIAR 2

using namespace std;
using namespace PzG;



void AktParam(const Manipulator & Manip, const vector<Wielobok> & Lista);
float Round(const float & Dana);
void PrzelWsz(Manipulator & Manip,LaczeDoGNUPlota &Lacze,
                                     const ListaPrzeszkod & Lista,
                                           const char *Wyb, float PomDlSegm);
void PlynPrzew(Manipulator & Manip, LaczeDoGNUPlota & Lacze, 
                                        const ListaPrzeszkod & Lista);
void Komunikat();
bool Obliczenia(Manipulator & Manip,LaczeDoGNUPlota & Lacze,   
                                        const ListaPrzeszkod & Lista);
bool ParamPrzeszkod(const ListaPrzeszkod &Lista);


/*  ROUND       (ZAOKRAGLENIE)

    Funkcja pozwala na zaokraglenie liczby do 2 cyfr po przecinku.
    Wykorzystywana tylko do ladnego wyswietlania MENU  
    Parametr:
      dana - dane do zaokraglenia         
*/
float Round(const float & Dana) {
  if(Dana-floor(100*Dana)/100>=0.005) return floor(100*Dana)/100+0.01;
  else return floor(100*Dana)/100;
}



/*  AKTUALNE PARAMETRY

    Funkcja wypisuje aktualne parametry i wspolrzedne punktow manipulatora
    Parametr:
      Manip - wszystkie informacje o manipulatorze  
*/
void AktParam(const Manipulator & Manip) {
  unsigned int i;

  cout <<endl<<"Aktualne wspolrzedne i parametry:"<< endl;
  for(i=0;i<Manip.Segment.size();i++) {
    cout<<"     q"<<i<<" =";
    cout<<setw(6)<<Round(Manip.Katy[i])<<"   Przegub_"<<i<<":";
    cout <<" (";
    if (abs(Round(Manip.Segment[i][0])) <0.0001) cout<<"0, ";
    else 
      cout<<Round(Manip.Segment[i][0])<<", ";
    if (abs(Round(Manip.Segment[i][1])) <0.0001) cout<<"0)"<<endl;
    else 
      cout<<Round(Manip.Segment[i][1])<<")"<< endl;

  }
  cout<<"                    Efektor: (";
  if (abs(Round(Manip.Efektor[0])) <0.0001) cout<<"0, ";
  else 
    cout <<Round(Manip.Efektor[0])<<", ";
  if (abs(Round(Manip.Efektor[1])) <0.0001) cout<<"0)"<<endl;
  else
    cout <<Round(Manip.Efektor[1])<<")"<<endl;
  cout<<"     l = "<<Round(Manip.DajDlSegm())<<endl;
}





/*  PRZELICZ WSZYSTKIE

    Funkcja pozwala na wyliczenie wszystkich punktow przy zmianie 
    ktoregos z katow                                        
    Parametry:
      Manip - wszystkie informacje o manipulatorze
      Lacze - Lacze do Gnuplota
      Wyb - wprowadzony przez chara numer przegubu, przy ktorym bedzie 
            dokonywana zmiana kata. Moze rowniez wynosic: -1 - gdy 
            zmieniana jest liczba lub dlugosc przegubow. Dla tej wartosci
            omijana jest zmiana kata 
    Funkcja zwraca:
      true - nastepuje przeciecie odcinkow boku i segmentu manipulatora
      false - przeciecie nie wystepuje */
void PrzelWsz(Manipulator &Manip,LaczeDoGNUPlota &Lacze,
                                    const ListaPrzeszkod & Lista,
                                        const char *Wyb,float PomDlSegm) {
  if (atoi(Wyb)!=-1) {                  // Wyb = "-1" gdy program startuje lub
    Manip.ZmienNrPrzegubu(atoi(Wyb));   // gdy zmieniamy dlugosc segmentu, to 
    PlynPrzew(Manip,Lacze,Lista);// zmiana kata 
  }                                                 // jest ominieta 
  else {
    if (Obliczenia(Manip,Lacze,Lista)) {
      cout<<endl<<"                       UWAGA !!!"<<endl<<endl;
      cout<<"                 WYKRYTO PRZESZKODE !!!"<<endl<<endl;
      cout<<"            Nastapilo zatrzymanie manipulatora."<<endl;
      Manip.ZmienDlSegm(PomDlSegm);
    }
    Manip.ZapiszDoPliku();
    Lacze.WczytajDoGnuPlota(Lista);   
  } 
  AktParam(Manip);
}           




/*  PLYNNE PRZEWIJANIE

    Funkcja pozwala na obliczanie punktow tak, aby przesuwanie sie obrazu
    w programie GNUPLOT bylo jaknajbardziej plynne    
    Parametry:
      Manip - wszystkie informacje o manipulatorze
      Lacze - lacze do GnuPlota                                      

    Funkcja zwraca:
      true - nastepuje przeciecie odcinkow boku i segmentu manipulatora
      false - przeciecie nie wystepuje */
void PlynPrzew(Manipulator & Manip,LaczeDoGNUPlota & Lacze,   
                                        const ListaPrzeszkod & Lista) {
  bool CzyPrzeciecie1 = false, CzyPrzeciecie2=false;
  float Pom1, Pom2, KatPom;
  int NrSegm = Manip.DajNrPrzegubu();  // Nr Segmentu, przy ktorym znajduje 
                                        // sie zmieniany kat
  Manip.ZmianaKata(); 
  Pom1 = Manip.Katy[NrSegm];      // stary kat
  Pom2 = Manip.DajKatPom();                  // nowy kat

  // przypadek gdy NOWY  >  STARY       (NOWY wiekszy niz STARY)
  if (Pom2 > Pom1) {     
    for(Manip.Katy[NrSegm];                    // stary kat
                 Pom2  >  Manip.Katy[NrSegm];     // nowy > stary
                KatPom = Manip.Katy[NrSegm], Manip.Katy[NrSegm]+=5)  //stary+5
    {
      CzyPrzeciecie1=Obliczenia(Manip,Lacze,Lista);
      Manip.ZapiszDoPliku(); 
      Lacze.WczytajDoGnuPlota(Lista);
      if (CzyPrzeciecie1) {
        Pom2 = KatPom;
        break;
      }
      system("sleep 0.01");      // przeczekać 0,01s po kazdym przesunieciu
    }                         // zapisanie ostatnio uzytego dobrego kata
    Manip.Katy[NrSegm]=Pom2; //wpisanie nowego kata do odpowiedniego
  }                                 //miejsca
                                           
  
  // przypadek gdy NOWY  <  STARY       (NOWY mniejszy niz STARY)
  if (Pom2 < Pom1) {     
    for(Manip.Katy[NrSegm];                      // stary kat
                Pom2  <  Manip.Katy[NrSegm];        // nowy < stary
              KatPom = Manip.Katy[NrSegm], Manip.Katy[NrSegm]-=5)     //stary-5
    { 
      CzyPrzeciecie1=Obliczenia(Manip,Lacze,Lista);
      Manip.ZapiszDoPliku(); 
      Lacze.WczytajDoGnuPlota(Lista); 
      system("sleep 0.01");         // przeczekać 0,01s po kazdym przesunieciu
      if (CzyPrzeciecie1) {
        Pom2 = KatPom;
        break;
      }
    }                          //zapisanie ostatnio uzytego dobrego kata
    Manip.Katy[NrSegm]=Pom2;   //wpisanie nowego kata odpowiedniego
  }                                        //miejsca 
  if ((CzyPrzeciecie2=Obliczenia(Manip,Lacze,Lista))) 
    Manip.Katy[NrSegm]=KatPom;
  if (CzyPrzeciecie1 || CzyPrzeciecie2) 
      cout<<endl<<"                       UWAGA !!!"<<endl<<endl;
      cout<<"                 WYKRYTO PRZESZKODE !!!"<<endl<<endl;
      cout<<"           Nastapilo zatrzymanie manipulatora."<<endl;
  Manip.ZapiszDoPliku();
  Lacze.WczytajDoGnuPlota(Lista);    
}



/*  OBLICZENIA

    Funkcja zawiera kilkanascie linii kodu potrzebnych do przeliczen wszystkich 
    punktow.Nie chce ich powtarzac za kazdym razem wiec zawieram je w funkcji
    Zwraca wartosci:
      true - gdy nastapilo przeciecie segmentu z przeszkoda w trakcie dzialania
      false - przeciecia nie bylo                       */
bool Obliczenia(Manipulator & Manip, LaczeDoGNUPlota & Lacze,   
                                        const ListaPrzeszkod & Lista) {
  int i;
  unsigned int j;
  bool CzyPrzeciecie=false;
  Manipulator Pom=Manip;
  for(i=0;i+1<Manip.DajLSegmentow();i++) {    // obliczenie wszystkich 
    Manip.ZmienNrPrzegubu(i);               // przegubow
    Manip.Segment[i+1]=Manip.Oblicz();
  }
  Manip.ZmienNrPrzegubu(Manip.DajLSegmentow()-1);
  Manip.Efektor=Manip.Oblicz();
  for(j=1;j<Lacze.WezLiczbePlikow()-1;j++) {//sprawdzanie czy nastepuje
    if (Lista[j]->CzyPunktWspolny(Manip)) {
      Manip = Pom;          // ostatnia dobra konfiguracja
      CzyPrzeciecie = true;
     
    }
  }
  return CzyPrzeciecie;
}

/*  PARAMETRY PRZESZKOD

    Funkcja pozwala na odczytanie wspolrzednych wierzcholkow danej przeszkody
    Parametr:
      Lista Przeszkod
    Zwraca wartosci:
      true - gdy sa wczytane przeszkody w programie
      false - gdy brak przeszkod                                */
bool ParamPrzeszkod(const ListaPrzeszkod &Lista) {
  unsigned int NrPrzeszkody,i;
  if (Lista.size()==1) {
    cout << "Brak przeszkod do wyswietlenia."<<endl;
    return false;
  }
  do {
    for(i=0;i<=Lista.size()-2;i++)
      cout <<"   "<<i<<". - "<< Lista.at(i+1)->_NazwaPliku<<endl;
    cout <<endl<< "Podaj numer przeszkody: ";
    cin >> NrPrzeszkody;
    if (NrPrzeszkody > (Lista.size()-2) )
      cout <<"Nieprawidlowy nr przeszkody. Sprobuj jeszcze raz."<<endl<<endl;
  } while (NrPrzeszkody > (Lista.size()-2)) ;
  Lista[NrPrzeszkody+1]->WyswPrzeszkode();
  return true;
}


int main() {

  LaczeDoGNUPlota  Lacze;
  char Wybor, *Wyb;
  int DoSwitcha, DoWhilea=0;
  Manipulator Manip;
  float PomDlSegmentu;

  ListaPrzeszkod Lista;
  
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.
  Lacze.ZmienTrybRys(PzG::TR_2D);
  Lacze.UstawZakresY(-35,35);
  Lacze.UstawZakresX(-53,53);

  Wielobok *A = new Wielobok, *B = new Wielobok, *C = new Wielobok;
  Okrag *D = new Okrag, *E = new Okrag;
  A->WczytajPrzeszkode("przeszkoda1.dat");
  B->WczytajPrzeszkode("przeszkoda2.dat");
  C->WczytajPrzeszkode("nowa.dat");
  D->WczytajPrzeszkode("okrag.dat");
  E->WczytajPrzeszkode("okrag1.dat");
  Lista.push_back(A);
  Lista.push_back(B);
  Lista.push_back(C);
  Lista.push_back(D);
  Lista.push_back(E);
  Lacze.WczytajDoGnuPlota(Lista);

  while (DoWhilea==0) {
	DoWhilea=1;
    PrzelWsz(Manip,Lacze,Lista,"-1",Manip.DajDlSegm());
    Manip.Menu();
	DoSwitcha=0;
	while (DoSwitcha==0) {
	  cout << endl<<"Twoj wybor?> ";
	  cin >> Wybor;
	  Wyb=&Wybor;

	  cout << endl;
	  if (isdigit(Wybor)) {	//spr. czy podana wartosc jest liczba
		if (atoi(Wyb) < Manip.DajLSegmentow()) { 
          PrzelWsz(Manip,Lacze,Lista,Wyb,Manip.DajDlSegm());        
        }
        else cout << "Niepoprawna opcja. Sprobuj jeszcze raz."<<endl;
	  }
	  else {
	    switch(Wybor) {
          case 'z': Manip.LSegmentow();
                    PrzelWsz(Manip,Lacze,Lista,"-1",Manip.DajDlSegm());
                    break;
          case 'l': PomDlSegmentu=Manip.DajDlSegm();
                    Manip.ZmienDlSegm();
                    PrzelWsz(Manip,Lacze,Lista,"-1",PomDlSegmentu);
                    break;
          case 'p': ParamPrzeszkod(Lista);
                    break;
          case 'u': Lista.UsunPrzeszkode(Lacze);
                    break;
          case 'd': Lista.DodajWielobok(Lacze);
                    break;
          case 's': Lista.DodajOkrag(Lacze);
                    break;
          case 'w': Lista.WczytajWielobokRecznie(Lacze);
                    break;
          case 'o': Lista.WczytajOkragRecznie(Lacze);
                    break;
		  case '?': DoWhilea=0;
			  	    DoSwitcha=1;
				    break;
  	   	  case 'k': DoSwitcha=1;
			   	    break;

	 	  default:cout<<"Wybrano niepoprawna opcje. Sprobuj jeszcze raz."<<endl;
			    	break;
		}
		
	  }
	}
  }
  delete A;
  delete B;
  delete C;
  delete D;
  delete E;

}
