# Pinagem ESP32-C3 Super Mini

## Pinos Recomendados para o Projeto

### LED IR Emissor
- **GPIO 10** (padrão no código)
- Alternativas: GPIO 4, 5, 6, 7

### LED Status
- **GPIO 8** (LED onboard RGB - componente azul)

## Mapa de Pinos ESP32-C3 Super Mini

```
                ESP32-C3 Super Mini
                ┌─────────────┐
         GND ──│ 1        13 │── 3V3
         GND ──│ 2        12 │── GND
         3V3 ──│ 3        11 │── 5V
      GPIO 0 ──│ 4        10 │── GPIO 10  ← LED IR (padrão)
      GPIO 1 ──│ 5         9 │── GPIO 9
      GPIO 2 ──│ 6         8 │── GPIO 8   ← LED Onboard
      GPIO 3 ──│ 7         7 │── GPIO 7
      GPIO 4 ──│ 8         6 │── GPIO 6
      GPIO 5 ──│ 9         5 │── GPIO 5
                └─────────────┘
```

## Notas Importantes

1. **GPIO 8** é o LED RGB onboard (componente azul)
2. **GPIO 9** é usado para boot - evite usar
3. **GPIO 18, 19** são para USB - NÃO USE
4. Para LED IR, use resistor de 220Ω e transistor BC547/2N2222 se alimentar com 5V

## Conexão do LED IR

```
ESP32-C3 GPIO 10 → Resistor 1kΩ → Base do Transistor BC547
Coletor → LED IR (ânodo) → Resistor 220Ω → 5V
Emissor → GND
Cátodo LED IR → GND
```

## Circuito Simplificado (3.3V direto - menor alcance)

```
GPIO 10 → Resistor 100Ω → LED IR → GND
```
⚠️ Alcance reduzido, mas funciona para testes!
