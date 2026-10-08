# ESP32 Dual-LED Control with OneButton

Dự án điều khiển 2 đèn LED (LED tích hợp và LED ngoài) thông qua 1 nút nhấn sử dụng thư viện **OneButton** trên nền tảng **PlatformIO**.

---

## 1. Phần cứng

| STT | Tên linh kiện | Số lượng | Ghi chú |
| :-: | :--- | :-: | :--- |
| 1 | ESP32 Devkit V1 | 01 | Vi điều khiển trung tâm |
| 2 | LED 1 (Built-in) | 01 | Đèn LED xanh lam tích hợp sẵn nội vi trên chân GPIO 2 của mạch |
| 3 | LED 2 (External) | 01 | Cực dương nối vào GPIO 18, cực âm nối qua trở 1K về GND |
| 4 | Điện trở vạch 1K 1/4W | 01 | Mắc nối tiếp giữa chân âm của LED 2 và chân GND của ESP32 để hạn dòng bảo vệ LED |
| 5 | Nút nhấn 4 chân | 01 | Một chân cắm vào GPIO 19, chân đối diện nối về GND |
| 6 | Breadboard & Dây nối | 01 | Cắm mạch thử nghiệm |

---

## 2. Tính năng phần mềm

* **Double Click (Nhấn đúp 2 lần):** Chuyển đổi đối tượng điều khiển giữa LED 1 (GPIO 2) và LED 2 (GPIO 18).
* **Single Click (Nhấn 1 lần):** Bật / Tắt  LED đang được chọn. Nếu LED đang nhấp nháy, nhấn 1 lần sẽ dừng nháy và tắt hẳn LED.
* **Long Press (Nhấn giữ > 800ms):** Bật / Tắt chế độ nhấp nháy liên tục 200ms cho LED đang được chọn.
* **Xử lý không gây nghẽn:** Áp dụng kỹ thuật đếm thời gian bằng hàm `millis()`, đảm bảo hiệu ứng nháy không làm nghẽn vòng lặp và chức năng quét phím `btn.tick()` luôn phản hồi tức thì.
