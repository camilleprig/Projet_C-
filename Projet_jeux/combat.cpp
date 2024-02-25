#include <iostream>
#include <string>
#include <vector>
#include "inventaire.hpp"
#include "random.hpp"
#include "personnage.hpp"

bool combat(std::shared_ptr<Personnage> heros, Monstre ennemi)
{
    bool gagne = true;
    int potion_de_force = 0;
    std::cout <<"Un " <<ennemi.nom() <<" apparaît !" <<std::endl;
    while ((*heros).PV > 0 && ennemi.PV() > 0)
    {
        std::cout <<"Que voulez-vous faire ?" <<std::endl;
        std::cout <<"1. Attaque brute" <<std::endl;
        std::cout <<"2. Utiliser un objet" <<std::endl;
        std::cout <<"3. Attaque sournoise" <<std::endl;
        int choix;
        std::cin >>choix;
        if (choix == 1)
        {
            int degats = (*heros).attaque_brute();
            std::cout <<"Vous infligez " <<degats <<" dégats à " <<ennemi.nom() <<std::endl;
            bool mort = ennemi.subir_degats(degats);
            if (mort)
            {
                std::cout <<ennemi.nom() <<" est mort" <<std::endl;
                (*heros).XP = (*heros).XP + ennemi.XP();
                break;
            }
            int degats_ennemi = ennemi.attaque();
            std::cout <<ennemi.nom() <<" vous inflige " <<degats_ennemi <<" dégats" <<std::endl;
            (*heros).PV = (*heros).PV - degats_ennemi;
            if ((*heros).PV <= 0)
            {
                std::cout <<"Vous êtes mort" <<std::endl;
                gagne = false;
                break;
            }
        }
        else if (choix == 2)
        {
            (*heros).inventaire().afficher();
            std::shared_ptr<Objet> objet = (*heros).inventaire().choisir_objet();
            if (objet->nom() == "Potion de soin")
            {
                (*heros).heal();
                (*heros).inventaire().supprimer(objet);
            }
            if (objet->nom() == "Potion de force")
            {
                (*heros).force += 5;
                potion_de_force++;
                (*heros).inventaire().supprimer(objet);
            }
            else
            {
                std::cout <<"Vous ne pouvez pas utiliser cet objet" <<std::endl;
            }
        }
        else if (choix == 3)
        {
            int degats = (*heros).attaque_sournoise();
            std::cout <<"Vous infligez " <<degats <<" dégats à " <<ennemi.nom() <<std::endl;
            bool mort = ennemi.subir_degats(degats);
            if (mort)
            {
                std::cout <<ennemi.nom() <<" est mort" <<std::endl;
                (*heros).XP = (*heros).XP + ennemi.XP();
                break;
            }
            int degats_ennemi = ennemi.attaque();
            std::cout <<ennemi.nom() <<" vous inflige " <<degats_ennemi <<" dégats" <<std::endl;
            (*heros).PV = (*heros).PV - degats_ennemi;
            if ((*heros).PV <= 0)
            {
                std::cout <<"Vous êtes mort" <<std::endl;
                gagne = false;
                break;
            }
        }
    }
    if (potion_de_force > 0)
    {
        (*heros).force -= 5*potion_de_force;
    }
    return gagne;
}

void revive(std::shared_ptr<Personnage> heros)
{
    std::cout <<"Alors que vous erriez dans les couloirs de la mort, vous sortez de cette torpeur et ouvrez les yeux" <<std::endl;
    std::cout <<"Paolina vous a sauvé" <<std::endl;
    (*heros).PV = (*heros).max_PV;
    (*heros).modifier_argent(-(*heros).argent()/2);
}

void labyrinth(std::shared_ptr<Personnage> heros)
{
    std::cout <<"Vous entrez dans le labyrinthe" <<std::endl;
    std::cout <<"Vous vous perdez dans les couloirs" <<std::endl;
    std::cout <<"Vous entendez des bruits de pas" <<std::endl;
    std::cout <<"Un monstre apparaît" <<std::endl;
    Monstre monstre=monstres[2];
    bool gagne = combat(heros, monstre);
    if (gagne)
    {
        std::cout <<"Vous avez gagné" <<std::endl;
    }
    else
    {
        revive(heros);
    }
    std::cout <<"Vous arrivez à un embranchement, à droite vous entendez des appel à l'aide, à gauche c'est silencieux" <<std::endl;
    std::string réponse;
    std::cin >>réponse;
    if (réponse == "droite")
    {
        std::cout <<"Vous pensez apercevoir la fille disparu mais elle se métamorphose en réalité en squelette, il s'agissait d'un piège" <<std::endl;
        Monstre squelette=monstres[5];
        gagne = combat(heros, squelette);
        if (gagne)
        {
            std::cout <<"Vous avez gagné" <<std::endl;
        }
        else
        {
            revive(heros);
        }
        std::cout <<"Vous rebroussez chemin et choisissez cette fois la voie de gauche"<<std::endl;
    }
    else
    {
        std::cout <<"Vous vous tournez à gauche" <<std::endl;
    }
    std::cout <<"Vous arrivez dans une salle, la jeune fille est là" <<std::endl;
}