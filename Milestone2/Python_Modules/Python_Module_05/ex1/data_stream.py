#!/usr/bin/env python3

from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):

    def __init__(self) -> None:
        self._storage: list[tuple[int, str]] = []
        self._index = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        ...

    def output(self) -> tuple[int, str]:
        if not self._storage:
            raise IndexError("No data remaining on processor")
        return self._storage.pop(0)


class NumericProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()

    def validate(self, data: Any) -> bool:
        if isinstance(data, (int, float)) and not isinstance(data, bool):
            return True
        if isinstance(data, list):
            if len(data) == 0:
                return True

            return all(
                isinstance(item, (int, float)) and not isinstance(item, bool)
                for item in data
            )
        return False

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

    def validate(self, data: Any) -> bool:
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            if len(data) == 0:
                return True
            return all(isinstance(item, str) for item in data)
        return False

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

    def validate(self, data: Any) -> bool:
        if isinstance(data, dict):
            return all(
                isinstance(a, str) and isinstance(b, str)
                for a, b in data.items()
                )
        if isinstance(data, list):
            if len(data) == 0:
                return True
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

        def format_log(log_dict: dict[Any, Any]) -> str:
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

class DataStream:
    def __init__(self) -> None:

        # List de armazenamento de instâncias dos processadores
        self._processos: list[DataProcessor] = []

        # Dict p guardar total de item por classe ("item":quant)
        self._stats: dict[str, int] = {}

    # proc obrigatoriamente precisa receber as regras de DataProcessor
    def register_processor(self, proc: DataProcessor) -> None:

        # Adiciona o processador na lista de processos
        self._processos.append(proc)

        # Descobrir o nome do processo
        class_name = proc.__class__.__name__

        # Contador do processador no dict
        self._stats[class_name] = 0

    def process_stream(self, stream: list[Any]) -> None:
        for elemento in stream:
            processado = False

            # Percorre os processadores
            for proc in self._processos:

                # Faz a validação
                if proc.validate(elemento):

                    # Se aceitar, processa
                    proc.ingest(elemento)

                    # Atualiza as stats usando o nome da classe
                    class_name = proc.__class__.__name__
                    self._stats[class_name] += 1

                    processado = True

                    # Para de procurar novos processadores para esse elemento
                    break

            # Caso nenhum processador aceite o elemento
            if not processado:
                print(f"DataStream error - Can't process element in stream: {elemento}")

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")

        # Verificando se não ha processos
        if not self._processos:
            print("No processor found, no data")
            return

        # Se houver, loop por cada um deles
        for proc in self._processos:
            class_name = proc.__class__.__name__
            total_processado = self._stats[class_name]
            resto = len(proc._storage)

            # Para seguir o PDF, mudo o nome para adicionar um espaço antes
            replace = class_name.replace("Processor", " Processor")
            print(f"{replace}: total {total_processado} items processed, "
                  f"remaining {resto} on processor"
            )
