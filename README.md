<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>README - Máy dò khói RAK3172</title>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
            line-height: 1.6;
            background-color: #f6f8fa;
            color: #24292e;
            margin: 0;
            padding: 0;
        }
        .container {
            max-width: 900px;
            margin: 20px auto;
            padding: 25px;
            background-color: #ffffff;
            border: 1px solid #e1e4e8;
            border-radius: 6px;
        }
        
        /* --- Bố cục Mục lục & Banner (như ví dụ) --- */
        .header-layout {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 20px;
        }
        .header-layout .toc-cell {
            width: 250px; /* Độ rộng cố định cho mục lục */
            vertical-align: top;
            padding-right: 20px;
        }
        .header-layout .toc-cell a {
            text-decoration: none;
            color: #0366d6;
        }
        .header-layout .toc-cell a:hover {
            text-decoration: underline;
        }
        .header-layout .banner-cell {
            width: auto; /* Phần còn lại cho banner */
            vertical-align: top;
        }
        .header-layout .banner-placeholder {
            display: flex;
            align-items: center;
            justify-content: center;
            height: 100px;
            background-color: #f1f1f1;
            border: 2px dashed #ccc;
            border-radius: 6px;
            color: #888;
            font-style: italic;
        }
        
        /* --- Badges --- */
        .badges {
            margin-top: 10px;
            margin-bottom: 20px;
        }
        .badges img {
            height: 20px;
            margin-right: 5px;
            display: inline-block;
        }
        
        /* --- Hướng dẫn nhanh (Quick Guide) --- */
        .quick-guide details {
            margin-bottom: 8px;
            border: 1px solid #e1e4e8;
            border-radius: 6px;
        }
        .quick-guide summary {
            padding: 10px 15px;
            font-weight: 600;
            cursor: pointer;
            background-color: #f6f8fa;
        }
        .quick-guide summary:hover {
            background-color: #f1f1f1;
        }
        .quick-guide details[open] {
            padding: 15px;
            padding-top: 5px;
        }
        .quick-guide a {
            color: #0366d6;
            font-weight: bold;
        }

        /* --- Các thành phần chuẩn --- */
        h1, h2, h3 {
            border-bottom: 1px solid #eaecef;
            padding-bottom: .3em;
            margin-top: 24px;
            margin-bottom: 16px;
            font-weight: 600;
        }
        h1 { font-size: 2.25em; }
        h2 { font-size: 1.75em; }
        h3 { font-size: 1.25em; }
        p {
            margin-top: 0;
            margin-bottom: 16px;
        }
        img.schematic {
            max-width: 100%;
            height: auto;
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: 5px;
            background-color: #fff;
            display: block;
            margin: 10px auto;
        }
        ul, ol {
            padding-left: 2em;
            margin-top: 0;
            margin-bottom: 16px;
        }
        li {
            margin-bottom: 6px;
        }
        table.pinout {
            border-collapse: collapse;
            border-spacing: 0;
            width: 100%;
            margin-bottom: 16px;
            display: block;
            overflow: auto;
        }
        table.pinout th, table.pinout td {
            padding: 10px 15px;
            border: 1px solid #dfe2e5;
        }
        table.pinout th {
            background-color: #f6f8fa;
            font-weight: 600;
        }
        table.pinout tr:nth-child(even) {
            background-color: #f6f8fa;
        }
        pre {
            background-color: #f6f8fa;
            border: 1px solid #e1e4e8;
            border-radius: 6px;
            padding: 16px;
            overflow: auto;
            line-height: 1.45;
        }
        code {
            font-family: "SFMono-Regular", Consolas, "Liberation Mono", Menlo, Courier, monospace;
            font-size: 0.9em;
            background-color: rgba(27,31,35,.05);
            border-radius: 3px;
            padding: .2em .4em;
        }
        pre > code {
            background-color: transparent;
            padding: 0;
            border-radius: 0;
        }
        strong {
            font-weight: 600;
        }
    </style>
