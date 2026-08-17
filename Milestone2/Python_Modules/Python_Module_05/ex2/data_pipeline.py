#!/usr/bin/env python3

from abc import ABC, abstractmethod
from typing import Any, Protocol


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

    def ingest(self, data: int | float | list[int | float]) -> None:
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

    def ingest(self, data: str | list[str]) -> None:
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

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
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

        self._processos: list[DataProcessor] = []
        self._stats: dict[str, int] = {}

    def register_processor(self, proc: DataProcessor) -> None:

        self._processos.append(proc)
        class_name = proc.__class__.__name__
        self._stats[class_name] = 0

    def process_stream(self, stream: list[Any]) -> None:
        for elemento in stream:
            processado = False

            for proc in self._processos:
                if proc.validate(elemento):

                    quant_origin = len(proc._storage)

                    proc.ingest(elemento)

                    quant_att = len(proc._storage)

                    class_name = proc.__class__.__name__
                    self._stats[class_name] += quant_att - quant_origin

                    processado = True
                    break

            if not processado:
                print(
                        "DataStream error - Can't process element in stream: "
                        f"{elemento}"
                )

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")

        if not self._processos:
            print("No processor found, no data")
            return

        for proc in self._processos:
            class_name = proc.__class__.__name__
            total_processado = self._stats[class_name]
            resto = len(proc._storage)

            replace = class_name.replace("Processor", " Processor")
            print(f"{replace}: total {total_processado} items processed, "
                  f"remaining {resto} on processor")

    def output_pipeline(self, nb: int, plugin: "ExportPlugin") -> None:
        for proc in self._processos:
            lote: list[tuple[int, str]] = []
            for _ in range(nb):
                try:
                    lote.append(proc.output())
                except IndexError:
                    break
            if lote:
                plugin.process_output(lote)

class ExportPlugin(Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...

class CSVExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        linha = ",".join(valor for _, valor in data)
        print("CSV output: ")
        print(linha)

class JSONExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        pares = [
            f'"item_{rank}": "{valor}"'
            for rank, valor in data
        ]
        print("JSON output: ")
        print("{" + ", ".join(pares)+ "}")


if __name__ == "__main__":
    print("=== Code Nexus - Data Pipeline ===\n")

    print("Initialize Data Stream...")
    stream = DataStream()
    stream.print_processors_stats()
    print()

    print("Registering Processors\n")
    stream.register_processor(NumericProcessor())
    stream.register_processor(TextProcessor())
    stream.register_processor(LogProcessor())

    batch_1 = [
        'Hello World',
        [3.14, -1, 2.71],
        [
            {'log_level': 'WARNING', 'log_message':
             'Telnet access! Use ssh instead'},
            {'log_level': 'INFO', 'log_message': 'User wil is connected'}
        ],
        42,
        ['Hi', 'five']        
    ]

    print(f"Send first batch of data on stream: {batch_1}")
    stream.process_stream(batch_1)
    print()
    stream.print_processors_stats()
    print()

    print("Send 3 processed data from each processor to a CSV plugin:")
    stream.output_pipeline(3, CSVExportPlugin())
    print()
    stream.print_processors_stats()
    print()

    batch_2 = [
        21,
        ['I love AI', 'LLMs are wonderful', 'Stay healthy'],
        [
            {'log_level': 'ERROR', 'log_message': '500 server crash'},
            {'log_level': 'NOTICE', 'log_message': 'Certificate expires in 10 days'}
        ],
        [32, 42, 64, 84, 128, 168],
        'World hello'
    ]

    print(f"Send another batch of data: {batch_2}")
    stream.process_stream(batch_2)
    print()
    stream.print_processors_stats()
    print()

    print("Send 5 processed data from each processor to a JSON plugin:")
    stream.output_pipeline(5, JSONExportPlugin())
    print()
    stream.print_processors_stats()
