#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>


class Objet
{
protected:
    std::string nom_;
    int valeur_;
public:
    Objet(std::string nom, int valeur);
    std::string afficher();
    bool operator==(Objet objet);
    bool operator!=(Objet objet);
    std::string nom();
    int get_valeur();
    virtual int get_degats();
};

class Inventaire
{ 
protected:  
  std::vector<std::shared_ptr<Objet>> liste_;
  int contenance_;
public:
    int argent;
    Inventaire(int contenance);
    void ajouter(std::string nom_objet);
    void supprimer(std::shared_ptr<Objet> objet);
    void afficher();
    void vider();
    std::shared_ptr<Objet> choisir_objet();
    void vendre(std::string nom_objet);
    std::shared_ptr<Objet> get_objet(std::string nom_objet);
    std::shared_ptr<Objet> get_objet(int index);
};


class Arme : public Objet
{
  protected:
    int degats_;
public:
  Arme(std::string nom, int degats, int valeur);
  int get_degats() override;
};

const std::array<std::shared_ptr<Objet>, 20> objets_existants;