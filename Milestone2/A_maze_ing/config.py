from random import randint
from dataclasses import dataclass

REQUIRED_KEYS = frozenset(
    {"WIDTH", "HEIGHT", "ENTRY", "EXIT", "OUTPUT_FILE", "PERFECT"}
)


class ConfigError(Exception):
    """Raised when the configuration file is missing, malformed or invalid."""


def _parse_line(line: str, number: int) -> tuple[str, str]:
    """Split one 'KEY=VALUE' line into a normalised (KEY, value) pair."""
    if "=" not in line:
        raise ConfigError(f"line {number}: missing '=': {line!r}")
    key, value = line.split("=", 1)
    key = key.strip().upper()
    if not key:
        raise ConfigError(f"line {number}: empty key: {line!r}")
    return key, value.strip()


def _read_pairs(path: str) -> dict[str, str]:
    """Read the config file into a KEY -> value dict.

    Blank lines and lines starting with '#' are ignored.

    Raises:
        ConfigError: unreadable file, malformed line or duplicate key.
    """
    raw: dict[str, str] = {}
    try:
        with open(path, encoding="utf-8") as f:
            lines = f.read().splitlines()
    except FileNotFoundError:
        raise ConfigError(f"config file not found: {path}")
    except (OSError, UnicodeDecodeError) as error:
        raise ConfigError(f"cannot read '{path}': {error}") from error

    for number, line in enumerate(lines, start=1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        key, value = _parse_line(line, number)
        if key in raw:
            raise ConfigError(f"line {number}: duplicate key {key}")
        raw[key] = value
    return raw


def _parse_int(raw: dict[str, str], key: str) -> int:
    """Return raw[key] as an int or raise a ConfigError naming the key."""
    try:
        return int(raw[key])
    except ValueError as error:
        raise ConfigError(
            f"{key} must be an integer: {raw[key]!r}"
        ) from error


def _parse_point(raw: dict[str, str], key: str) -> tuple[int, int]:
    """Return raw[key] ('x,y') as an (x, y) tuple of ints."""
    parts = raw[key].split(",")
    if len(parts) != 2:
        raise ConfigError(f"{key} must look like 'x,y': {raw[key]!r}")
    try:
        return int(parts[0]), int(parts[1])
    except ValueError as error:
        raise ConfigError(
            f"{key} must be two integers: {raw[key]!r}"
        ) from error


def _parse_bool(raw: dict[str, str], key: str) -> bool:
    """Accept only True/False (any case); anything else is an error."""
    value = raw[key].lower()
    if value not in ("true", "false"):
        raise ConfigError(f"{key} must be True or False: {raw[key]!r}")
    return value == "true"


@dataclass(frozen=True)
class MazeConfig:
    """Validated, immutable maze settings read from the config file."""

    width: int
    height: int
    entry: tuple[int, int]
    exit_block: tuple[int, int]
    output_file: str
    perfect: bool
    seed: int

    def __post_init__(self) -> None:
        """Validate sizes, entry/exit bounds and the output filename."""
        size = f"{self.width}x{self.height}"
        if self.width <= 0 or self.height <= 0:
            raise ConfigError(f"width/height must be positive: {size}")
        for name, (x, y) in (("entry", self.entry),
                             ("exit", self.exit_block)):
            if not (0 <= x < self.width and 0 <= y < self.height):
                raise ConfigError(f"{name} ({x},{y}) out of range {size}")
        if self.entry == self.exit_block:
            raise ConfigError(
                f"entry and exit cannot be equal: {self.entry}"
            )
        if not self.output_file:
            raise ConfigError("output_file cannot be empty")

    @classmethod
    def from_file(cls, path: str) -> "MazeConfig":
        """Build a MazeConfig from a KEY=VALUE file.

        Unknown keys are ignored; SEED is optional (random if absent).

        Raises:
            ConfigError: on any problem with the file or its values.
        """
        raw = _read_pairs(path)
        missing = REQUIRED_KEYS - raw.keys()
        if missing:
            raise ConfigError(
                f"missing required keys: {', '.join(sorted(missing))}"
            )
        if "SEED" in raw:
            seed = _parse_int(raw, "SEED")
        else:
            seed = randint(0, 999999)
            print(f"Seed: {seed}")
        return cls(
            width=_parse_int(raw, "WIDTH"),
            height=_parse_int(raw, "HEIGHT"),
            entry=_parse_point(raw, "ENTRY"),
            exit_block=_parse_point(raw, "EXIT"),
            output_file=raw["OUTPUT_FILE"],
            perfect=_parse_bool(raw, "PERFECT"),
            seed=seed,
        )
