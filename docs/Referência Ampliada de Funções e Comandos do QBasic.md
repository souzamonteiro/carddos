# 📘 **Referência Ampliada de Funções e Comandos do QBasic**

## 1️⃣ **Entrada e Saída**

| Comando/Função | Descrição                                  | Parâmetros                        |
| -------------- | ------------------------------------------ | --------------------------------- |
| `PRINT`        | Exibe texto ou valores na tela.            | `PRINT expressão[, expressão...]` |
| `INPUT`        | Lê entrada do usuário.                     | `INPUT [mensagem;] variável`      |
| `LINE INPUT`   | Lê uma linha completa incluindo espaços.   | `LINE INPUT [mensagem;] variável` |
| `LOCATE`       | Move o cursor para uma posição específica. | `LOCATE linha, coluna`            |
| `CLS`          | Limpa a tela.                              | Nenhum                            |
| `COLOR`        | Define cor do texto e fundo.               | `COLOR texto[, fundo]`            |

---

## 2️⃣ **Controle de Fluxo**

| Comando/Função     | Descrição                              | Parâmetros                             |
| ------------------ | -------------------------------------- | -------------------------------------- |
| `IF...THEN...ELSE` | Estrutura condicional.                 | `IF condição THEN ... ELSE ...`        |
| `SELECT CASE`      | Múltiplas condições.                   | `SELECT CASE expressão ... END SELECT` |
| `FOR...NEXT`       | Laço com contador.                     | `FOR var = início TO fim [STEP passo]` |
| `WHILE...WEND`     | Laço enquanto condição for verdadeira. | `WHILE condição ... WEND`              |
| `DO...LOOP`        | Laço com teste no início ou fim.       | `DO [WHILE/UNTIL condição] ... LOOP`   |
| `GOTO`             | Salta para um rótulo.                  | `GOTO rótulo`                          |
| `GOSUB...RETURN`   | Chama um sub-bloco e retorna.          | `GOSUB rótulo`                         |

---

## 3️⃣ **Manipulação de Variáveis e Dados**

| Comando/Função | Descrição                                   | Parâmetros               |
| -------------- | ------------------------------------------- | ------------------------ |
| `DIM`          | Declara variável ou matriz.                 | `DIM nome[(tamanho)]`    |
| `LET`          | Atribui valor (opcional, pode ser omitido). | `LET var = valor`        |
| `CONST`        | Define constante.                           | `CONST nome = valor`     |
| `DATA`         | Armazena valores de dados para `READ`.      | `DATA valor1, valor2...` |
| `READ`         | Lê valores de `DATA`.                       | `READ var1, var2...`     |
| `RESTORE`      | Reinicia leitura de `DATA`.                 | Nenhum                   |

---

## 4️⃣ **Funções Numéricas**

| Função     | Descrição                              | Parâmetros |
| ---------- | -------------------------------------- | ---------- |
| `ABS(x)`   | Valor absoluto.                        | `x`        |
| `SGN(x)`   | Sinal (-1, 0, 1).                      | `x`        |
| `SQR(x)`   | Raiz quadrada.                         | `x ≥ 0`    |
| `INT(x)`   | Parte inteira (arredonda para baixo).  | `x`        |
| `FIX(x)`   | Parte inteira truncada.                | `x`        |
| `ROUND(x)` | Arredonda para o inteiro mais próximo. | `x`        |
| `RND`      | Número aleatório entre 0 e 1.          | Nenhum     |
| `SIN(x)`   | Seno (x em radianos).                  | `x`        |
| `COS(x)`   | Cosseno.                               | `x`        |
| `TAN(x)`   | Tangente.                              | `x`        |
| `ATN(x)`   | Arco-tangente.                         | `x`        |
| `LOG(x)`   | Logaritmo natural.                     | `x > 0`    |
| `EXP(x)`   | e^x.                                   | `x`        |

---

## 5️⃣ **Funções de Strings**

| Função                   | Descrição                           | Parâmetros        |
| ------------------------ | ----------------------------------- | ----------------- |
| `LEN(s)`                 | Tamanho da string.                  | `s`               |
| `LEFT$(s, n)`            | N primeiros caracteres.             | `s, n`            |
| `RIGHT$(s, n)`           | N últimos caracteres.               | `s, n`            |
| `MID$(s, start[, len])`  | Substring.                          | `s, start, [len]` |
| `INSTR([start,] s1, s2)` | Posição de s2 em s1.                | `start, s1, s2`   |
| `LTRIM$(s)`              | Remove espaços à esquerda.          | `s`               |
| `RTRIM$(s)`              | Remove espaços à direita.           | `s`               |
| `TRIM$(s)`               | Remove espaços nas extremidades.    | `s`               |
| `SPACE$(n)`              | String com n espaços.               | `n`               |
| `STRING$(n, ch)`         | Repete caractere.                   | `n, ch`           |
| `CHR$(code)`             | Caractere ASCII de código.          | `code`            |
| `ASC(s)`                 | Código ASCII do primeiro caractere. | `s`               |

---

## 6️⃣ **Gráficos**

| Comando/Função | Descrição                       | Parâmetros                           |
| -------------- | ------------------------------- | ------------------------------------ |
| `SCREEN`       | Muda o modo de vídeo.           | `SCREEN modo`                        |
| `PSET`         | Plota um pixel.                 | `PSET (x, y), cor`                   |
| `LINE`         | Desenha linha ou caixa.         | `LINE (x1, y1)-(x2, y2), cor[, B/F]` |
| `CIRCLE`       | Desenha círculo.                | `CIRCLE (x, y), raio[, cor]`         |
| `PAINT`        | Preenche área.                  | `PAINT (x, y), cor`                  |
| `DRAW`         | Desenha com comandos vetoriais. | `DRAW string`                        |
| `POINT`        | Cor de um pixel.                | `POINT(x, y)`                        |

---

## 7️⃣ **Som**

| Comando/Função | Descrição          | Parâmetros                  |
| -------------- | ------------------ | --------------------------- |
| `BEEP`         | Som padrão.        | Nenhum                      |
| `SOUND`        | Gera tom.          | `SOUND frequência, duração` |
| `PLAY`         | Música via string. | `PLAY string`               |

---

## 8️⃣ **Arquivos**

| Comando/Função | Descrição           | Parâmetros                   |
| -------------- | ------------------- | ---------------------------- |
| `OPEN`         | Abre arquivo.       | `OPEN nome FOR modo AS #n`   |
| `CLOSE`        | Fecha arquivo.      | `CLOSE [#n]`                 |
| `PRINT #`      | Escreve em arquivo. | `PRINT #n, dados`            |
| `INPUT #`      | Lê de arquivo.      | `INPUT #n, variáveis`        |
| `LINE INPUT #` | Lê linha inteira.   | `LINE INPUT #n, variável`    |
| `EOF(n)`       | Fim de arquivo.     | `n`                          |
| `GET` / `PUT`  | Acesso aleatório.   | `GET #n, registro, variável` |

---

## 9️⃣ **Sistema**

| Comando/Função | Descrição                  | Parâmetros        |
| -------------- | -------------------------- | ----------------- |
| `TIMER`        | Segundos desde meia-noite. | Nenhum            |
| `DATE$`        | Data atual (string).       | Nenhum            |
| `TIME$`        | Hora atual (string).       | Nenhum            |
| `RANDOMIZE`    | Semente para `RND`.        | `RANDOMIZE timer` |
| `SYSTEM`       | Sai do QBasic.             | Nenhum            |
| `SHELL`        | Executa comando do DOS.    | `SHELL comando$`  |

---

