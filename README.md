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
recommended as a transport mechanism. For non-RPC use other mechanisms
may be used, e.g. plain TCP socket, a file, a serial line with a
wrapping wire protocol.

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

Message specification
=====================

An OGRP message is composed of one JSON object. Two mandatory fields
exist

    msg = {
        'protocol': protocol,
        'id': id,
        ...
    }

    protocol = 'OGRP1'
    id = string ; lower-case, underscore separated id, e.g. 'raw_meas', ...

The additional content in the message is dependant on the message id.
Optional fields are allowed and must be ignored by parsers if unknown
(according to JSON).

In general "list-of-struct" are preferred over "struct-of-list" as this eases
processing and data output.

Example definitions
-------------------

A message of id 'raw\_meas' for raw measurements of a GNSS receiver,
e.g. including pseudorange and carrier phase measurements for multiple
satellites on different channels, can look like this:

    raw_meas = {
        'protocol': protocol,
        'id': 'raw_meas',
        'sw_version': int / hex,
        'timestamp': float,
        'time_status': time_status,
        'nr_obs': int,
        'obs': [*raw_meas_obs]
        }

    channel_state = 'IDLE' / 'SEARCHING' / 'PULL_IN' / 'SEARCHING' / 'SYNCED'

    raw_meas_obs = {
        'gnss': string, ; 'GPS' / 'GPS' / ...
        'sat_id': int,
        'signal_type': string, ; 'L1CA' / 'L5I' / 'E5aI' / ...
        'channel_state': channel_state
        'dopp': float,
        'carr_phase': float,
        'snr': float,
        'locktime': float,
        'prange': float,
        'ch_nr': int
    }

    time_status = 'FREE_RUNNING' / 'GPS_SYNCED' / ...


Key naming
----------

Names of keys should be explicit and unambiguous.

If desired, abbreviations can be used but should be properly defined. Both
variants of a key, abbreviated and non-abbreviated should be supported.

Example: "ch_meas" --> "channel_measurement"


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

