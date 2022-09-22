/**================================================================================================
 * *                                           INFO
 *  Autore    : Francesco Pio Nocerino
 *  @email    : kekko.dev16@gmail.com
 *  File      : FCFSv4.cpp
 *  Versione  : 1.0
 *  Data      :
 *  Descr     :
 * ? Algoritmo di scheduling First come first served
 *================================================================================================**/

#ifdef _WIN32 // Win32
#include <windows.h>
#include <stdlib.h>
#endif

#include <iostream>
#include <iomanip>
using namespace std;

#define M 30 // Dimensione array

/*================================ CARICAMENTO ==============================*/
void carica(int dim, int v[]); // caricamento

/*================================ CONTROLLI ==============================*/
void controllo(int Max, int &n); // controllo dimensione
void controlloNeg(int &n, int i);

/*================================ CALCOLI ==============================*/
float totale(int dim, int v[]); // calcolo tempo medio
void gantt(int dim, int v[]);   // diagramma di gantt

/*================================ GRAFICA ==============================*/
void banner();
void cl();
#ifdef _WIN32
void set_console_color(int dim);
void strGantt_Win(int dim, int v[], string C);
#elif defined __APPLE__ || defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux__)
string color(string word, string back, string frase); // colore per diagramma di gantt
void strGantt(int dim, int v[], string C);            // struttura diagramma
#endif
/*================================ FINE PROTOTIPI ==============================*/

int main()
{
    int n, processi[M];

    banner();
    cout << "Inserisci numero processi: ";
    cin >> n;

    controllo(M, n);
    carica(n, processi);
    gantt(n, processi);

    cout << "\nTempo di attesa medio: " << totale(n, processi) << endl
         << endl;

    return 0;
}

/*================================ CARICAMENTO ==============================*/

void carica(int dim, int v[])
{
    // Caricamento del vettore processi
    cout << "NB:Inserisci i processi in ordine\n";
    for (int i = 0; i < dim; i++)
    {
        cout << "Inserisci processo P" << i + 1 << ": ";
        cin >> v[i];
        controlloNeg(v[i], i);
    }
}

/*================================ CONTROLLI ==============================*/

void controllo(int Max, int &n)
{
    // Controlla se la dimensione del vettore non superi la dimensione massima (M 50)
    while (n > Max || n <= 0)
    {
        // Se la dimensione non rispetta la dimensione massima o e` minore di 0 viene richiesta in input
        cout << "Numero di processi non valido!\n";
        cout << "Inserisci numero processi: ";
        cin >> n;
    }
}

/*===============================================*/

void controlloNeg(int &n, int i)
{
    // controllo se c`e un numero negativo
    while (n < 0)
    {
        cout << "Numero inserito negativo non Accetto!!\n";
        cout << "Inserisci processo P" << i + 1 << ": ";
        cin >> n;
    }
}

/*================================ CALCOLI ==============================*/

float totale(int dim, int v[])
{
    // Calcolo tempo medio durata
    float tot = 0, t = 0;
    for (int i = 0; i < dim - 1; i++)
    {
        tot += v[i];
        t += tot;
    }
    t /= dim;
    return t;
}

/*===============================================*/

void gantt(int dim, int v[])
{
    // Adattamento progress bar a tutti i SO
#if defined _WIN32
    char x = 219;
    string C = string(x);
    strGantt_Win(dim, v, C);
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    string C = "█";
    strGantt(dim, v, C);
#elif defined(__APPLE__)
    string C = "█";
    strGantt(dim, v, C);
#endif
}

/*================================ GRAFICA ==============================*/

void banner()
{
    // Banner nome algoritmo
    cl();
    cout << "    _______________________\n";
    cout << "   / ____/ ____/ ____/ ___/\n";
    cout << "  / /_  / /   / /_   \\__ \\ \n";
    cout << " / __/ / /___/ __/  ___/ / \n";
    cout << "/_/    \\____/_/    /____/  \n";
    cout << setw(62) << "+--------------------------+\n";
    cout << setw(34) << "|"
         << setw(15) << "FCFS" << setw(12) << "|" << endl;
    cout << setw(34) << "|"
         << setw(10) << " FRIST COME FRIST SERVED" << setw(3) << "|" << endl;
    cout << setw(34) << "|"
         << setw(10) << "By:Francesco Pio Nocerino" << setw(2) << "|" << endl;
    cout << setw(62) << "+--------------------------+\n";
}

/*===============================================*/

void cl()
{
#ifdef _WIN32
    system("cls");
#elif defined __APPLE__ || defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux__)
    system("clear");
#endif
}
/*===============================================*/

#ifdef _WIN32
void set_console_color(int cl)
{
    // colori windows
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cl);
}
void strGantt_Win(int dim, int v[], string C)
{
    // struttura diagramma di gannt
    int colori[5] = {9, 10, 12, 13, 14}; // Colori per diagramma
    int indiceC = 0;
    cout << endl;
    cout << "DIAGRAMMA DI GANTT\n";
    for (int i = 0; i < dim; i++) // stampa nomi processi
    {
        cout << setw(v[i] - 1) << "P" << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < dim; i++, indiceC++) // Stampa diagramma
    {
        set_console_color(colori[indiceC]);
        if (indiceC >= 5) // Se l'indice dei colori supera l'array viene riportato a 0
            indiceC = 0;
        for (int j = 0; j < v[i]; j++)
        {
            cout << C;
        }
        cout << setw(3) << "\b";
        set_console_color(15); // resetta il colore della console
    }
    cout << endl;
    int tot = 0;
    cout << tot;
    for (int i = 0; i < dim; i++)
    {
        tot += v[i];
        cout << setw(v[i]) << tot << " ";
    }
    cout << endl;
}
#elif defined __APPLE__ || defined(__linux__) || defined(__LINUX__) || defined(__gnu_linux__)
string color(string word, string back, string frase)
{
    string tot = "\033[" + back + ";" + word + "m" + frase + "\033[0m";
    // viene chiesto il colore delle lettere, lo sfondo e la frase da stampare;
    // Può essere passato in nome del colore oppure il rispettivo codice-> "sotto forma di stringa"
    return tot;
}

/*=========================================*/

void strGantt(int dim, int v[], string C)
{
    // struttura diagramma di gannt
    string colori[5] = {"31", "32", "33", "34", "36"}; // Codice ANSI dei colori
    int indiceC = 0;
    cout << endl;
    cout << "DIAGRAMMA DI GANTT\n";
    for (int i = 0; i < dim; i++) // stampa nomi processi
    {
        cout << setw(v[i] - 1) << "P" << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < dim; i++, indiceC++) // Stampa diagramma
    {
        if (indiceC >= 5) // Se l'indice dei colori supera l'array viene riportato a 0
            indiceC = 0;
        for (int j = 0; j < v[i]; j++)
        {
            cout << color(colori[indiceC], "", C);
        }
        cout << setw(3) << "\b";
    }
    cout << endl;
    int tot = 0;
    cout << tot;
    for (int i = 0; i < dim; i++)
    {
        tot += v[i];
        cout << setw(v[i]) << tot << " ";
    }
    cout << endl;
}
#endif

/*================================ FINE PROGRAMMA ==============================*/
