#pragma once
#include <map>
#include "personnage.hpp" // Assuming the file is in the same directory as catalogue.hpp
#include "inventaire.hpp"
#include <memory>

void catalogue(std::shared_ptr<Personnage> heros, int& code_histoire, bool& echec_enigme);
void action(std::string commande, int& code_histoire);
const std::map<int, std::array<int, 4>> correpondance;