# Introdução ao WebAssembly

## **Introdução ao WebAssembly (Wasm): Arquitetura, Compiladores e Simuladores**  

### **O Que é WebAssembly?**  
O **WebAssembly (Wasm)** é um formato de código binário de baixo nível e alta performance, projetado para execução em navegadores modernos. Ele complementa o JavaScript, permitindo que linguagens como C, C++, Rust e Go sejam compiladas para um formato eficiente que roda na web com desempenho próximo ao nativo.  

### **Arquitetura do WebAssembly**  
1. **Baseado em Pilha Virtual**:  
   - Wasm usa uma **máquina de pilha** para execução (em contraste com registradores, como em RISC-V).  
   - Instruções operam sobre valores na pilha (ex: `i32.add` consome dois valores do topo e empilha o resultado).  

2. **Tipos de Dados**:  
   - Suporta tipos primitivos: `i32`, `i64`, `f32`, `f64`.  
   - Não há tipos complexos nativos (estruturas são simuladas via memória linear).  

3. **Memória Linear**:  
   - Um array binário de tamanho ajustável (`memory.grow`).  
   - Acessado via loads/stores (ex: `i32.load offset=4`).  

4. **Módulos**:  
   - Programas Wasm são organizados em **módulos** (.wasm) com funções, memória, tabelas e globais.  

5. **Segurança**:  
   - Execução em **sandbox** (isolada do sistema hospedeiro).  
   - Verificação estática de tipos antes da execução.  

---

### **Compiladores para WebAssembly**
1. **Emscripten (C/C++)**:  
   - Ferramenta mais popular para compilar código C/C++ para Wasm + JavaScript.  
   - Exemplo:  
     ```bash
     emcc hello.c -o hello.html
     ```  

2. **Rust**:  
   - Suporte nativo via `wasm-pack`.  
   - Exemplo:  
     ```bash
     wasm-pack build --target web
     ```  

3. **LLVM (Clang/Flang)**:  
   - Gera Wasm através do backend `wasm32-unknown-unknown`.  

4. **AssemblyScript (TypeScript-like)**:  
   - Compila um subconjunto de TypeScript para Wasm.  

---

### **Simuladores e Runtimes**  
1. **Navegadores**:  
   - Chrome, Firefox, Safari e Edge suportam Wasm nativamente.  
   - Carregamento via JavaScript:  
     ```javascript
     WebAssembly.instantiateStreaming(fetch('program.wasm'))
       .then(obj => obj.instance.exports.function());
     ```  

2. **Wasmtime (Standalone)**:  
   - Runtime independente para executar Wasm fora do navegador.  
   - Exemplo:  
     ```bash
     wasmtime program.wasm
     ```  

3. **WABT (WebAssembly Binary Toolkit)**:  
   - Ferramentas como `wasm2wat` (binário para texto) e `wat2wasm` (texto para binário).  

4. **Simuladores Didáticos**:  
   - **Wasmi**: Interpretador em Rust para fins educacionais.  
   - **TinyGo**: Compilador Go para Wasm com foco em microcontroladores.  

---

### **Comparação com Outras Arquiteturas**  
| Característica       | WebAssembly       | RISC-V           | x86              |
|----------------------|-------------------|------------------|------------------|
| **Modelo**           | Pilha Virtual     | Registradores    | Registradores    |
| **Alvo Principal**   | Navegadores/Web   | Embarcados/Serv. | Desktops/Serv.   |
| **Segurança**        | Sandbox Rigoroso  | Depende do HW    | Modo Protegido   |
| **Portabilidade**    | Universal         | Multiplataforma  | Limitada a x86   |

---

### **Exemplo de Código Wasm (Formato Textual - WAT)**  
```wat
(module
  (func $add (param $a i32) (param $b i32) (result i32)
    local.get $a
    local.get $b
    i32.add
  )
  (export "add" (func $add))
```
- **Compilação**:  
  ```bash
  wat2wasm add.wat -o add.wasm
  ```

---

### **Conclusão**  
O WebAssembly é uma revolução para a web, trazendo desempenho próximo ao nativo e interoperabilidade com múltiplas linguagens. Seu design seguro e portável o torna útil não só em navegadores, mas também em **edge computing**, **blockchain** (ex: Ethereum WASM) e **plugins de aplicativos**.  

## Referência das Instruções

