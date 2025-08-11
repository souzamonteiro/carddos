# **Documentação Técnica do CardDOS**

## **1. Visão Geral do Projeto**
O **CardDOS** é um sistema operacional estilo DOS desenvolvido para o **ESP32-S3 Cardputer**, combinando a simplicidade do MS-DOS com capacidades modernas de hardware. O projeto visa criar um ambiente leve, eficiente e compatível com programas em Assembly e C.

---

## **2. Arquitetura do Sistema**

### **2.1. Diagrama de Alto Nível**
![alt text](High-Level_Diagram.png)

### **2.2. Componentes Principais**
| **Componente**       | **Descrição**                                                                 |
|-----------------------|-----------------------------------------------------------------------------|
| **Bootloader**        | Carrega o kernel e o shell da flash para a RAM.                             |
| **Kernel**            | Gerencia tasks, syscalls e drivers.                                        |
| **Drivers**           | Controlam hardware (display, teclado, microSD).                            |
| **Syscalls**          | Interface entre aplicações e kernel (ex: `SYS_PRINT`, `SYS_READ`).         |
| **Shell**             | Interpretador de comandos (`CARDOM.COM`).                                  |

---

## **3. Hardware do ESP32-S3 Cardputer**

### **3.1. Especificações**
| **Componente**       | **Detalhes**                                                                |
|-----------------------|-----------------------------------------------------------------------------|
| **CPU**               | Xtensa LX7 (dual-core, 240 MHz)                                            |
| **RAM**               | 512KB SRAM + 320KB ROM                                                     |
| **Flash**             | 8MB (expandível via microSD)                                               |
| **Display**           | ST7789 (135x240 pixels, SPI, RGB565)                                       |
| **Teclado**           | Matriz 8x8 (56 teclas)                                                     |
| **Armazenamento**     | Slot para microSD (FAT32)                                                  |

### **3.2. Pinout (Exemplos Críticos)**
| **Periférico**  | **Pino ESP32-S3** | **Protocolo** |
|-----------------|-------------------|---------------|
| Display (SCLK)  | GPIO 12           | SPI           |
| Teclado (Linha 1)| GPIO 2           | GPIO          |
| microSD (CS)    | GPIO 10           | SPI           |

---

## **4. Arquitetura do Kernel**

### **4.1. Fluxo de Boot**
1. **Bootloader**:  
   - Carrega `kernel.bin` da flash para `0x3FFC0000`.  
   - Inicializa hardware básico (SPI, GPIO).  
2. **Kernel**:  
   - Configura syscalls e drivers.  
   - Executa `CARDOM.COM`.

### **4.2. Syscalls (Chamadas de Sistema)**
| **Syscall** | **Assembly**                          | **Descrição**                     |
|-------------|---------------------------------------|-----------------------------------|
| `0x09`      | `movi a2, 0x09; movi a3, msg; syscall` | Imprime string no display.        |
| `0x3F`      | `movi a2, 0x3F; syscall`             | Lê tecla do teclado.              |

### **4.3. Gerenciamento de Memória**
- **Alocação Estática**:  
  - Kernel: `0x3FFB0000`–`0x3FFBFFFF` (64KB).  
  - Aplicações: `0x3FFC0000`–`0x3FFDFFFF` (128KB).  

---

## **5. Arquitetura de Aplicações**

### **5.1. Formato .COM**
- **Cabeçalho**: Nenhum (binário puro).  
- **Entry Point**: `_start` (definido em Assembly).  
- **Tamanho Máximo**: 32KB (devido à RAM limitada).

### **5.2. Exemplo em Assembly**
```assembly
; HELLO.COM
.global _start
_start:
    movi a2, 0x09       ; Syscall: PRINT
    movi a3, msg        ; String
    syscall
    movi a2, 0x4C       ; Syscall: EXIT
    syscall
msg: .string "Olá, CardDOS!"
```

### **5.3. Compilação**
```bash
xtensa-esp32s3-elf-gcc -nostdlib -Wl,--oformat=binary hello.S -o HELLO.COM
```

---

## **6. Ferramentas e Linguagens**
| **Ferramenta**            | **Uso**                                      |
|---------------------------|---------------------------------------------|
| **ESP-IDF v5.0+**         | Toolchain oficial para ESP32-S3.            |
| **Xtensa GCC**            | Compilação de código Assembly/C.            |
| **FFmpeg**                | Conversão de imagens para RGB565.           |
| **Git**                   | Controle de versão.                         |

---

## **7. Roadmap Detalhado**
### **Fase 1: Núcleo Básico (v0.1)**
- [x] Bootloader funcional.  
- [x] Driver de display.  
- [ ] Shell (`CARDOM.COM`).  

### **Fase 2: Extensões (v0.2)**
- [ ] Suporte a escrita no microSD.  
- [ ] API de arquivos (`fopen()`, `fread()`).  

### **Fase 3: Rede (v0.3)**
- [ ] Stack Wi-Fi (HTTP/NTP).  

---

## **8. Desafios e Soluções**
| **Desafio**               | **Solução**                              |
|---------------------------|------------------------------------------|
| **RAM limitada**          | Alocação estática + overlays.            |
| **Ausência de MMU**       | Verificação manual de ponteiros.         |
| **Latência do SPI**       | Uso de DMA para transferências.          |

---

## **9. Referências**
- [Datasheet ESP32-S3](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf).  
- [Manual do ST7789](https://www.rhydolabz.com/documents/33/ST7789.pdf).  

---

**🔗 Repositório**: [github.com/souzamonteiro/carddos](https://github.com/souzamonteiro/carddos)  
**📝 Licença**: Apache 2.0.  

*(Documentação atualizada em outubro/2023. Revisão técnica contínua.)*  

---

