#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "inventaire.hpp"
#include "random.hpp"

class Personnage
{
protected:
    std::string nom_;
    std::string crush_;
    std::string classe_;   
    std::shared_ptr<Objet> arme_;
    std::shared_ptr<Inventaire> inventaire_;
public:
    int max_PV;
    int PV;
    int XP;
    int force;
    int intelligence;
    int agilite;
    int chance;
    Personnage(std::string nom_, std::string crush_, std::string classe_, int max_PV_, int force_, int intelligence_, int agilite_, int chance_)
    {
        this->nom_ = nom_;
        this->crush_ = crush_;
        this->classe_ = classe_;
        this->max_PV = max_PV_;
        this->PV = max_PV_;
        this->XP = 0;
        this->force = force_;
        this->intelligence = intelligence_;
        this->agilite = agilite_;
        this->chance = chance_;
        Inventaire inventaire(20);
        this->inventaire_ = std::make_shared<Inventaire>(inventaire);
    };
    virtual void level_up()=0;
    void print() const
    {
        std::cout <<"Nom :" <<nom_ <<std::endl;
        std::cout <<"Crush :" <<crush_ <<std::endl;
        std::cout <<"Classe :" <<classe_ <<std::endl;
        std::cout <<"PV :" <<PV <<std::endl;
        std::cout <<"XP :" <<XP <<std::endl;
        std::cout <<"Force :" <<force <<std::endl;
        std::cout <<"Intelligence :" <<intelligence <<std::endl;
        std::cout <<"Agilité :" <<agilite <<std::endl;
        std::cout <<"Chance :" <<chance <<std::endl;
    };
    void heal()
    {
        PV = PV + 20;
        if (PV > max_PV)
        {
            PV = max_PV;
        }
    };
    int attaque_brute() 
    {
        int degat = (RandomNumber()*force+arme_->get_degats())/10;
        if (degat > arme_->get_degats()){ std::cout <<"Succès critique" <<std::endl; return arme_->get_degats()+1;}
        else if(degat==0) 
        { 
            std::cout <<"Echec critique, vous perdez un PV" <<std::endl; 
            PV-=1; 
            return degat;
        }
        else {return degat;}
    };
    int attaque_sournoise()
    {
        int degat = (RandomNumber()*(agilite+intelligence))/20;
        if (degat > arme_->get_degats()){ std::cout <<"Succès critique" <<std::endl; return arme_->get_degats()+1;}
        else if(degat==0) 
        { 
            std::cout <<"Echec critique, vous perdez un PV" <<std::endl; 
            PV-=1; 
            return degat;
        }
        else {return degat;}
    };
    bool discret()
    {
        if (RandomNumber()*(agilite+intelligence) > 50)
        {
            return true;
        }
        return false;
    };
    std::string crush() const
    {
        return crush_;
    };
    std::string nom() const
    {
        return nom_;
    };
    void set_arme(std::shared_ptr<Objet> arme)
    {
        if(this->arme_!=nullptr)
        {
            inventaire_->ajouter(arme_->nom());
            this->arme_ = arme;
        }
        else{
            this->arme_ = arme;
        }
    };
    int argent() const
    {
        return inventaire_->argent;
    };
    void modifier_argent(int somme)
    {
        inventaire_->argent += somme;
    };
    Inventaire inventaire() const
    {
        return *inventaire_;
    };
};

class Guerrier : public Personnage
{
public:
    Guerrier(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "guerrier", 100, 20, 4, 5,5){};
    void level_up() override{
        max_PV += 10;
        PV = max_PV;
        XP -= 100;
        force += 5;
        intelligence += 1;
        agilite += 1;
        chance += 1;
    };
};


class Mage : public Personnage
{
public:
    Mage(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "mage", 70, 5, 15, 4, 10){};
    void level_up() override{
        max_PV += 5;
        PV = max_PV;
        XP -= 100;
        force += 1;
        intelligence += 3;
        agilite += 1;
        chance += 3;
    };
};


class Voleur : public Personnage
{
public:
    Voleur(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "voleur", 70, 7, 10, 12, 5){};
    void level_up() override{
        max_PV += 5;
        PV = max_PV;
        XP -= 100;
        force += 1;
        intelligence += 3;
        agilite += 3;
        chance += 1;
    };
};


class Paladin : public Personnage
{
public:
    Paladin(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "paladin", 90, 12, 10, 7, 5){};
    void level_up() override{
        max_PV += 5;
        PV = max_PV;
        XP -= 100;
        force += 3;
        intelligence += 2;
        agilite += 2;
        chance += 1;
    };
};

