#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "HCSR04.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "driver/adc.h"

// ==== Định nghĩa chân và thông số ====
#define TRIG_PIN 23
#define ECHO_PIN 5

#define MQ2_SENSOR_PIN ADC1_CHANNEL_4  // GPIO32

#define BUZZER_PIN 15
#define BUZZER_CHANNEL 0

#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

#define TIMER_PERIOD pdMS_TO_TICKS(1000)  // 5 giây

// button_led
#define BTN_ON 2
#define BTN_OFF 18
#define LED_PIN 14

// Semaphore
#define BUTTON_SEM_PIN  27
#define LED_BLINK_PIN   12
#define DEBOUNCE_DELAY_MS 50
#define BLINK_COUNT 3
#define LED_ON_TIME  500
#define LED_OFF_TIME 500

// ==== LCD và cảm biến siêu âm ====
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);

SemaphoreHandle_t btnSemaphore = NULL;
int mq2SensorValue = 0;

// ==== Task đọc cảm biến MQ2 (ADC) ====
void readMQ2SensorTask(void *pvParameters)
{
    while (1) {
        mq2SensorValue = adc1_get_raw((adc1_channel_t)MQ2_SENSOR_PIN);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// ==== Hàm callback timer ====
void timerCallback(TimerHandle_t xTimer)
{
    double distance = distanceSensor.measureDistanceCm();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MQ2:");
    lcd.print(mq2SensorValue);

    lcd.setCursor(0, 1);
    if (isnan(distance)) {
        lcd.print("Distance err");
    } else {
        lcd.print("D:");
        lcd.print(distance, 2);
        lcd.print(" cm");
    }
}

// ==== Task điều khiển buzzer ====

// Tempo and timing
int tempo = 200;
int wholenote;

// Notes definitions
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Melody array: note, duration pairs
const int melody[] = {
  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
  REST,1, 
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
  
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  REST,1,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  
  //game over sound
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  
};

// Calculate number of notes
const int numNotes = sizeof(melody) / sizeof(melody[0]) / 2;

// Task function to play melody once
void TaskPlayMelody(void* pvParameters) {
  // Compute wholenote duration
  wholenote = (60000 * 4) / tempo;

  for (int i = 0; i < numNotes * 2; i += 2) {
    int note = melody[i];
    int durationCode = melody[i + 1];
    int noteDuration;

    if (durationCode > 0) {
      noteDuration = wholenote / durationCode;
    } else {
      noteDuration = (wholenote / abs(durationCode)) * 1.5;
    }

    // Play tone for 90% of duration
    tone(BUZZER_PIN, note, noteDuration * 0.9);
    vTaskDelay((noteDuration) / portTICK_PERIOD_MS);
    noTone(BUZZER_PIN);
  }

  // Suspend task when done
  vTaskSuspend(NULL);
}

// ==== Task điều khiển LED bằng nút ON/OFF ====

void ledControlTask(void *pvParameters) {
    bool lastBtnOnState  = LOW;
    bool lastBtnOffState = LOW;
    bool stableBtnOnState  = LOW;
    bool stableBtnOffState = LOW;

    TickType_t lastDebounceOnTime  = 0;
    TickType_t lastDebounceOffTime = 0;

    while (1) {
        TickType_t currentTime = xTaskGetTickCount();
        bool currentOnReading  = digitalRead(BTN_ON);
        bool currentOffReading = digitalRead(BTN_OFF);

        // Xử lý nút BTN_ON
        if (currentOnReading != lastBtnOnState) {
            lastDebounceOnTime = currentTime;
        }
        if ((currentTime - lastDebounceOnTime) >= pdMS_TO_TICKS(DEBOUNCE_DELAY_MS)) {
            if (currentOnReading != stableBtnOnState) {
                stableBtnOnState = currentOnReading;
                if (stableBtnOnState == HIGH) {
                    digitalWrite(LED_PIN, HIGH);
                    Serial.println("LED ON");
                }
            }
        }
        lastBtnOnState = currentOnReading;

        // Xử lý nút BTN_OFF
        if (currentOffReading != lastBtnOffState) {
            lastDebounceOffTime = currentTime;
        }
        if ((currentTime - lastDebounceOffTime) >= pdMS_TO_TICKS(DEBOUNCE_DELAY_MS)) {
            if (currentOffReading != stableBtnOffState) {
                stableBtnOffState = currentOffReading;
                if (stableBtnOffState == HIGH) {
                    digitalWrite(LED_PIN, LOW);
                    Serial.println("LED OFF");
                }
            }
        }
        lastBtnOffState = currentOffReading;

        vTaskDelay(pdMS_TO_TICKS(10));  // Delay nhỏ để phản hồi nhanh
    }
}


// ==== Task đọc nút và cấp semaphore ====
void btnSemaphoreTask(void *pvParameters) {
    bool buttonState = LOW;
    bool lastReading = LOW;
    TickType_t lastDebounceTime = 0;

    while(1) {
        TickType_t currentTime = xTaskGetTickCount();
        bool currentReading = digitalRead(BUTTON_SEM_PIN);

        if (currentReading != lastReading) {
            lastDebounceTime = currentTime;
        }

        if ((currentTime - lastDebounceTime) >= pdMS_TO_TICKS(DEBOUNCE_DELAY_MS)) {
            if (currentReading != buttonState) {
                buttonState = currentReading;
                if (buttonState == HIGH) {
                    if (xSemaphoreGive(btnSemaphore) == pdTRUE) {
                        Serial.println("Semaphore given!");
                    }
                }
            }
        }

        lastReading = currentReading;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// ==== Task blink LED khi nhận được semaphore ====
void ledBlinkTask(void *pvParameters) {
    while(1) {
        if (xSemaphoreTake(btnSemaphore, portMAX_DELAY) == pdTRUE) {
            Serial.println("Semaphore taken, start LED blink!");
            for (int i = 0; i < BLINK_COUNT; i++) {
                digitalWrite(LED_BLINK_PIN, HIGH);
                vTaskDelay(pdMS_TO_TICKS(LED_ON_TIME));
                digitalWrite(LED_BLINK_PIN, LOW);
                vTaskDelay(pdMS_TO_TICKS(LED_OFF_TIME));
            }
            Serial.println("LED blink complete.");
        }
    }
}

// ==== Setup ====
void setup()
{
    Serial.begin(115200);

    pinMode(BTN_ON, INPUT_PULLDOWN);
    pinMode(BTN_OFF, INPUT_PULLDOWN);
    pinMode(LED_PIN, OUTPUT);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(MQ2_SENSOR_PIN, ADC_ATTEN_DB_0);

    lcd.init();
    lcd.setBacklight(1);

    pinMode(BUZZER_PIN, OUTPUT);

    TimerHandle_t xTimer = xTimerCreate("SensorTimer", TIMER_PERIOD, pdTRUE, (void *)0, timerCallback);
    if (xTimer != NULL) {
        xTimerStart(xTimer, 0);
    }

    pinMode(BUTTON_SEM_PIN, INPUT_PULLDOWN);
    pinMode(LED_BLINK_PIN, OUTPUT);
    btnSemaphore = xSemaphoreCreateCounting(5, 0);
    if (btnSemaphore == NULL) {
        Serial.println("Failed to create semaphore!");
        while (1);
    }

    // Tạo các task
    xTaskCreate(readMQ2SensorTask, "ReadMQ2SensorTask", 2048, NULL, 2, NULL);
    xTaskCreate(TaskPlayMelody, "PlayMelody", 2048, NULL, 2, NULL);
    xTaskCreate(ledControlTask, "LED Control", 2048, NULL, 3, NULL);
    xTaskCreate(btnSemaphoreTask, "BtnSemaphoreTask", 2048, NULL, 2, NULL);
    xTaskCreate(ledBlinkTask, "LED_BlinkTask", 2048, NULL, 2, NULL);
}

void loop() {
    // Không sử dụng loop trong FreeRTOS
}
