#include <iostream>
#include <string>
#include "inventaire.hpp"
#include "random.hpp"
#include "combat.hpp"
#include "personnage.hpp"
#include <map>
#include <string_view>
#include <array>

//Dictionnaire de correpondance.at(des codes his)oires la clé est le code_histoire, la valeur est un tableau de 4 entiers avec les code_histoires accessible dans l'ordre suivant [Nord, Ouest, Sud, Est], on met -1 si ce n'est pas possible
//exemple : 0 -> [1, -1, -1, 6]
const std::map<int, std::array<int, 4>> correpondance= {
    {0, {1, -1, -1, 6}},
    {1, {2, -1, -1, 6}},
    {2, {2, -1, -1, 6}},
    {3,{-1, 4, -1, -1}},
    {4, {-1, -1, -1, -1}},
    {5, {-1, 11, 13, -1}},
    {6, {-1, -1, 7, 1}},
    {7, {-1, -1, 8, -1}},
    {8, {-1, -1, -1, -1}},
    {9, {-1, -1, -1, -1}},
    {10, {-1, -1, -1, -1}},
    {11, {-1, -1, -1, -1}},
    {12, {14, -1, 13, 11}},
    {13, {12, -1, -1, -1}},
    {14, {-1, -1, -1, -1}},
    {15, {-1, -1, -1, -1}}
};
const std::map<std::string, int> code_direction = {
    {"Nord", 0},
    {"Ouest", 1},
    {"Sud", 2},
    {"Est", 3}
};


void action(std::shared_ptr<Personnage> heros,std::string commande, int& code_histoire)
{
    while ((commande != "Nord" && commande !="Ouest" && commande !="Sud" && commande !="Est") || correpondance.at(code_histoire)[code_direction.at(commande)] == -1)
    {
        std::cout <<"Vous ne pouvez pas aller dans cette direction ou la commande est invalide" <<std::endl;
        std::cout <<"Rappel, les commandes valides sont : Nord, Ouest, Sud, Est, Inventaire, Quitter" <<std::endl;
        std::cin >>commande;
    }
    if (commande == "Nord" && correpondance.at(code_histoire)[0] != -1)
    {
        code_histoire = correpondance.at(code_histoire)[0];
    }
    else if (commande == "Ouest" & correpondance.at(code_histoire)[1] != -1)
    {
        code_histoire = correpondance.at(code_histoire)[1];
    }
    else if (commande == "Sud" & correpondance.at(code_histoire)[2] != -1)
    {
        code_histoire = correpondance.at(code_histoire)[2];
    }
    else if (commande == "Est" & correpondance.at(code_histoire)[3] != -1)
    {
        code_histoire = correpondance.at(code_histoire)[3];
    }
    else if (commande == "Inventaire")
    {
        bool sortir = false;
        while(not sortir)
        {
            gestion_inventaire(heros);
            std::cout <<"Voulez-vous sortir de l'inventaire ?" <<std::endl;
            std::string reponse;
            std::cin >>reponse;
            if (reponse == "oui")
            {
                sortir = true;
            }
        }
    }
    else if (commande == "Quitter")
    {
        std::cout <<"A bientôt" <<std::endl;
        exit(0);
    }
}


