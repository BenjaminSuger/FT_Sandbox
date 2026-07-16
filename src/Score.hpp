#pragma once

#include <string>
#include <vector>

struct Player {
    std::string name;
    int rating;
};

namespace Score {
// Elo classique, K=32. Retourne le NOUVEAU rating du joueur.
int computeElo(int playerRating, int opponentRating, bool won);

// 3 à 20 caractères, alphanumériques + underscore uniquement.
bool isValidUsername(const std::string &name);

// TODO: exercice 3 — à implémenter
// Doit retourner le classement trié par rating décroissant,
// et à rating égal, par nom alphabétique croissant.
std::vector<Player> rank(const std::vector<Player> &players);
} // namespace Score
