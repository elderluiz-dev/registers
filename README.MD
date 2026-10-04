# DFC-8 - Microcontrolador

O projeto foi desenvolvido para a disciplina de Estrutura de Dados, com o objetivo de simular um microcontrolador de 8 bits que possui dois registradores, um de controle de fluxo de dados (CTRL_CTRL) e outro para notificar quando a fila ou a pilha estão cheias (DATA0_STATUS).

## Integrantes

- Elder Luiz
- Ray Samuel
- Ruan Victor

## Compilação e Execução

O projeto utiliza um `Makefile` para automatizar o processo de compilação. Para compilar todos os arquivos-fonte e gerar o executável, basta executar o seguinte comando no terminal, a partir do diretório raiz do projeto:

```bash
make
```

Após a compilação, um arquivo executável (chamado `run`) será criado. Para executar o programa, use:

```bash
./run
```

Para limpar os arquivos objeto e o executável gerados, utilize:

```bash
make clean
```
