from dataclasses import dataclass
from typing import Any, Optional, TypeVar, Type, cast
from datetime import datetime
from uuid import UUID
import dateutil.parser


T = TypeVar("T")


def from_float(x: Any) -> float:
    assert isinstance(x, (float, int)) and not isinstance(x, bool)
    return float(x)


def to_float(x: Any) -> float:
    assert isinstance(x, (int, float))
    return x


def from_none(x: Any) -> Any:
    assert x is None
    return x


def from_union(fs, x):
    for f in fs:
        try:
            return f(x)
        except:
            pass
    assert False


def to_class(c: Type[T], x: Any) -> dict:
    assert isinstance(x, c)
    return cast(Any, x).to_dict()


def from_str(x: Any) -> str:
    assert isinstance(x, str)
    return x


def from_int(x: Any) -> int:
    assert isinstance(x, int) and not isinstance(x, bool)
    return x


def from_datetime(x: Any) -> datetime:
    return dateutil.parser.parse(x)


@dataclass
class CovarianceMatrix:
    """Upper-triangular elements of a symmetric 4×4 covariance matrix for variables {t, x, y,
    z}. Units must match the associated state components.
    """
    tt: float
    """Variance (t)"""

    xt: float
    """Covariance (x, t)"""

    xx: float
    """Variance (x)"""

    xy: float
    """Covariance (x, y)"""

    xz: float
    """Covariance (x, z)"""

    yt: float
    """Covariance (y, t)"""

    yy: float
    """Variance (y)"""

    yz: float
    """Covariance (y, z)"""

    zt: float
    """Covariance (z, t)"""

    zz: float
    """Variance (z)"""

    @staticmethod
    def from_dict(obj: Any) -> 'CovarianceMatrix':
        assert isinstance(obj, dict)
        tt = from_float(obj.get("tt"))
        xt = from_float(obj.get("xt"))
        xx = from_float(obj.get("xx"))
        xy = from_float(obj.get("xy"))
        xz = from_float(obj.get("xz"))
        yt = from_float(obj.get("yt"))
        yy = from_float(obj.get("yy"))
        yz = from_float(obj.get("yz"))
        zt = from_float(obj.get("zt"))
        zz = from_float(obj.get("zz"))
        return CovarianceMatrix(tt, xt, xx, xy, xz, yt, yy, yz, zt, zz)

    def to_dict(self) -> dict:
        result: dict = {}
        result["tt"] = to_float(self.tt)
        result["xt"] = to_float(self.xt)
        result["xx"] = to_float(self.xx)
        result["xy"] = to_float(self.xy)
        result["xz"] = to_float(self.xz)
        result["yt"] = to_float(self.yt)
        result["yy"] = to_float(self.yy)
        result["yz"] = to_float(self.yz)
        result["zt"] = to_float(self.zt)
        result["zz"] = to_float(self.zz)
        return result


@dataclass
class VelocityCovarianceMatrix:
    """Upper-triangular elements of a symmetric 4×4 covariance matrix for variables {dt, vx, vy,
    vz}. Units must match the associated state components.
    """
    dtdt: float
    """Variance (dt)"""

    vxdt: float
    """Covariance (vx, dt)"""

    vxvx: float
    """Variance (vx)"""

    vxvy: float
    """Covariance (vx, vy)"""

    vxvz: float
    """Covariance (vx, vz)"""

    vydt: float
    """Covariance (vy, dt)"""

    vyvy: float
    """Variance (vy)"""

    vyvz: float
    """Covariance (vy, vz)"""

    vzdt: float
    """Covariance (vz, dt)"""

    vzvz: float
    """Variance (vz)"""

    @staticmethod
    def from_dict(obj: Any) -> 'VelocityCovarianceMatrix':
        assert isinstance(obj, dict)
        dtdt = from_float(obj.get("dtdt"))
        vxdt = from_float(obj.get("vxdt"))
        vxvx = from_float(obj.get("vxvx"))
        vxvy = from_float(obj.get("vxvy"))
        vxvz = from_float(obj.get("vxvz"))
        vydt = from_float(obj.get("vydt"))
        vyvy = from_float(obj.get("vyvy"))
        vyvz = from_float(obj.get("vyvz"))
        vzdt = from_float(obj.get("vzdt"))
        vzvz = from_float(obj.get("vzvz"))
        return VelocityCovarianceMatrix(dtdt, vxdt, vxvx, vxvy, vxvz, vydt, vyvy, vyvz, vzdt, vzvz)

    def to_dict(self) -> dict:
        result: dict = {}
        result["dtdt"] = to_float(self.dtdt)
        result["vxdt"] = to_float(self.vxdt)
        result["vxvx"] = to_float(self.vxvx)
        result["vxvy"] = to_float(self.vxvy)
        result["vxvz"] = to_float(self.vxvz)
        result["vydt"] = to_float(self.vydt)
        result["vyvy"] = to_float(self.vyvy)
        result["vyvz"] = to_float(self.vyvz)
        result["vzdt"] = to_float(self.vzdt)
        result["vzvz"] = to_float(self.vzvz)
        return result


