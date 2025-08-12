# Exemplos de Acesso a Hardwares do ESP32-S3 em Assembly

## **1. Controle de LCD 16x2 (8-bit mode)**
Assumimos que o LCD está conectado da seguinte forma:
- **Dados (D0-D7):** GPIO4 a GPIO11  
- **RS (Register Select):** GPIO12  
- **RW (Read/Write):** GPIO13 (sempre em modo escrita = GND)  
- **EN (Enable):** GPIO14  

### **Exemplo: Enviar um comando para o LCD**
```asm
# Função: lcd_send_command (envia um comando para o LCD)
# Argumento: a2 = comando (8 bits)
.section .text
.global lcd_send_command

lcd_send_command:
    # 1. Configurar RS = 0 (comando), RW = 0 (escrita)
    movi a3, 0x60004000           # Base GPIO
    movi a4, (1 << 12)            # Máscara para RS (GPIO12)
    xor a4, a4, a4                # RS = 0 (comando)
    s32i a4, a3, 0x04             # GPIO_OUT_REG (define RS=0, RW=0 implícito)

    # 2. Colocar dados nos pinos D0-D7 (GPIO4-GPIO11)
    movi a5, 0x60004000 + 0x08   # GPIO_OUT_W1TS (setar bits)
    slli a6, a2, 4                # Desloca para alinhar com GPIO4-GPIO11
    s32i a6, a5, 0                # Envia dados para os pinos

    # 3. Pulsar EN (Enable)
    movi a7, (1 << 14)            # Máscara para EN (GPIO14)
    s32i a7, a5, 0                # EN = 1
    movi a8, 100                  # Pequeno delay (ajustar conforme clock)
delay_loop:
    addi a8, a8, -1
    bnez a8, delay_loop
    s32i a7, a3, 0x0C            # GPIO_OUT_W1TC (EN = 0)

    ret
```

### **Exemplo: Enviar um caractere para o LCD**
```asm
# Função: lcd_send_data (envia um caractere para o LCD)
# Argumento: a2 = caractere (8 bits)
.section .text
.global lcd_send_data

lcd_send_data:
    # 1. Configurar RS = 1 (dados), RW = 0 (escrita)
    movi a3, 0x60004000           # Base GPIO
    movi a4, (1 << 12)            # Máscara para RS (GPIO12)
    s32i a4, a3, 0x08             # GPIO_OUT_W1TS (RS = 1)

    # 2. Colocar dados nos pinos D0-D7 (mesmo que lcd_send_command)
    movi a5, 0x60004000 + 0x08    # GPIO_OUT_W1TS
    slli a6, a2, 4                # Desloca para alinhar com GPIO4-GPIO11
    s32i a6, a5, 0                # Envia dados

    # 3. Pulsar EN (igual ao exemplo anterior)
    movi a7, (1 << 14)            # Máscara EN (GPIO14)
    s32i a7, a5, 0                # EN = 1
    movi a8, 100                  # Delay
delay_loop_data:
    addi a8, a8, -1
    bnez a8, delay_loop_data
    s32i a7, a3, 0x0C             # EN = 0

    ret
```

---

## **2. Leitura de Teclado Matricial 4x4**
Assumimos que o teclado está conectado assim:
- **Linhas (L1-L4):** GPIO15, GPIO16, GPIO17, GPIO18 (saídas, pull-down)  
- **Colunas (C1-C4):** GPIO19, GPIO20, GPIO21, GPIO22 (entradas, pull-up)  

### **Exemplo: Verificar tecla pressionada**
```asm
# Função: keyboard_scan (retorna tecla pressionada ou 0xFF se nenhuma)
# Retorno: a2 = tecla (0x00 a 0x0F) ou 0xFF se nenhuma
.section .text
.global keyboard_scan

keyboard_scan:
    # 1. Configurar linhas como saídas e colunas como entradas (feito em C antes)
    movi a3, 0x60004000           # Base GPIO
    movi a4, 0xFF                 # Inicializa retorno como 0xFF (nenhuma tecla)
    movi a5, 0                    # Contador de linha (0-3)

scan_loop:
    # 2. Ativar linha atual (L1-L4)
    movi a6, (1 << 15)            # Máscara para L1 (GPIO15)
    slli a7, a6, a5               # Desloca para L1, L2, L3 ou L4
    s32i a7, a3, 0x08             # GPIO_OUT_W1TS (ativa linha)

    # 3. Ler colunas (C1-C4)
    l32i a8, a3, 0x3C             # GPIO_IN_REG (ler estado das colunas)
    andi a8, a8, 0x780000         # Máscara para GPIO19-22 (C1-C4)

    # 4. Verificar se alguma coluna está ativa (pull-down detectado)
    beqz a8, next_line            # Se nenhuma coluna, próxima linha

    # 5. Decodificar tecla (linha + coluna)
    # Exemplo: Se L1 ativo e C1 pressionado → tecla 0x00
    #          Se L2 ativo e C3 pressionado → tecla 0x06
    movi a9, 0x780000             # Máscara completa das colunas
    xor a9, a9, a8                # Inverte para detectar qual coluna está baixa
    srli a9, a9, 19               # Alinha bits para 0-3 (coluna)
    nsau a10, a9                  # Encontra a posição do bit setado
    addi a10, a10, -1             # Ajusta para 0-3
    slli a11, a5, 2               # Linha * 4
    add a4, a11, a10              # Tecla = (linha * 4) + coluna

next_line:
    # 6. Desativar linha atual antes de mudar
    s32i a7, a3, 0x0C             # GPIO_OUT_W1TC (desativa linha)

    # 7. Próxima linha ou retorna
    addi a5, a5, 1
    blti a5, 4, scan_loop         # Repete para todas as linhas

    # 8. Retorna tecla encontrada (ou 0xFF)
    mov a2, a4
    ret
```

---

### **Observações importantes:**
1. **GPIOs e Pull-up/Pull-down:**  
   - No teclado matricial, as **colunas** devem ser configuradas com **pull-up**, e as **linhas** devem ser **pull-down**.
   - No LCD, os pinos de controle (**RS, RW, EN**) devem ser configurados como saídas.

2. **Delays:**  
   - O LCD precisa de pequenos atrasos (`delay_loop`) entre comandos.  
   - No teclado, um **debounce** (filtro de ruído) pode ser necessário em software.

3. **Otimização:**  
   - Em código real, considere usar **interrupções** para o teclado em vez de polling.  
   - O LCD pode ser otimizado com escrita em buffer ou DMA (se suportado).

4. **Adaptação:**  
   - Os endereços dos GPIOs (`0x60004000`) são padrão no ESP32-S3, mas verifique no *Technical Reference Manual* para confirmação.  

Esses exemplos fornecem uma base funcional, mas podem ser ajustados conforme sua conexão física e requisitos de desempenho. 🚀
