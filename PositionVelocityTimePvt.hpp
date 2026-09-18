//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     PositionVelocityTimePvt.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "CovarianceMatrices.hpp"
#include "GeodeticDatum.hpp"
#include "CartesianPosition.hpp"
#include "Time.hpp"
#include "CartesianVelocity.hpp"

namespace ogrp {
    /**
     * Position and velocity refer to earth-centered, earth-fixed cartesian coordinate system
     * defined by `datum`.
     */

    using nlohmann::json;

    /**
     * Position and velocity refer to earth-centered, earth-fixed cartesian coordinate system
     * defined by `datum`.
     */
    struct PositionVelocityTimePvt {
        std::optional<std::string> algorithm;
        std::optional<CovarianceMatrices> covariance;
        GeodeticDatum datum;
        std::string fix;
        CartesianPosition position;
        Time time;
        std::optional<CartesianVelocity> velocity;
    };
}
