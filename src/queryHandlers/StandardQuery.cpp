#include "StandardQuery.hpp"

StandardQuery::StandardQuery(nlohmann::json parsedQuery)
{
    if (!parsedQuery.contains("command"))
    {
        throw std::invalid_argument("[ERROR] 'command' is required.");
    }

    if (!parsedQuery.contains("key"))
    {
        throw std::invalid_argument("[ERROR] 'key' is required.");
    }

    cmd = stringToCommand(parsedQuery["command"].get<std::string>());
    key = parsedQuery["key"].get<std::string>();

    if (cmd == Command::set)
    {
        if (!parsedQuery.contains("value"))
        {
            throw std::invalid_argument("[ERROR] Invalid format: 'set' commands require a value.");
        }
        value = parsedQuery["value"].get<std::string>();
    }
    else if (parsedQuery.contains("value") && (cmd == Command::get || cmd == Command::del))
    {
        throw std::invalid_argument("[ERROR] 'value' is not required with 'get' or 'del' commands.");
    }
}

StandardQuery::Command StandardQuery::stringToCommand(const std::string &str)
{
    if (str == "get")
        return Command::get;
    if (str == "set")
        return Command::set;
    if (str == "del")
        return Command::del;

    throw std::invalid_argument("[ERROR] Invalid command");
}

std::string StandardQuery::commandToString(Command cmd) const
{
    switch (cmd)
    {
    case Command::get:
        return "get";
    case Command::set:
        return "set";
    case Command::del:
        return "del";
    default:
        return "unknown";
    }
}

std::string StandardQuery::getCommand() const
{
    return commandToString(cmd);
}

std::string StandardQuery::getKey() const
{
    return key;
}

std::string StandardQuery::getValue() const
{
    return value;
}