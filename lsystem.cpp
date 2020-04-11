#include "lsystem.h"

#include <iostream>
#include <utility>
#include <exception>
#include <regex>

using std::make_pair;

LSystem::LSystem(string const &s, MapOneRuleType const &mo, MapNoRuleType const &mn) : stringS_(s), rules_1_arg_(mo),
                                                                                       rules_no_arg_(mn) {
}

bool LSystem::ParseRule(string const &str) {
    std::regex regex("(.+)=(.*):(.+)");
    std::smatch match;
    std::regex_match(str, match, regex);
    if (match.empty()) {
        return false;
    }
    std::cout << match.size() << '\n';
    for (auto &&el : match) {
        std::cout << el << ' ';
    }

    std::regex one_rule_regex("(.)\\((.)\\)");
    std::smatch temp;
    string function_match = match[1];
    if (std::regex_match(function_match, temp, one_rule_regex)) {
        std::string func_name = temp[1];
        std::string param_name = temp[2];
        std::string ret = match[3];
        auto condition = ParseCondition(match[2], param_name[0]);
        return AddRule(func_name[0], [condition, ret](char, bool &b, int x) -> string {
            b = condition(x);
            return ret;
        });
    } else {
        std::string ret = match[3];
        return AddRule(function_match.at(0), [ret](char) {
            return ret;
        });
    }
}

bool LSystem::AddRule(char c, OneRuleType const &r) {
    rules_1_arg_[c].push_back(r);
    return true;
}

bool LSystem::AddRule(char c, NoRuleType const &r) {
    return rules_no_arg_.insert(make_pair(c, r)).second;
}

LSystem::MapNoRuleType const &LSystem::ShowNoArg() const {
    return rules_no_arg_;
}

LSystem::MapOneRuleType const &LSystem::ShowOneArg() const {
    return rules_1_arg_;
}

void LSystem::SetString(string const &s) {
    stringS_ = s;
}

string const &LSystem::stringS() const {
    return stringS_;
}

void LSystem::Update() {
    string temp = "";

    for (int i = 0; i < stringS_.size(); i++) {
        char c = stringS_[i];

        string s = "";
        if (stringS_[i + 1] == '(') {
            auto it = rules_1_arg_.find(c);
            if (it == rules_1_arg_.cend()) {
                temp += c;
                continue;
            }

            bool ret = false;
            auto id = stringS_.find_first_of(')', i);
            if (id == string::npos) {
                throw std::runtime_error("no ).");
            }
            string sub = stringS_.substr(i + 2, (id - i - 1));
            int k = std::stoi(sub);
            for (auto j = it->second.cbegin(); !ret && j != it->second.cend(); ++j) {
                s = (*j)(c, ret, k);
            }
            i = id;
        } else {
            auto it = rules_no_arg_.find(c);

            if (it != rules_no_arg_.cend())
                s = it->second(c);
            else
                temp += c;
        }
        temp += s;
    }

    stringS_ = temp;
}

LSystem::ConditionType LSystem::ParseCondition(string const &str, char param_name) {
    return [](int) { return true; };
}
