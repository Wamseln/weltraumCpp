#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // Für usleep (Wartezeit in Mikrosekunden)

using namespace std;

const int FIELD_WIDTH = 100;  // Breite des Feldes
const int FIELD_HEIGHT = 20; // Höhe des Feldes

const int SMALL_ASTEROIDS = 50;   // Anzahl der kleinen Asteroiden
const int MEDIUM_ASTEROIDS = 30;   // Anzahl der mittelgroßen Asteroiden
const char SMALL_ASTEROID_SYMBOL = '.';
const char MEDIUM_ASTEROID_SYMBOL = 'O';

char FELD[FIELD_HEIGHT][FIELD_WIDTH];
int positionX = 0;
int positionY = FIELD_HEIGHT/2;
int feldlaenge = 10;

void feldInitialisieren(int seed = 10) {
    // Initialisiere das Feld mit Leerzeichen
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            FELD[i][j] = ' ';
        }
    }

    // Setze den Zufallszahlengenerator
    srand(seed);

    // Platziere kleine Asteroiden und speichere Koordinaten
    for (int i = 0; i < SMALL_ASTEROIDS; i++) {
        int x = rand() % FIELD_WIDTH;
        int y = rand() % FIELD_HEIGHT;
        FELD[y][x] = SMALL_ASTEROID_SYMBOL;
    }

    // Platziere mittelgroße Asteroiden und speichere Koordinaten
    for (int i = 0; i < MEDIUM_ASTEROIDS; i++) {
        int x = rand() % FIELD_WIDTH;
        int y = rand() % FIELD_HEIGHT;
        FELD[y][x] = MEDIUM_ASTEROID_SYMBOL;
    }
}

void karteAnzeigen() {
    // Lösche die alte Ausgabe
    system("clear");
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            cout << FELD[i][j];
        }
        cout << endl;
    }
    cout << endl << endl << "X = " << positionX << ", Y = " << positionY << endl;
    usleep(100000); // Wartezeit in Mikrosekunden (100ms)
}

bool sensorWarnung(int x, int y) {
    // Gibt wahr zurück, wenn Position (x,y) außerhalb des Feldes liegt
    if(x < 0 or y < 0 or y >= FIELD_HEIGHT) {
        return true;
    }
    // Gibt wahr zurück, wenn auf Position (x,y) ein Asteroid ist
    if (FELD[y][x] == SMALL_ASTEROID_SYMBOL or FELD[y][x] == MEDIUM_ASTEROID_SYMBOL) {
        return true;
    }
    return false;
}

void kollisionstest(int x, int y) {
    // Überprüft, ob ein Asteroid getroffen wurde. Falls ja wird das Feld ausgegeben
    // und das Spiel beendet.
    if (FELD[y][x] == SMALL_ASTEROID_SYMBOL or FELD[y][x] == MEDIUM_ASTEROID_SYMBOL) {
        FELD[y][x] = 'Q';
        FELD[y+1][x] = '|';
        FELD[y-1][x] = '|';
        FELD[y][x-1] = '-';
        FELD[y][x+1] = '-';
        FELD[y+1][x+1] = '\\';
        FELD[y-1][x-1] = '\\';
        FELD[y+1][x-1] = '/';
        FELD[y-1][x+1] = '/';
        karteAnzeigen();
        cout << "Das Raumschiff hat einen Asteroiden getroffen!" << endl;
        usleep(100000);
        exit(0);
    }
}


void bewegeRaumschiff(int x, int y) {
    // Bewege das Raumschiff um x-Schritte nach vorn und um y-Schritte nach unten.
    while(x != 0 or y != 0) {
        if(x < 0) {
            if(y == 0) {
                // Pfad markieren
                FELD[positionY][positionX] = '-';
                // Keine y-Positionsveränderung
            }
            else if(y > 0) {
                // Pfad markieren
                FELD[positionY][positionX] = '/';
                // y-Position verändern
                positionY++;
                y--;
            }
            else if(y < 0){
                // Pfad markieren
                FELD[positionY][positionX] = '\\';
                // y-Position verändern
                positionY--;
                y++;
            }
            // x-Position verändern
            positionX--;
            x++;
        }
        else if(x > 0) {
            if(y == 0) {
                // Pfad markieren
                FELD[positionY][positionX] = '-';
                // Keine y-Positionsveränderung
            }
            else if(y > 0) {
                // Pfad markieren
                FELD[positionY][positionX] = '\\';
                // y-Position verändern
                positionY++;
                y--;
            }
            else if(y < 0) {
                // Pfad markieren
                FELD[positionY][positionX] = '/';
                // y-Position verändern
                positionY--;
                y++;
            }
            // x-Position verändern
            positionX++;
            x--;
        }
        else if(x == 0 and y != 0) {
            // Pfad markieren
            FELD[positionY][positionX] = '|';
            if(y > 0) {
                // y-Position verändern
                positionY++;
                y--;
            }
            else if(y < 0){
                // y-Position verändern
                positionY--;
                y++;
            }
        }
        // Kolliosionsprüfung
        kollisionstest(positionX, positionY);
        if(positionX >= FIELD_WIDTH) {
            feldlaenge -= 1;
            if(feldlaenge == 0) {
                cout << "Das Raumschiff hat den Asteroidengürtel durchquert!" << endl;
                usleep(100000);
                exit(0);
            }
            else {
                positionX = 0;
                positionY = FIELD_HEIGHT/2;
                feldInitialisieren(time(NULL));
            }
        }
        else if(positionY >= FIELD_HEIGHT or positionY < 0) {
            karteAnzeigen();
            cout << "Das Raumschiff hat den kartierten Bereich verlassen und ist explodiert!" << endl;
            usleep(100000);
            exit(0);
        }
        // Raumschiff einzeichnen
        FELD[positionY][positionX] = 'X';
        karteAnzeigen();
    }

}


void steuerRaumschiff() {
    while(true) {

    }
}
