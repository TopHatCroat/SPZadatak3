#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>

/*
cetvorka[2] - Prioriteti 	1-VIP		2-Invalid	3.Trudnice	4.Umirovljenici	5.Obicni smrtnici
cetvorka[3] - Usluga		1-Posiljka	2-Racun		3.Lutrija	4.Western Union	5.EvoTV

*/

struct element {
	char ime[20];
	char prezime[20];
	char spol;
	int datum[3];
	int cetvorka[4];
};

//#include "red_polje.h"
#include "red_pokazivaci.h"


using namespace std;
static const string slogovi = "entetinisavarakatinabibamabulilaloetrekanalolamarininafiribonolesimekeducenedaio";


void generator(red *Q){
	srand(time(0));
	int n;
	cout << "Broj elemenata za generiranje: ";
	cin >> n;
	random_device rand_dev;
	mt19937 generator(rand_dev());
  	uniform_int_distribution<int> distribution(1,5);
	
	element e;
	int trenutni = 0;
	while(trenutni < n){
		e.cetvorka[0] = rand() % 490 + 10;
		e.cetvorka[1] = rand() % 720 + 80;
		e.cetvorka[2] = distribution(generator);
		e.cetvorka[3] = distribution(generator);
		
		for (int j = 0; j < 12; j++) {
			int OldSpice = (rand()%40)*2;
			e.ime[j++] = slogovi[OldSpice++];
			e.ime[j] = slogovi[OldSpice];	
		}
		e.ime[0] -=32;
		e.ime[rand()%5+3] = '\0';
		
		for (int j = 0; j < 14; j++) {
			int OldSpice = (rand()%40)*2;
			e.prezime[j++] = slogovi[OldSpice++];
			e.prezime[j] = slogovi[OldSpice];
		}
		e.prezime[0] -=32;
		e.prezime[rand()%8+3] = '\0';
		
		if(rand()%2) e.spol = 'z';
		else e.spol = 'm';
		
		if(e.spol == 'm' && e.cetvorka[2] == 3 && trenutni % 2 ) continue; //provjera musko/trudnica
		else e.spol = 'z';
		e.datum[0] = rand()%30+1;
		e.datum[1] = rand()%12+1;
		e.datum[2] = 1996 - (rand()%75);
		
		if(e.datum[2] < 1953 && e.cetvorka[2] == 3) continue; //provjera stariji od 45/trudnice
		if(e.datum[2] > 1943 && e.cetvorka[2] == 4) continue; //provjera mladi od 55/umirovljenici
		
		
	
		EnQueueQ(e, Q);
		trenutni++;
	}
}

void ispisE(element e){
	    cout<<"Ime i prezime: "<< e.ime<< " " << e.prezime<<endl;
        cout<<"Datum rodenja: "<<e.datum[0]<< "-" << e.datum[1]<< "-" << e.datum[2] << endl;
        cout<<"Spol: "<<e.spol<<endl;
        cout << "Cetvorka: \t" << e.cetvorka[0] << "\t" << e.cetvorka[1];
        switch(e.cetvorka[2]){
        	case 1:
        		cout << "\tVIP     ";
        		break;
        	case 2:
        		cout << "\tInvalid ";
        		break;
        	case 3:
        		cout << "\tTrudnica";
        		break;
        	case 4:
        		cout << "\tUmirovljen";
        		break;
        	case 5:
        		cout << "\tKorisnik";
        		break;
        }
        switch(e.cetvorka[3]){
        	case 1:
        		cout << "\tPosiljka";
        		break;
        	case 2:
        		cout << "\tRacun";
        		break;
        	case 3:
        		cout << "\tLutrija";
        		break;
        	case 4:
        		cout << "\tW Union";
        		break;
        	case 5:
        		cout << "\tEvoTV";
        		break;
        }
        cout << endl;
        cout << "------------------" << endl;
}

void ispisR(red *Q, int usluga){
    red* vicious;
    vicious = InitQ();
    element delicious;
    while(!IsEmptyQ(Q)){
        delicious = FrontQ(Q);
		if (usluga == 0) ispisE(delicious);	
		else if (usluga == delicious.cetvorka[3]) ispisE(delicious);	
		EnQueueQ(delicious, vicious);
        DeQueueQ(Q);
        }
    int brojac = 0;
    while(!IsEmptyQ(vicious)){
        delicious=FrontQ(vicious);
        EnQueueQ(delicious, Q);
        DeQueueQ(vicious);
        brojac++;
    }
    cout << "================================================" << endl;
    cout << " ***** Broj ljudi u redu: " << brojac << " *****" << endl;
    cout << "================================================" << endl;
}

