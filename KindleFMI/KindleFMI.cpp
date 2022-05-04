#include <iostream>
#include "Kindle.h"
//4096

using namespace std;

int main()
{
    Kindle kindleFMI;
    char input[4096];
    while (true) {
        cin.getline(input, 4096);

    }
    kindleFMI.Register("Antonia", "5550125");


    return 0;
}
