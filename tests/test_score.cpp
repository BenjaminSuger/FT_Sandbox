#include "Score.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Score::computeElo - victory against stronger opponent", "[elo]") {
    int playerRating = 1000;
    int opponentRating = 1200;
    int newRating = Score::computeElo(playerRating, opponentRating, true);
    REQUIRE(newRating > playerRating);
}

TEST_CASE("Score::computeElo - victory against weaker opponent", "[elo]") {
    int playerRating = 1200;
    int opponentRating = 1000;
    int newRating = Score::computeElo(playerRating, opponentRating, true);
    REQUIRE(newRating > playerRating);
    REQUIRE(newRating < playerRating + 20);
}

TEST_CASE("Score::computeElo - loss against stronger opponent", "[elo]") {
    int playerRating = 1000;
    int opponentRating = 1200;
    int newRating = Score::computeElo(playerRating, opponentRating, false);
    REQUIRE(newRating < playerRating);
    REQUIRE(newRating > playerRating - 20);
}

TEST_CASE("Score::computeElo - equal rating victory", "[elo]") {
    int playerRating = 1000;
    int opponentRating = 1000;
    int newRating = Score::computeElo(playerRating, opponentRating, true);
    REQUIRE(newRating == 1016);
}

TEST_CASE("Score::isValidUsername - valid names", "[username]") {
    REQUIRE(Score::isValidUsername("alice") == true);
    REQUIRE(Score::isValidUsername("alice_42") == true);
    REQUIRE(Score::isValidUsername("A") == false);
    REQUIRE(Score::isValidUsername("ab") == false);
    REQUIRE(Score::isValidUsername("abc") == true);
}

TEST_CASE("Score::isValidUsername - empty string", "[username]") {
    REQUIRE(Score::isValidUsername("") == false);
}

TEST_CASE("Score::isValidUsername - too long", "[username]") {
    REQUIRE(Score::isValidUsername("abcdefghijklmnopqrstuv") == false);
}

TEST_CASE("Score::isValidUsername - special characters", "[username]") {
    REQUIRE(Score::isValidUsername("alice-bob") == false);
    REQUIRE(Score::isValidUsername("alice bob") == false);
    REQUIRE(Score::isValidUsername("alice@bob") == false);
    REQUIRE(Score::isValidUsername("café") == false);
}

TEST_CASE("Score::rank - sorts by rating descending", "[rank]") {
    std::vector<Player> players = {{"Charlie", 1000}, {"Alice", 1800}, {"Bob", 1500}};
    std::vector<Player> ranked = Score::rank(players);
    REQUIRE(ranked.size() == 3);
    REQUIRE(ranked[0].name == "Alice");
    REQUIRE(ranked[1].name == "Bob");
    REQUIRE(ranked[2].name == "Charlie");
}

TEST_CASE("Score::rank - equal rating sorted by name ascending", "[rank]") {
    std::vector<Player> players = {{"Bob", 1500}, {"Alice", 1500}, {"Charlie", 1000}};
    std::vector<Player> ranked = Score::rank(players);
    REQUIRE(ranked.size() == 3);
    REQUIRE(ranked[0].name == "Alice");
    REQUIRE(ranked[0].rating == 1500);
    REQUIRE(ranked[1].name == "Bob");
    REQUIRE(ranked[1].rating == 1500);
    REQUIRE(ranked[2].name == "Charlie");
}

TEST_CASE("Score::rank - empty vector", "[rank]") {
    std::vector<Player> players;
    std::vector<Player> ranked = Score::rank(players);
    REQUIRE(ranked.empty());
}

TEST_CASE("Score::rank - single player", "[rank]") {
    std::vector<Player> players = {{"Alice", 1500}};
    std::vector<Player> ranked = Score::rank(players);
    REQUIRE(ranked.size() == 1);
    REQUIRE(ranked[0].name == "Alice");
    REQUIRE(ranked[0].rating == 1500);
}

TEST_CASE("Score::rank - does not modify input", "[rank]") {
    std::vector<Player> players = {{"Bob", 1500}, {"Alice", 1800}};
    Score::rank(players);
    REQUIRE(players[0].name == "Bob");
    REQUIRE(players[1].name == "Alice");
}
