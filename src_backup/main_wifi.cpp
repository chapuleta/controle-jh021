/*
 * FIRMWARE EMISSOR IR - ESP32 Controle JH021 (BLE)
 * GPIO 15: LED IR Emissor
 * GPIO 2: LED Status (onboard)
 * Comunicação: Bluetooth Low Energy (BLE)
 */

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <IRsend.h>

const uint16_t IR_LED_PIN = 15;
const uint16_t STATUS_LED_PIN = 2;
IRsend irsend(IR_LED_PIN);

// UUIDs para BLE Service e Characteristic
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

struct IRMapping {
    const char* cmd;
    uint64_t code;
};

const IRMapping webToIR[] = {
    {"POWER", 0xFF00FFULL},
    {"UP", 0xFF807FULL},
    {"12_24", 0xFF40BFULL},
    {"LEFT", 0xFF20FFULL},
    {"OK", 0xFFA05FULL},
    {"RIGHT", 0xFF609FULL},
    {"EXIT", 0xFF10EFULL},
    {"DOWN", 0xFF906FULL},
    {"SET", 0xFF50AFULL},
    {"0", 0xFF30CFULL},
    {"STOPWATCH", 0xFFB04FULL},
    {"AL", 0xFF708FULL},
    {"1", 0xFF08F7ULL},
    {"2", 0xFF8877ULL},
    {"3", 0xFF48B7ULL},
    {"4", 0xFF28D7ULL},
    {"5", 0xFFA857ULL},
    {"6", 0xFF6897ULL},
    {"7", 0xFF18E7ULL},
    {"8", 0xFF9867ULL},
    {"9", 0xFF58A7ULL}
};

const int TOTAL_CODES = sizeof(webToIR) / sizeof(webToIR[0]);
decode_type_t PROTOCOL = NEC;
uint16_t BITS = 32;

// Callback para conexões BLE
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        Serial.println("Cliente BLE conectado!");
        digitalWrite(STATUS_LED_PIN, HIGH);
    };

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        Serial.println("Cliente BLE desconectado!");
        digitalWrite(STATUS_LED_PIN, LOW);
    }
};

// Callback para receber comandos via BLE
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        String cmd = String(pCharacteristic->getValue().c_str());
        cmd.trim();

        if (cmd.length() > 0) {
            Serial.printf("Recebido via BLE: %s\n", cmd.c_str());
            
            uint64_t irCode = 0;
            bool found = false;
            
            for (int i = 0; i < TOTAL_CODES; i++) {
                if (cmd == webToIR[i].cmd) {
                    irCode = webToIR[i].code;
                    found = true;
                    break;
                }
            }
            
            if (found && irCode != 0) {
                digitalWrite(STATUS_LED_PIN, LOW);
                irsend.send(PROTOCOL, irCode, BITS);
                Serial.printf("Enviado: %s (0x%llX)\n", cmd.c_str(), (unsigned long long)irCode);
                delay(100);
                digitalWrite(STATUS_LED_PIN, HIGH);
                
                // Envia confirmação de volta
                pCharacteristic->setValue("OK");
                pCharacteristic->notify();
            } else {
                Serial.printf("Comando nao encontrado: %s\n", cmd.c_str());
                pCharacteristic->setValue("ERROR");
                pCharacteristic->notify();
            }
        }
    }
};

void setup() {
    Serial.begin(115200);
    delay(500);
    
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);
    
    Serial.println("\n========================================");
    Serial.println("  EMISSOR IR BLE - CONTROLE JH021");
    Serial.println("========================================\n");
    
    irsend.begin();
    Serial.printf("Emissor IR: GPIO %d\n", IR_LED_PIN);
    
    Serial.println("Inicializando BLE...");
    
    // Inicializa BLE com nome do dispositivo
    BLEDevice::init("ESP32-JH021");
    
    // Cria servidor BLE
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Cria serviço BLE
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Cria característica BLE (leitura/escrita/notificação)
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_READ   |
                        BLECharacteristic::PROPERTY_WRITE  |
                        BLECharacteristic::PROPERTY_NOTIFY
                      );

    pCharacteristic->setCallbacks(new MyCallbacks());
    
    // Adiciona descritor para notificações
    pCharacteristic->addDescriptor(new BLE2902());
    
    // Inicia o serviço
    pService->start();

    // Inicia advertising (transmissão BLE)
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    
    Serial.println("BLE iniciado com sucesso!");
    Serial.println("  Nome: ESP32-JH021");
    Serial.println("  Aguardando conexao...\n");
    
    // Pisca LED para indicar pronto
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED_PIN, HIGH);
        delay(200);
        digitalWrite(STATUS_LED_PIN, LOW);
        delay(200);
    }
    
    Serial.println("========================================");
    Serial.println("         PRONTO PARA USO!");
    Serial.println("========================================");
    Serial.println("  Dispositivo BLE: ESP32-JH021");
    Serial.println("  Abra a interface HTML no navegador");
    Serial.println("========================================\n");
}

void loop() {
    // Reconecta se desconectado
    if (!deviceConnected && oldDeviceConnected) {
        delay(500);
        pServer->startAdvertising();
        Serial.println("Aguardando nova conexao...");
        oldDeviceConnected = deviceConnected;
    }
    
    // Conectado
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
    
    delay(10);
}
