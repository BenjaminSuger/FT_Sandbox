#include <catch2/catch_test_macros.hpp>
#include "Database.hpp"
#include <cstdlib>
#include <string>

std::string getConninfo() {
    auto getEnv = [](const char* key, const char* defaultValue) -> std::string {
        const char* val = std::getenv(key);
        return std::string(val ? val : defaultValue);
    };

    std::string host = getEnv("DB_HOST", "localhost");
    std::string port = getEnv("DB_PORT", "5432");
    std::string user = getEnv("DB_USER", "sandbox");
    std::string password = getEnv("DB_PASSWORD", "sandbox");
    std::string dbname = getEnv("DB_NAME", "sandbox");

    std::string result = "host=" + host + " port=" + port + " user=" + user
                       + " password=" + password + " dbname=" + dbname;
    return result;
}

TEST_CASE("Database - connect and create schema", "[database]") {
    Database db(getConninfo());
    REQUIRE_NOTHROW(db.createSchema());
}

TEST_CASE("Database - add and fetch players", "[database]") {
    Database db(getConninfo());
    db.createSchema();

    db.addPlayer("test_player_1");
    auto players = db.fetchAll();

    REQUIRE(players.size() >= 1);
    bool found = false;
    for (const auto& p : players) {
        if (p.name == "test_player_1") {
            found = true;
            REQUIRE(p.rating == 1000);
            break;
        }
    }
    REQUIRE(found);
}

TEST_CASE("Database - update rating", "[database]") {
    Database db(getConninfo());
    db.createSchema();

    db.addPlayer("test_player_2");
    db.updateRating("test_player_2", 1500);

    auto players = db.fetchAll();
    bool found = false;
    for (const auto& p : players) {
        if (p.name == "test_player_2") {
            found = true;
            REQUIRE(p.rating == 1500);
            break;
        }
    }
    REQUIRE(found);
}
