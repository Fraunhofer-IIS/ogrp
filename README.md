OGRP
====

The Open Gnss Receiver Protocol (<http://fraunhofer-iis.github.io/ogrp/>).

[![Build Status](https://secure.travis-ci.org/Fraunhofer-IIS/ogrp.png)](http://travis-ci.org/Fraunhofer-IIS/ogrp)

Introduction
============

Previous attempts to define an exchange protocol for GNSS related data
have been proposed only by manufacturers for their own products with
proprietary wire protocols or for limited applications, e.g.
[RTCM](http://www.navipedia.net/index.php/DGNSS_Standards),
[RINEX](https://en.wikipedia.org/wiki/RINEX),
[NMEA](https://en.wikipedia.org/wiki/NMEA_0183).

OGRP (<b>O</b>pen  <b>G</b>NSS <b>R</b>eceiver <b>P</b>rotocol) tries to be a
protocol for many different use cases in the domain of [GNSS](http://en.wikipedia.org/wiki/GNSS)
may it be output of raw measurements from receivers over a physical wire
connection but also supporting RPC (remote procedure call) like
[JSON-RPC](https://de.wikipedia.org/wiki/JSON-RPC).

OGRP is a protocol based on JSON [[RFC4627](#RFC4627)].

For the use in RPC, zerorpc (<http://zerorpc.dotcloud.com/>) is recommended as a transport mechanism.
Protocols that already provide message framing should use one JSON object per message.
Stream oriented protocols, e.g. a plain TCP socket, a file, a serial line, should use
the media type "application/json-seq". See [[RFC7464](#RFC7464)].
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

The OGRP protocol definition uses the ABNF syntax [[RFC5234](#RFC5234)].
where appropriate but mixes with examples in JSON syntax.

License information
-------------------

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/80x15.png" /></a>

This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.

Reasoning: [Licenses for Protocols](http://hintjens.com/blog:41)

OGRP Trademark Policy
---------------------
Fraunhofer owns the registered EU trademark „OGRP“ (No 015314545). This chapter outlines the policy of Fraunhofer regarding the use of the trademark „OGRP“. Any use of the trademark „OGRP“ must be in accordance with this policy. 
Fraunhofer encourages the use of the trademark „OGRP“ if you are implementing the Open Gnss Receiver Protocol in your products. However, any use of the  trademark „OGRP“ must comply with all of the conditions set forth in this Trademark Policy as follows:

1. Any use of the trademark „OGRP“ depends on your compliance with the CC-BY-SA 4.0 license for the specification of the Open Gnss Receiver Protocol. If you do not comply with the CC-BY-SA 4.0 license for the use of the specification of the Open Gnss Receiver Protocol you are not permitted to use the trademark „OGRP“ for your products and your right to use the trademark terminates automatically.
For the avoidance of doubt, implementations of the Open Gnss Receiver Protocol are not covered by the CC-BY-SA 4.0 license. This license is limited to the specification of the protocol as published at https://github.com/Fraunhofer-IIS/ogrp in the „master“ branch and Adapted Material thereof (as defined in the CC-BY-SA 4.0 license).
Any use of the trademark „OGRP“ that is permitted by statutory law shall not be restricted by this trademark policy.

1. You may distribute products implementing the OGRP specification as published at https://github.com/Fraunhofer-IIS/ogrp in the „master“ branch or any other repository Fraunhofer may use in the future for the specification of OGRP. In this case no specific requirements need to be met for the use of the trademark „OGRP“.

1. You may distribute products implementing the OGRP specification in a modified version than the one published at https://github.com/Fraunhofer-IIS/ogrp in the „master“ branch, or any other repository Fraunhofer may use in the future for the specification of OGRP.  In this case you have to commit your modifications at https://github.com/Fraunhofer-IIS/ogrp under the CC-BY-SA 4.0 license to allow any third party the use of the modified specification.  

1. You may publish modified versions of the OGRP specification than the one published at https://github.com/Fraunhofer-IIS/ogrp in the „master“ branch under the CC-BY-SA 4.0 license. You are encouraged to inform Fraunhofer about such publications at https://github.com/Fraunhofer-IIS/ogrp.



Maturity
--------

Maturity indicator: Is this an experimental, draft, stable, legacy, or
retired specification?

A: OGRP is considered in draft state.

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

```
msg = {
    "protocol": protocol,
    "id": id,
    ...
}

protocol = "OGRP1"
id = string ; lower-case, underscore separated id, e.g. "measurement", ...
```

The additional content in the message is dependant on the message id.
Optional fields are allowed and must be ignored by parsers if unknown
(according to JSON).

Example definitions
-------------------

A message of id 'measurement' for raw measurements of a GNSS receiver,
e.g. including pseudorange and carrier phase measurements for multiple
satellites on different channels, can look like this:

```
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
```

Key naming
----------

Names of keys should be explicit and unambiguous.

If desired, abbreviations can be used but should be properly defined using a
title element in the schema.


Usage
=====

Applications using OGRP for input or output should define the supported messages
as JSON Schema [[json-schema](#json-schema)].

An example how to extend the OGRP core schema:

```JSON
{
    "id": "http://example.org/pvt-input-schema#",
    "$schema": "http://json-schema.org/draft-04/schema#",
    "description": "Minimum schema for a PVT application",
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
                },
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
                },
                "position": {
                    "type": "object",
                    "properties": {
                        "x": { "type": "number" },
                        "y": { "type": "number" },
                        "z": { "type": "number" }
                    }
                }
            }
        }
    }
}
```
Security considerations
=======================

See JSON considerations on this topic in [[RFC4627](#RFC4627)].

No further security mechanisms are designed into OGRP.


References
==========

 * <a name="RFC2119">**[RFC2119]**</a>:  
   Bradner, S., "Key words for use in RFCs to Indicate Requirement Levels",  
   BCP 14, RFC 2119, March 1997, <https://tools.ietf.org/html/rfc2119>.
 * <a name="RFC4627">**[RFC4627]**</a>:  
   Crockford, D., "The application/json Media Type for JavaScript Object Notation (JSON)",  
   RFC 4627, DOI 10.17487/RFC4627, July 2006, <https://tools.ietf.org/html/rfc4627>
 * <a name="RFC5234">**[RFC5234]**</a>:  
   Crocker, D., Ed., and P. Overell, "Augmented BNF for Syntax Specifications: ABNF",  
   STD 68, RFC 5234, DOI 10.17487/RFC5234, January 2008, <https://tools.ietf.org/html/rfc5234>.
 * <a name="RFC7464">**[RFC7464]**</a>:  
   Williams, N., "JavaScript Object Notation (JSON) Text Sequences",  
   RFC 7464, DOI 10.17487/RFC7464, February 2015, <https://tools.ietf.org/html/rfc7464>
 * <a name="json-schema">**[json-schema]**</a>:  
   Wright, A., "JSON Schema: A Media Type for Describing JSON Documents",  
   draft-wright-json-schema-01 (work in progress), October 2016.  
   <https://tools.ietf.org/html/draft-wright-json-schema-01>  
   <http://json-schema.org/>
