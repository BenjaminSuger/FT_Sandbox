#include "Score.hpp"
#include "Database.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>

std::string getEnv(const std::string& key, const std::string& defaultValue = "") {
    const char* val = std::getenv(key.c_str());
    return val ? std::string(val) : defaultValue;
}

int main() {
    try {
        std::string host = getEnv("DB_HOST", "localhost");
        std::string port = getEnv("DB_PORT", "5432");
        std::string user = getEnv("DB_USER", "sandbox");
        std::string password = getEnv("DB_PASSWORD", "sandbox");
        std::string dbname = getEnv("DB_NAME", "sandbox");

        std::ostringstream oss;
        oss << "host=" << host << " port=" << port << " user=" << user
            << " password=" << password << " dbname=" << dbname;
        std::string conninfo = oss.str();

        Database db(conninfo);
        db.createSchema();

        db.addPlayer("Alice");
        db.addPlayer("Bob");
        db.addPlayer("Charlie");

        db.updateRating("Alice", Score::computeElo(1000, 1200, true));
        db.updateRating("Bob", Score::computeElo(1200, 1000, false));
        db.updateRating("Charlie", Score::computeElo(1000, 1000, true));

        auto players = db.fetchAll();
        std::cout << "\n=== Scoreboard ===\n";
        for (const auto& p : players) {
            std::cout << p.name << ": " << p.rating << "\n";
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
