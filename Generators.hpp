//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Generators.hpp data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include <nlohmann/json.hpp>
#include "helper.hpp"

#include "Message.hpp"
#include "PositionVelocityTimePvt.hpp"
#include "CartesianVelocity.hpp"
#include "Time.hpp"
#include "GnssTime.hpp"
#include "CartesianPosition.hpp"
#include "GeodeticDatum.hpp"
#include "ReferenceEllipsoid.hpp"
#include "CovarianceMatrices.hpp"
#include "VelocityCovarianceMatrix.hpp"
#include "CovarianceMatrix.hpp"

namespace ogrp {
    void from_json(const json & j, CovarianceMatrix & x);
    void to_json(json & j, const CovarianceMatrix & x);

    void from_json(const json & j, VelocityCovarianceMatrix & x);
    void to_json(json & j, const VelocityCovarianceMatrix & x);

    void from_json(const json & j, CovarianceMatrices & x);
    void to_json(json & j, const CovarianceMatrices & x);

    void from_json(const json & j, ReferenceEllipsoid & x);
    void to_json(json & j, const ReferenceEllipsoid & x);

    void from_json(const json & j, GeodeticDatum & x);
    void to_json(json & j, const GeodeticDatum & x);

    void from_json(const json & j, CartesianPosition & x);
    void to_json(json & j, const CartesianPosition & x);

    void from_json(const json & j, GnssTime & x);
    void to_json(json & j, const GnssTime & x);

    void from_json(const json & j, Time & x);
    void to_json(json & j, const Time & x);

    void from_json(const json & j, CartesianVelocity & x);
    void to_json(json & j, const CartesianVelocity & x);

    void from_json(const json & j, PositionVelocityTimePvt & x);
    void to_json(json & j, const PositionVelocityTimePvt & x);

    void from_json(const json & j, Message & x);
    void to_json(json & j, const Message & x);

    inline void from_json(const json & j, CovarianceMatrix& x) {
        x.tt = j.at("tt").get<double>();
        x.xt = j.at("xt").get<double>();
        x.xx = j.at("xx").get<double>();
        x.xy = j.at("xy").get<double>();
        x.xz = j.at("xz").get<double>();
        x.yt = j.at("yt").get<double>();
        x.yy = j.at("yy").get<double>();
        x.yz = j.at("yz").get<double>();
        x.zt = j.at("zt").get<double>();
        x.zz = j.at("zz").get<double>();
    }

    inline void to_json(json & j, const CovarianceMatrix & x) {
        j = json::object();
        j["tt"] = x.tt;
        j["xt"] = x.xt;
        j["xx"] = x.xx;
        j["xy"] = x.xy;
        j["xz"] = x.xz;
        j["yt"] = x.yt;
        j["yy"] = x.yy;
        j["yz"] = x.yz;
        j["zt"] = x.zt;
        j["zz"] = x.zz;
    }

    inline void from_json(const json & j, VelocityCovarianceMatrix& x) {
        x.dtdt = j.at("dtdt").get<double>();
        x.vxdt = j.at("vxdt").get<double>();
        x.vxvx = j.at("vxvx").get<double>();
        x.vxvy = j.at("vxvy").get<double>();
        x.vxvz = j.at("vxvz").get<double>();
        x.vydt = j.at("vydt").get<double>();
        x.vyvy = j.at("vyvy").get<double>();
        x.vyvz = j.at("vyvz").get<double>();
        x.vzdt = j.at("vzdt").get<double>();
        x.vzvz = j.at("vzvz").get<double>();
    }

    inline void to_json(json & j, const VelocityCovarianceMatrix & x) {
        j = json::object();
        j["dtdt"] = x.dtdt;
        j["vxdt"] = x.vxdt;
        j["vxvx"] = x.vxvx;
        j["vxvy"] = x.vxvy;
        j["vxvz"] = x.vxvz;
        j["vydt"] = x.vydt;
        j["vyvy"] = x.vyvy;
        j["vyvz"] = x.vyvz;
        j["vzdt"] = x.vzdt;
        j["vzvz"] = x.vzvz;
    }

    inline void from_json(const json & j, CovarianceMatrices& x) {
        x.position = j.at("position").get<CovarianceMatrix>();
        x.velocity = get_stack_optional<VelocityCovarianceMatrix>(j, "velocity");
    }

    inline void to_json(json & j, const CovarianceMatrices & x) {
        j = json::object();
        j["position"] = x.position;
        if (x.velocity) {
            j["velocity"] = x.velocity;
        }
    }

    inline void from_json(const json & j, ReferenceEllipsoid& x) {
        x.a = j.at("a").get<double>();
        x.f = j.at("f").get<double>();
        x.name = j.at("name").get<std::string>();
    }

    inline void to_json(json & j, const ReferenceEllipsoid & x) {
        j = json::object();
        j["a"] = x.a;
        j["f"] = x.f;
        j["name"] = x.name;
    }