@dataclass
class CovarianceMatrices:
    """Covariance matrices for position + time and velocity + time drift."""

    position: CovarianceMatrix
    velocity: Optional[VelocityCovarianceMatrix] = None

    @staticmethod
    def from_dict(obj: Any) -> 'CovarianceMatrices':
        assert isinstance(obj, dict)
        position = CovarianceMatrix.from_dict(obj.get("position"))
        velocity = from_union([VelocityCovarianceMatrix.from_dict, from_none], obj.get("velocity"))
        return CovarianceMatrices(position, velocity)

    def to_dict(self) -> dict:
        result: dict = {}
        result["position"] = to_class(CovarianceMatrix, self.position)
        if self.velocity is not None:
            result["velocity"] = from_union([lambda x: to_class(VelocityCovarianceMatrix, x), from_none], self.velocity)
        return result


@dataclass
class ReferenceEllipsoid:
    """Reference ellipsoid. If omitted, it is implied by reference frame (e.g., WGS84)."""

    a: float
    """Semi-major axis a, meters."""

    f: float
    """Flattening f (unitless)."""

    name: str
    """e.g., WGS84, GRS80"""

    @staticmethod
    def from_dict(obj: Any) -> 'ReferenceEllipsoid':
        assert isinstance(obj, dict)
        a = from_float(obj.get("a"))
        f = from_float(obj.get("f"))
        name = from_str(obj.get("name"))
        return ReferenceEllipsoid(a, f, name)

    def to_dict(self) -> dict:
        result: dict = {}
        result["a"] = to_float(self.a)
        result["f"] = to_float(self.f)
        result["name"] = from_str(self.name)
        return result


@dataclass
class GeodeticDatum:
    """A Geodetic Datum consists of a reference frame and optional definition of epoch and
    ellipsoid.
    """
    frame: str
    """Geodetic reference frame/datum (e.g., ITRF2020, WGS84, GTRF, PZ90, CGCS2000)."""

    ellipsoid: Optional[ReferenceEllipsoid] = None
    """Reference ellipsoid. If omitted, it is implied by reference frame (e.g., WGS84)."""

    epoch: Optional[float] = None
    """Reference epoch of coordinates as decimal year (e.g., 2025.0). Required if the frame is
    time-dependent.
    """

    @staticmethod
    def from_dict(obj: Any) -> 'GeodeticDatum':
        assert isinstance(obj, dict)
        frame = from_str(obj.get("frame"))
        ellipsoid = from_union([ReferenceEllipsoid.from_dict, from_none], obj.get("ellipsoid"))
        epoch = from_union([from_float, from_none], obj.get("epoch"))
        return GeodeticDatum(frame, ellipsoid, epoch)

    def to_dict(self) -> dict:
        result: dict = {}
        result["frame"] = from_str(self.frame)
        if self.ellipsoid is not None:
            result["ellipsoid"] = from_union([lambda x: to_class(ReferenceEllipsoid, x), from_none], self.ellipsoid)
        if self.epoch is not None:
            result["epoch"] = from_union([to_float, from_none], self.epoch)
        return result


