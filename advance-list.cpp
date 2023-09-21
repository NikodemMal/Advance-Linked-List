#include <iostream>

#define rozmiar 11
#define wielkosc 15

struct liczby {
    unsigned long long int liczba;
    liczby* next;
    liczby* before;

    liczby();
};
liczby::liczby() {
    next = 0;
    liczba = 0;
    before = 0;
}

struct lista {
    liczby* pierwsza;
    liczby* ostatnia;
    liczby* it[rozmiar];

    lista();
    void dodaj(unsigned long long int a, char* napis, int przed);
    void wyswietl(char* x);
    void usun(char* x);
    void czyszczenie();
    void zainicjuj(char* indeks, int a);
    void przesun(int a, int kierunek);
    void wstawprzed(liczby* nowa, liczby* nowa2);
    void wstawza(liczby* nowa, liczby* nowa2);
    void sprawdz(liczby* tmp);
};

lista::lista() {
    pierwsza = 0;
    ostatnia = 0;
    for (int i = 0; i < rozmiar; i++) {
        it[i] = 0;
    }
}


using namespace std;
int main()
{
    char a[wielkosc], x[wielkosc];
    unsigned long long int y;
    int liczba;

    lista* baza = new lista;

    while (cin >> a) {

        if (strcmp(a, "I") == 0) {
            cin >> x;

        }

        if (strcmp(a, ".A") == 0) {
            cin >> x;
            cin >> y;
            baza->dodaj(y, x, 1);
        }

        if (strcmp(a, "A.") == 0) {
            cin >> x;
            cin >> y;
            baza->dodaj(y, x, 0);
        }

        if (strcmp(a, "P") == 0) {
            cin >> x;
            baza->wyswietl(x);
        }

        if (strcmp(a, "R") == 0) {
            cin >> x;
            baza->usun(x);
        }

        if (strcmp(a, "i") == 0) {
            cin >> liczba;
            cin >> x;
            baza->zainicjuj(x, liczba);
        }

        if (strcmp(a, "+") == 0) {
            cin >> liczba;
            baza->przesun(liczba, 1);
        }
        if (strcmp(a, "-") == 0) {
            cin >> liczba;
            baza->przesun(liczba, -1);
        }
    }
    baza->czyszczenie();
}

void lista::dodaj(unsigned long long int a, char* napis, int przed) {

    liczby* nowa = new liczby;
    nowa->liczba = a;

    if (pierwsza == 0) {
        pierwsza = nowa;
        ostatnia = nowa;
    }
    else {

        if (strcmp(napis, "END") == 0) {

            if (przed == 0) {
                wstawza(nowa, ostatnia);
            }
            else {
                wstawprzed(nowa, ostatnia);
            }
        }
        else if (strcmp(napis, "BEG") == 0) {

            if (przed == 0) {
                wstawza(nowa, pierwsza);
            }
            else {
                wstawprzed(nowa, pierwsza);
            }


        }
        else {
            int indeks = atoi(napis);

            if (przed == 0) {
                wstawza(nowa, it[indeks]);
            }
            else {
                wstawprzed(nowa, it[indeks]);
            }
        }

    }
}
void lista::wstawza(liczby* nowa, liczby* nowa2) {
    nowa->next = nowa2->next;
    nowa2->next = nowa;
    nowa->before = nowa2;
    if (nowa->next)
        nowa->next->before = nowa;
    else
        ostatnia = nowa;
}

void lista::wstawprzed(liczby* nowa, liczby* nowa2) {

    if (nowa2 == pierwsza) {
        nowa->next = nowa2;
        nowa2->before = nowa;
        pierwsza = nowa;
        nowa->before = 0;
    }
    else {
        nowa->before = nowa2->before;
        nowa2->before->next = nowa;
        nowa2->before = nowa;
        nowa->next = nowa2;
    }

}

void lista::wyswietl(char* x) {
    liczby* tmp = pierwsza;

    if (strcmp(x, "ALL") == 0) {
        while (tmp) {
            cout << tmp->liczba << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    else {
        int indeks = atoi(x);
        cout << it[indeks]->liczba << endl;
    }

}

void lista::usun(char* x) {

    if (strcmp(x, "BEG") == 0) {
        if (pierwsza->next) {
            liczby* temp = pierwsza;
            pierwsza = temp->next;

            sprawdz(temp);
            delete temp;
        }
        else
            pierwsza = 0;
    }
    else if (strcmp(x, "END") == 0) {
        if (ostatnia != pierwsza) {
            liczby* temp = ostatnia;
            ostatnia = temp->before;
            ostatnia->next = 0;

            sprawdz(temp);
            delete temp;
        }
        else
            pierwsza = 0;

    }
    else {
        int indeks = atoi(x);
        if (ostatnia != pierwsza) {
            liczby* temp = it[indeks];

            if (temp->before)
                temp->before->next = temp->next;
            else {
                temp->next->before = 0;
                pierwsza = temp->next;
            }
            if (temp->next) {
                temp->next->before = temp->before;
            }
            else {
                temp->before->next = 0;
                ostatnia = temp->before;
            }

            sprawdz(temp);

            delete temp;
        }
        else
            pierwsza = 0;
    }
}
void lista::sprawdz(liczby* tmp) {

    for (int i = 0; i < rozmiar; i++) {
        if (tmp == it[i]) {
            if (tmp->next)
                it[i] = tmp->next;
            else if (tmp->before)
                it[i] = tmp->before;
        }
    }
}

void lista::czyszczenie() {
    if (pierwsza)
        while (pierwsza->next) {
            liczby* temp = pierwsza;
            pierwsza = temp->next;
            delete temp;
        }

}

void lista::zainicjuj(char* indeks, int a) {

    if (strcmp(indeks, "END") == 0) {
        it[a] = ostatnia;
    }
    else if (strcmp(indeks, "BEG") == 0) {
        it[a] = pierwsza;
    }
    else {
        int indeks2 = atoi(indeks);
        liczby* temp = pierwsza;
        while (temp && indeks2) {
            temp = temp->next;
            indeks2--;
        }
        it[a] = temp;

    }
}

void lista::przesun(int a, int kierunek) {
    if (kierunek == 1) {
        if (it[a]->next) {
            it[a] = it[a]->next;
        }
    }
    if (kierunek == -1) {
        if (it[a]->before) {
            it[a] = it[a]->before;
        }
    }
}