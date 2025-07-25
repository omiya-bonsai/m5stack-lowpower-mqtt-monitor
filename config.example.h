#ifndef CONFIG_H
#define CONFIG_H

// =============================================================================
// 設定項目 - このファイルを "config.h" にコピーして、
//           あなたの環境に合わせて値を変更してください。
// =============================================================================

// WiFi接続設定
const char* WIFI_SSID     = "YOUR_WIFI_SSID";          // あなたのWiFiのSSID（名前）
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";  // あなたのWiFiのパスワード

// MQTT接続設定
const char* MQTT_SERVER_IP = "YOUR_MQTT_BROKER_IP";    // MQTTブローカーのIPアドレス
const int   MQTT_PORT      = 1883;                     // MQTTポート番号 (通常は1883)
const char* MQTT_TOPIC     = "your/device/topic";      // 購読したいMQTTトピック
const char* MQTT_CLIENT_ID = "M5Stack-Client-1";       // MQTTクライアントID (他の機器と重複しないように)

#endif // CONFIG_H