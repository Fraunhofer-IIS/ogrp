from dataclasses import dataclass
from uuid import UUID
from typing import Any, TypeVar, Type, cast


T = TypeVar("T")


def from_str(x: Any) -> str:
    assert isinstance(x, str)
    return x


def to_class(c: Type[T], x: Any) -> dict:
    assert isinstance(x, c)
    return cast(Any, x).to_dict()


@dataclass
class Ogrp:
    """The OGRP message is the base schema for all OGRP messages."""

    epoch: UUID
    """Either UUIDv1 or UUIDv6 according to RFC9562. The Node ID should be the MAC address of
    the GNSS receiver.
    """
    schema: str
    """The schema of this OGRP message."""

    @staticmethod
    def from_dict(obj: Any) -> 'Ogrp':
        assert isinstance(obj, dict)
        epoch = UUID(obj.get("$epoch"))
        schema = from_str(obj.get("$schema"))
        return Ogrp(epoch, schema)

    def to_dict(self) -> dict:
        result: dict = {}
        result["$epoch"] = str(self.epoch)
        result["$schema"] = from_str(self.schema)
        return result


def ogrp_from_dict(s: Any) -> Ogrp:
    return Ogrp.from_dict(s)


def ogrp_to_dict(x: Ogrp) -> Any:
    return to_class(Ogrp, x)
