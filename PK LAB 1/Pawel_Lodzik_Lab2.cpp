// Lab2 Pawel Lodzik.cpp : Defines the entry point for the console application.
// @author Paweł Lodzik
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class Punkt
{
private:
	float x;
	float y;

public:
	Punkt(float x_ = 0, float y_ = 0);
	Punkt(const Punkt& p);
	void dodaj(const Punkt &p); //dodawanie do siebie współrzędnych wektora
	void dodaj(const Punkt *p);
	void drukuj();
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	float getX() { return this->x; }
	float getY() { return this->y; }
	~Punkt();

	Punkt& operator+=(const Punkt& p2);
	Punkt& operator=(const Punkt& p2);
	bool operator==(const Punkt &p);
	bool operator!=(const Punkt &p);
	Punkt operator+(const Punkt& p2);
	friend ostream& operator<< (ostream& out, const Punkt& p) {
		out << "X: " << p.x << " ";
		out << "Y: " << p.y;
		out << endl;
		return out;
	}



};

class Tablica
{
private:
	Punkt *w;
	int dl; //Długość tablicy

public:

	Tablica(int dl = 0); // tworzy Tablice o zadanej długości i wypełnia punktami (0,0)
	Tablica(const Tablica &w_); //inicjalizacja za pomocą Tablicy w_
	Tablica(float *x, float *y, int dl); // inicjalizacja tablicy  punktów  tablicami x -ów i y -ów
	Tablica(string nazwa_pliku);
	~Tablica();
	void dodaj(const Tablica &w_);// dodaje do siebie Tablice w_
	bool porownaj(const Tablica &w);// porownaie z Tablica w_;
	void drukuj();

	Tablica& operator=(const Tablica& p2);
	bool operator==(const Tablica &p);
	friend ostream& operator<< (ostream& out, const Tablica& t) {
		if (!t.dl) {
			out << "Tablica jest pusta" << endl;
			return out;
		}

		out << "Wypisywanie tablicy" << endl;
		for (int i = 0; i < t.dl; i++) {
			out << "(" << t.w[i].getX() << ", " << t.w[i].getY() << ")" << endl;
		}

		return out;
	}
	Tablica& operator+=(const Tablica& t);
	Tablica& operator+=(const Punkt& p);
	Punkt& operator[](size_t el) { return w[el]; }
	const Punkt & operator[](size_t el) const { return w[el]; }


};

Punkt::Punkt(float x_, float y_)
{
	this->x = x_;
	this->y = y_;
}

Punkt::Punkt(const Punkt& p)
{
	this->x = p.x;
	this->y = p.y;
}

void Punkt::dodaj(const Punkt &p)
{
	this->x += p.x;
	this->y += p.y;
}

void Punkt::dodaj(const Punkt *p)
{
	this->x += p->x;
	this->y += p->y;
}

void Punkt::drukuj() {
	using namespace std;
	cout << "X: " << this->x << " ";
	cout << "Y: " << this->y;
	cout << endl;
}

Punkt::~Punkt()
{
}

Punkt& Punkt::operator+=(const Punkt& p2) {
	this->dodaj(p2);
	return *this;
}

Punkt& Punkt::operator=(const Punkt& p2) {
	//Jeśli obiekty są takie same nie musimy ich kopiować
	if (this != &p2) {
		this->x = p2.x;
		this->y = p2.y;
	}
	return *this;
}

bool Punkt::operator==(const Punkt &p) {
	return this->x == p.x && this->y == p.y;
}

bool Punkt::operator!=(const Punkt &p) {
	return !(this->x == p.x && this->y == p.y);
}

Punkt Punkt::operator+(const Punkt& p2) {
	Punkt p3;
	p3.x = this->x + p2.x;
	p3.y = this->y + p2.y;
	return p3;
}


Tablica::Tablica(int dl)
{
	this->dl = dl;

	if (!dl) {
		this->w = NULL;
	}
	else {
		w = new Punkt[dl];
	}

}

Tablica::Tablica(const Tablica &w_)
{
	this->dl = w_.dl;

	if (!dl) {
		this->w = NULL;
	}
	else {
		this->w = new Punkt[this->dl];
		for (int i = 0; i < this->dl; i++) {
			*(this->w + i) = *(w_.w + i);
		}
	}
}

