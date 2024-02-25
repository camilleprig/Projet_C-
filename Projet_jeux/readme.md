Choix de conceptions:

## Gestion des embranchement d'histoire
J'ai décidé de faire une fonction catalogue qui a un code entier renvoie un bout d'histoire, selon la scène le joueur est ensuite en capacité de choisir une direction (Nord, Est, Sud, Ouest) parmis celles valides ce qui va venir modifier le code_histoire selon un dictionnaire de correspondance défini dans le programme. Si il n'y a pas d'embranchements possible à la fin de la scène la fonction ne permet pas à l'utilisateur de rentrer un choix

## Gestion de l'inventaire
Pour gérer l'inventaire j'ai crée une classe inventaire qui est composée d'une liste de shared_ptr<Objet> ( Objet étant une classe que j'ai défini au préalable ) et d'un entier représentant la contenance. J'ai implémenter plusisuers méthodes sur cette classe comme afficher, enlever et ajouter un objet. L'inventaire est géré de la manière suivante : la classe personnage possède un attribut qui est un pointeur vers un inventaire.

## Gestion de l'arme
La classe Arme hérite de la classe Objet, l'Arme du personnage est relié à lui par un pointeur qui est l'un de ses attributs. Au début je voulais faire un shared_ptr<Arme> dans la classe Personnage mais j'avais des problèmes de gestion des Armes dans l'inventaire je l'ai donc transformé en shared_ptr<Objet> mais comme mon programme ne compile pas je ne sais pas si c'est ce qu'il fallait faire.