@dataclass
class CartesianPosition:
    """Cartesian coordinates in meters."""

    x: float
    """X coordinate in meters."""

    y: float
    """Y coordinate in meters."""

    z: float
    """Z coordinate in meters."""

    @staticmethod
    def from_dict(obj: Any) -> 'CartesianPosition':
        assert isinstance(obj, dict)
        x = from_float(obj.get("x"))
        y = from_float(obj.get("y"))
        z = from_float(obj.get("z"))
        return CartesianPosition(x, y, z)

    def to_dict(self) -> dict:
        result: dict = {}
        result["x"] = to_float(self.x)
        result["y"] = to_float(self.y)
        result["z"] = to_float(self.z)
        return result


@dataclass
class GNSSTime:
    """BeiDou Time (strictly monotonic)
    
    Native GNSS time in week and time-of-week in milliseconds. No leap seconds for
    GPS/Galileo/BeiDou; GLONASS is UTC-like.
    
    GPS Time (strictly monotonic)
    
    Galileo System Time (strictly monotonic)
    """
    tow_ms: int
    """Time of week in milliseconds."""

    week: int
    """Week number since GNSS system epoch. Maximum depends on GNSS system."""

    drift_ns_per_s: Optional[float] = None
    """Clock drift in ns/s. Positive means GNSS time is faster than receiver clock."""

    leap_seconds_utc: Optional[int] = None
    """Number of leap seconds (GNSS-UTC) applicable at this epoch."""

    offset_ns: Optional[float] = None
    """Clock offset in nanoseconds. Positive means GNSS time is ahead of receiver clock."""

    rollovers: Optional[int] = None
    """Number of week rollovers since GNSS system epoch (e.g., GPS epoch: January 6, 1980)."""

    @staticmethod
    def from_dict(obj: Any) -> 'GNSSTime':
        assert isinstance(obj, dict)
        tow_ms = from_int(obj.get("tow_ms"))
        week = from_int(obj.get("week"))
        drift_ns_per_s = from_union([from_float, from_none], obj.get("drift_ns_per_s"))
        leap_seconds_utc = from_union([from_int, from_none], obj.get("leap_seconds_utc"))
        offset_ns = from_union([from_float, from_none], obj.get("offset_ns"))
        rollovers = from_union([from_int, from_none], obj.get("rollovers"))
        return GNSSTime(tow_ms, week, drift_ns_per_s, leap_seconds_utc, offset_ns, rollovers)

    def to_dict(self) -> dict:
        result: dict = {}
        result["tow_ms"] = from_int(self.tow_ms)
        result["week"] = from_int(self.week)
        if self.drift_ns_per_s is not None:
            result["drift_ns_per_s"] = from_union([to_float, from_none], self.drift_ns_per_s)
        if self.leap_seconds_utc is not None:
            result["leap_seconds_utc"] = from_union([from_int, from_none], self.leap_seconds_utc)
        if self.offset_ns is not None:
            result["offset_ns"] = from_union([to_float, from_none], self.offset_ns)
        if self.rollovers is not None:
            result["rollovers"] = from_union([from_int, from_none], self.rollovers)
        return result


@dataclass
class Time:
    """GNSS system time representations."""

    bdt: Optional[GNSSTime] = None
    """BeiDou Time (strictly monotonic)"""

    glonasst: Optional[datetime] = None
    """GLONASS Time (UTC-like)"""

    gpst: Optional[GNSSTime] = None
    """GPS Time (strictly monotonic)"""

    gst: Optional[GNSSTime] = None
    """Galileo System Time (strictly monotonic)"""

    tai: Optional[datetime] = None
    """International Atomic Time (strictly monotonic)"""

    @staticmethod
    def from_dict(obj: Any) -> 'Time':
        assert isinstance(obj, dict)
        bdt = from_union([GNSSTime.from_dict, from_none], obj.get("bdt"))
        glonasst = from_union([from_datetime, from_none], obj.get("glonasst"))
        gpst = from_union([GNSSTime.from_dict, from_none], obj.get("gpst"))
        gst = from_union([GNSSTime.from_dict, from_none], obj.get("gst"))
        tai = from_union([from_datetime, from_none], obj.get("tai"))
        return Time(bdt, glonasst, gpst, gst, tai)

    def to_dict(self) -> dict:
        result: dict = {}
        if self.bdt is not None:
            result["bdt"] = from_union([lambda x: to_class(GNSSTime, x), from_none], self.bdt)
        if self.glonasst is not None:
            result["glonasst"] = from_union([lambda x: x.isoformat(), from_none], self.glonasst)
        if self.gpst is not None:
            result["gpst"] = from_union([lambda x: to_class(GNSSTime, x), from_none], self.gpst)
        if self.gst is not None:
            result["gst"] = from_union([lambda x: to_class(GNSSTime, x), from_none], self.gst)
        if self.tai is not None:
            result["tai"] = from_union([lambda x: x.isoformat(), from_none], self.tai)
        return result