Tablica::Tablica(float *x, float *y, int dl)
{
	this->dl = dl;
	if (!this->dl) {
		this->w = NULL;
	}
	else {
		this->w = new Punkt[this->dl];
		for (int i = 0; i < this->dl; i++) {
			this->w[i].setX(*(x));
			this->w[i].setY(*(y));
		}
	}
}

Tablica::Tablica(string nazwa_pliku) {

	ifstream plik(nazwa_pliku);
	if (plik.is_open()) {
		//Zczytujemy plik do wektora
		Punkt p;
		float x;
		float y;
		while (plik >> x >> y) {
			p.setX(x);
			p.setY(y);
			*this += p;
		}
	}

}

void Tablica::dodaj(const Tablica &w_)
{
	if (w_.dl != this->dl) {
		cout << "Tablice są różnych rozmiarów" << endl;
		return;
	}


	for (int i = 0; i < this->dl; i++) {
		this->w[i] += w_[i];
	}
}

bool Tablica::porownaj(const Tablica &w_) {

	for (int i = 0; i < this->dl; i++) {
		if (this->w[i] != w_[i])
		{
			return false;
		}
	}

	return true;
}

void Tablica::drukuj()
{
	cout << *this << endl;

}

Tablica::~Tablica()
{
	delete[] this->w;
	this->w = NULL;
}

Tablica& Tablica::operator=(const Tablica& t2) {
	//Jeśli obiekty są takie same nie musimy ich kopiować
	if (this != &t2) {
		this->dl = t2.dl;
		delete[] this->w;
		this->w = new Punkt[this->dl];
		for (int i = 0; i < this->dl; i++) {
			*(this->w+i) = *(t2.w + i);
		}
	}
	return *this;
}

bool Tablica::operator==(const Tablica &p) {
	return this->porownaj(p);
}

Tablica& Tablica::operator+=(const Tablica& t) {
	this->dodaj(t);
	return *this;
}

Tablica& Tablica::operator+=(const Punkt& p) {

	if (w == NULL) {
		this->dl = 1;
		w = new Punkt[this->dl];
		*w = p;
	}
	else {
		Punkt * tmp = w;
		this->dl++;
		w = new Punkt[this->dl];
		for (int i = 0; i < this->dl - 1; i++) {
			w[i] = tmp[i];
		}
		delete[] tmp;
		w[this->dl - 1] = p;
	}
	return *this;
}

