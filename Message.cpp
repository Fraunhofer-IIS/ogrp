//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Message.cpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "CovarianceMatrix.hpp"
#include "VelocityCovarianceMatrix.hpp"
#include "CovarianceMatrices.hpp"
#include "ReferenceEllipsoid.hpp"
#include "GeodeticDatum.hpp"
#include "CartesianPosition.hpp"
#include "GnssTime.hpp"
#include "Time.hpp"
#include "CartesianVelocity.hpp"
#include "PositionVelocityTimePvt.hpp"
#include "Message.hpp"
namespace ogrp {
}
