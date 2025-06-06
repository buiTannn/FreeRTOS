# ESP32
## Mô tả
FRAMEWORK : ARDUINO 
Dự án này sử dụng bo mạch ESP32 để đọc và hiển thị dữ liệu từ các cảm biến bao gồm:

- **Cảm biến MQ2** (phát hiện khí gas/smoke qua ADC)
- **Cảm biến siêu âm HC-SR04** (đo khoảng cách)
- **Màn hình LCD I2C 16x2** (hiển thị dữ liệu cảm biến)
- **Buzzer** (phát nhạc nền Super Mario)
- **LED điều khiển bằng nút nhấn**
- **Nút nhấn sử dụng Semaphore + FreeRTOS**

## Tính năng

- Đọc giá trị khí gas từ MQ2 mỗi 1 giây và lưu vào biến toàn cục.
- Đo khoảng cách bằng HC-SR04 và hiển thị cùng giá trị MQ2 lên LCD mỗi 1 giây.
- Phát nhạc nền Super Mario trên buzzer khi được kích hoạt.
- Điều khiển LED qua hai nút ON/OFF.
- Một nút nhấn dùng `Semaphore` để chớp LED 3 lần.
- Chạy đa nhiệm sử dụng **FreeRTOS**.

## Phần cứng yêu cầu

| Thiết bị            | Ghi chú            |
|--------------------|--------------------|
| ESP32 Dev Board     |                    |
| Cảm biến MQ2       | Dùng GPIO32 (ADC1_CHANNEL_4) |
| Cảm biến HC-SR04   | Trig: GPIO23, Echo: GPIO5 |
| LCD 16x2 I2C       | I2C addr: 0x27     |
| Buzzer             | GPIO15             |
| LED                | GPIO14             |
| Nút nhấn ON        | GPIO2              |
| Nút nhấn OFF       | GPIO18             |
| Nút nhấn semaphore | GPIO27             |
| LED chớp (sem)     | GPIO12             |

## Thư viện cần cài đặt

- **LiquidCrystal_I2C** (có sẵn trong Library Manager)
- **HCSR04** (từ `gamegine/HCSR04`)
- **FreeRTOS** (đã tích hợp sẵn trong ESP32 Arduino Core)

## Cấu trúc mã chính

- `readMQ2SensorTask`: đọc cảm biến MQ2 mỗi 1 giây.
- `timerCallback`: gọi mỗi 1 giây để cập nhật LCD.
- `TaskPlayMelody`: phát bài nhạc Super Mario qua buzzer.
- `ledControlTask`: kiểm tra nút ON/OFF để điều khiển LED.
- `blinkLedOnButton`: sử dụng semaphore để chớp LED khi nhấn nút.

## Cách sử dụng

1. Kết nối phần cứng như mô tả ở trên.
2. Tải code lên ESP32 qua Arduino IDE.
3. Nhấn nút ON/OFF để bật/tắt LED.
4. Nhấn nút semaphore để làm LED chớp 3 lần.
5. Xem dữ liệu cảm biến hiển thị trên màn hình LCD.
6. Buzzer tự động phát nhạc nền khi task `TaskPlayMelody` được kích hoạt.

## License

MIT License

---

© 2025 - Arduino FreeRTOS Project
