//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     CartesianPosition.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace ogrp {
    /**
     * Cartesian coordinates in meters.
     */

    using nlohmann::json;

    /**
     * Cartesian coordinates in meters.
     */
    struct CartesianPosition {
        /**
         * X coordinate in meters.
         */
        double x;
        /**
         * Y coordinate in meters.
         */
        double y;
        /**
         * Z coordinate in meters.
         */
        double z;
    };
}
