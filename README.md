OGRP
====

The Open Gnss Receiver Protocol

Introduction
============

Previous attempts to define an exchange protocol for GNSS related data
have been proposed only by manufacturers for their own products with
proprietary wire protocols or for limited applications, e.g. RTCM,
RINEX, NMEA.

OGRP (**O**pen **G**NSS **R**eceiver **P**rotocol) tries to be a
protocol for many different causes in the domain of GNSS may it be
output of raw measurements from receivers over a physical wire
connection but also supporting RPC (remote procedure call) like
JSON-RPC.

OGRP is a protocol based on JSON ([RFC4627]).

For the use in RPC, zerorpc (<http://zerorpc.dotcloud.com/>) is
recommended as a transport mechanism. Other mechanisms
may be used for non-RPC, e.g. plain TCP socket, a file, a serial line with a
wrapping wire protocol all using [NDJ](http://en.wikipedia.org/wiki/Line_Delimited_JSON).
Files containing OGRP should have the filename extension *.ogrp*.

OGRP is meant to be extendable and future-proof rather than optimized
regarding performance for a specific case. Many messages are not defined but
it should be easy to define one on your own fitting into the common scheme.
OGRP should also support complete wrapping of other message protocols in
itself, e.g. any message used in proprietary protocols should be expressable
by OGRP or embeddable in OGRP messages.

Conventions used
----------------

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT",
"SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this
document are to be interpreted as described in [RFC2119].

The underlying format used for OGRP is JSON. Consequently, terms and
types are to be interpreted as described in section 1 of [RFC4627].

The OGRP protocol definition uses the ABNF syntax
(<http://www.ietf.org/rfc/rfc5234.txt>)
where appropriate but mixes with examples in JSON syntax.

License information
-------------------

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a>

This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.

Reasoning: [Licenses for Protocols](http://hintjens.com/blog:41)

Maturity
--------

Maturity indicator: Is this an experimental, draft, stable, legacy, or
retired specification?

A: OGRP is considered in experimental state.

Extending the protocol / specification
--------------------------------------

Consider the following:

-   Use formal grammar: prevents arguments due to different
    interpretations of the text.

-   Use technical explanation: semantics of each message, error
    handling, and so on.

-   Add references: to other documents, protocols, and so on.

-   Use list-of-structs instead of struct-of-lists.

-   Use explicit and unambiguous key names.

-   Use lower-case, underscore separated key names.

Message specification
=====================

An OGRP message is composed of one JSON object. Two mandatory fields
exist

    msg = {
        "protocol": protocol,
        "id": id,
        ...
    }

    protocol = "OGRP1"
    id = string ; lower-case, underscore separated id, e.g. "measurement", ...

The additional content in the message is dependant on the message id.
Optional fields are allowed and must be ignored by parsers if unknown
(according to JSON).

Example definitions
-------------------

A message of id 'measurement' for raw measurements of a GNSS receiver,
e.g. including pseudorange and carrier phase measurements for multiple
satellites on different channels, can look like this:

    measurement = {
        "protocol": protocol,
        "id": "measurement",
        "sw_version": int / hex,
        "timestamp": float / string, ; (see Representing time and date)
        "time_status": time_status,
        "channel_measurement": [*channel_measurement]
        }

    time_status = string, ; "FREE_RUNNING" / "COARSE" / "GPS_SYNCED" / ...

    channel_measurement = {
        "gnss": string, ; "GPS" / "GALILEO" / "GLONASS" / "SBAS" / ...
        "satellite_id": int, ; starting at 1
        "signal_type": string, ; "L1CA" / "L5I" / "E5aI" / ...
        "channel_state": channel_state,
        "doppler": float, ; (Hz)
        "carrier_phase": float, ; (cycles)
        "signal_to_noise_ratio": float, ; (dB)
        "locktime": float, ; (seconds)
        "pseudorange": float, ; (meters)
        "code_phase": float, ; (chips)
        "channel_number": int ; starting at 0
    }

    channel_state = string, ; "IDLE" / "SEARCHING" / "PULL_IN" / "LOCKED" / "SYNCED"


Key naming
----------

Names of keys should be explicit and unambiguous.

If desired, abbreviations can be used but should be properly defined. Both
variants of a key, abbreviated and non-abbreviated should be supported.

Here is the list of currently defined abbreviations:

| full name             | abbreviation |
|-----------------------|--------------|
| channel_measurement   | ch_meas      |
| channel_number        | ch_nr        |
| pseudorange           | psr          |
| satellite_id          | sat_id       |
| signal_to_noise_ratio | snr          |


Representing time and date
--------------------------

Fields called 'timestamp' can hold times specified in UNIX time or ISO 8601. So if the JSON
type is float it's a UNIX time referred to UTC. If the JSON type is string, it must conform
to ISO 8601.

GPS or Galileo time is only valid for fields called 'gps_time' or 'galileo_time'.


Usage
=====

Applications using OGRP for input or output should define the supported messages as [JSON Schema](http://json-schema.org/).
An example for a PVT application's minimum input data could be:

    {
        "id": "http://example.org/pvt-input-schema#"
        "$schema": "http://json-schema.org/draft-04/schema#",
        "description": "Minimum schema for a PVT application"
        "type": "object",
        "properties": {
            "protocol": { "type": "string" },
            "id": { "type": "string" },
            "timestamp": { "$ref": "http://ogrp.org/definitions/timestamp" },
            "channel_measurements": {
                "type": "object",
                "properties": {
                    "satellite_id": {
                        "type": "integer",
                        "minimum": 1
                    }
                    "pseudorange": {
                        "type": "number"
                    }
                }
            },
            "satellites": {
                "type": "object",
                "properties": {
                    "satellite_id": {
                        "type": "integer",
                        "minimum": 1
                    }
                    "position": {
                        "type": "object",
                        "properties": {
                            "x": { "type": "number" },
                            "y": { "type": "number" },
                            "z": { "type": "number" },
                        }
                    }
                }
            }
        }
    }

Security considerations
=======================

See JSON considerations on this topic in [RFC4627].

No further security mechanisms are designed into OGRP.


References
==========

[RFC2119]: <http://www.ietf.org/rfc/rfc2119.txt>
: RFC2119

[RFC4627]: <http://www.ietf.org/rfc/rfc4627.txt>
: RFC4627