void catalogue(std::shared_ptr<Personnage> heros, int& code_histoire, bool& echec_enigme)
{
   std::string commande;
   if (code_histoire==0)
   {
        std::cout <<"Vous vous reveillez après une bonne nuit de sommeil dans une chambre, cela semble être la votre" <<std::endl;
        std::cout <<"L'ambiance est sombre et pesante, vous entendez du bruit en bas, ces voix vous sont familières ce sont vos amis de toujours Edmond et Paolina" <<std::endl;
        std::cout <<"Vous decidez de descendre. La lumière vous éblouie et vous voyez vos deux amis entrain de se disputer" <<std::endl;
        std::cout <<"Edmond : Je te dis que c'est trop dangereux ! Or de question que j'y aille" <<std::endl;
        std::cout <<"Paolina : Mais enfin on ne peut pas l'abandonner comme ça !" <<std::endl;
        std::cout <<"Ils remarquent enfin votre présence" <<std::endl;
        std::cout <<"Paolina : Ah " << heros->nom() <<" te voilà. Un évènement terrible est arrivé !" <<heros->crush() <<" a été enlevé. Nous étions tous les trois à la recherche de bois pour ce soir quand le dragon Zvanar a surgit et l'a saisit. Nous devons aller à son secours" <<std::endl;
        std::cout <<heros->crush() <<"! C'est terrible ! Vous êtes fou amoureux de " <<heros->crush() <<std::endl;
        std::cout <<"Edmond : Zvanar est un serviteur du clan des Hylites. Les attaquer est beaucoup trop dangereux et risquerais de provoquer une guerre" <<std::endl;
        std::cout <<"Malgré le risque vous devez partir à sa recherche. Edmond est agacé mais vous tend une epée" <<std::endl;
        heros->inventaire().ajouter("Epée d'Edmond");
        heros->set_arme(heros->inventaire().get_objet("Epée d'Edmond"));
        std::cout <<"Edmond : c'est complètement inconcient mais ça le serait encore plus d'y aller sans arme. Je vous attendrai ici et veillerai sur vous" <<std::endl;
        std::cout <<"Paolina : Ne trainons pas. Nous devons nous rendre au chateau pour demander de l'aide au Roi" <<std::endl;
        std::cout <<"Vous sortez de la maison avec Paolina" <<std::endl;
        std::cout <<"Le chateau est au Nord mais on pourrais également aller rendre visite au Professeur qui habite à l'Est" <<std::endl;
    }
    else if (code_histoire==1)
    {
        std::cout << "Vous arrivez au centre du village. C'est paisible, l'eau coule calmement dans la fontaine. Un panneau indique que le chateau se trouve droit devant au Nord, votre Maison au Sud, celle du Professeur à l'Est" <<std::endl;
    }
    else if (code_histoire==2)
    {
        std::cout <<"Vous arrivez au chateau. Il est imposant et majestueux. Les gardes vous arrêtent" <<std::endl;
        std::cout <<"Garde : Halte ! Que venez-vous faire ici ? Si vous voulez passer il va falloir nous donner le mot de passe" <<std::endl;
        std::cout <<"Paolina : Le mot de passe ? Mais nous n'en avons pas. Nous sommes ici pour une mission de la plus haute importance, nous devons absolument nous entretenir avec le Roi" <<std::endl;
        std::cout <<"Garde : Je suis désolé mais sans mot de passe je ne peux pas vous laisser passer. En revanche ce mot de passe est la solution à une énigme. Vous pouvez tenter votre chance" <<std::endl;
        std::cout <<"Paolina : Une énigme ? Mais nous n'avons pas le temps pour ça" <<std::endl;
        std::cout <<"Garde : C'est ça ou vous ne passez pas" <<std::endl;
        std::cout <<"Paolina : Bon d'accord. Quelle est cette énigme ?" <<std::endl;
        std::cout <<"Garde : Je suis grand quand je suis jeune et petit quand je suis vieux. Je rayonne de vie et le vent est mon plus grand ennemi. Que suis-je ?" <<std::endl;
        std::string reponse;
        std::cin >>reponse;
        if(reponse=="une bougie" or reponse=="bougie")
        {
            std::cout <<"Garde : C'est exact. Vous pouvez passer" <<std::endl;
            std::cout <<"Vous entrez dans le chateau" <<std::endl;
            code_histoire = 3;
            commande = "NPDLMAJ";
        }
        else
        {
            std::cout <<"Garde : Ce n'est pas la bonne réponse. Vous ne passerez pas" <<std::endl;
            std::cout <<"Vous êtes renvoyé au centre du village" <<std::endl;
            echec_enigme = true;
            std::cout <<"Paolina : Le chateau est au Nord mais on pourrais également aller rendre visite au Professeur qui habite à l'Est, il pourrait peut-être nous aider" <<std::endl;
        }
    }
    else if(code_histoire==3)
    {
        std::cout <<"Vous pénétrez dans le chateau. La décoration est sompteuse, alors que vous vous appretez à rentrez dans la salle du trône, un vieil homme vous arrête" <<std::endl;
        std::cout <<"Vieil homme : Faites bien attention à vous jeunes gens, les apparences sont parfois trompeuses, vos amis pourrait bien se révéler être vos pires ennemis" <<std::endl;
        std::cout <<"Vous décidez de continuer votre route sans trop porter attention à cette discution étrange" <<std::endl;
        std::cout <<"Les portes de la salle du trone s'ouvrent et vous rentrez. Le Roi est assis sur son trône, il n'a pas remarqué votre présence. Paolina s'avance devant lui" <<std::endl;
        std::cout <<"Paolina : Votre Majesté, nous avons besoin de votre aide. " <<heros->crush() <<" a été enlevé par le dragon Zvanar et nous avons besoin de votre aide pour le sauver" <<std::endl;
        std::cout <<"Le Roi : Vous me mettez dans une situation difficile, jeune fille. Zvanar est un serviteur du clan des Hylites. La paix entre nos deux maisons est un équilibre fragile, obtenu après des siècles de guerre. Je ne peux m'engager dans une mission frontale contre les Hylites. Je peux en revanche vous indiquer un vieil ami, il est chef d'une troupe de mercenaire, ils accepterons surement de vous aider, mais pas gratuitement. Leur camp se trouve à l'Ouest, ce passage vous permettra de vous y rendre plus rapidment" <<std::endl;
        std::cout <<"Il vous montre alors un passage dérobé dans la salle du trône. Vous remerciez le Roi et vous dirigez prudemment dans ce sombre tunnel" <<std::endl;
        std::cout <<"Vous avancez à taton dans le tunnel, la lumière qui s'échappe de votre cierge est faible et vous ne voyez pas grand chose. Vous arrivez à une intersection" <<std::endl;
        //possibilité de combat ici
        std::cout <<"Vous avez la possibilité de continuer tout droit vers l'Ouest ou de tourner à droite vers le Nord" <<std::endl;
    }
    else if (code_histoire==4)
    {
        std::cout <<"Décidés à trouver le camp de mercenaire indiquez par le Roi, vous continuez votre route vers l'Ouest" <<std::endl; 
        std::cout <<"Alors que vous déambulez dans le tunnel, vous entendez des bruits étranges, un squelette surgit et engage le combat" <<std::endl;
        bool mort = combat(heros, monstres[5]);
        if (mort){ revive(heros);}
        while (heros->PV > 100){heros->level_up();}
        std::cout <<"Après avoir marché un bon moment, vous arrivez en face d'une porte verouillée" <<std::endl;
        std::string reponse;
        std::cin >>reponse;
        if(reponse=="attaquer")
        {  
            int degats = heros->attaque_brute();
            if (degats > 10)
            {
                std::cout <<"Vous avez réussi à enfoncer la porte" <<std::endl;
            }
            else
            {
                std::cout <<"Vous ouvrez la porte mais vous vous blessez avec votre épee. Vous perdez 5 PV" <<std::endl;
                heros->PV -= 5;
            }
            code_histoire = 5;
            commande = "NPDLMAJ";

        }
        else if(reponse=="crocheter")
        {
            std::cout <<"Vous avez réussi à crocheter la porte" <<std::endl;
            code_histoire = 10;
            commande = "NPDLMAJ";

        }
        else if(reponse=="bruler")
        {
            std::cout <<"Vous avez réussi à bruler la porte. Mais vous vous blessez le pouce. Vous perdez 2 PV" <<std::endl;
            heros->PV -= 2;
            code_histoire = 10;
            commande = "NPDLMAJ";
        }
    }
    else if (code_histoire==5)
    {
        std::cout <<"Vous arrivez au camp de mercenaire. Il est composé de plusieurs tentes et d'un feu de camp" <<std::endl;
        std::cout <<"Vous vous approchez du feu de camp et un homme vous interpelle" <<std::endl;
        std::cout <<"Homme : Qui êtes-vous ?" <<std::endl;
        std::cout <<"Paolina : Nous sommes des amis du Roi. Nous avons besoin de votre aide pour sauver " <<heros->crush() <<" qui a été enlevé par le dragon Zvanar" <<std::endl;
        std::cout <<"Homme : Le Roi ? Il nous doit de l'argent. Nous ne bougerons pas le petit doigt tant qu'il ne nous aura pas remboursé" <<std::endl;
        std::cout <<"Paolina : Mais nous n'avons pas d'argent" <<std::endl;
        std::cout <<"Homme : Alors nous ne bougerons pas le petit doigt" <<std::endl;
        std::cout <<"Vous: J'aimerais parler à votre chef" <<std::endl;
        std::cout <<"L'homme est de mauvais humeur mais il accepte de vous conduire à sa tente" <<std::endl;
        std::cout <<"Chef : Que me vaut l'honneur de votre visite ?" <<std::endl;
        std::cout <<"Paolina : Nous avons besoin de votre aide. " <<heros->crush() <<" a été enlevé par le dragon Zvanar" <<std::endl;
        std::cout <<"Nous pourrions vous aider mais nous sommes des mercenaires, nous ne faisons rien gratuitement. Le Roi nous doit de l'argent, si vous nous en apportez, nous vous aiderons" <<std::endl;
        std::cout <<"Vous n'avez pas suffisament d'argent pour payer les mercenaires. Mais Paolina vous indique que vous pourriez chasser des créatures et les vendre au marchand du village" <<std::endl;
        std::cout <<"Une plaine de chasse se trouve à l'Ouest et le marchand se trouve au Sud" <<std::endl;
    }
    else if (code_histoire==6)
    {
        std::cout <<"Vous arrivez devant la maison du Professeur. Elle est grande et imposante. Vous frappez à la porte et un homme vous ouvre" <<std::endl;
        std::cout <<"Professeur : Bonjour, que puis-je faire pour vous ? Oh mais c'est mes petits Paolina et" <<heros->nom() <<"! Rentrez je vous prie, je suis heureux de vous voir, vous avez tellement grandi" <<std::endl;
        std::cout <<"Vous entrez dans la maison du Professeur. Le salon ressemble plus à une bibliothèque fusioné avec un atelier d'alchimiste qu'a un endroit où on prendrait le thé mais le professeur vous fait signe de vous asseoir sur un vieux canapé style Louis 15 et apporte un plateau avec des biscuit et 3 tasses de thé" <<std::endl;
        std::cout <<"Le proffesseur vous propose des gateaux, ils ont un aspect étrange" <<std::endl;
        std::string reponse;
        std::cin >>reponse;
        if(reponse=="accepter" or reponse=="oui")
        {
            std::cout <<"Vous acceptez les gateaux. Ils ont un gout étrange mais vous sentez que se ne sont pas des gateau ordianaire, ils ont changé quelque chose en vous" <<std::endl;
            heros->force += 3;
            heros->max_PV += 5;
            heros->PV = heros->max_PV;
            std::cout <<"Vous vous sentez plus fort (votre force à augmenté de 3)" <<std::endl;
            std::cout <<"Vous vous sentez plus résistant (votre vie à augmenté de 5)" <<std::endl;

        }
        else
        {
            std::cout <<"Vous refusez la propostition du professeur, il est décu mais ne vous en tiens pas rigueur" <<std::endl;
        }
        std::cout <<"Professeur : Alors que me vaut l'honneur de votre visite ?" <<std::endl;
        std::cout <<"Paolina : Nous avons besoin de votre aide. " <<heros->crush() <<" a été enlevé par le dragon Zvanar" <<std::endl;
        if(echec_enigme)
        {
           std::cout <<"Paolina : Nous voulions demander de l'aide au Roi mais nous avons échoué à l'énigme du garde du chateau" <<std::endl;
           std::cout <<"Professeur : Hum je vois. Je peux vous aider à résoudre cette énigme, la réponse est une bougie cependant je pense que le Roi ne vous sera d'aucune aide, c'est un couard, vous n'obtiendrez rien de lui" <<std::endl;
        }
        else
        {
            std::cout <<"Paolina : Nous voulions demander de l'aide au Roi mais nous nous sommes dit que vous pouriez nous donner des conseils dans notre quête au préalable" <<std::endl;
            std::cout <<"Professeur : Je pense que le Roi ne vous sera d'aucune aide, c'est un couard, vous n'obtiendrez rien de lui" <<std::endl;
        }
        std::cout <<"Paolina : Alors que pouvons-nous faire ?" <<std::endl;
        std::cout <<"Professeur : Je sais où se terre le dragon Zvanar. Je peux vous y conduire mais il vous faudra être fort pour le vaincre, il existe un peuple au Sud, les gobelins qui entretiennent une relation particulière avec le clan des Hylites" <<std::endl;
        std::cout <<"Professeur : Autrefois ces deux peuples étaient meilleurs amis mais la tentative des Hylites de réduire les gobelins en esclavage a mis fin à cette amitié. Les gobelins connaissent tous les secret des Hylites et de leur arme maitraisse Zvanar. Leur rancoeur envers les Hylites pourrait les pousser à vous aider." <<std::endl;
        std::cout <<"Professeur : Si vous arrivez à les convaincre de vous aider, je me joindrais à vous pour la bataille finale contre Zvanar" <<std::endl;
        std::cout <<"Vous remerciez le professeur et quittez sa maison" <<std::endl;
    }
    else if(code_histoire==7)
    {
        std::cout <<"Vous arrivez au village des gobelins. Il est composé de plusieurs huttes et d'un feu de camp" <<std::endl;
        std::cout <<"Vous vous approchez du feu de camp et un gobelin vous interpelle" <<std::endl;
        std::cout <<"Gobelin : Qui êtes-vous ?" <<std::endl;
        std::cout <<"Paolina : Nous sommes des amis du Professeur. Nous avons besoin de votre aide pour sauver " <<heros->crush() <<" qui a été enlevé par le dragon Zvanar" <<std::endl;
        std::cout <<"Gobelin : Zvanar ! Ce dragon est un monstre ! Tout comme ses maîtres les Hylites. Nous ne pouvons pas les laisser faire. Nous vous aiderons mais il faudra nous aider en retour, la fille du chef a disparu dans la forêt au Sud du village, nous ne sommes pas assez grand nous gobelins pour la chercher efficacement dans cette forêt" <<std::endl;
        std::cout <<"Si vous la trouvez, le chef ne pourra refuser de vous aider !" <<std::endl;
    }
    else if(code_histoire==8)
    {
        std::cout <<"Vous arrivez dans la forêt. Elle est sombre et inquiétante. Vous entendez des bruits étranges" <<std::endl;
        labyrinth(heros);
        std::cout <<"Vous avez trouvé la fille du chef des gobelins. Elle est blessée" <<std::endl;
        std::cout <<"Vous la ramenez au village des gobelins" <<std::endl;
        std::cout <<"Gobelin : Vous avez retrouvé ma fille ! Vous avez notre reconnaissance éternelle. Nous allons vous aidez à trouver et combattre Zvanar" <<std::endl;
        std::cout <<"Je reunis un petit groupe d'homme et nous allons pouvoir partir en direction de son antre, si nous sommes suffisament discret nous pourrions récupérer votre ami sans combattre" <<std::endl;
        std::cout <<"Vous partez en direction de l'antre de Zvanar" <<std::endl;
    }
    else if(code_histoire==9)
    {
        std::cout <<"Vous arrivez devant l'antre de Zvanar. Il est imposant et effrayant. Les gobelins vous font signe de vous cacher" <<std::endl;
        std::cout <<"Gobelin : Zvanar est là, il est en train de dormir. Nous allons devoir être très discret pour ne pas le réveiller" <<std::endl;
        std::cout <<"Vous avancez prudemment dans la grotte. Vous voyez " <<heros->crush() <<" attaché à un poteau" <<std::endl;
        bool discret = heros->discret();
        if (discret)
        {
            std::cout <<"Vous vous approchez de lui et le détachez" <<std::endl;
            std::cout <<"Vous sortez de la grotte avec " <<heros->crush() <<" et les gobelins" <<std::endl;
        }
        else
        {
            std::cout <<"Vous avez réveillé Zvanar" <<std::endl;
            std::cout <<"Zvanar : Qui ose me déranger dans mon sommeil ?" <<std::endl;
            std::cout <<"Vous vous préparez au combat" <<std::endl;
            Monstre Zvanar = monstres[6];
            bool mort = combat(heros, Zvanar);
            if (mort)
            {
                std::cout <<"Vous avez été vaincu par Zvanar" <<std::endl;
                std::cout <<"VMais alors que vous pensez que tout espoir de sauver" <<heros->crush() <<"s'évanouit. Le professeur surgit et terasse Zvanar vous sauvant par la même ocassion" <<std::endl;
                (*heros).PV = (*heros).max_PV;
                (*heros).modifier_argent(-(*heros).argent()/2);
            }
            std::cout <<"Vous avez vaincu Zvanar" <<std::endl;
            std::cout <<"Vous détachez" <<heros->crush() <<"et sortez de la grotte avec " <<heros->crush() <<" et les gobelins" <<std::endl;
        }
        std::cout <<heros->crush() <<"est sous le choc et ne parle pas. Vous faites de votre mieux pour l'apaiser" <<std::endl;
        std::cout <<"Vous rentrez au village des gobelins" <<std::endl;
        std::cout <<"Vous remerciez chaleureusement les Gobelins pour leur aide et leur promettez de revenir les voir" <<std::endl;
        std::cout <<"Vous partez en direction de la maison du Professeur" <<std::endl;
        std::cout <<"Professeur : Vous êtes revenus ! Vous avez réussi à sauver " <<heros->crush() <<" ! Je suis si fier de vous" <<std::endl;
        std::cout <<"Professeur : Oh mais je vois que" <<heros->crush() <<"n'est pas en grande forme. Je vais lui préparer une potion" <<std::endl;
        std::cout <<"Le Professeur tend une potion à" <<heros->crush() <<" qui la boit d'un coup. Vous voyez son visage se réilluminer et reprendre ses esprits" <<std::endl;
        std::cout <<heros->crush() <<" : Merci à tous. Je ne sais pas ce que j'aurais fait sans vous. J'ai eu si peur de terminer mes jours dans cette antre. Rentrons chez" <<heros->nom() <<"désormais" <<std::endl;
        std::cout <<"Vous vous mettez en route vers votre maison" <<std::endl;
        code_histoire = 10;
        commande = "NPDLMAJ";
    }
    else if(code_histoire==10)
    {
        std::cout <<"Vous apercevez votre petit maison au loin, qu'il est bon de retrouvez un endroit familier après tant d'aventures" <<std::endl;
        std::cout <<"Edmond est là, il vous attendait. Son visage s'illumine en vous voyant, il est soulagé, vous n'avez pas déclenché de guerre avec les Hylites" <<std::endl;
        std::cout <<"Edmond : Vous êtes revenus ! Vous avez réussi à sauver " <<heros->crush() <<" ! Je suis si fier de vous. Fêtons ça autour d'un bon repas" <<std::endl;
        std::cout <<"Vous rentrez dans la maison et vous vous asseyez autour de la table. Edmond apporte des farandoles de plats que vous dégustez avec joie" <<std::endl;
        std::cout <<"Après un bon moment à parler, manger et boire, vous emmenez" <<heros->crush() <<"à l'extérieur pour regarder les étoiles" <<std::endl;
        std::cout <<"Vous vous allongez dans l'herbe et regardez le ciel étoilé" <<std::endl;
        std::cout <<"Vous vous tournez vers" <<heros->crush() <<"et lui murmurez" <<std::endl;
        std::cout <<"Je suis si soulagé que tu sois en sécurité" <<std::endl;
        std::cout <<"Vous vous endormez dans les bras l'un de l'autre" <<std::endl;
        std::cout <<"THE END" <<std::endl;
        commande = "NPDLMAJ";
    }
    else if(code_histoire==11)
    {
        std::cout <<"Vous arrivez dans une plaine et parcourez les hautes herbes à la recherche de créatures à chasser" <<std::endl;
        bool fin = false;
        while (!fin)
        {
            std::cout <<"Vous apercevez une créature" <<std::endl;
            int i = rand() % 6;
            bool mort = combat(heros, monstres[4]);
            if (mort){ revive(heros);}
            while (heros->PV > 100){heros->level_up();}
            std::cout <<"Vous pouvez continuer de chassé en appuyant sur entrée ou retourner au campement a l'Est" <<std::endl;
            std::string commande;
            std::cin >>commande;
            if (commande == "Est")
            {
                fin = true;
            }
        }
        code_histoire=12;
        commande = "NPDLMAJ";

    }
    else if(code_histoire==12)
    {
        std::cout <<"Vous êtes de retour au camp des mercenaires. Vous pouvez aller voir le chef au Nord pour lui donner l'argent, le marchand pour vendre vos peaux au Sud ou aller chasser à l'Ouest" <<std::endl;
    }
    else if(code_histoire==13)
    {
        std::cout <<"Vous arrivez devant le marchand, il pourrait vous échanger de l'argent contre vos objets gagnés au combat" <<std::endl;
        while(true)
        {
        heros->inventaire().afficher();
        std::cout <<"Que voulez-vous vendre ?" <<std::endl;
        std::string objet;
        std::cin >>objet;
        heros->inventaire().vendre(objet);
        std::cout <<"Vous avez " <<heros->argent() <<" pièces d'or" <<std::endl;
        std::cout <<"Voulez-vous vendre autre chose ?" <<std::endl;
        std::string reponse;
        std::cin >>reponse;
        if(reponse=="non")
        {
            break;
        }
        }
    }
    else if(code_histoire==14)
    {
        std::cout <<"Vous vous présentez de nouveau devant le chef des mercenaires" <<std::endl;
        if(heros->argent() >= 100)
        {
            std::cout <<"Chef : Vous avez l'argent ?" <<std::endl;
            std::cout <<"Vous lui donnez l'argent" <<std::endl;
            heros->modifier_argent(-100);
            std::cout <<"Chef : Bien, nous vous aiderons à sauver " <<heros->crush() <<std::endl;
            std::cout <<"Suivez-moi nous partons" <<std::endl;
            code_histoire = 15;
            commande = "NPDLMAJ";
        }
        else
        {
            std::cout <<"Chef : Vous n'avez pas l'argent ? Alors houste ! Retournez d'où vous venez" <<std::endl;
            code_histoire = 12;
            commande = "NPDLMAJ";
        }
        
    }
    else if(code_histoire==15)
    {
        std::cout <<"Vous suivez le chef des mercenaires et son armée. Il vous mène devant une montagne" <<std::endl;
        std::cout <<"Là, le dragon Zvanar est posé, menaçant, il surveille la vallée, nul doute qu'il vous a vu arriver" <<std::endl;
        std::cout <<"Vous vous préparez au combat" <<std::endl;
        Monstre Zvanar = monstres[6];
        bool mort = combat(heros, Zvanar);
        if (mort)
        {
            std::cout <<"Vous avez été vaincu par Zvanar" <<std::endl;
            std::cout <<"Vous avez échoué à sauver " <<heros->crush() <<std::endl;
            std::cout <<"THE END" <<std::endl;
            exit(0);
        }
        std::cout <<"Vous avez vaincu Zvanar et par chance les Hylites n'ont pas été alertés" <<std::endl;
        std::cout <<"Vous penetrez dans la tanière de Zvanar et détachez " <<heros->crush() <<std::endl;
        std::cout <<heros->crush() <<"est sous le choc et ne parle pas. Vous faites de votre mieux pour l'apaiser" <<std::endl;
        std::cout <<"Vous remerciez les mercenaires et partez chacun de votre côté" <<std::endl;
        std::cout <<"Paolina :" <<heros->crush() <<" a besoin d'aide. Nous devrions aller voir le Professeur" <<std::endl;
        std::cout <<"Vous partez en direction de la maison du Professeur" <<std::endl;
        std::cout <<"Professeur : Vous ici ? Oh mais que s'est il passé. Venez mes chers enfants" <<std::endl;
        std::cout <<"Professeur : Oh mais je vois que" <<heros->crush() <<"n'est pas en grande forme. Je vais lui préparer une potion" <<std::endl;
        std::cout <<"Le Professeur tend une potion à" <<heros->crush() <<" qui la boit d'un coup. Vous voyez son visage se réilluminer et reprendre ses esprits" <<std::endl;
        std::cout <<heros->crush() <<" : Merci à tous. Je ne sais pas ce que j'aurais fait sans vous. J'ai eu si peur de terminer mes jours dans cette antre. Rentrons chez" <<heros->nom() <<"désormais" <<std::endl;
        std::cout <<"Vous vous mettez en route vers votre maison" <<std::endl;
        code_histoire = 10;
        commande = "NPDLMAJ";
    }

    if(commande != "NPDLMAJ")
    {
        std::cin >>commande;
    }
    action(heros, commande, code_histoire);
};



