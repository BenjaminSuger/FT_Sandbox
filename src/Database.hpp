#pragma once

#include "Score.hpp"
#include <string>
#include <vector>
#include <memory>

class Database {
public:
    explicit Database(const std::string& conninfo);
    ~Database();

    void createSchema();
    void addPlayer(const std::string& name);
    void updateRating(const std::string& name, int rating);
    std::vector<Player> fetchAll();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};
