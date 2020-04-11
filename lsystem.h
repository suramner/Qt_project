#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <map>
#include <functional>
#include <vector>
using namespace std;

using std::string;
using std::map;
using std::function;
using std::vector;


class LSystem
{
public:
    using OneRuleType = function<string(char, bool&, int)>;
    using NoRuleType = function<string(char)>;
    using MapOneRuleType = map<char, vector<OneRuleType>>;
    using MapNoRuleType = map<char, NoRuleType>;

    LSystem(string const& = "", MapOneRuleType const & = {}, MapNoRuleType const & = {});

    bool ParseRule(string const&);
    bool AddRule(char, OneRuleType const &);
    bool AddRule(char, NoRuleType const &);
    MapNoRuleType const &ShowNoArg() const;
    MapOneRuleType const &ShowOneArg() const;
    void SetString(string const &);
    string const& stringS() const;
    void Update();

private:
    using ConditionType = function<bool(int)>;
    ConditionType ParseCondition(string const&, char param_name);
    MapNoRuleType rules_no_arg_;
    MapOneRuleType rules_1_arg_;
    string stringS_;
};

#endif // LSYSTEM_H
