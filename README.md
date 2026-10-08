# ESP32 Dual-LED Control with OneButton

Dự án điều khiển 2 đèn LED (LED tích hợp và LED ngoài) thông qua 1 nút nhấn sử dụng thư viện **OneButton** trên nền tảng **PlatformIO**.

---

## 1. Phần cứng

| STT | Tên linh kiện | Số lượng | Ghi chú |
| :-: | :--- | :-: | :--- |
| 1 | ESP32 Devkit V1 | 01 | Vi điều khiển trung tâm |
| 2 | LED 1 (Built-in) | 01 | Đèn LED xanh lam tích hợp trên board |
| 3 | LED 2 (External) | 01 | Mắc nối tiếp trở 1K về chân GND |
| 4 | Điện trở vạch 1K 1/4W | 01 | Hạn dòng bảo vệ LED 2 |
| 5 | Nút nhấn 4 chân | 01 | Nối về GND (kích hoạt Internal Pull-up) |
| 6 | Breadboard & Dây nối | 01 | Cắm mạch thử nghiệm |

---

## 2. Tính năng phần mềm

* **Double Click (Nhấn đúp 2 lần):** Chuyển đổi đối tượng điều khiển giữa LED 1 (GPIO 2) và LED 2 (GPIO 18).
* **Single Click (Nhấn 1 lần):** Bật / Tắt  LED đang được chọn. Nếu LED đang nhấp nháy, nhấn 1 lần sẽ dừng nháy và tắt hẳn LED.
* **Long Press (Nhấn giữ > 800ms):** Bật / Tắt chế độ nhấp nháy liên tục 200ms cho LED đang được chọn.
* **Non-blocking Execution:** Áp dụng kỹ thuật đếm thời gian bằng hàm `millis()`, đảm bảo hiệu ứng nháy không làm nghẽn vòng lặp và chức năng quét phím `btn.tick()` luôn phản hồi tức thì.
