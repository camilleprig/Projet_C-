#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include "inventaire.hpp"
#include "random.hpp"

class Personnage
{
protected:
    std::string nom_;
    std::string crush_;
    std::string classe_;   
    std::shared_ptr<Arme> arme_;
    std::shared_ptr<Inventaire> inventaire_;
public:
    int max_PV;
    int PV;
    int XP;
    int force;
    int intelligence;
    int agilite;
    int chance;
    Personnage(std::string nom_, std::string crush_, std::string classe_, int max_PV_, int force_, int intelligence_, int agilite_, int chance_);
    virtual void level_up()=0;
    void print() const;
    void heal();
    int attaque_brute();
    int attaque_sournoise();
    bool discret();
    std::string crush() const;
    std::string nom() const;
    void set_arme(std::shared_ptr<Objet> arme);
    int argent() const;
    void modifier_argent(int somme);
    Inventaire inventaire() const;
};

class Guerrier : public Personnage
{
public:
    Guerrier(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "guerrier", 100, 20, 4, 5,5){};
    void level_up() override;
};


class Mage : public Personnage
{
public:
    Mage(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "mage", 70, 5, 15, 4, 10){};
    void level_up() override;;
};


class Voleur : public Personnage
{
public:
    Voleur(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "voleur", 70, 7, 10, 12, 5){};
    void level_up() override;
};


class Paladin : public Personnage
{
public:
    Paladin(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "paladin", 90, 12, 10, 7, 5){};
    void level_up() override;
};

class Chasseur : public Personnage
{
public:
    Chasseur(std::string nom_, std::string crush_) : Personnage(nom_, crush_, "chasseur", 80, 10, 7, 10, 7){};
    void level_up() override;
};


std::shared_ptr<Personnage> creation_personnage();

class Monstre
{
protected:
    std::string nom_;
    int PV_;
    int attaque_;
    std::vector<std::string> loot_;
public:
    Monstre(std::string nom, int PV, int attaque, std::vector<std::string> loot);
    void print() const;
    int attaque() const;
    bool subir_degats(int degats);
    std::string loot() const;
    int PV() const;
    std::string nom() const;
    int XP() const;
};

void gestion_inventaire(std::shared_ptr<Personnage> heros);

const std::array<Monstre, 5> monstres = {
    Monstre("Loup", 20, 5, {"peau de loup", "viande de loup"}),
    Monstre("Ours", 30, 10, {"peau d'ours", "viande d'ours"}),
    Monstre("Troll", 40, 15, {"oeil de troll", "dent de troll"}),
    Monstre("Dragon", 200, 20, {"oeil de dragon", "dent de dragon"}),
    Monstre("Squelette", 25, 7, {"os de squelette", "poussière de squelette"})
};
