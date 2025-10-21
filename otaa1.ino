#define OTAA_PERIOD   (25000) // Uplink check period in milliseconds
#define OTAA_BAND     (RAK_REGION_AS923_2) // Set your LoRaWAN region
#define OTAA_DEVEUI   {0x47, 0x3A, 0x16, 0xE1, 0x0B, 0xF6, 0x21, 0xB2}
#define OTAA_APPEUI   {0x47, 0x3A, 0x16, 0xE1, 0x0B, 0xF6, 0x21, 0xB2}
#define OTAA_APPKEY   {0x58, 0x1A, 0x0E, 0x35, 0x90, 0x12, 0x93, 0x01, 0xD6, 0x0C, 0xC4, 0x7D, 0xB6, 0x51, 0x53, 0xBF}

const int ALARM_ON_THRESHOLD = 3600; 

// Định nghĩa các trạng thái của hệ thống
enum SystemState {
  MONITORING, // Trạng thái giám sát bình thường
  CONFIRMING, // Trạng thái chờ xác nhận trong 3 giây
  ALARMING    // Trạng thái báo động trong 5 phút
};
SystemState currentState = MONITORING; // Trạng thái ban đầu

// Các hằng số thời gian
const unsigned long CONFIRMATION_DURATION = 3000;   // 3 giây để xác nhận
const unsigned long ALARM_PERIOD = 300000;        // 5 phút báo động (5 * 60 * 1000)

// Các biến theo dõi thời gian
unsigned long confirmation_start_time = 0; // Mốc thời gian bắt đầu xác nhận
unsigned long alarm_period_start_time = 0;   // Mốc thời gian bắt đầu báo động

// Cài đặt phần cứng và các biến khác
bool button_press_handled = false;                          
uint8_t analogPin = PA10; 
const int BUZZER_PIN = PA1;
const int USER_BUTTON_PIN = PA8;
const int SENSOR_POWER_PIN = PA9;
const int SENSOR_STABILIZE_TIME = 300;
const int LED_PIN = PB4;
uint32_t last_blink_time = 0;
const int BLINK_INTERVAL = 200;

/** Packet buffer for sending */
uint8_t collected_data[64] = { 0 };

// --- CÁC HÀM CALLBACK CỦA LORAWAN (giữ nguyên) ---
void recvCallback(SERVICE_LORA_RECEIVE_T * data) {
    if (data->BufferSize > 0) {
        Serial.println("Something received!");
        for (int i = 0; i < data->BufferSize; i++) {
            Serial.printf("%x", data->Buffer[i]);
        }
        Serial.print("\r\n");
    }
}
void joinCallback(int32_t status) {
    Serial.printf("Join status: %d\r\n", status);
}
void sendCallback(int32_t status) {
    if (status == RAK_LORAMAC_STATUS_OK) {
        Serial.println("Successfully sent packet");
    } else {
        Serial.println("Sending failed");
    }
}
void wakeup_callback() {
}

void setup()
{
    Serial.begin(115200);
    delay(2000);
    Serial.println("RAKwireless Smoke Detector with LoRaWAN OTAA - State Machine Logic");
    Serial.println("------------------------------------------------------");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    pinMode(SENSOR_POWER_PIN, OUTPUT);
    digitalWrite(SENSOR_POWER_PIN, LOW);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    
    analogReadResolution(14);
    pinMode(USER_BUTTON_PIN, INPUT_PULLUP);
    api.system.sleep.setup(RUI_WAKEUP_FALLING_EDGE, USER_BUTTON_PIN);
    api.system.sleep.registerWakeupCallback(wakeup_callback);
    if (api.system.sleep.registerWakeupCallback(wakeup_callback) == false)
    {
        Serial.println("Failed to register wakeup callback.");
    }

    Serial.println("Pins initialized. Wakeup source configured. Current State: MONITORING");
    
    if(api.lorawan.nwm.get() != 1) {
        Serial.printf("Set Node device work mode %s\r\n", api.lorawan.nwm.set() ? "Success" : "Fail");
        api.system.reboot();
    }
    uint8_t node_device_eui[8] = OTAA_DEVEUI;
    uint8_t node_app_eui[8] = OTAA_APPEUI;
    uint8_t node_app_key[16] = OTAA_APPKEY;
    if (!api.lorawan.deui.set(node_device_eui, 8)) { Serial.printf("LoRaWan OTAA - set device EUI is incorrect! \r\n"); return; }
    if (!api.lorawan.appeui.set(node_app_eui, 8)) { Serial.printf("LoRaWan OTAA - set application EUI is incorrect! \r\n"); return; }
    if (!api.lorawan.appkey.set(node_app_key, 16)) { Serial.printf("LoRaWan OTAA - set application key is incorrect! \r\n"); return; }
    if (!api.lorawan.band.set(OTAA_BAND)) { Serial.printf("LoRaWan OTAA - set band is incorrect! \r\n"); return; }
    if (!api.lorawan.njm.set(RAK_LORA_OTAA)) { Serial.printf("LoRaWan OTAA - set network join mode is incorrect! \r\n"); return; }
    if (!api.lorawan.join()) { Serial.printf("LoRaWan OTAA - join fail! \r\n"); return; }
    while (api.lorawan.njs.get() == 0) { Serial.print("Wait for LoRaWAN join..."); api.lorawan.join(); delay(10000); }
    Serial.println("Successfully joined the network.");
    if (!api.lorawan.adr.set(true)) { Serial.printf("LoRaWan OTAA - set adaptive data rate is incorrect! \r\n"); }
    if (!api.lorawan.rety.set(1)) { Serial.printf("LoRaWan OTAA - set retry times is incorrect! \r\n"); }
    if (!api.lorawan.cfm.set(1)) { Serial.printf("LoRaWan OTAA - set confirm mode is incorrect! \r\n"); }
    api.lorawan.registerRecvCallback(recvCallback);
    api.lorawan.registerJoinCallback(joinCallback);
    api.lorawan.registerSendCallback(sendCallback);
}

