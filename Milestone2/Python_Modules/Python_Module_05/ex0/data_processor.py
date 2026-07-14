#!/usr/bin/env python3

from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):

    def __init__(self) -> None:
        self._storage: list[tuple[int, str]] = []
        self._index = 0

    # Contrato obrigatório que toda classe que herda é obrigada a ter, mas quem
    # define a utilidade é quem herda, a mãe só define a assinatura.
    # Se a filha tbm for abstrata, a obrigatoriedade segue passando a herança
    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        # Ellipsis - Faz o mesmo que pass, deixa claro que é um corpo vazio.
        ...

    # Sys FIFO (1st-in, 1st-out), reorganiza a fila, se não estoura IndexError
    def output(self) -> tuple[int, str]:
        if not self._storage:
            raise IndexError("No data remaining on processor")

        # Remove e retorna o primeiro elemento (mais antigo)
        return self._storage.pop(0)


class NumericProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()

    # Valida se o dado é int ou float, e checa se não é bool
    def validate(self, data: Any) -> bool:

        # Verifica se é int, e precisa verificar o bool, já que bool é uma sub
        # classe de int, sendo 1 T, 0 F, resumindo uma verificação de segurança
        # para se alguém passar um bool ele não valide
        if isinstance(data, (int, float)) and not isinstance(data, bool):
            return True
        if isinstance(data, list):
            if len(data) == 0:
                return True

            # all faz verifica se tudo é true, se um "item" der erro, invalida
            return all(
                isinstance(item, (int, float)) and not isinstance(item, bool)
                for item in data
            )
        return False

    # Transforma int em str
    def ingest(self, data: Any) -> None:
        if not self.validate(data):
            raise ValueError("Improper numeric data")

        if isinstance(data, list):
            for item in data:
                self._storage.append((self._index, str(item)))
                self._index += 1

        else:
            self._storage.append((self._index, str(data)))
            self._index += 1


class TextProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()

    # Garante que seja str, ou uma lista com str (apenas)
    def validate(self, data: Any) -> bool:
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            if len(data) == 0:
                return True
            return all(isinstance(item, str) for item in data)
        return False

    # Armazena os textos
    def ingest(self, data: Any) -> None:
        if not self.validate(data):
            raise ValueError("improper text data")

        if isinstance(data, list):
            for item in data:
                self._storage.append((self._index, item))
                self._index += 1
        else:
            self._storage.append((self._index, data))
            self._index += 1


class LogProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()

    # Valida se é dict, ou uma list de dict
    def validate(self, data: Any) -> bool:
        if isinstance(data, dict):
            return all(
                isinstance(a, str) and isinstance(b, str)
                for a, b in data.items()
                )
        if isinstance(data, list):
            if len(data) == 0:
                return True

            # Validação em cascata para ver se todos os valores são str, e
            # depois que cada item seja um dict
            return all(
                isinstance(item, dict) and all(
                    isinstance(a, str) and isinstance(b, str)
                    for a, b in item.items()
                )
                for item in data
            )
        return False

    def ingest(self, data: Any) -> None:
        if not self.validate(data):
            raise ValueError("Improper log data")

        # Função para formatar do dict de logs
        def format_log(log_dict: dict[Any, Any]) -> str:

            # Get verifica se tem o valor, se não retorna o estipulado,
            # evitando falha de chave (KeyError)
            level = log_dict.get("log_level", "")
            msg = log_dict.get("log_message", "")
            return f"{level}: {msg}"

        if isinstance(data, list):
            for item in data:
                self._storage.append((self._index, format_log(item)))
                self._index += 1
        else:
            self._storage.append((self._index, format_log(data)))
            self._index += 1


if __name__ == "__main__":
    print("=== Code Nexus - Data Processor ===\n")

    print("Testing Numeric Processor...")
    np = NumericProcessor()

    print(f"Testing to validate input '42': {np.validate(42)}")
    print(f"Testing to validate input 'Hello': {np.validate('Hello')}")

    print("Test invalid ingestion of string 'foo' without prior validation: ")
    try:
        invalid_data: Any = "foo"
        np.ingest(invalid_data)
    except ValueError as error:
        print(f"Got exception: {error}")

    print("Processing data: [1, 2, 3, 4, 5]")
    np.ingest([1, 2, 3, 4, 5])

    print("Extrating 3 values...")
    for _ in range(3):
        rank, value = np.output()
        print(f"Numeric value {rank}: ", end="")
        print(value)

    print("\nTesting Text Processor...")
    tp = TextProcessor()

    print(f"Trying to validate input '42': {tp.validate(42)}")

    print("Processing data: ['Hello', 'Nexus', 'World']")
    tp.ingest(['Hello', 'Nexus', 'World'])

    print("Extracting 1 value...")
    rank, value = tp.output()
    print(f"Text value {rank}: {value}")

    print("\nTesting Log Processor...")
    lp = LogProcessor()

    print(f"Trying to validate input 'Hello': {lp.validate('Hello')}")

    log_data = [
        {'log_level': 'NOTICE', 'log_message': 'Connection to server'},
        {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}
    ]
    print(f"Processing data: {log_data}")
    lp.ingest(log_data)

    print("Extracting 2 values...")
    for _ in range(2):
        rank, value = lp.output()
        print(f"Log entry {rank}: {value}")