</head>
<body>
    <div class="container">

        <table class="header-layout">
            <tr>
                <td class="toc-cell" rowspan="8">
                    <strong>Mục lục</strong>
                    <br>&emsp;<a href="#top">Tổng quan</a>
                    <br>&emsp;<a href="#quick-guide">Hướng dẫn nhanh</a>
                    <br>&emsp;<a href="#features">Tính năng</a>
                    <br>&emsp;<a href="#pinout">Cấu hình phần cứng</a>
                    <br>&emsp;<a href="#logic-flow">Luồng hoạt động</a>
                    <br>&emsp;<a href="#lorawan-payload">Cấu trúc gói tin</a>
                    <br>&emsp;<a href="#setup">Cài đặt & Tùy chỉnh</a>
                </td>
                
                <td class="banner-cell">
                    <div class="banner-placeholder">
                        (Đây là nơi đặt Banner, ví dụ: Discord)
                    </div>
                </td>
            </tr>
            <tr><td></td></tr>
            <tr><td></td></tr>
            <tr><td></td></tr>
            <tr><td></td></tr>
            <tr><td></td></tr>
            <tr><td></td></tr>
            <tr><td></td></tr>
        </table>
        
        <h1 id="top">Máy dò khói sử dụng RAK3172 với LoRaWAN</h1>
        
        <div class="badges">
            <img alt="Hardware" src="https://img.shields.io/badge/Hardware-RAK3172-blue?style=flat&logo=rakwireless">
            <img alt="Protocol" src="https://img.shields.io/badge/Protocol-LoRaWAN-orange?style=flat&logo=lora">
            <img alt="License" src="https://img.shields.io/badge/License-MIT-green?style=flat">
            <img alt="Language" src="https://img.shields.io/badge/Language-C++%20(Arduino)-blueviolet?style=flat&logo=cplusplus">
        </div>
        
        <p>Dự án này là một thiết bị dò khói thông minh sử dụng mô-đun RAK3172, có khả năng kết nối LoRaWAN. Thiết bị được thiết kế để tiết kiệm năng lượng bằng cách sử dụng chế độ ngủ sâu và một máy trạng thái (state machine) để xử lý logic báo động một cách đáng tin cậy.</p>
        
        <img class="schematic" src="kinglerrr/smoke-detector-using-rak3172/Smoke-detector-using-RAK3172-c89e80f68978ae7cde9dc17f3c26443eaf579467/Schematic-image.jpg" alt="Sơ đồ mạch">

        <h2 id="quick-guide">Hướng dẫn nhanh</h2>
        <div class="quick-guide">
            <details>
                <summary>
                    <b>Tôi muốn xem sơ đồ chân (pinout).</b> <sup>(Nhấn để mở)</sup>
                </summary>
                <a href="#pinout">Nhấn vào đây</a> để xem bảng cấu hình phần cứng.
            </details>
            <details>
                <summary>
                    <b>Tôi muốn cấu hình thông số LoRaWAN.</b> <sup>(Nhấn để mở)</sup>
                </summary>
                <a href="#setup">Nhấn vào đây</a> để xem hướng dẫn cài đặt và tùy chỉnh, bao gồm <code>DEVEUI</code>, <code>APPKEY</code>.
            </details>
            <details>
                <summary>
                    <b>Logic hoạt động của thiết bị như thế nào?</b> <sup>(Nhấn để mở)</sup>
                </summary>
                <a href="#logic-flow">Nhấn vào đây</a> để xem giải thích về 3 trạng thái: Giám sát, Xác nhận, và Báo động.
            </details>
        </div>
        
        <h2 id="features">Tính năng</h2>
        <ul>
            <li><strong>Mô-đun lõi:</strong> RAK3172</li>
            <li><strong>Kết nối:</strong> LoRaWAN OTAA (Over-The-Air Activation).</li>
            <li><strong>Cảm biến:</strong> Cảm biến khói/khí analog (ví dụ: dòng MQ).</li>
            <li><strong>Logic thông minh:</strong> Sử dụng máy trạng thái với 3 chế độ: <code>MONITORING</code> (Giám sát), <code>CONFIRMING</code> (Xác nhận), và <code>ALARMING</code> (Báo động).</li>
            <li><strong>Tiết kiệm năng lượng:</strong> Tận dụng chế độ ngủ sâu (deep sleep) và chỉ bật nguồn cảm biến khi cần đọc giá trị.</li>
            <li><strong>Cảnh báo tại chỗ:</strong> Tích hợp còi (Buzzer) và đèn LED để báo động khi phát hiện khói.</li>
            <li><strong>Nút nhấn thủ công:</strong> Cho phép người dùng nhấn nút để ngay lập tức đọc cảm biến và gửi một gói tin LoRaWAN.</li>
        </ul>
        
        <h2 id="pinout">Cấu hình phần cứng (Pinout)</h2>
        <p>Sơ đồ mạch và mã nguồn (<code>otaa1.ino</code>) xác định các chân sau:</p>
        <table class="pinout">
            <thead>
                <tr>
                    <th>Chân RAK3172</th>
                    <th>Chức năng</th>
                    <th>Mô tả</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td><code>PA10</code></td>
                    <td><code>MQ_ADC</code></td>
                    <td>Chân Analog để đọc giá trị từ cảm biến khói.</td>
                </tr>
                <tr>
                    <td><code>PA9</code></td>
                    <td><code>Sensor_EN</code></td>
                    <td>Chân Digital để bật/tắt nguồn cho cảm biến (tiết kiệm pin).</td>
                </tr>
                <tr>
                    <td><code>PA1</code></td>
                    <td><code>BUZZER_CTRL</code></td>
                    <td>Chân Digital để điều khiển còi báo động.</td>
                </tr>
                <tr>
                    <td><code>PB4</code></td>
                    <td><code>LED_CTRL</code></td>
                    <td>Chân Digital để điều khiển đèn LED báo động.</td>
                </tr>
                <tr>
                    <td><code>PA8</code></td>
                    <td><code>USER_BUTTON</code></td>
                    <td>Chân Input (kéo lên) cho nút nhấn của người dùng.</td>
                </tr>
            </tbody>
        </table>
        
        <h2 id="logic-flow">Luồng hoạt động (Máy trạng thái)</h2>
        <p>Thiết bị hoạt động dựa trên một máy trạng thái để tránh báo động giả và quản lý năng lượng hiệu quả.</p>
        <ol>
            <li>
                <strong><code>MONITORING</code> (Giám sát)</strong>
                <p>Đây là trạng thái mặc định. Thiết bị sẽ thức dậy sau mỗi 25 giây (<code>OTAA_PERIOD</code>) (hoặc khi nhấn nút).</p>
                <p>Thiết bị bật nguồn cảm biến, đọc giá trị ADC.</p>
                <ul>
                    <li><strong>Nếu giá trị &lt; 3600</strong> (<code>ALARM_ON_THRESHOLD</code>): Mọi thứ bình thường. Thiết bị tắt còi/LED và quay lại chế độ ngủ sâu.</li>
                    <li><strong>Nếu giá trị &gt; 3600</strong>: Có dấu hiệu khói. Thiết bị chuyển sang trạng thái <code>CONFIRMING</code>.</li>
                </ul>
            </li>
            <li>
                <strong><code>CONFIRMING</code> (Xác nhận)</strong>
                <p>Trạng thái này kéo dài 3 giây (<code>CONFIRMATION_DURATION</code>).</p>
                <p>Thiết bị liên tục đọc cảm biến mà không ngủ.</p>
                <ul>
                    <li><strong>Nếu giá trị vẫn &gt; 3600</strong> sau 3 giây: Xác nhận có khói. Thiết bị gửi một gói tin LoRaWAN chứa giá trị ADC, sau đó chuyển sang trạng thái <code>ALARMING</code>.</li>
                    <li><strong>Nếu giá trị &lt; 3600</strong> (khói tan): Đây là báo động giả. Thiết bị quay lại trạng thái <code>MONITORING</code>.</li>
                </ul>
            </li>
            <li>
                <strong><code>ALARMING</code> (Báo động)</strong>
                <p>Thiết bị kích hoạt còi kêu và đèn LED nhấp nháy liên tục.</p>
                <p>Trạng thái này duy trì trong 5 phút (<code>ALARM_PERIOD</code>).</p>
                <p>Sau 5 phút, thiết bị tự động quay lại trạng thái <code>MONITORING</code> để đánh giá lại tình hình.</p>
            </li>
        </ol>
        
        <h2 id="lorawan-payload">Cấu trúc gói tin LoRaWAN</h2>
        <p>Gói tin (payload) gửi đi khi có báo động hoặc khi nhấn nút thủ công chỉ bao gồm 2 byte, chứa giá trị ADC đọc được từ cảm biến.</p>
        <ul>
            <li><strong>Byte 1:</strong> <code>(adc_value >> 8) & 0xFF</code> (Byte cao)</li>
            <li><strong>Byte 2:</strong> <code>adc_value & 0xFF</code> (Byte thấp)</li>
        </ul>
        <p><strong>Payload Decoder (ví dụ cho The Things Network):</strong></p>