// Hàm đọc ADC và trả về giá trị
int readSensor() {
    digitalWrite(SENSOR_POWER_PIN, HIGH);
    delay(SENSOR_STABILIZE_TIME);
    int adc_value = analogRead(analogPin);
    digitalWrite(SENSOR_POWER_PIN, LOW);
    return adc_value;
}

// Hàm xử lý nút nhấn (giữ nguyên)
void handleButtonPressAndSendData() {
    int adc_value = readSensor();
    Serial.printf("Manual ADC Read: %d\n", adc_value);
    
    uint8_t data_len = 0;
    collected_data[data_len++] = (adc_value >> 8) & 0xFF;
    collected_data[data_len++] = adc_value & 0xFF;
    if (api.lorawan.send(data_len, collected_data, 2, true, 1)) {
        Serial.println("Sending is requested");
    } else {
        Serial.println("Sending failed");
    }
}

// Hàm xử lý còi và đèn LED
void handleAlarmVisuals() {
    if (currentState == ALARMING) {
        digitalWrite(BUZZER_PIN, HIGH);
        if (millis() - last_blink_time > BLINK_INTERVAL) {
            last_blink_time = millis();
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        }
    } else {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
    }
}

void loop() {
    // Luôn xử lý nút nhấn nếu có
    if (digitalRead(USER_BUTTON_PIN) == LOW && !button_press_handled) {
        handleButtonPressAndSendData();
        button_press_handled = true; 
    } else if (digitalRead(USER_BUTTON_PIN) == HIGH) {
        button_press_handled = false;
    }

    // --- MÁY TRẠNG THÁI ---
    switch (currentState) {
        case MONITORING: {
            int adc_value = readSensor();
            Serial.printf("State: MONITORING, ADC: %d\r\n", adc_value);

            if (adc_value > ALARM_ON_THRESHOLD) {
                currentState = CONFIRMING;
                confirmation_start_time = millis();
                Serial.println("State change: -> CONFIRMING. Waiting for 3 seconds...");
            } else {
                // Nếu mọi thứ bình thường, đi ngủ sâu
                handleAlarmVisuals(); // Tắt đèn còi trước khi ngủ
                Serial.printf("All clear. Entering deep sleep for %d ms...\r\n", OTAA_PERIOD);
                api.system.sleep.all(OTAA_PERIOD);
                Serial.println("...Woke up from sleep.");
            }
            break;
        }

        case CONFIRMING: {
            int adc_value = readSensor();
            Serial.printf("State: CONFIRMING, ADC: %d\r\n", adc_value);
            
            if (adc_value > ALARM_ON_THRESHOLD) {
                if (millis() - confirmation_start_time > CONFIRMATION_DURATION) {
                    currentState = ALARMING;
                    alarm_period_start_time = millis();
                    Serial.println("State change: -> ALARMING. Alarm for 5 minutes. Sending LoRa packet.");
                    
                    // Gửi dữ liệu LoRaWAN khi xác nhận báo động
                    uint8_t data_len = 0;
                    collected_data[data_len++] = (adc_value >> 8) & 0xFF;
                    collected_data[data_len++] = adc_value & 0xFF;
                    api.lorawan.send(data_len, collected_data, 2, true, 1);
                }
            } else {
                currentState = MONITORING;
                Serial.println("Smoke cleared during confirmation. State change: -> MONITORING");
            }
            break;
        }

        case ALARMING: {
            Serial.println("State: ALARMING");
            if (millis() - alarm_period_start_time > ALARM_PERIOD) {
                currentState = MONITORING;
                Serial.println("5-minute alarm period ended. State change: -> MONITORING");
            }
            break;
        }
    }

   
    handleAlarmVisuals();
    
    
    delay(200);
}