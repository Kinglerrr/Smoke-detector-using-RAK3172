<table>
  <tr>
    <td><a href="#main-title">RAK3172 Smoke Detector</a></td>
        <td valign="top" rowspan="99">
        <div style="border: 2px dashed #ccc; padding: 40px 80px; text-align: center; color: #888; font-family: sans-serif; min-height: 100px;">
            (Your Project Banner)
            <br><br>
            (e.g., Discord Link, Image...)
        </div>
    </td>
  </tr>
  <tr>
    <td>&emsp;<a href="#quick-guide">Quick Guide</a></td>
  </tr>
  <tr>
    <td>&emsp;<a href="#overview">Overview</a></td>
  </tr>
  <tr>
    <td>&emsp;&emsp;<a href="#features">Features</a></td>
  </tr>
  <tr>
    <td>&emsp;&emsp;<a href="#pinout">Hardware Configuration</a></td>
  </tr>
  <tr>
    <td>&emsp;&emsp;<a href="#logic-flow">Operational Flow</a></td>
  </tr>
  <tr>
    <td>&emsp;<a href="#lorawan-payload">Payload Structure</a></td>
  </tr>
  <tr>
    <td>&emsp;<a href="#setup">Setup & Customization</a></td>
  </tr>
    <tr><td>&nbsp;</td></tr>
  <tr><td>&nbsp;</td></tr>
  <tr><td>&nbsp;</td></tr>
</table>

<h1 id="main-title">RAK3172 Smoke Detector</h1>

<p>
    <a href="#"><img alt="Hardware" src="https://img.shields.io/badge/Hardware-RAK3172-blue?style=flat&logo=rakwireless"></a>
    <a href="#"><img alt="Protocol" src="https://img.shields.io/badge/Protocol-LoRaWAN-orange?style=flat&logo=lora"></a>
    <a href="#"><img alt="License" src="https://img.shields.io/badge/License-MIT-green?style=flat"></a>
    <a href="#"><img alt="Language" src="https://img.shields.io/badge/Language-C++%20(Arduino)-blueviolet?style=flat&logo=cplusplus"></a>
</p>

<h2 id="quick-guide">Quick Guide</h2>
<p>
  Press the arrows to reveal the option you want.
  <details>
    <summary>
      <b>I want to see the pinout.</b> <sup>(Click to Expand)</sup>
    </summary>
    <a href="#pinout">Click here</a> to see the hardware configuration table.
  </details>
  <details>
    <summary>
      <b>I want to configure the LoRaWAN parameters.</b> <sup>(Click to Expand)</sup>
    </summary>
    <a href="#setup">Click here</a> for setup and customization instructions, including <code>DEVEUI</code>, <code>APPKEY</code>.
  </details>
  <details>
    <summary>
      <b>How does the device's logic work?</b> <sup>(Click to Expand)</sup>
    </summary>
    <a href="#logic-flow">Click here</a> for an explanation of the 3 states: Monitoring, Confirming, and Alarming.
  </details>
</p>

<h2 id="overview">Overview</h2>
<p>
  This project is a smart smoke detector using the RAK3172 module, featuring LoRaWAN connectivity. The device is designed for energy efficiency by using deep sleep and a state machine to reliably handle alarm logic.
  <br>
  <img alt="Schematic" src="kinglerrr/smoke-detector-using-rak3172/Smoke-detector-using-RAK3172-c89e80f68978ae7cde9dc17f3c26443eaf579467/Schematic-image.jpg" width="800">
</p>

<h2 id="features">Features</h2>
  <ul>
    <li><strong>Core Module:</strong> RAK3172</li>
    <li><strong>Connectivity:</strong> LoRaWAN OTAA (Over-The-Air Activation).</li>
    <li><strong>Sensor:</strong> Analog smoke/gas sensor (e.g., MQ series).</li>
    <li><strong>Smart Logic:</strong> Uses a state machine with 3 modes: <code>MONITORING</code>, <code>CONFIRMING</code>, and <code>ALARMING</code>.</li>
    <li><strong>Energy Efficient:</strong> Leverages deep sleep and only powers the sensor when a reading is needed.</li>
    <li><strong>On-site Alerts:</strong> Integrated Buzzer and LED to provide alerts when smoke is detected.</li>
    <li><strong>Manual Button:</strong> Allows the user to press a button to immediately take a sensor reading and send a LoRaWAN packet.</li>
  </ul>

<h2 id="pinout">Hardware Configuration (Pinout)</h2>
<p>
  The schematic and source code (<code>otaa1.ino</code>) define the following pins:
