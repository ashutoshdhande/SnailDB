#ifndef STANDARDQUERY_HPP
#define STANDARDQUERY_HPP

#include <string>
#include <stdexcept>
#include <json.hpp>

class StandardQuery
{
public:
    StandardQuery(nlohmann::json parsedQuery);
    std::string getCommand() const;
    std::string getKey() const;
    std::string getValue() const;


private:
    enum Command
    {
        get,
        set,
        del
    };

    Command cmd;
    std::string key;
    std::string value;

    Command stringToCommand(const std::string &str);
    std::string commandToString(Command cmd) const;
};

#endif