### **📌 Instruções Básicas (Stack-Based)**
#### **Constantes**
| Instrução  | Descrição               | Exemplo (WAT)        |
|------------|-------------------------|----------------------|
| `i32.const` | Empilha um `i32`        | `(i32.const 42)`     |
| `i64.const` | Empilha um `i64`        | `(i64.const 100)`    |
| `f32.const` | Empilha um `f32`        | `(f32.const 3.14)`   |
| `f64.const` | Empilha um `f64`        | `(f64.const 2.718)`  |

#### **Aritméticas (Inteiros)**
| Instrução  | Descrição               | Exemplo (WAT)        |
|------------|-------------------------|----------------------|
| `i32.add`  | Soma `i32`              | `(i32.add)`          |
| `i32.sub`  | Subtrai `i32`           | `(i32.sub)`          |
| `i32.mul`  | Multiplica `i32`        | `(i32.mul)`          |
| `i32.div_s`| Divisão (signed)        | `(i32.div_s)`        |

#### **Aritméticas (Ponto Flutuante)**
| Instrução  | Descrição               | Exemplo (WAT)        |
|------------|-------------------------|----------------------|
| `f32.add`  | Soma `f32`              | `(f32.add)`          |
| `f64.sqrt` | Raiz quadrada `f64`     | `(f64.sqrt)`         |

---

### **📌 Controle de Fluxo**
#### **Branches e Loops**
| Instrução      | Descrição                          | Exemplo (WAT)                     |
|----------------|------------------------------------|-----------------------------------|
| `if` / `else`  | Condicional                        | `(if (i32.eqz) (then ...) (else ...))` |
| `loop`         | Loop infinito                      | `(loop $label ...)`               |
| `br`           | Branch (jump) para label           | `(br $label)`                     |
| `br_if`        | Branch condicional                 | `(br_if $label (i32.eqz))`        |

#### **Exemplo de Loop (Contagem Regressiva)**
```wat
(func $countdown (param $n i32)
  (loop $loop
    (local.set $n (i32.sub (local.get $n) (i32.const 1)))
    (br_if $loop (i32.gt_s (local.get $n) (i32.const 0)))
  )
)
```

---

### **📌 Memória**
#### **Load/Store**
| Instrução          | Descrição                          | Exemplo (WAT)                     |
|--------------------|------------------------------------|-----------------------------------|
| `i32.load`         | Carrega `i32` da memória          | `(i32.load offset=4)`             |
| `i64.store`        | Armazena `i64` na memória         | `(i64.store (i64.const 123))`     |
| `memory.grow`      | Aumenta memória linear             | `(memory.grow (i32.const 1))`     |

#### **Exemplo de Acesso à Memória**
```wat
(module
  (memory 1)  ; 1 página (64KB)
  (func $store (param $addr i32) (param $value i32)
    (i32.store (local.get $addr) (local.get $value))
  )
)
```

---

### **📌 Funções**
| Instrução      | Descrição                          | Exemplo (WAT)                     |
|----------------|------------------------------------|-----------------------------------|
| `call`         | Chama uma função                   | `(call $func)`                    |
| `return`       | Retorna de uma função              | `(return)`                        |

#### **Exemplo de Função Exportada**
```wat
(module
  (func $add (param $a i32) (param $b i32) (result i32)
    (i32.add (local.get $a) (local.get $b))
  )
  (export "add" (func $add))  ; Exporta para JavaScript
)
```

---

### **📌 Operações Lógicas/Comparação**
| Instrução      | Descrição                          | Exemplo (WAT)                     |
|----------------|------------------------------------|-----------------------------------|
| `i32.eqz`      | Testa se zero                      | `(i32.eqz (i32.const 0))` → `1`   |
| `i32.eq`       | Igualdade                          | `(i32.eq (i32.const 5) (i32.const 5))` → `1` |
| `i32.lt_s`     | Menor que (signed)                 | `(i32.lt_s (i32.const 3) (i32.const 5))` → `1` |

---

### **📌 SIMD (Opcional)**
Instruções vetoriais para paralelismo (ativadas com a flag `-msimd128`):
```wat
(module
  (func $vec_add (result v128)
    (v128.const i32x4 1 2 3 4)  ; Vetor [1, 2, 3, 4]
    (v128.const i32x4 5 6 7 8)
    (i32x4.add)                 ; Soma vetorial
  )
)
```

---

