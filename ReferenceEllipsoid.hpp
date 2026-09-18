//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     ReferenceEllipsoid.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace ogrp {
    /**
     * Reference ellipsoid. If omitted, it is implied by reference frame (e.g., WGS84).
     */

    using nlohmann::json;

    /**
     * Reference ellipsoid. If omitted, it is implied by reference frame (e.g., WGS84).
     */
    struct ReferenceEllipsoid {
        /**
         * Semi-major axis a, meters.
         */
        double a;
        /**
         * Flattening f (unitless).
         */
        double f;
        /**
         * e.g., WGS84, GRS80
         */
        std::string name;
    };
}
