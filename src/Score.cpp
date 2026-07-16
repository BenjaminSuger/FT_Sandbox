#include "Score.hpp"
#include <cmath>
#include <stdexcept>

int Score::computeElo(int playerRating, int opponentRating, bool won) {
    const int K = 32;
    double expected = 1.0 / (1.0 + std::pow(10.0, (opponentRating - playerRating) / 400.0));
    int actual = won ? 1 : 0;
    int delta = static_cast<int>(K * (actual - expected));
    return playerRating + delta;
}

bool Score::isValidUsername(const std::string &name) {
    if (name.length() < 3 || name.length() > 20)
        return false;
    for (char c : name) {
        if (!std::isalnum(c) && c != '_')
            return false;
    }
    return true;
}

std::vector<Player> Score::rank(const std::vector<Player> &players) {
    // TODO: exercice 3
    (void)players;
    throw std::runtime_error("rank() not implemented yet");
}
