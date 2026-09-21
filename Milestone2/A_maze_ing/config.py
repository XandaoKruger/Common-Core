from random import randint
from dataclasses import dataclass


# Classe generica que vai expor os erros
class ConfigError(Exception):
    '''
    Docstring for ConfigError
    '''
    pass


# Frozen impede que alguem mude um campo depois de
# criado, nao pode ser reatribuido
@dataclass(frozen=True)
class MazeConfig:
    '''
    Docstring for MazeConfig
    '''

    width: int 
    height: int
    entry: tuple[int, int]
    exit_block: tuple[int, int]
    output_file: str
    perfect: bool
    seed: int

    # chamado automaticamente, logo depois do __init__
    # gerado terminar de atribuir os campos
    def __post_init__(self) -> None:
        '''

        '''

        if self.width <= 0 or self.height <= 0:
            raise ConfigError(
                f"width/height needs to be positive: \
{self.width}x{self.height}"
            )

        # comparacao encadeada
        # entry e uma tupla[x, y], x=0 y=1
        # numa so linha faco: se x nao for negativo e (maior ou igual a 0)
        # x e menor que width (nao ultrapassa o limite)
        # e o mesmo apos o and, mas para height
        if not (
            0 <= self.entry[0] < self.width 
            and 0 <= self.entry[1] < self.height
        ):
            raise ConfigError(
                f"entry {self.entry} out of range {self.width}x{self.height}"
            )

        if not (
            0 <= self.exit_block[0] < self.width
            and 0 <= self.exit_block[1] < self.height
        ):
            raise ConfigError(
                f"exit {self.exit_block} out of range \
{self.width}x{self.height}"
            )

        if self.entry == self.exit_block:
            raise ConfigError(
                f"entry and exit cannot be equal: {self.entry}"
            )

        if not self.output_file:
            raise ConfigError("output_file cannot be empty")

    @classmethod
    def from_file(cls, path: str) -> "MazeConfig":
        '''

        '''

        raw: dict[str, str] = {}
        try:
            with open(path) as f:
                for line in f:
                    line = line.strip()
                    if not line or line.startswith("#"):
                        continue
                    if "=" not in line:
                        raise ConfigError(
                            f"malformed line (missing '='): {line!r}"
                        )
                    key, value = line.split("=", 1)
                    raw[key] = value

        except FileNotFoundError:
            raise ConfigError(f"Config file not found: {path}")

        required = {
            "WIDTH",
            "HEIGHT",
            "ENTRY",
            "EXIT",
            "OUTPUT_FILE",
            "PERFECT"
        }

        # issubset confirma se todos os "required" (nesse caso) estao presentes
        # se nao tiverem, lanca erro
        if not required.issubset(raw):
            raise ConfigError(
                f"missing required keys: {required - raw.keys()}"
            )

        try:
            width = int(raw["WIDTH"])
            height = int(raw["HEIGHT"])

            entry_parts = raw["ENTRY"].split(",")
            exit_parts = raw["EXIT"].split(",")

            if len(entry_parts) != 2 or len(exit_parts) != 2:
                raise ConfigError(
                    f"entry/exit must have exactly 2 values: "
                    f"{raw['ENTRY']}, {raw['EXIT']}"
                )

            # Tupla com os valores de x e y
            entry = (int(entry_parts[0]), int(entry_parts[1]))
            exit_block = (int(exit_parts[0]), int(exit_parts[1]))

            perfect = raw["PERFECT"].strip().lower() == "true"
            seed = int(raw["SEED"]) if "SEED" in raw else randint(0, 999999)
        except (ValueError, IndexError) as error:
            raise ConfigError(f"Invalid value config: {error}") from error

        if "SEED" not in raw:
            print(f"Seed: {seed}")

        return cls(
            width=width,
            height=height,
            entry=entry,
            exit_block=exit_block,
            output_file=raw["OUTPUT_FILE"],
            perfect=perfect,
            seed=seed
        )
