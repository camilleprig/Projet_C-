#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "inventaire.hpp"
#include "random.hpp"
#include "personnage.hpp"

bool combat(std::shared_ptr<Personnage> heros, Monstre ennemi);

void revive(std::shared_ptr<Personnage> heros);

void labyrinth(std::shared_ptr<Personnage> heros);
