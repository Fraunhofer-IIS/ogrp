//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     VelocityCovarianceMatrix.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace ogrp {
    /**
     * Upper-triangular elements of a symmetric 4×4 covariance matrix for variables {dt, vx, vy,
     * vz}. Units must match the associated state components.
     */

    using nlohmann::json;

    /**
     * Upper-triangular elements of a symmetric 4×4 covariance matrix for variables {dt, vx, vy,
     * vz}. Units must match the associated state components.
     */
    struct VelocityCovarianceMatrix {
        /**
         * Variance (dt)
         */
        double dtdt;
        /**
         * Covariance (vx, dt)
         */
        double vxdt;
        /**
         * Variance (vx)
         */
        double vxvx;
        /**
         * Covariance (vx, vy)
         */
        double vxvy;
        /**
         * Covariance (vx, vz)
         */
        double vxvz;
        /**
         * Covariance (vy, dt)
         */
        double vydt;
        /**
         * Variance (vy)
         */
        double vyvy;
        /**
         * Covariance (vy, vz)
         */
        double vyvz;
        /**
         * Covariance (vz, dt)
         */
        double vzdt;
        /**
         * Variance (vz)
         */
        double vzvz;
    };
}
