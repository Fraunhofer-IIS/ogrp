//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Message.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "PositionVelocityTimePvt.hpp"

namespace ogrp {
    /**
     * The OGRP message is the base schema for all OGRP messages.
     */

    using nlohmann::json;

    /**
     * The OGRP message is the base schema for all OGRP messages.
     */
    struct Message {
        std::optional<PositionVelocityTimePvt> pvt;
        /**
         * Either UUIDv1 or UUIDv6 according to RFC9562. The Node ID should be the MAC address of
         * the GNSS receiver.
         */
        std::string epoch;
        /**
         * The schema of this OGRP message.
         */
        std::string schema;
    };
}
