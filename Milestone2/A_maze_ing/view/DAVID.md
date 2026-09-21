# A-Maze-ing — Nota de alinhamento
 
Já comecei o projeto sozinho enquanto não te consegui contactar, pra não perder tempo.
Fica aqui tudo o que decidi e o estado atual — se quiseres mudar algo, à vontade,
mas isto evita retrabalho enquanto não falamos.
 
## Divisão de trabalho proposta
 
- **Eu (Xandão): engine (backend)** — parser de config, classe `MazeGenerator`
  (geração + validação estrutural + solver BFS), writer do output hex,
  empacotamento pip (`mazegen-*.whl`), `LICENSE.md`.
- **Tu: visualização + interação (view/)** — renderer (ASCII ou MLX), menu
  interativo (regenerar, show/hide path, trocar cores), consumindo só a
  API pública da minha classe. Não precisas de mexer em nada dentro de `mazegen/`.
Faz sentido essa divisão porque o enunciado já exige que a geração seja uma
classe importável, standalone, empacotável em wheel — ou seja, o motor tem de
ser independente da visualização de qualquer forma. Isso já é o contrato
natural entre nós.
 
## Contrato de interface — o que vais consumir
 
```python
from mazegen import MazeGenerator
 
m = MazeGenerator(
    width=20, height=15,
    entry=(0, 0), exit_pos=(19, 14),
    perfect=True, seed=42,
)
m.generate()
 
m.get_cell_walls(x, y)   # -> int, bitmask: North=1, East=2, South=4, West=8
                          #    bit ligado = parede FECHADA, desligado = aberta
m.solve()                 # -> list[str], ex: ['E','E','S','S',...] caminho mais curto
m.width, m.height, m.entry, m.exit_pos, m.seed   # atributos públicos
```
 
Não precisas de saber nada do que está por dentro — só isto. Se precisares
de mais alguma coisa da classe (ex: exportar todas as paredes de uma vez em
vez de célula a célula), avisa que eu adiciono um método.
 
## Estrutura de pastas (já criada no repo)
 
```
a-maze-ing/
├── a_maze_ing.py          ← orquestrador (config -> gera -> escreve output -> chama view)
├── config.txt              ← config default
├── config.py                ← parser (MazeConfig, ConfigError)
├── mazegen/                 ← MEU território, não mexer
│   ├── __init__.py
│   ├── generator.py
│   ├── encoding.py           (ainda por fazer: to_hex_rows)
│   └── solver.py             (lógica do solve() pode migrar pra cá)
├── view/                    ← TEU território
│   └── __init__.py
├── pyproject.toml           ← já criado (mínimo, vamos expandir)
├── uv.lock
├── Makefile, README.md, LICENSE.md, .gitignore
```
 
## Decisão: `uv` como gestor de dependências
 
Estou a usar `uv` (não `pip`/`venv` direto). Se ainda não tens instalado:
```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
uv sync          # instala tudo igual ao meu ambiente, a partir do uv.lock
uv run python a_maze_ing.py config.txt
```
`uv.lock` está commitado — garante que ficamos com as mesmas versões exatas
de tudo, sem "funciona na minha máquina só".
 
## Decisão: `rich` na camada de visualização
 
Quero fugir do labirinto "quadrado maciço" clássico — pensei em usar a lib
`rich` pro terminal: cores true-color, caracteres de desenho Unicode
(`─ │ ┌ ┐ └ ┘` em vez de `+ - |`), e possivelmente animação da geração ao
vivo (`rich.live.Live` — isto cobre o bónus "animation during maze
generation" do Capítulo VIII de graça).
 
Isto é território teu (`view/`), então é só sugestão — se preferires outra
abordagem (MLX, ASCII puro, `curses`), tudo bem, o contrato acima não muda.
Só avisa qual escolheste pra eu saber se preciso adicionar algo à classe.
 
Se topares `rich`: `uv add rich` (já fica registado no pyproject.toml pra todos).
 
## Estado atual (o que já está pronto e testado)
 
- [x] `config.py` completo — parsing, validação, `ConfigError` com mensagens claras
- [x] `MazeGenerator.__init__`, `get_cell_walls`, `generate()` (recursive
      backtracker iterativo, modo `PERFECT=True`) — testado visualmente,
      spanning tree válida, bordas fechadas
- [x] `solve()` (BFS) — em progresso
- [ ] `to_hex_rows()` — output pro ficheiro final
- [ ] Modo `PERFECT=False` (braiding — loops + Pac-Man rules)
- [ ] Padrão "42" + restrição de corredor ≤2 células
- [ ] Empacotamento pip (`mazegen-*.whl`) + `LICENSE.md`
- [ ] `view/` — todo teu
Qualquer dúvida, ou se quiseres mudar a divisão, me chama. Bora terminar isto.