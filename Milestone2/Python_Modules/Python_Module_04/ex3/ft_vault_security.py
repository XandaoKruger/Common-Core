#!/usr/bin/env python3


def secure_archive(
    nome: str, action: str = "r", conteudo: str = ""
) -> tuple[bool, str]:
    try:

        # substitui open()+close() manual; garante fechamento mesmo com
        # exceção, via protocolo __enter__/__exit__
        with open(nome, action) as f:
            if action == "r":
                conteudo = f.read()
                return (True, conteudo)
            else:
                f.write(conteudo)
                return (True, "Content successfully written to file")
    except OSError as error:
        return (False, str(error))


if __name__ == "__main__":
    print("=== Cyber Archives Security ===\n")

    print("Using 'secure_archive' to read from a nonexistent file:")
    # 1º caso -> arquivo que não existente
    print(secure_archive("/not/existing/file"))
    print()

    print("Using 'secure_archive' to read from an inaccessible file:")
    # 2º caso -> arquivo existe mas sem permissão de leitura
    print(secure_archive("/etc/shadow"))  # /etc/master.passwd -> no linux
    print()

    print("Using 'secure_archive' to read from a regular file:")
    # 3º caso -> leitura normal, sem erro. Lê ("r") o arquivo
    print(secure_archive("ancient_fragment.txt"))
    print()

    print("Using 'secure_archive' to write previous content to a new file:")
    # 4º caso -> Entra no caso else, e retorna a mensagem de que o conteudo foi
    # escrito ("w") com sucesso
    print(secure_archive("output.txt", "w", "algum conteúdo aqui"))

# cat > ancient_fragment.txt << 'EOF'
# [FRAGMENT 001] Digital preservation protocols established 2087
# [FRAGMENT 002] Knowledge must survive the entropy wars
# [FRAGMENT 003] Every byte saved is a victory against oblivion
# EOF