@dataclass
class CartesianVelocity:
    """Cartesian velocity in meters per second."""

    vx: float
    """X velocity in meters per second."""

    vy: float
    """Y velocity in meters per second."""

    vz: float
    """Z velocity in meters per second."""

    @staticmethod
    def from_dict(obj: Any) -> 'CartesianVelocity':
        assert isinstance(obj, dict)
        vx = from_float(obj.get("vx"))
        vy = from_float(obj.get("vy"))
        vz = from_float(obj.get("vz"))
        return CartesianVelocity(vx, vy, vz)

    def to_dict(self) -> dict:
        result: dict = {}
        result["vx"] = to_float(self.vx)
        result["vy"] = to_float(self.vy)
        result["vz"] = to_float(self.vz)
        return result


@dataclass
class PositionVelocityTimePVT:
    """Position and velocity refer to earth-centered, earth-fixed cartesian coordinate system
    defined by `datum`.
    """
    datum: GeodeticDatum
    fix: str
    position: CartesianPosition
    time: Time
    algorithm: Optional[str] = None
    covariance: Optional[CovarianceMatrices] = None
    velocity: Optional[CartesianVelocity] = None

    @staticmethod
    def from_dict(obj: Any) -> 'PositionVelocityTimePVT':
        assert isinstance(obj, dict)
        datum = GeodeticDatum.from_dict(obj.get("datum"))
        fix = from_str(obj.get("fix"))
        position = CartesianPosition.from_dict(obj.get("position"))
        time = Time.from_dict(obj.get("time"))
        algorithm = from_union([from_str, from_none], obj.get("algorithm"))
        covariance = from_union([CovarianceMatrices.from_dict, from_none], obj.get("covariance"))
        velocity = from_union([CartesianVelocity.from_dict, from_none], obj.get("velocity"))
        return PositionVelocityTimePVT(datum, fix, position, time, algorithm, covariance, velocity)

    def to_dict(self) -> dict:
        result: dict = {}
        result["datum"] = to_class(GeodeticDatum, self.datum)
        result["fix"] = from_str(self.fix)
        result["position"] = to_class(CartesianPosition, self.position)
        result["time"] = to_class(Time, self.time)
        if self.algorithm is not None:
            result["algorithm"] = from_union([from_str, from_none], self.algorithm)
        if self.covariance is not None:
            result["covariance"] = from_union([lambda x: to_class(CovarianceMatrices, x), from_none], self.covariance)
        if self.velocity is not None:
            result["velocity"] = from_union([lambda x: to_class(CartesianVelocity, x), from_none], self.velocity)
        return result


@dataclass
class Ogrp:
    """The OGRP message is the base schema for all OGRP messages."""

    epoch: UUID
    """Either UUIDv1 or UUIDv6 according to RFC9562. The Node ID should be the MAC address of
    the GNSS receiver.
    """
    schema: str
    """The schema of this OGRP message."""

    pvt: Optional[PositionVelocityTimePVT] = None

    @staticmethod
    def from_dict(obj: Any) -> 'Ogrp':
        assert isinstance(obj, dict)
        epoch = UUID(obj.get("$epoch"))
        schema = from_str(obj.get("$schema"))
        pvt = from_union([PositionVelocityTimePVT.from_dict, from_none], obj.get("pvt"))
        return Ogrp(epoch, schema, pvt)

    def to_dict(self) -> dict:
        result: dict = {}
        result["$epoch"] = str(self.epoch)
        result["$schema"] = from_str(self.schema)
        if self.pvt is not None:
            result["pvt"] = from_union([lambda x: to_class(PositionVelocityTimePVT, x), from_none], self.pvt)
        return result


def ogrp_from_dict(s: Any) -> Ogrp:
    return Ogrp.from_dict(s)


def ogrp_to_dict(x: Ogrp) -> Any:
    return to_class(Ogrp, x)
