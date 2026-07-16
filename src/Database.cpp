#include "Database.hpp"
#include <iostream>
#include <pqxx/pqxx>

class Database::Impl {
  public:
    pqxx::connection conn;
    explicit Impl(const std::string &conninfo) : conn(conninfo) {}
};

Database::Database(const std::string &conninfo) : pimpl(std::make_unique<Impl>(conninfo)) {}

Database::~Database() = default;

void Database::createSchema() {
    pqxx::work txn(pimpl->conn);
    txn.exec("CREATE TABLE IF NOT EXISTS players ("
             "  id SERIAL PRIMARY KEY,"
             "  name TEXT UNIQUE NOT NULL,"
             "  rating INT NOT NULL DEFAULT 1000"
             ")");
    txn.commit();
}

void Database::addPlayer(const std::string &name) {
    pqxx::work txn(pimpl->conn);
    txn.exec_params("INSERT INTO players (name) VALUES ($1)", name);
    txn.commit();
}

void Database::updateRating(const std::string &name, int rating) {
    pqxx::work txn(pimpl->conn);
    txn.exec_params("UPDATE players SET rating = $1 WHERE name = $2", rating, name);
    txn.commit();
}

std::vector<Player> Database::fetchAll() {
    pqxx::work txn(pimpl->conn);
    auto result = txn.exec("SELECT name, rating FROM players");
    std::vector<Player> players;
    for (auto row : result) {
        players.push_back({row["name"].as<std::string>(), row["rating"].as<int>()});
    }
    return players;
}