</p>
<table border="1" cellpadding="5" cellspacing="0" style="border-collapse: collapse;">
    <thead>
        <tr style="background-color: #f0f0f0;">
            <th>RAK3172 Pin</th>
            <th>Function</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><code>PA10</code></td>
            <td><code>MQ_ADC</code></td>
            <td>Analog pin to read the value from the smoke sensor.</td>
        </tr>
        <tr>
            <td><code>PA9</code></td>
            <td><code>Sensor_EN</code></td>
            <td>Digital pin to turn the sensor power on/off (power saving).</td>
        </tr>
        <tr>
            <td><code>PA1</code></td>
            <td><code>BUZZER_CTRL</code></td>
            <td>Digital pin to control the buzzer.</td>
        </tr>
        <tr>
            <td><code>PB4</code></td>
            <td><code>LED_CTRL</code></td>
            <td>Digital pin to control the alarm LED.</td>
        </tr>
        <tr>
            <td><code>PA8</code></td>
            <td><code>USER_BUTTON</code></td>
            <td>Input pin (pull-up) for the user button.</td>
        </tr>
    </tbody>
</table>

<h2 id="logic-flow">Operational Flow (State Machine)</h2>
<p>
  The device operates on a state machine to avoid false alarms and manage power efficiently.
</p>
  <ol>
    <li>
      <strong><code>MONITORING</code></strong>
      <p>This is the default state. The device wakes up every 25 seconds (<code>OTAA_PERIOD</code>) (or on button press).</p>
      <p>The device powers on the sensor, reads the ADC value.</p>
      <ul>
        <li><strong>If value &lt; 3600</strong> (<code>ALARM_ON_THRESHOLD</code>): All normal. The device turns off the buzzer/LED and returns to deep sleep.</li>
        <li><strong>If value &gt; 3600</strong>: Smoke detected. The device switches to the <code>CONFIRMING</code> state.</li>
      </ul>
    </li>
    <li>
      <strong><code>CONFIRMING</code></strong>
      <p>This state lasts for 3 seconds (<code>CONFIRMATION_DURATION</code>).</p>
      <p>The device continuously reads the sensor without sleeping.</p>
      <ul>
        <li><strong>If value remains &gt; 3600</strong> after 3 seconds: Smoke confirmed. The device sends a LoRaWAN packet containing the ADC value, then switches to the <code>ALARMING</code> state.</li>
        <li><strong>If value &lt; 3600</strong> (smoke cleared): This was a false alarm. The device returns to <code>MONITORING</code>.</li>
      </ul>
    </li>
    <li>
      <strong><code>ALARMING</code></strong>
      <p>The device activates the buzzer and continuously flashes the LED.</p>
      <p>This state is maintained for 5 minutes (<code>ALARM_PERIOD</code>).</p>
      <p>After 5 minutes, the device automatically returns to <code>MONITORING</code> to re-evaluate the situation.</p>
    </li>
  </ol>

<h2 id="lorawan-payload">LoRaWAN Payload Structure</h2>
<p>
  The payload (payload) sent during an alarm or manual press consists of only 2 bytes, containing the ADC value read from the sensor.
</p>
  <ul>
    <li><strong>Byte 1:</strong> <code>(adc_value >> 8) & 0xFF</code> (High Byte)</li>
    <li><strong>Byte 2:</strong> <code>(adc_value & 0xFF)</code> (Low Byte)</li>
  </ul>
  <p><strong>Payload Decoder (example for The Things Network):</strong></p>
<pre><code>function Decoder(bytes, port) {
  var adc_value = (bytes[0] &lt;&lt; 8) | bytes[1];
  return {
    adc: adc_value
  };
}</code></pre>

<h2 id="setup">Setup & Customization</h2>
<p>
  To use this source code, you need to customize the parameters in the <code>otaa1.ino</code> file:
</p>
  <h3>1. LoRaWAN Region</h3>
<pre><code>#define OTAA_BAND (RAK_REGION_AS923_2) // Set your LoRaWAN region</code></pre>
  <h3>2. OTAA Credentials</h3>
  <p>Replace these values with the credentials from your LoRaWAN server:</p>
<pre><code>#define OTAA_DEVEUI {0x47, 0x3A, 0x16, 0xE1, 0x0B, 0xF6, 0x21, 0xB2}
#define OTAA_APPEUI {0x47, 0x3A, 0x16, 0xE1, 0x0B, 0xF6, 0x21, B2}
#define OTAA_APPKEY {0x58, 0x1A, 0x0E, 0x35, 0x90, 0x12, 0x93, 0x01, 0xD6, 0x0C, 0xC4, 0x7D, 0xB6, 0x51, 0x53, 0xBF}</code></pre>
  <h3>3. Alarm Threshold</h3>
  <p>Adjust the ADC value to trigger the alarm. This value depends on your sensor and environment.</p>
<pre><code>const int ALARM_ON_THRESHOLD = 3600;</code></pre>
  <h3>4. Timings</h3>
  <p>You can also adjust the time constants (in milliseconds):</p>
<pre><code>#define OTAA_PERIOD (25000) // Sleep time in MONITORING mode
const unsigned long CONFIRMATION_DURATION = 3000; // Time in CONFIRMING mode
const unsigned long ALARM_PERIOD = 300000; // Alarm duration (5 minutes)</code></pre>
