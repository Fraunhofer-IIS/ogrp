//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     CovarianceMatrix.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace ogrp {
    /**
     * Upper-triangular elements of a symmetric 4×4 covariance matrix for variables {t, x, y,
     * z}. Units must match the associated state components.
     */

    using nlohmann::json;

    /**
     * Upper-triangular elements of a symmetric 4×4 covariance matrix for variables {t, x, y,
     * z}. Units must match the associated state components.
     */
    struct CovarianceMatrix {
        /**
         * Variance (t)
         */
        double tt;
        /**
         * Covariance (x, t)
         */
        double xt;
        /**
         * Variance (x)
         */
        double xx;
        /**
         * Covariance (x, y)
         */
        double xy;
        /**
         * Covariance (x, z)
         */
        double xz;
        /**
         * Covariance (y, t)
         */
        double yt;
        /**
         * Variance (y)
         */
        double yy;
        /**
         * Covariance (y, z)
         */
        double yz;
        /**
         * Covariance (z, t)
         */
        double zt;
        /**
         * Variance (z)
         */
        double zz;
    };
}
