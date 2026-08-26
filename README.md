# ECOM042-CI
Repositório dedicado a reserva de CI voltadas a correções das atividades.

## Como funciona

Workflow reutilizável (`.github/workflows/check-activity.yml`) chamado pelos
repositórios de atividade (ex: `ECOM042-monitoria`) quando um aluno abre PR.
Atualmente roda em runner hospedado pelo GitHub (`ubuntu-latest`), pra testes
iniciais do CI — dá pra trocar depois pra `self-hosted` só mudando `runs-on`.
Ele roda, em sequência:

1. **clang-format** — `--dry-run --Werror` com o estilo em `.clang-format`.
2. **Build** — `west build` pra `native_sim` usando o código do PR.
3. **Testes internos** — copia `atividades/<nome-da-atividade>/testcase.yaml`
   pro repo do aluno e roda `west twister`; se existir
   `atividades/<nome-da-atividade>/unit/testcase.yaml`, roda também como um
   segundo test root (testes unitários ztest, separados do app do aluno).

A atividade é identificada pelo nome da branch do PR (ex: `Atividade-01`), que
precisa ter uma pasta correspondente em `atividades/`.

## Adicionar uma atividade nova

Criar `atividades/<Nome-Da-Atividade>/testcase.yaml` com o harness/regex (ou
outro tipo de harness do Twister) que valida o comportamento esperado do app
do aluno (build + saída). Não precisa mexer no código do aluno nem no
workflow.

### Testes unitários (opcional)

Pra testar função(ões) isoladas do aluno via ztest (não só a saída do app
inteiro), criar `atividades/<Nome-Da-Atividade>/unit/` com um app de teste
próprio (`CMakeLists.txt`, `prj.conf`, `src/test_main.c`, `testcase.yaml`).
O `CMakeLists.txt` pode incluir arquivos-fonte do aluno via
`$ENV{STUDENT_SRC_DIR}` (setado automaticamente pelo CI, apontando pro
checkout do aluno), ex:

```cmake
target_sources(app PRIVATE $ENV{STUDENT_SRC_DIR}/src/logica.c)
target_include_directories(app PRIVATE $ENV{STUDENT_SRC_DIR}/src)
```

Ver `atividades/Atividade-01/unit/` como esqueleto de referência.

## Runner atual: GitHub-hosted (`ubuntu-latest`)

Cada run instala tudo do zero (`apt`, `pip`, `west init/update` clonando o
Zephyr). Simples e sem infra pra manter, mas lento (west update baixa o
Zephyr inteiro) — ok pra validar o pipeline agora.

Pré-requisito no repositório de atividade: um `west.yml` na raiz com
`self.path: application` importando o manifest oficial do Zephyr (é o que
permite `west init -l zephyrproject/application` funcionar sem workspace
pré-existente).

## Migrar pra runner self-hosted (quando fizer sentido)

1. Registrar `actions-runner` do GitHub no repositório ou organização
   (precisa enxergar `ECOM042-monitoria` e `ECOM042-CI`).
2. `west init && west update` uma vez num diretório fixo local (ex.:
   `/opt/zephyrproject`), com `west`, `twister` e `clang-format` no `PATH`.
3. Trocar `runs-on: ubuntu-latest` por `runs-on: self-hosted` no job
   `corrigir`, remover os passos de instalação (`apt-get`, `pip install
   west`, `west init/update`, requirements) e usar `working-directory`
   apontando pro workspace fixo em vez de `zephyrproject/` local ao runner.