### **📌 Referência Rápida de Tipos**
| Tipo     | Descrição          | Tamanho |
|----------|--------------------|---------|
| `i32`    | Inteiro 32-bit     | 4 bytes |
| `i64`    | Inteiro 64-bit     | 8 bytes |
| `f32`    | Float 32-bit       | 4 bytes |
| `f64`    | Float 64-bit       | 8 bytes |
| `v128`   | Vetor 128-bit      | 16 bytes|

---

### **📌 Ferramentas Úteis**
1. **Compilação**:
   - **Emscripten**: `emcc file.c -o file.wasm`
   - **wat2wasm**: Converte texto (.wat) para binário (.wasm).
     ```bash
     wat2wasm input.wat -o output.wasm
     ```

2. **Depuração**:
   - **wasm-objdump**: Inspeciona binários.
     ```bash
     wasm-objdump -x file.wasm
     ```

3. **Runtimes**:
   - **Node.js**: 
     ```javascript
     const wasm = await WebAssembly.instantiate(fs.readFileSync('file.wasm'));
     ```

---

### **📚 Referências**
- **Documentação Oficial**: [WebAssembly.org](https://webassembly.org/)
- **MDN Web Docs**: [Guia Wasm](https://developer.mozilla.org/en-US/docs/WebAssembly)

## Ponteiros em WebAssembly

### 1. **Memória Linear em WebAssembly**
   - O Wasm tem um modelo de **memória linear contígua**, que é um grande array de bytes. Esse é o único tipo de memória disponível (não há múltiplos espaços de endereçamento como em sistemas tradicionais).
   - Quando o código C é compilado para Wasm, todos os ponteiros acabam se referindo a offsets (deslocamentos) nessa memória linear.

### 2. **Ponteiros como Offsets**
   - Um ponteiro em C compilado para Wasm é simplesmente um **inteiro de 32 bits (ou 64 bits, dependendo do target)** que representa um offset na memória linear.
   - Por exemplo, se você tem `int* ptr = &var;`, `ptr` será um número como `0x1000`, que é a posição onde `var` está armazenada na memória linear do Wasm.

### 3. **Gerenciamento de Memória pelo Compilador**
   - Compiladores como **Emscripten (baseado em LLVM/Clang)** traduzem o código C/C++ para Wasm e geram um **"heap"** dentro da memória linear para alocações dinâmicas (`malloc`, `new`, etc.).
   - O compilador também cuida de:
     - **Alinhamento de dados** (Wasm exige alinhamento para acessos à memória).
     - **Conversão de ponteiros de/para índices** na memória linear.
     - **Aritmética de ponteiros** (que funciona como em C, mas dentro do espaço linear).

### 4. **Acesso à Memória em Wasm**
   - Instruções Wasm como `i32.load` ou `i64.store` são usadas para ler/escrever na memória linear usando offsets.
   - Exemplo (WAT - Textual format):
     ```wasm
     (i32.load offset=16 (local.get $ptr))  ; Lê um i32 na posição $ptr + 16
     ```

### 5. **Passagem de Ponteiros entre JavaScript e Wasm**
   - Quando você passa um ponteiro do JavaScript para Wasm (via `Module._malloc` no Emscripten), está passando um offset na memória linear.
   - O JavaScript **não pode acessar diretamente a memória do Wasm**, mas pode copiar dados para ela (usando `Module.HEAP8`, `Module.HEAP32`, etc.).

### 6. **Ponteiros para Funções**
   - Funções em Wasm são referenciadas por índices em uma tabela (não por endereços de memória).
   - O Emscriptem converte ponteiros de função em índices dessa tabela.

### 7. **Limitações**
   - Wasm não suporta **ponteiros brutos** como em C (não há acesso direto à memória do sistema hospedeiro).
   - Não há `pointer arithmetic` além do que é permitido pelo modelo de memória linear.

### Exemplo Prático (Emscripten)
Se você tem um código C:
```c
int* ptr = (int*)malloc(10 * sizeof(int));
ptr[3] = 42;
```
Isso será compilado para Wasm como:
1. Chamada para `malloc` (que aloca no heap do Wasm).
2. O `ptr` será um offset (ex: `0x1000`).
3. O acesso `ptr[3]` vira um `i32.store` no offset `0x1000 + 3 * 4`.

### Conclusão
Ponteiros em C compilado para Wasm são **offsets na memória linear**, gerenciados pelo compilador (Emscripten) e pelo runtime do Wasm. O modelo é mais simples que em sistemas nativos, mas mantém a semântica esperada do C (desde que você não espere recursos como múltiplos espaços de endereçamento ou ponteiros para dispositivos físicos).

## Exemplos
### **Código em C** (`example.c`)
```c
// Função que soma dois números
int add(int a, int b) {
    return a + b;
}

// Função que manipula ponteiros
void pointer_operations() {
    int x = 10;          // Variável local
    int* ptr = &x;       // Ponteiro para x
    *ptr = 20;           // Modifica x via ponteiro

    int arr[3] = {1, 2, 3};  // Array
    int* arr_ptr = arr;       // Ponteiro para array
    arr_ptr[1] = 5;           // Modifica arr[1] via ponteiro
}

// Função principal
int main() {
    int result = add(3, 4);  // Chama add()
    pointer_operations();     // Chama pointer_operations()
    return result;
}
```

---

### **Código WAT Gerado (Simplificado e Comentado)**
Aqui está uma versão simplificada do WAT que o Emscripten/Clang geraria, com comentários mostrando a relação com o código C:

```wasm
(module
  ;; =============================================
  ;; Seção de Memória (Heap para variáveis/ponteiros)
  ;; =============================================
  (memory (export "memory") 1)  ;; 1 página = 64KB (memória linear)

  ;; =============================================
  ;; Função 'add' (correspondente a int add(int a, int b))
  ;; =============================================
  (func $add (param $a i32) (param $b i32) (result i32)
    (i32.add
      (local.get $a)
      (local.get $b)
    )
  )

  ;; =============================================
  ;; Função 'pointer_operations' (manipulação de ponteiros)
  ;; =============================================
  (func $pointer_operations
    (local $x i32)       ;; int x = 10 (variável local)
    (local $ptr i32)     ;; int* ptr
    (local $arr_ptr i32) ;; int* arr_ptr
    (local $arr i32 i32 i32)  ;; int arr[3] = {1, 2, 3}

    ;; x = 10
    (i32.const 10)
    (local.set $x)

    ;; ptr = &x (x está no stack frame, digamos no offset 0)
    (i32.const 0)        ;; Assume-se que x está no offset 0 do stack
    (local.set $ptr)

    ;; *ptr = 20
    (i32.const 20)
    (local.get $ptr)
    (i32.store offset=0)  ;; Armazena 20 no endereço ptr (x)

    ;; Inicializa arr = {1, 2, 3}
    (i32.const 1)
    (local.set $arr 0)
    (i32.const 2)
    (local.set $arr 1)
    (i32.const 3)
    (local.set $arr 2)

    ;; arr_ptr = arr (endereço base do array)
    (i32.const 16)       ;; Assume-se que arr começa no offset 16
    (local.set $arr_ptr)

    ;; arr_ptr[1] = 5
    (i32.const 5)
    (local.get $arr_ptr)
    (i32.const 4)        ;; Offset = 1 * sizeof(int) = 4 bytes
    (i32.add)
    (i32.store offset=0) ;; Armazena 5 em arr[1]
  )

  ;; =============================================
  ;; Função 'main' (ponto de entrada)
  ;; =============================================
  (func $main (result i32)
    (local $result i32)

    ;; result = add(3, 4)
    (i32.const 3)
    (i32.const 4)
    (call $add)
    (local.set $result)

    ;; pointer_operations()
    (call $pointer_operations)

    ;; return result
    (local.get $result)
  )

  ;; Exportações (para JavaScript)
  (export "add" (func $add))
  (export "main" (func $main))
)
```

---

### **Explicação Detalhada**
#### **1. Memória em WAT**
- O Wasm usa uma **memória linear** declarada com `(memory 1)` (1 página = 64KB).
- Variáveis globais, alocações dinâmicas (`malloc`) e stacks são mapeados aqui.

#### **2. Função `add`**
- Em C:
  ```c
  int add(int a, int b) { return a + b; }
  ```
- Em WAT:
  ```wasm
  (func $add (param $a i32) (param $b i32) (result i32)
    (i32.add (local.get $a) (local.get $b))
  )
  ```
  - Parâmetros são passados como `i32` (inteiros de 32 bits).
  - `i32.add` realiza a soma.

#### **3. Função `pointer_operations`**
- Em C:
  ```c
  int x = 10;
  int* ptr = &x;
  *ptr = 20;
  ```
- Em WAT:
  ```wasm
  (local $x i32)       ;; Aloca x no stack
  (local $ptr i32)     ;; Ponteiro como offset na memória
  (i32.const 10)       ;; x = 10
  (local.set $x)
  (i32.const 0)        ;; ptr = &x (assume offset 0)
  (local.set $ptr)
  (i32.const 20)       ;; *ptr = 20
  (local.get $ptr)
  (i32.store offset=0)  ;; Armazena 20 no endereço ptr
  ```
  - Ponteiros são **offsets na memória linear**.
  - `i32.store` escreve na memória (equivalente a `*ptr = 20`).

#### **4. Arrays e Aritmética de Ponteiros**
- Em C:
  ```c
  int arr[3] = {1, 2, 3};
  int* arr_ptr = arr;
  arr_ptr[1] = 5;
  ```
- Em WAT:
  ```wasm
  (local $arr i32 i32 i32)  ;; Array no stack
  (local $arr_ptr i32)      ;; Ponteiro para array
  (i32.const 16)            ;; Assume que arr começa no offset 16
  (local.set $arr_ptr)
  (i32.const 5)             ;; arr_ptr[1] = 5
  (local.get $arr_ptr)
  (i32.const 4)             ;; Offset = 1 * 4 bytes
  (i32.add)                 ;; Calcula endereço (arr_ptr + 4)
  (i32.store offset=0)      ;; Armazena 5
  ```
  - Acesso a arrays usa **aritmética de ponteiros** (offsets em bytes).

#### **5. Função `main`**
- Chama `add` e `pointer_operations`, retornando o resultado.

---

### **Observações Importantes**
1. **Stack Frame**:
   - No WAT real (gerado pelo Emscripten), variáveis locais são gerenciadas em um **stack frame** (não mostrado aqui por simplicidade).
2. **Otimizações**:
   - O compilador pode reorganizar variáveis ou eliminar ponteiros se possível.
3. **Heap vs Stack**:
   - `malloc` aloca no heap (gerenciado pelo Emscripten), enquanto variáveis locais vão para o stack.

Se você compilar com `emcc example.c -o example.wasm -s SIDE_MODULE=1` e depois usar `wasm2wat` para ver o WAT real, a estrutura será similar, mas mais complexa (com gerenciamento de memória adicional).

Vou criar um exemplo em C mais completo, incluindo estruturas de controle (`if`, `else`, `else if`, `while`, `do while`, `for`), e depois mostrar a versão em WAT (WebAssembly Text Format) com comentários explicando cada parte.  

---

### **Compilação de Código em C**
#### **Código em C** (`control_structures.c`)

```c
// Função que demonstra if, else if, else
int check_number(int num) {
    if (num > 0) {
        return 1;  // Positivo
    } 
    else if (num < 0) {
        return -1; // Negativo
    } 
    else {
        return 0;  // Zero
    }
}

// Função que demonstra while
int factorial_while(int n) {
    int result = 1;
    while (n > 0) {
        result *= n;
        n--;
    }
    return result;
}

// Função que demonstra do-while
int factorial_do_while(int n) {
    int result = 1;
    do {
        result *= n;
        n--;
    } while (n > 0);
    return result;
}

// Função que demonstra for loop
int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Função principal
int main() {
    int num = -5;
    int check = check_number(num);  // if-else if-else
    int fact_while = factorial_while(5);  // while
    int fact_dowhile = factorial_do_while(5);  // do-while
    int array[3] = {1, 2, 3};
    int sum = sum_array(array, 3);  // for loop
    return check + fact_while + fact_dowhile + sum;
}
```

---

#### **Código WAT Gerado (Comentado)**
Abaixo está uma versão simplificada, mas funcional, do WAT equivalente, com comentários mostrando como cada estrutura de controle é traduzida.

```wasm
(module
  ;; =============================================
  ;; Memória (necessária para arrays/ponteiros)
  ;; =============================================
  (memory (export "memory") 1)

  ;; =============================================
  ;; Função 'check_number' (if-else if-else)
  ;; =============================================
  (func $check_number (param $num i32) (result i32)
    (if (i32.gt_s (local.get $num) (i32.const 0))  ;; if (num > 0)
      (then (i32.const 1))  ;; return 1
      (else
        (if (i32.lt_s (local.get $num) (i32.const 0))  ;; else if (num < 0)
          (then (i32.const -1))  ;; return -1
          (else (i32.const 0))  ;; else return 0
        )
      )
    )
  )

  ;; =============================================
  ;; Função 'factorial_while' (while loop)
  ;; =============================================
  (func $factorial_while (param $n i32) (result i32)
    (local $result i32)
    (local.set $result (i32.const 1))  ;; result = 1

    (block $loop_exit  ;; Rótulo para sair do loop
      (loop $loop_start  ;; Início do loop
        ;; Condição: while (n > 0)
        (if (i32.le_s (local.get $n) (i32.const 0))  ;; Se n <= 0, sai
          (then (br $loop_exit))
          (else
            ;; Corpo do while: result *= n; n--;
            (local.set $result
              (i32.mul (local.get $result) (local.get $n))
            )
            (local.set $n (i32.sub (local.get $n) (i32.const 1)))
            (br $loop_start)  ;; Volta ao início
          )
        )
      )
    )
    (local.get $result)  ;; Retorna result
  )

  ;; =============================================
  ;; Função 'factorial_do_while' (do-while loop)
  ;; =============================================
  (func $factorial_do_while (param $n i32) (result i32)
    (local $result i32)
    (local.set $result (i32.const 1))  ;; result = 1

    (block $loop_exit
      (loop $loop_start
        ;; Corpo do do-while: result *= n; n--;
        (local.set $result
          (i32.mul (local.get $result) (local.get $n))
        )
        (local.set $n (i32.sub (local.get $n) (i32.const 1)))

        ;; Condição: while (n > 0)
        (if (i32.gt_s (local.get $n) (i32.const 0))
          (then (br $loop_start))  ;; Se n > 0, continua
          (else (br $loop_exit))   ;; Senão, sai
        )
      )
    )
    (local.get $result)
  )

  ;; =============================================
  ;; Função 'sum_array' (for loop)
  ;; =============================================
  (func $sum_array (param $arr_ptr i32) (param $size i32) (result i32)
    (local $sum i32)
    (local $i i32)
    (local.set $sum (i32.const 0))  ;; sum = 0
    (local.set $i (i32.const 0))    ;; i = 0

    (block $loop_exit
      (loop $loop_start
        ;; Condição: i < size
        (if (i32.ge_s (local.get $i) (local.get $size)))
          (then (br $loop_exit))
          (else
            ;; sum += arr[i]
            (local.set $sum
              (i32.add
                (local.get $sum)
                (i32.load offset=0  ;; Carrega arr[i] (arr_ptr + i*4)
                  (i32.add
                    (local.get $arr_ptr)
                    (i32.mul (local.get $i) (i32.const 4))
                  )
                )
              )
            )
            (local.set $i (i32.add (local.get $i) (i32.const 1)))  ;; i++
            (br $loop_start)
          )
        )
      )
    )
    (local.get $sum)
  )

  ;; =============================================
  ;; Função 'main' (ponto de entrada)
  ;; =============================================
  (func $main (result i32)
    (local $num i32)
    (local $check i32)
    (local $fact_while i32)
    (local $fact_dowhile i32)
    (local $sum i32)
    (local $array i32 i32 i32)  ;; array[3] = {1, 2, 3}

    ;; Inicializa array
    (i32.const 1) (local.set $array 0)
    (i32.const 2) (local.set $array 1)
    (i32.const 3) (local.set $array 2)

    ;; num = -5
    (i32.const -5) (local.set $num)

    ;; check = check_number(num)
    (call $check_number (local.get $num))
    (local.set $check)

    ;; fact_while = factorial_while(5)
    (i32.const 5)
    (call $factorial_while)
    (local.set $fact_while)

    ;; fact_dowhile = factorial_do_while(5)
    (i32.const 5)
    (call $factorial_do_while)
    (local.set $fact_dowhile)

    ;; sum = sum_array(&array, 3)
    (i32.const 0)  ;; Assume que array começa no offset 0
    (i32.const 3)
    (call $sum_array)
    (local.set $sum)

    ;; return check + fact_while + fact_dowhile + sum
    (i32.add
      (local.get $check)
      (i32.add
        (local.get $fact_while)
        (i32.add
          (local.get $fact_dowhile)
          (local.get $sum)
        )
      )
    )
  )

  ;; Exportações (para JavaScript)
  (export "main" (func $main))
)
```

---

### **Explicação Detalhada**
#### **1. `if-else if-else` em WAT**
- Em C:
  ```c
  if (num > 0) return 1;
  else if (num < 0) return -1;
  else return 0;
  ```
- Em WAT:
  ```wasm
  (if (i32.gt_s (local.get $num) (i32.const 0))  ;; num > 0
    (then (i32.const 1))  ;; return 1
    (else
      (if (i32.lt_s (local.get $num) (i32.const 0))  ;; num < 0
        (then (i32.const -1))  ;; return -1
        (else (i32.const 0))   ;; return 0
      )
    )
  )
  ```
  - `i32.gt_s` = "greater than signed" (`>`).  
  - `i32.lt_s` = "less than signed" (`<`).  

#### **2. `while` em WAT**
- Em C:
  ```c
  while (n > 0) { result *= n; n--; }
  ```
- Em WAT:
  ```wasm
  (block $loop_exit
    (loop $loop_start
      (if (i32.le_s (local.get $n) (i32.const 0))  ;; if (n <= 0)
        (then (br $loop_exit))  ;; break
        (else
          ;; result *= n
          (local.set $result (i32.mul (local.get $result) (local.get $n)))
          ;; n--
          (local.set $n (i32.sub (local.get $n) (i32.const 1)))
          (br $loop_start)  ;; continue
        )
      )
    )
  )
  ```
  - `block` + `loop` + `br` (branch) são usados para implementar loops.  
  - `br $loop_start` = `continue`.  
  - `br $loop_exit` = `break`.  

#### **3. `do-while` em WAT**
- Em C:
  ```c
  do { result *= n; n--; } while (n > 0);
  ```
- Em WAT:
  ```wasm
  (block $loop_exit
    (loop $loop_start
      ;; Corpo do loop
      (local.set $result (i32.mul (local.get $result) (local.get $n)))
      (local.set $n (i32.sub (local.get $n) (i32.const 1)))

      ;; Condição while (n > 0)
      (if (i32.gt_s (local.get $n) (i32.const 0))
        (then (br $loop_start))  ;; Volta ao início
        (else (br $loop_exit))   ;; Sai do loop
      )
    )
  )
  ```
  - Semelhante ao `while`, mas a condição é verificada **depois** do corpo.  

#### **4. `for` em WAT**
- Em C:
  ```c
  for (int i = 0; i < size; i++) { sum += arr[i]; }
  ```
- Em WAT:
  ```wasm
  (local.set $i (i32.const 0))  ;; i = 0
  (block $loop_exit
    (loop $loop_start
      (if (i32.ge_s (local.get $i) (local.get $size))  ;; if (i >= size)
        (then (br $loop_exit))
        (else
          ;; sum += arr[i]
          (local.set $sum
            (i32.add
              (local.get $sum)
              (i32.load offset=0  ;; arr[i] = mem[arr_ptr + i*4]
                (i32.add
                  (local.get $arr_ptr)
                  (i32.mul (local.get $i) (i32.const 4))
                )
              )
            )
          )
          (local.set $i (i32.add (local.get $i) (i32.const 1)))  ;; i++
          (br $loop_start)
        )
      )
    )
  )
  ```
  - O `for` é implementado como um `while` com inicialização (`i = 0`) e incremento (`i++`).  
  - `i32.load offset=0` lê um `i32` da memória (equivalente a `arr[i]`).  

---

### **Conclusão**
- **`if-else`** → Usa `(if (cond) (then ...) (else ...))`.  
- **`while`** → Usa `(block)` + `(loop)` + `(br)` para controle.  
- **`do-while`** → Similar ao `while`, mas a condição é verificada depois.  
- **`for`** → Implementado como um `while` com inicialização e incremento.  

Se você compilar o código C com `emcc` e converter para WAT usando `wasm2wat`, verá uma estrutura semelhante, mas mais detalhada (com alocação de memória adicional).

### **Exemplo em C com `switch` e sua Tradução para WAT**
#### **Código em C** (`switch_example.c`)
```c
int switch_example(int num) {
    int result;
    switch (num) {
        case 1:
            result = 10;
            break;
        case 2:
            result = 20;
            break;
        case 3:
            result = 30;
            break;
        default:
            result = 0;
    }
    return result;
}

int main() {
    int x = switch_example(2);  // Retorna 20
    return x;
}
```

---

#### **Código WAT Gerado (Comentado)**
```wasm
(module
  ;; =============================================
  ;; Função 'switch_example' (tradução do switch)
  ;; =============================================
  (func $switch_example (param $num i32) (result i32)
    (local $result i32)  ;; Variável local 'result'

    ;; Bloco do switch (usando 'block' e 'br_table')
    (block $switch_default
      (block $case3
        (block $case2
          (block $case1
            ;; Verifica o valor de 'num' e salta para o caso correspondente
            (br_table $case1 $case2 $case3  ;; Casos 1, 2, 3
              (i32.sub (local.get $num) (i32.const 1))  ;; num - 1 (ajuste para índice 0)
            )
          )  ;; Fim do bloco $case1
          ;; Caso 1: result = 10
          (i32.const 10)
          (local.set $result)
          (br $switch_default)  ;; Sai do switch (break)
        )  ;; Fim do bloco $case2
        ;; Caso 2: result = 20
        (i32.const 20)
        (local.set $result)
        (br $switch_default)  ;; Sai do switch (break)
      )  ;; Fim do bloco $case3
      ;; Caso 3: result = 30
      (i32.const 30)
      (local.set $result)
      (br $switch_default)  ;; Sai do switch (break)
    )  ;; Fim do bloco $switch_default
    ;; Default: result = 0 (se nenhum caso for correspondido)
    (i32.const 0)
    (local.set $result)

    (local.get $result)  ;; Retorna 'result'
  )

  ;; =============================================
  ;; Função 'main' (chama switch_example)
  ;; =============================================
  (func $main (result i32)
    (i32.const 2)  ;; Argumento para switch_example (num = 2)
    (call $switch_example)  ;; Chama a função
  )

  ;; Exportações (para JavaScript)
  (export "main" (func $main))
```

---

### **Explicação Detalhada**
#### **1. Estrutura do `switch` em WAT**
O `switch` em WebAssembly é implementado usando:
- **`br_table`**: Uma tabela de saltos que mapeia valores para rótulos (`block`).
- **`block`**: Define os rótulos para cada caso (`case1`, `case2`, etc.).
- **`br`**: Usado para sair do bloco (`break`).

##### **Fluxo do `switch` em WAT**

1. **Ajuste do valor** (`num - 1`):
   ```wasm
   (i32.sub (local.get $num) (i32.const 1))  ;; Converte num para índice 0 (case1 = 0, case2 = 1, etc.)
   ```
2. **Tabela de saltos** (`br_table`):
   ```wasm
   (br_table $case1 $case2 $case3  ;; Lista de rótulos (casos 1, 2, 3)
   ```
   - Se `num = 1` → Salta para `$case1`.
   - Se `num = 2` → Salta para `$case2`.
   - Se `num = 3` → Salta para `$case3`.
   - Se não corresponder a nenhum caso, cai no `default`.

3. **Blocos de casos**:
   ```wasm
   (block $case1
     (i32.const 10)  ;; result = 10
     (local.set $result)
     (br $switch_default)  ;; break
   )
   ```
   - Cada `block` representa um `case`.
   - `(br $switch_default)` equivale ao `break` em C.

4. **Bloco `default`**:
   - Se nenhum caso for correspondido, o fluxo continua após o `br_table` e executa o código do `default`.

---

#### **2. Comparação com o Código C**
| Código C | Código WAT |
|----------|------------|
| `switch (num)` | `(br_table $case1 $case2 $case3 ...)` |
| `case 1: result = 10; break;` | `(block $case1) (i32.const 10) (local.set $result) (br $switch_default)` |
| `default: result = 0;` | Código após o `br_table` (se nenhum caso for correspondido) |

---

#### **3. Otimizações Possíveis**
- Se os casos forem **não consecutivos** (ex: `case 1`, `case 5`, `case 100`), o compilador pode usar uma **tabela de saltos esparsa** ou substituir por uma série de `if-else`.
- Casos muito espaçados podem resultar em código menos eficiente.

---

#### **4. Como Testar**
1. Compile o código C para Wasm:
   ```sh
   emcc switch_example.c -o switch_example.wasm -s SIDE_MODULE=1
   ```
2. Converta para WAT:
   ```sh
   wasm2wat switch_example.wasm -o switch_example.wat
   ```
3. O WAT gerado será mais detalhado (com alocações de memória adicionais), mas a lógica do `switch` será a mesma.

---

### **Conclusão**
- O `switch` em WebAssembly é traduzido para **`br_table` + blocos (`block`)**.
- Cada `case` vira um rótulo de salto.
- O `default` é tratado como o fluxo após o `br_table`.
- **`break`** é implementado com `(br $switch_default)`.
