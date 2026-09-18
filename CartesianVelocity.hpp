//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     CartesianVelocity.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace ogrp {
    /**
     * Cartesian velocity in meters per second.
     */

    using nlohmann::json;

    /**
     * Cartesian velocity in meters per second.
     */
    struct CartesianVelocity {
        /**
         * X velocity in meters per second.
         */
        double vx;
        /**
         * Y velocity in meters per second.
         */
        double vy;
        /**
         * Z velocity in meters per second.
         */
        double vz;
    };
}