void sort(red *Q, bool uzlazno){
	int i, top, pomak;
	if(uzlazno){
		i = 1;
		top = 6;
		pomak = 1;
	} else {
		i = 5;
		top = 0;
		pomak = -1;
	}
	
	element e;
	red *help = InitQ(), *moreHelp = InitQ();
	for(; i != top; i += pomak){
		while(!IsEmptyQ(Q)){
			e = FrontQ(Q);
			DeQueueQ(Q);
			if(e.cetvorka[2] == i) EnQueueQ(e, help);
			else EnQueueQ(e, moreHelp);
		}
		while(!IsEmptyQ(moreHelp)){
			e = FrontQ(moreHelp);
			DeQueueQ(moreHelp);
			EnQueueQ(e, Q);
		}
	}
	while(!IsEmptyQ(help)){
		e = FrontQ(help);
		DeQueueQ(help);
		EnQueueQ(e,Q);
	}
}

void horoskop(red *Q){
	red* vicious;
    vicious = InitQ();
    element delicious;
    cout << "Ispis svih Jarceva mladih od 40 koji cekaju u redu za uplatu lutrije: " << endl;
	
	while(!IsEmptyQ(Q)){
        delicious = FrontQ(Q);
        if(delicious.cetvorka[3] == 3 && ((delicious.datum[0] >= 22 && delicious.datum[1] == 12) || (delicious.datum[0] <= 20 && delicious.datum[1] == 1)) && delicious.datum[2] > 1974){
			ispisE(delicious);
        }
		EnQueueQ(delicious, vicious);
        DeQueueQ(Q);
        }
    int brojac = 0;
    while(!IsEmptyQ(vicious)){
        delicious=FrontQ(vicious);
        EnQueueQ(delicious, Q);
        DeQueueQ(vicious);
        brojac++;
    }	
}

void trudnice(red *Q){
	red* vicious;
	red* DontStopBelieving;
	DontStopBelieving = InitQ();
    vicious = InitQ();
    element delicious;
    sort(Q, true);
    cout << "Ispis svih trudnica koje su otisle: " << endl;
	
	while(!IsEmptyQ(Q)){
        delicious = FrontQ(Q);
        if(delicious.cetvorka[3] == 5 && delicious.cetvorka[2] == 3){
			EnQueueQ(delicious, DontStopBelieving);
			ispisE(delicious);
        }
		else EnQueueQ(delicious, vicious);
        DeQueueQ(Q);
        }
    int brojac = 0;
    while(!IsEmptyQ(vicious)){
        delicious=FrontQ(vicious);
        EnQueueQ(delicious, Q);
        DeQueueQ(vicious);
        brojac++;
    }	
}

void brziQ(red *Q, red *QQ){
	if(IsEmptyQ(Q)){
		return;
	}
	element nindja = FrontQ(Q);
	DeQueueQ(Q);
	brziQ(Q, QQ);
	static int u1 = 0, u2 = 0, u3 = 0, u4 = 0, u5 = 0;
	if(nindja.cetvorka[2] == 4) EnQueueQ(nindja, QQ);
	else if(nindja.cetvorka[3] == 1 && u1 < 2) {
		EnQueueQ(nindja, QQ);
		u1++;
	} 
	else if(nindja.cetvorka[3] == 2 && u2 < 2) {
		EnQueueQ(nindja, QQ);
		u2++;
	} 	
	else if(nindja.cetvorka[3] == 3 && u3 < 2) {
		EnQueueQ(nindja, QQ);
		u3++;
	} 	
	else if(nindja.cetvorka[3] == 4 && u4 < 2) {
		EnQueueQ(nindja, QQ);
		u4++;
	} 	
	else if(nindja.cetvorka[3] == 5 && u5 < 2) {
		EnQueueQ(nindja, QQ);
		u5++;
	} 	
	else EnQueueQ(nindja, Q);
	
}

int main(){
	red *Q = InitQ();
	red *QQ = InitQ();
	int izbor;
	do {
		cout << " ===   Simulacija reda u posti      === " << endl;
		cout << " ===   Odaberite opciju             === " << endl;
		cout << " ===    1. Generiranje ljudi        === " << endl;
		cout << " ===    2. Prikaz stanja u redu     === " << endl;
		cout << " ===    3. Jarci u redu za lutriju  === " << endl;
		cout << " ===    4. Trudnice odlaze          === " << endl;
		cout << " ===    5. Brzi red                 === " << endl;
		cin >> izbor;
		
		switch(izbor){
			case 1:
				generator(Q);
				ispisR(Q, 0);
				break;
			case 2:
				sort(Q, true);
				cout << "Ispis ljudi u salteru za posiljke..." << endl;
				ispisR(Q, 1);
				cout << "Ispis ljudi u salteru za placanje racuna..." << endl;
				ispisR(Q, 2);
				cout << "Ispis ljudi u salteru za lutriju..." << endl;
				ispisR(Q, 3);
				cout << "Ispis ljudi u salteru za Western Union..." << endl;
				ispisR(Q, 4);
				cout << "Ispis ljudi u salteru za EvoTV..." << endl;
				ispisR(Q, 5);
				break;
			case 3:
				horoskop(Q);
				break;
			case 4:
				trudnice(Q);
				break;
			case 5:
				sort(Q, false);
				brziQ(Q, QQ);
				sort(QQ, true);
				ispisR(QQ, 0);
				break;
		}
		
	}while (izbor != 9);
	
	
	
	
}
