#include <iostream>
#include "raumschiffSteuerung.h"


int main() {
    feldInitialisieren();

    cout << "Raumschiff befindet sich an: (" << positionX << ", " << positionY << ")" << endl;

    karteAnzeigen(); // Muss die Ausgabe leeren und dann neu Zeichnen

    int x;
    int y;

    x = 10;
    y = 6;

    bewegeRaumschiff(x, y);

    x = 80;
    y = 0;

    bewegeRaumschiff(x, y);

    x = 0;
    y = 2;

    bewegeRaumschiff(x, y);

    y = 0;
    x = 10;

    bewegeRaumschiff(x, y);

    while(true){
        if(sensorWarnung(positionX+1, positionY)) {
            x = 0;
            if(!sensorWarnung(positionX, positionY+1))
                y = 1;
            else
                y = -1;
        }
        else {
            x = 1;
            y = 0;
        }
        bewegeRaumschiff(x, y);
    }
}