    inline void from_json(const json & j, GeodeticDatum& x) {
        x.ellipsoid = get_stack_optional<ReferenceEllipsoid>(j, "ellipsoid");
        x.epoch = get_stack_optional<double>(j, "epoch");
        x.frame = j.at("frame").get<std::string>();
    }

    inline void to_json(json & j, const GeodeticDatum & x) {
        j = json::object();
        if (x.ellipsoid) {
            j["ellipsoid"] = x.ellipsoid;
        }
        if (x.epoch) {
            j["epoch"] = x.epoch;
        }
        j["frame"] = x.frame;
    }

    inline void from_json(const json & j, CartesianPosition& x) {
        x.x = j.at("x").get<double>();
        x.y = j.at("y").get<double>();
        x.z = j.at("z").get<double>();
    }

    inline void to_json(json & j, const CartesianPosition & x) {
        j = json::object();
        j["x"] = x.x;
        j["y"] = x.y;
        j["z"] = x.z;
    }

    inline void from_json(const json & j, GnssTime& x) {
        x.drift_ns_per_s = get_stack_optional<double>(j, "drift_ns_per_s");
        x.leap_seconds_utc = get_stack_optional<int64_t>(j, "leap_seconds_utc");
        x.offset_ns = get_stack_optional<double>(j, "offset_ns");
        x.rollovers = get_stack_optional<int64_t>(j, "rollovers");
        x.tow_ms = j.at("tow_ms").get<int64_t>();
        x.week = j.at("week").get<int64_t>();
    }

    inline void to_json(json & j, const GnssTime & x) {
        j = json::object();
        if (x.drift_ns_per_s) {
            j["drift_ns_per_s"] = x.drift_ns_per_s;
        }
        if (x.leap_seconds_utc) {
            j["leap_seconds_utc"] = x.leap_seconds_utc;
        }
        if (x.offset_ns) {
            j["offset_ns"] = x.offset_ns;
        }
        if (x.rollovers) {
            j["rollovers"] = x.rollovers;
        }
        j["tow_ms"] = x.tow_ms;
        j["week"] = x.week;
    }

    inline void from_json(const json & j, Time& x) {
        x.bdt = get_stack_optional<GnssTime>(j, "bdt");
        x.glonasst = get_stack_optional<std::string>(j, "glonasst");
        x.gpst = get_stack_optional<GnssTime>(j, "gpst");
        x.gst = get_stack_optional<GnssTime>(j, "gst");
        x.tai = get_stack_optional<std::string>(j, "tai");
    }

    inline void to_json(json & j, const Time & x) {
        j = json::object();
        if (x.bdt) {
            j["bdt"] = x.bdt;
        }
        if (x.glonasst) {
            j["glonasst"] = x.glonasst;
        }
        if (x.gpst) {
            j["gpst"] = x.gpst;
        }
        if (x.gst) {
            j["gst"] = x.gst;
        }
        if (x.tai) {
            j["tai"] = x.tai;
        }
    }

    inline void from_json(const json & j, CartesianVelocity& x) {
        x.vx = j.at("vx").get<double>();
        x.vy = j.at("vy").get<double>();
        x.vz = j.at("vz").get<double>();
    }

    inline void to_json(json & j, const CartesianVelocity & x) {
        j = json::object();
        j["vx"] = x.vx;
        j["vy"] = x.vy;
        j["vz"] = x.vz;
    }

    inline void from_json(const json & j, PositionVelocityTimePvt& x) {
        x.algorithm = get_stack_optional<std::string>(j, "algorithm");
        x.covariance = get_stack_optional<CovarianceMatrices>(j, "covariance");
        x.datum = j.at("datum").get<GeodeticDatum>();
        x.fix = j.at("fix").get<std::string>();
        x.position = j.at("position").get<CartesianPosition>();
        x.time = j.at("time").get<Time>();
        x.velocity = get_stack_optional<CartesianVelocity>(j, "velocity");
    }

    inline void to_json(json & j, const PositionVelocityTimePvt & x) {
        j = json::object();
        if (x.algorithm) {
            j["algorithm"] = x.algorithm;
        }
        if (x.covariance) {
            j["covariance"] = x.covariance;
        }
        j["datum"] = x.datum;
        j["fix"] = x.fix;
        j["position"] = x.position;
        j["time"] = x.time;
        if (x.velocity) {
            j["velocity"] = x.velocity;
        }
    }

    inline void from_json(const json & j, Message& x) {
        x.pvt = get_stack_optional<PositionVelocityTimePvt>(j, "pvt");
        x.epoch = j.at("$epoch").get<std::string>();
        x.schema = j.at("$schema").get<std::string>();
    }

    inline void to_json(json & j, const Message & x) {
        j = json::object();
        if (x.pvt) {
            j["pvt"] = x.pvt;
        }
        j["$epoch"] = x.epoch;
        j["$schema"] = x.schema;
    }
}
