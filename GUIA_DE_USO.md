# 🎮 GUIA COMPLETO - CLONADOR IR JH021

## 📋 ETAPAS DO PROJETO

### **ETAPA 1: CAPTURA DOS SINAIS IR** ✅ (Código atual: main.cpp)

#### O que faz:
- Captura interativamente os sinais IR do controle JH021
- Valida e armazena cada código hexadecimal
- Gera código C++ pronto para usar no emissor

#### Como usar:
1. **Compile e faça upload** do `main.cpp` atual para o ESP32
2. **Abra o Monitor Serial** (115200 baud)
3. **Siga as instruções** pressionando cada botão quando solicitado
4. **Aguarde a conclusão** de todos os 21 botões
5. **Copie o código gerado** na seção "MAPEAMENTO PARA SERVIDOR WEB"

#### Exemplo de saída esperada:
```cpp
const IRMapping webToIR[] = {
    {"POWER", 0x00FF30CFULL},
    {"UP", 0x00FF18E7ULL},
    // ... outros códigos ...
};
```

---

### **ETAPA 2: EMISSOR IR COM SERVIDOR WEB** (Código: main_emissor.cpp.exemplo)

#### O que faz:
- Cria um Access Point WiFi (ESP32-JH021)
- Hospeda a interface web do controle
- Emite sinais IR quando os botões são pressionados na interface

#### Preparação:

1. **Cole os códigos capturados** no arquivo `main_emissor.cpp.exemplo`:
   - Localize a seção `const IRMapping webToIR[]`
   - Substitua os valores de exemplo pelos seus códigos reais

2. **Atualize o protocolo e bits**:
   ```cpp
   decode_type_t PROTOCOL = NEC;  // Será informado na captura
   uint16_t BITS = 32;            // Será informado na captura
   ```

3. **Renomeie o arquivo**:
   - De: `main_emissor.cpp.exemplo`
   - Para: `main.cpp` (substitua o arquivo de captura)

4. **Compile e faça upload** para o ESP32

#### Como usar o controle web:

1. **Conecte no WiFi**:
   - SSID: `ESP32-JH021`
   - Senha: `12345678`

2. **Acesse no navegador**:
   - URL: `http://192.168.4.1`

3. **Use a interface**:
   - Clique nos botões para enviar comandos IR
   - LED verde indica transmissão
   - Vibração tátil em dispositivos móveis

---

## 🔧 HARDWARE NECESSÁRIO

### Etapa 1 (Captura):
- ✅ Receptor IR v1222 → GPIO 15

### Etapa 2 (Emissor):
- ✅ LED IR emissor → GPIO 4 (através de transistor NPN/PNP)
- ✅ Resistor limitador (220Ω-470Ω)
- ✅ Transistor BC547 ou similar
- ✅ LED onboard (GPIO 2) - Indicador de status automático

#### Circuito do Emissor IR:
```
ESP32 GPIO 4 ──┐
               │
               ├── R1 (1kΩ) ──► Base (Transistor BC547)
               │
           Emissor ──► GND
               │
          Coletor ──┬── LED IR (Cátodo)
                    │
                    └── Ânodo LED IR ──► R2 (220Ω) ──► VCC (3.3V ou 5V)
```

---

## 📝 CHECKLIST DE USO

- [ ] **Passo 1**: Upload do código de captura (`main.cpp` atual)
- [ ] **Passo 2**: Capturar todos os 21 botões via Monitor Serial
- [ ] **Passo 3**: Copiar os códigos gerados
- [ ] **Passo 4**: Colar códigos no `main_emissor.cpp.exemplo`
- [ ] **Passo 5**: Ajustar protocolo e bits conforme informado
- [ ] **Passo 6**: Renomear para `main.cpp`
- [ ] **Passo 7**: Conectar LED IR emissor no GPIO 4
- [ ] **Passo 8**: Upload do código emissor
- [ ] **Passo 9**: Conectar no WiFi "ESP32-JH021"
- [ ] **Passo 10**: Acessar http://192.168.4.1 e testar!

---

## 🎯 BOTÕES MAPEADOS (21 no total)

1. POWER
2. UP
3. 12/24
4. LEFT
5. OK
6. RIGHT
7. EXIT
8. DOWN
9. SET
10. 0
11. STOPWATCH
12. AL
13. 1
14. 2
15. 3
16. 4
17. 5
18. 6
19. 7
20. 8
21. 9

---

## 🚨 IMPORTANTE: IP FIXO SEM MONITOR SERIAL

### O IP é SEMPRE fixo: **192.168.4.1**

Você **NÃO precisa** do Monitor Serial para usar o produto! 

### Indicadores Visuais (LED Onboard - GPIO 2):

| Comportamento do LED | Significado |
|---------------------|-------------|
| **LIGADO (fixo)** | ✅ Sistema OK - WiFi AP ativo |
| **Pisca 3x na inicialização** | ✅ Configuração concluída |
| **Pisca rápido contínuo** | ❌ ERRO ao criar Access Point |
| **Apaga brevemente ao clicar** | 📡 Comando IR sendo enviado |

### Como usar sem Monitor Serial:

1. **Ligue o ESP32** (USB ou bateria)
2. **Aguarde 5 segundos**
3. **Verifique o LED onboard**:
   - Piscou 3x e ficou ligado? ✅ Tudo certo!
4. **Conecte no WiFi**: `ESP32-JH021` (senha: `12345678`)
5. **Acesse**: `http://192.168.4.1`

### 💡 Dica para Produto Final:
Você pode imprimir um adesivo com estas informações:
```
📱 CONTROLE JH021
WiFi: ESP32-JH021
Senha: 12345678
URL: http://192.168.4.1
```

---

## ⚙️ CONFIGURAÇÕES PERSONALIZÁVEIS

### Servidor Web (main_emissor.cpp):
```cpp
const char* AP_SSID = "ESP32-JH021";          // Nome do WiFi
const char* AP_PASSWORD = "12345678";         // Senha (mín. 8 caracteres)
const uint16_t IR_LED_PIN = 4;                // GPIO do LED IR
const uint16_t STATUS_LED_PIN = 2;            // GPIO do LED de status

// IP FIXO - NÃO MUDA!
IPAddress local_IP(192, 168, 4, 1);           // Sempre 192.168.4.1
```

### Interface HTML:
- Localização: `interface.html` (já integrada no código)
- Personalização: Edite as cores no CSS do `main_emissor.cpp`

---

## 🐛 TROUBLESHOOTING

### Problema: Monitor Serial não mostra nada
- Verifique a velocidade (115200 baud)
- Certifique-se que o cabo USB transmite dados

### Problema: Códigos capturados são todos 0xFFFFFFFF
- Isso é código de repetição, solte e pressione novamente
- Aproxime o controle do receptor IR

### Problema: WiFi não aparece
- Aguarde 5-10 segundos após boot
- Verifique se há outro dispositivo com mesmo SSID

### Problema: Interface carrega mas botões não funcionam
- Verifique se os códigos foram colados corretamente
- Confirme que o protocolo está correto
- Teste o LED IR com uma câmera de celular (deve brilhar ao transmitir)

---

## 📚 BIBLIOTECAS UTILIZADAS

- **IRremoteESP8266** v2.8.6 - Captura e emissão IR
- **WiFi** - Built-in ESP32
- **WebServer** - Built-in ESP32

Configurado automaticamente no `platformio.ini`

---

**Criado para: Controle Remoto JH021**  
**Plataforma: ESP32**  
**Framework: Arduino**
