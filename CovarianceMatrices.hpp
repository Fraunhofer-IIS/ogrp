//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     CovarianceMatrices.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "CovarianceMatrix.hpp"
#include "VelocityCovarianceMatrix.hpp"

namespace ogrp {
    /**
     * Covariance matrices for position + time and velocity + time drift.
     */

    using nlohmann::json;

    /**
     * Covariance matrices for position + time and velocity + time drift.
     */
    struct CovarianceMatrices {
        CovarianceMatrix position;
        std::optional<VelocityCovarianceMatrix> velocity;
    };
}
