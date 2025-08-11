# 📚 Referência de Funções e Comandos do QBasic

## 1️⃣ **Entrada e Saída de Dados**

| Comando/Função    | Descrição                                  |
| ----------------- | ------------------------------------------ |
| `PRINT`           | Exibe texto ou valores na tela.            |
| `INPUT`           | Lê valores digitados pelo usuário.         |
| `LINE INPUT`      | Lê uma linha inteira de texto.             |
| `CLS`             | Limpa a tela.                              |
| `LOCATE row, col` | Move o cursor para a posição especificada. |
| `WIDTH`           | Define a largura da tela ou da impressora. |

---

## 2️⃣ **Controle de Fluxo**

| Comando/Função         | Descrição                                     |
| ---------------------- | --------------------------------------------- |
| `IF ... THEN ... ELSE` | Estrutura condicional.                        |
| `SELECT CASE`          | Estrutura condicional múltipla.               |
| `FOR ... TO ... STEP`  | Loop com contador.                            |
| `NEXT`                 | Finaliza o `FOR`.                             |
| `WHILE ... WEND`       | Loop enquanto condição for verdadeira.        |
| `DO ... LOOP`          | Loop até ou enquanto condição for satisfeita. |
| `GOTO`                 | Salta para um rótulo especificado.            |
| `GOSUB` / `RETURN`     | Chama e retorna de uma sub-rotina.            |
| `END`                  | Finaliza o programa.                          |
| `STOP`                 | Interrompe temporariamente a execução.        |

---

## 3️⃣ **Variáveis e Tipos**

| Tipo      | Sufixo | Descrição                            |
| --------- | ------ | ------------------------------------ |
| `INTEGER` | `%`    | Inteiro de 16 bits (-32768 a 32767). |
| `LONG`    | `&`    | Inteiro de 32 bits.                  |
| `SINGLE`  | `!`    | Ponto flutuante de precisão simples. |
| `DOUBLE`  | `#`    | Ponto flutuante de precisão dupla.   |
| `STRING`  | `$`    | Cadeia de caracteres.                |

Funções relacionadas:

* `DIM` — Declara variáveis (e matrizes).
* `REDIM` — Redimensiona matrizes dinâmicas.
* `TYPE` — Define tipos compostos.

---

## 4️⃣ **Funções Numéricas**

| Função                         | Descrição                              |
| ------------------------------ | -------------------------------------- |
| `ABS(x)`                       | Valor absoluto.                        |
| `SGN(x)`                       | Sinal do número (-1, 0, 1).            |
| `INT(x)`                       | Parte inteira (arredonda para baixo).  |
| `FIX(x)`                       | Parte inteira sem arredondar (trunca). |
| `SQR(x)`                       | Raiz quadrada.                         |
| `RND`                          | Número aleatório (0 a 1).              |
| `SIN(x)` / `COS(x)` / `TAN(x)` | Funções trigonométricas.               |
| `ATN(x)`                       | Arco-tangente.                         |
| `LOG(x)`                       | Logaritmo natural.                     |
| `EXP(x)`                       | Exponencial (e^x).                     |

---

## 5️⃣ **Funções de Strings**

| Função                      | Descrição                           |
| --------------------------- | ----------------------------------- |
| `LEN(s$)`                   | Comprimento da string.              |
| `LEFT$(s$, n)`              | n primeiros caracteres.             |
| `RIGHT$(s$, n)`             | n últimos caracteres.               |
| `MID$(s$, start, len)`      | Substring.                          |
| `INSTR([start, ] s1$, s2$)` | Posição de s2\$ em s1\$.            |
| `CHR$(n)`                   | Caractere ASCII do código `n`.      |
| `ASC(s$)`                   | Código ASCII do primeiro caractere. |
| `LCASE$(s$)`                | Converte para minúsculas.           |
| `UCASE$(s$)`                | Converte para maiúsculas.           |
| `STRING$(n, c$)`            | Repete um caractere n vezes.        |
| `SPACE$(n)`                 | Espaços em branco.                  |

---

## 6️⃣ **Manipulação de Arquivos**

| Comando/Função | Descrição                                                  |
| -------------- | ---------------------------------------------------------- |
| `OPEN`         | Abre arquivo (modo INPUT, OUTPUT, APPEND, RANDOM, BINARY). |
| `CLOSE`        | Fecha arquivo.                                             |
| `PRINT #`      | Escreve em arquivo.                                        |
| `INPUT #`      | Lê de arquivo.                                             |
| `LINE INPUT #` | Lê linha de arquivo.                                       |
| `GET` / `PUT`  | Leitura e escrita em acesso aleatório.                     |
| `FIELD`        | Associa variáveis a campos de arquivo.                     |
| `LOF(n)`       | Tamanho do arquivo em bytes.                               |
| `EOF(n)`       | Fim do arquivo.                                            |
| `SEEK(n)`      | Posição do ponteiro do arquivo.                            |
| `KILL`         | Exclui arquivo.                                            |
| `NAME`         | Renomeia arquivo.                                          |

---

## 7️⃣ **Gráficos**

| Comando/Função                  | Descrição                              |
| ------------------------------- | -------------------------------------- |
| `SCREEN`                        | Define modo gráfico ou texto.          |
| `PSET (x, y), color`            | Plota pixel.                           |
| `PRESET (x, y)`                 | Apaga pixel.                           |
| `LINE (x1, y1)-(x2, y2), color` | Linha.                                 |
| `CIRCLE (x, y), r, color`       | Círculo.                               |
| `PAINT (x, y), color`           | Preenche área.                         |
| `DRAW`                          | Desenha formas via string de comandos. |
| `COLOR fg, bg`                  | Define cores de texto.                 |
| `POINT(x, y)`                   | Obtém cor de pixel.                    |

---

## 8️⃣ **Som**

| Comando/Função    | Descrição                      |
| ----------------- | ------------------------------ |
| `BEEP`            | Emite bip padrão.              |
| `SOUND freq, dur` | Frequência e duração.          |
| `PLAY "string"`   | Música usando notação interna. |

---

## 9️⃣ **Outras Funções Úteis**

| Função      | Descrição                        |
| ----------- | -------------------------------- |
| `TIMER`     | Segundos desde a meia-noite.     |
| `DATE$`     | Data atual.                      |
| `TIME$`     | Hora atual.                      |
| `RANDOMIZE` | Semente para números aleatórios. |
| `SYSTEM`    | Sai para o DOS.                  |

---