<pre><code>function Decoder(bytes, port) {
  var adc_value = (bytes[0] &lt;&lt; 8) | bytes[1];
  return {
    adc: adc_value
  };
}</code></pre>
        
        <h2 id="setup">Cài đặt và Tùy chỉnh</h2>
        <p>Để sử dụng mã nguồn này, bạn cần tùy chỉnh các thông số trong tệp <code>otaa1.ino</code>:</p>
        
        <h3>1. Khu vực LoRaWAN</h3>
<pre><code>#define OTAA_BAND (RAK_REGION_AS923_2) // Đặt vùng LoRaWAN của bạn</code></pre>
        
        <h3>2. Thông tin xác thực OTAA</h3>
        <p>Thay thế các giá trị này bằng thông tin từ máy chủ LoRaWAN của bạn:</p>
<pre><code>#define OTAA_DEVEUI {0x47, 0x3A, 0x16, 0xE1, 0x0B, 0xF6, 0x21, 0xB2}
#define OTAA_APPEUI {0x47, 0x3A, 0x16, 0xE1, 0x0B, 0xF6, 0x21, 0xB2}
#define OTAA_APPKEY {0x58, 0x1A, 0x0E, 0x35, 0x90, 0x12, 0x93, 0x01, 0xD6, 0x0C, 0xC4, 0x7D, 0xB6, 0x51, 0x53, 0xBF}</code></pre>
        
        <h3>3. Ngưỡng báo động</h3>
        <p>Điều chỉnh giá trị ADC để kích hoạt báo động. Giá trị này phụ thuộc vào loại cảm biến và môi trường của bạn.</p>
<pre><code>const int ALARM_ON_THRESHOLD = 3600;</code></pre>
        
        <h3>4. Thời gian</h3>
        <p>Bạn cũng có thể điều chỉnh các hằng số thời gian (tính bằng mili giây):</p>
<pre><code>#define OTAA_PERIOD (25000) // Thời gian ngủ ở chế độ MONITORING
const unsigned long CONFIRMATION_DURATION = 3000; // Thời gian ở chế độ CONFIRMING
const unsigned long ALARM_PERIOD = 300000; // Thời gian báo động (5 phút)</code></pre>
    </div>
</body>
</html>
