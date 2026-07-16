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
