#include <iostream>
#include <string>
#include "catalogue.hpp"
#include "personnage.hpp"
#include "inventaire.hpp"

void jouer(std::shared_ptr<Personnage> heros, int& code_histoire)
{
    bool echec_enigme = false;
    while (code_histoire !=100)
    {
        catalogue(heros, code_histoire, echec_enigme); // Call the catalogue function
    }
}

int main()
{
    while (true)
    {
        std::cout <<"Bienvenue dans Légende des Anciens" <<std::endl;
        std::cout <<"a/ Nouvelle Partie" <<std::endl;
        std::shared_ptr<Personnage> heros = creation_personnage();
        std::string nom_sauvegarde;
        int code_histoire = 0;
        jouer(heros, code_histoire);
    }
    
}