int main()
{
	//Inicjalizowanie nowego punktu o x = 5 y = 6
	Punkt punkt = Punkt(5, 6);
	//Wydruk
	punkt.drukuj();

	//kopiowanie punktu do 2 punktu wartosci w obu punktach powinny byc te same
	Punkt punkt2 = Punkt(punkt);
	punkt2.drukuj();

	//Dodawanie wartosci z punktu 2 do 1 czyli powinno x = 10 y = 12 po tym
	punkt.dodaj(punkt2);
	punkt.drukuj();

	//Dodawanie wartosci z punktu 2 przez wskaznik powinno byc x = 15 y = 18 po tym
	punkt.dodaj(&punkt2);
	punkt.drukuj();

	//Dodawanie wartosci z dynamicznie tworzonego obiektu powinno byc x = 25 y = 28 po tym 
	Punkt *punkt3 = new Punkt(10, 10);
	punkt.dodaj(punkt3);
	delete punkt3;
	punkt.drukuj();

	//Odpowiedz na pytanie
	/*
	Klasa Tablica nie może wykorzystac domyślnego operatora kopiowania,
	ponieważ zawiera ona dynamicznie inicjalizowane dane(pointery).

	W takim przypadku trzeba by było własnoręcznie nadpisać operator kopiowania.
	*/
	//Testowanie tablicy
	//Tworzenie 10 elementowej tablicy o wartościach 0
	Tablica tab2(10);
	tab2.drukuj();

	//Tworzenie 2 tablicy, która kopiuje 1 tablice
	Tablica tab3(tab2);
	tab3.drukuj();

	//Tworzenie 3 tablicy, z wartosciami dynamicznymi x i y o wartosciach 5 i 6 o dlugosci 5
	float *x = new float;
	float *y = new float;
	*x = 5;
	*y = 6;
	Tablica tab4(x, y, 5);
	tab4.drukuj();
	delete x;
	delete y;

	//Dodawanie do siebie 2 tablic
	x = new float;
	y = new float;
	*x = 7;
	*y = 8;
	Tablica tab5(x, y, 5);
	tab5.drukuj();
	delete x;
	delete y;

	tab5.dodaj(tab4);
	tab5.drukuj();

	//Porównanie 2 tablic

	if (tab4.porownaj(tab5)) {
		cout << "Tablica 4 i tablica 5 są takie same" << endl;
	}
	else {
		cout << "Tablica 4 i tablica 5 nie są takie same" << endl;
	}

	//Porównanie 2 tablic
	if (tab2.porownaj(tab3)) {
		cout << "Tablica 2 i tablica 3 sa takie same" << endl;
	}
	else {
		cout << "Tablica 2 i tablica 3 nie sa takie same" << endl;
	}

	//Testowanie przeciążenia operatorów dla 2 punktów
	Punkt p1(13.00, 14.00);
	Punkt p2(15.00, 16.00);

	//Dodajemy do punktu p2 punkt p1
	p2 += p1;
	cout << "Drukowanie punktu p2" << endl;
	p2.drukuj();

	//Kopiujemy 2 punkt do 1
	p1 = p2;
	cout << "Drukowanie punktu p1" << endl;
	p1.drukuj();

	//Sprawdzenie czy punkt p1 i p2 są takie same
	if (p1 == p2) {
		cout << "Punkt p1 i p2 są takie same" << endl;
	}
	else {
		cout << "Punkt p1 i p2 nie są takie same" << endl;
	}

	//Dodawanie punktu p1 do p2 w celu uzyskania punktu 3 p3
	cout << "Wynik p3 = p1 + p2 " << endl;
	Punkt p3 = p1 + p2;
	//Testowanie operatora wypisywania << 
	cout << p3;

	//Testowanie przeciążenia operatorów dla 2 tablic
	x = new float;
	y = new float;
	*x = 3;
	*y = 4;
	Tablica tab6(x, y, 10);
	*x = 10;
	*y = 20;
	Tablica tab7(x, y, 20);
	//Kopiowanie tablicy tab7 do tablicy tab6
	tab6 = tab7;
	cout << "Drukowanie tablicy tab 6" << endl;
	tab6.drukuj();
	//Odpowiedź na pytanie 
	// Czy dla klasy Tablica można użyć opertaora = bez jego definiowania, czy program będzie wtedy          działał prawidłowo ? (2p)
	/*Nie można użyć opetatora = bez jego definiowania ponieważ wtedy przekopiuje się adres wskaznika w, a nie jego zawartosc
	Krótko mówiąc jeśli obiekt z którego kopiowaliśmy zostanie zniszczony, tablica w obiekcie do którego kopiowaliśmy nie będzie już istniała i odwołanie się do którego kolwiek indeksu z niej
	wyrzuci błąd indeksu lub jakąś dziwną wartość

	Najprościej mówiąc operator = trzeba zdefiniować kiedy obiekty zawierają dynamicznie alokowaną pamięć
	*/

	//Sprawdzenie czy tablica tab6 == tab7
	if (tab6 == tab7) {
		cout << "Tablice tab6 i tab7 są takie same" << endl;
	}
	else {
		cout << "Tablice tab6 i tab7 nie są takie same" << endl;
	}

	//Drukowanie tablicy tab7 operatorem << 
	cout << "Drukowanie tablicy tab7" << endl;
	cout << tab7;

	//Dodawanie tablicy tab6 do tablicy tab7
	tab7 += tab6;
	cout << tab7;

	//Edycja 3 elementu wektora tablicy tab6
	tab7[3].setX(100);
	tab7[3].setY(200);
	
	//Odczytywanie 3 elementu tablicy tab7
	cout << tab7[3] << endl;

	delete x;
	delete y;

	//Tworzenie testowego pliku do zczytania
	std::ofstream outfile("tablica.txt");
	outfile << 1.0f << " " << 2.0f << endl;
	outfile << 3.0f << " " << 2.0f << endl;
	outfile << 5.0f << " " << 6.0f << endl;
	outfile << 7.0f << " " << 8.0f << endl;
	outfile << 9.0f << " " << 10.0f << endl;
	outfile << 11.0f << " " << 12.0f << endl;
	outfile << 13.5f << " " << 15.5f << endl;
	outfile << 40.3f << " " << 30.2f << endl;
	outfile.close();

	//Tworzenie tablicy tab8 i wczytywanie jej z pliku za pomocą konstruktora
	Tablica tab8("tablica.txt");
	cout << "Tablica tab8 wczytana z pliku" << endl;
	cout << tab8;

	system("pause");
	//Wybrany projekt
	//Węzeł sieci
	return 0;
}

