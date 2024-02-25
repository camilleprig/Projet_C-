#include <iostream>
#include <cstdlib>
#include <ctime>

int RandomNumber() {
    std::srand(std::time(0)); // Utilize the current time as seed
    int nombreAleatoire = std::rand() % 10; // Generate a random number between 0 and 10
    return nombreAleatoire;
}

