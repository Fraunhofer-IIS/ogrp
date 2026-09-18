//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Generators.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "Message.hpp"

namespace ogrp {
    void from_json(const json & j, Message & x);
    void to_json(json & j, const Message & x);

    inline void from_json(const json & j, Message& x) {
        x.epoch = j.at("$epoch").get<std::string>();
        x.schema = j.at("$schema").get<std::string>();
    }

    inline void to_json(json & j, const Message & x) {
        j = json::object();
        j["$epoch"] = x.epoch;
        j["$schema"] = x.schema;
    }
}
