#include <iostream>
#include <string>
#include <memory>
#include <vector>


class Objet
{
protected:
    std::string nom_;
    int valeur_;
public:
    Objet(std::string nom, int valeur)
    {
        this->nom_ = nom;
        this->valeur_ = valeur;
    }
    void afficher()
    {
        std::cout <<"Nom de l'objet: " <<nom_ <<std::endl;
        std::cout <<"Valeur: " <<valeur_ <<std::endl;

    }
    bool operator==(Objet objet)
    {
        return nom_ == objet.nom_;
    }
    bool operator!=(Objet objet)
    {
        return nom_ != objet.nom_;
    }
    int get_valeur()
    {
        return valeur_;
    }
    std::string nom()
    {
        return nom_;
    }
    virtual int get_degats(){return 0;};
    virtual ~Objet(){};
};

class Arme : public Objet
{
protected:
    int degats_;
public:
    Arme(std::string nom, int degats, int valeur) : Objet(nom, valeur)
    {
        degats_ = degats;
    }
    int get_degats() override
    {
        return degats_;
    }
};

const std::array<std::shared_ptr<Objet>, 11> objets_existants = {
    std::make_shared<Objet>("Potion de soin", 10),
    std::make_shared<Objet>("Potion de force", 10),
    std::make_shared<Arme>("Epée d'Edmond", 5, 5),
    std::make_shared<Arme>("Epée en bois", 10, 10),
    std::make_shared<Arme>("Epée en fer", 20, 20),
    std::make_shared<Arme>("Epée en acier", 30, 30),
    std::make_shared<Arme>("Epée en diamant", 40, 40),
    std::make_shared<Objet>("Viande de loup", 5),
    std::make_shared<Objet>("Peau de loup", 5),
    std::make_shared<Objet>("Viande d'ours", 5),
    std::make_shared<Objet>("Peau d'ours", 10)
};

class Inventaire
{
protected:
    std::vector<std::shared_ptr<Objet>> liste_;
    int contenance_;
public:
    int argent;
    Inventaire(int contenance)
    {
        contenance_ = contenance;
    }
    void ajouter(std::string nom_objet)
    {
        if (liste_.size() < contenance_)
        {
            for(std::shared_ptr<Objet> x : objets_existants)
            {
                Objet objet = *x;
                if (objet.nom() == nom_objet)
                {
                    liste_.push_back(x);
                    objet.afficher();
                    std::cout <<" a été ajouté à votre inventaire" <<std::endl;
                    break;
                }
            }
        }
        else
        {
            std::cout <<"Votre inventaire est plein" <<std::endl;
            std::cout <<"Voulez-vous supprimer un objet pour faire de la place ? Mettre 0 si non" <<std::endl;
            this->afficher();
            int reponse;
            if(reponse == 0)
            {
                return;
            }
            else if (reponse-1 <= liste_.size())
            {
                this->supprimer(liste_[reponse-1]);
                ajouter(nom_objet);
            }

        }
    }
    void supprimer(std::shared_ptr<Objet> objet)
    {
        for (int i=0; i<liste_.size(); i++)
        {
            if (*liste_[i] == *objet)
            {
                liste_.erase(liste_.begin()+i);
                break;
            }
        }
    }
    void afficher()
    {
        for (int i=0; i<liste_.size(); i++)
        {
            std::cout <<i <<std::endl;
            liste_[i]->afficher();
        }
    }
    void vider()
    {
        liste_.clear();
    }
    std::shared_ptr<Objet> choisir_objet()
    {
        int choix;
        std::cout <<"Quel objet voulez-vous utiliser ? Indiquez son numéro" <<std::endl;
        std::cin >>choix;
        while (choix < 0 || choix > liste_.size())
        {
            std::cout <<"Veuillez choisir un objet valide" <<std::endl;
            std::cin >>choix;
        }
        return liste_[choix];
    }
    void vendre(std::string nom_objet)
    {
        for (int i=0; i<liste_.size(); i++)
        {
            if (liste_[i]->nom() == nom_objet)
            {
                int gain = liste_[i]->get_valeur();
                argent += gain;
                supprimer(liste_[i]);
                std::cout <<"Vous avez vendu " <<nom_objet <<" pour " <<gain <<" pièces d'or" <<std::endl;
                break;
            }
        }
    }
    std::shared_ptr<Objet> get_objet(std::string nom_objet)
    {
        for (std::shared_ptr<Objet> x : liste_)
        {
            if (x->nom() == nom_objet)
            {
                return x;
            }
        }
    }
    std::shared_ptr<Objet> get_objet(int index)
    {
        return liste_[index];
    }
};



