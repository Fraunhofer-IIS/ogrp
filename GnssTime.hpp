//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     GnssTime.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

namespace ogrp {
    /**
     * BeiDou Time (strictly monotonic)
     *
     * Native GNSS time in week and time-of-week in milliseconds. No leap seconds for
     * GPS/Galileo/BeiDou; GLONASS is UTC-like.
     *
     * GPS Time (strictly monotonic)
     *
     * Galileo System Time (strictly monotonic)
     */

    using nlohmann::json;

    /**
     * BeiDou Time (strictly monotonic)
     *
     * Native GNSS time in week and time-of-week in milliseconds. No leap seconds for
     * GPS/Galileo/BeiDou; GLONASS is UTC-like.
     *
     * GPS Time (strictly monotonic)
     *
     * Galileo System Time (strictly monotonic)
     */
    struct GnssTime {
        /**
         * Clock drift in ns/s. Positive means GNSS time is faster than receiver clock.
         */
        std::optional<double> drift_ns_per_s;
        /**
         * Number of leap seconds (GNSS-UTC) applicable at this epoch.
         */
        std::optional<int64_t> leap_seconds_utc;
        /**
         * Clock offset in nanoseconds. Positive means GNSS time is ahead of receiver clock.
         */
        std::optional<double> offset_ns;
        /**
         * Number of week rollovers since GNSS system epoch (e.g., GPS epoch: January 6, 1980).
         */
        std::optional<int64_t> rollovers;
        /**
         * Time of week in milliseconds.
         */
        int64_t tow_ms;
        /**
         * Week number since GNSS system epoch. Maximum depends on GNSS system.
         */
        int64_t week;
    };
}