class Chasseur : public Personnage
{
public:
    Chasseur(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "chasseur", 80, 10, 7, 10, 7){};
    void level_up() override{
        max_PV += 5;
        PV = max_PV;
        XP -= 100;
        force += 2;
        intelligence += 2;
        agilite += 2;
        chance += 2;
    };
};

std::shared_ptr<Personnage> creation_personnage()
{
    std::shared_ptr<Personnage> personnage;
    std::cout <<"Bienvenue dans la création de personnage" <<std::endl;
    std::cout <<"Veuillez choisir un nom" <<std::endl;
    std::string nom;
    std::cin >>nom;
    std::cout <<"Veuillez choisir le nom de votre crush" <<std::endl;
    std::string crush;
    std::cin >>crush;
    std::cout <<"Veuillez choisir une classe parmi: guerrier, mage, voleur, paladin, chassseur" <<std::endl;
    std::string classe;
    while (classe!="guerrier" | classe!="mage" | classe!="voleur" | classe!="paladin" | classe!="chasseur")
    {
        std::cout <<"Veuillez choisir une classe parmi: guerrier, mage, voleur, paladin, chassseur" <<std::endl;
        std::cin >>classe;
    }
    if (classe=="guerrier")
    {
        personnage = std::make_shared<Guerrier>(nom, crush);
    }
    else if (classe=="mage")
    {
        personnage = std::make_shared<Mage>(nom, crush);
    }
    else if (classe=="voleur")
    {
        personnage = std::make_shared<Voleur>(nom, crush);
    }
    else if (classe=="paladin")
    {
        personnage = std::make_shared<Paladin>(nom, crush);
    }
    else if (classe=="chasseur")
    {
        personnage = std::make_shared<Chasseur>(nom, crush);  
    }
    std::cout <<"Votre personnage a été créé" <<std::endl;
    std::cout <<"Ces caractéristiques actuelles sont :" <<std::endl;
    personnage->print();
    return personnage;
}

class Monstre
{
protected:
    std::string nom_;
    int PV_;
    int attaque_;
    int gain_XP_;
    std::vector<std::string> loot_;
public:
    Monstre(std::string nom, int PV, int attaque, std::vector<std::string> loot) 
    {
        this->nom_ = nom;
        this->PV_ = PV;
        this->attaque_ = attaque;
        this->loot_ = loot;
    };
    void print() const
    {
        std::cout <<"Nom :" <<nom_ <<std::endl;
        std::cout <<"PV :" <<PV_ <<std::endl;
        std::cout <<"Attaque :" <<attaque_ <<std::endl;
    };
    int attaque() const
    {
        return attaque_;
    };
    bool subir_degats(int degats)
    {
        PV_ -= degats;
        if (PV_ < 0)
        {
            return true;
        }
        return false;
    };
    std::string loot() const
    {
        return loot_[RandomNumber()%loot_.size()];
    };
    int PV() const
    {
        return PV_;
    };
    std::string nom() const
    {
        return nom_;
    };
    int XP() const
    {
        return gain_XP_;
    };

};

void gestion_inventaire(std::shared_ptr<Personnage> heros)
{
    std::cout <<"Votre inventaire contient :" <<std::endl;
    (*heros).inventaire().afficher();
    std::cout <<"Vous avez " <<(*heros).argent() <<" pièces d'or" <<std::endl;
    std::cout <<"Que voulez-vous faire ?" <<std::endl;
    std::cout <<"1. Utiliser un objet" <<std::endl;
    std::cout <<"2. Equiper une arme" <<std::endl;
    int reponse;
    std::cin >>reponse;
    if(reponse==1)
    {
        std::shared_ptr<Objet> objet = (*heros).inventaire().choisir_objet();
        //à revoir
    }
    else if(reponse==2)
    {
        std::cout <<"Quelle arme voulez-vous équiper ?" <<std::endl;
        (*heros).inventaire().afficher();
        int choix;
        std::cin >>choix;
        heros->set_arme(heros->inventaire().get_objet(choix));
    }
    else
    {
        std::cout <<"Veuillez choisir une option valide" <<std::endl;
    }

}

const std::array<Monstre, 5> monstres = {
    Monstre("Loup", 20, 5, {"peau de loup", "viande de loup"}),
    Monstre("Ours", 30, 10, {"peau d'ours", "viande d'ours"}),
    Monstre("Troll", 40, 15, {"oeil de troll", "dent de troll"}),
    Monstre("Dragon", 200, 20, {"oeil de dragon", "dent de dragon"}),
    Monstre("Squelette", 25, 7, {"os de squelette", "poussière de squelette"})
};


