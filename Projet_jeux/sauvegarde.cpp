#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "personnage.hpp"

class Save
{
protected:
    std::string nom_sauvegarde_;
    Personnage personnage_;
    int code_histoire_;
    Inventaire inventaire_;
public:
    Save(std::string nom_sauvegarde, Personnage personnage, int code_histoire, Inventaire inventaire)
    {
        nom_sauvegarde_ = nom_sauvegarde;
        personnage_ = personnage;
        code_histoire_ = code_histoire;
        inventaire_ = inventaire;
    }
    void print() const
    {
        std::cout <<"Nom de la sauvegarde :" <<nom_sauvegarde_ <<std::endl;
        std::cout <<"Personnage :" <<personnage_ <<std::endl;
    }
    void sauvegarder()
    {
        std::ofstream fichier(nom_sauvegarde_ + ".txt", std::ios::out | std::ios::trunc);
        if (fichier)
        {
            fichier <<"Nom de la sauvegarde :" <<nom_sauvegarde_ <<std::endl;
            fichier <<"Personnage :" <<personnage_ <<std::endl;
            fichier <<"Code histoire :" <<code_histoire_ <<std::endl;
            fichier <<"Inventaire :" <<inventaire_ <<std::endl;
            fichier.close();
        }
        else
        {
            std::cout <<"Erreur lors de l'ouverture du fichier" <<std::endl;
        }
    }
    void charger()
    {
        std::ifstream fichier(nom_sauvegarde_ + ".txt", std::ios::in);
        if (fichier)
        {
            std::string ligne;
            while (getline(fichier, ligne))
            {
                std::cout <<ligne <<std::endl;
            }
            fichier.close();
        }
        else
        {
            std::cout <<"Erreur lors de l'ouverture du fichier" <<std::endl;
        }
    }
};