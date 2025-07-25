# m5stack-lowpower-mqtt-monitor

[![M5Stack MQTT Monitor](https://github.com/user-attachments/assets/10f7d67f-31d8-4458-b196-be0de5a500e0)](https://github.com/omiya-bonsai/m5stack-lowpower-mqtt-monitor)

---

## 概要

このプロジェクトは、M5Stack BasicをMQTTで受信した環境データ（CO2、温度、湿度）のモニターとして機能させるためのArduinoスケッチです。

**低電力**での常時稼働を目指し、MQTT接続を維持しながらバックグラウンドでデータを受信し続けます。一定時間操作がない場合はディスプレイを完全にオフにして消費電力を抑え、いずれかのボタンを押すと即座に復帰して最新のデータを表示します。

Wi-FiやMQTTの接続情報といった個人設定は、安全な共有と管理のため `config.h` ファイルに分離されています。

---

## ✨ 機能

- **リアルタイムデータ表示**: MQTTで受信した環境データをスタイリッシュなダークモードUIで表示
- **詳細画面**: 本体ボタンでCO2・温度・湿度の各詳細画面に切り替え可能
- **高度な省電力機能**: 一定時間（デフォルト5分）無操作でディスプレイを完全オフ
- **常時接続**: 省電力中もWi-FiとMQTT接続を維持し、データ受信を継続
- **即時復帰**: ボタン押下でスリープから即座に復帰し、最新データを表示
- **安全な設定管理**: Wi-Fi認証情報などを `config.h` に分離し、GitHubでの安全なコード共有が可能

---

## 🛠️ 必要なもの

### ハードウェア
- M5Stack Basic

### ソフトウェア・ライブラリ
- Arduino IDE
- **Arduino IDEライブラリ:**
  - `M5Unified`
  - `PubSubClient`
  - `ArduinoJson`

---

## 🚀 セットアップ手順

1.  **リポジトリのクローン:**
    このリポジトリをローカルにクローンします。
    
    **HTTPSの場合:**
    ```zsh
    git clone https://github.com/omiya-bonsai/m5stack-lowpower-mqtt-monitor.git
    ```
    
    **SSHの場合:**
    ```zsh
    git clone git@github.com:omiya-bonsai/m5stack-lowpower-mqtt-monitor.git
    ```

2.  **ライブラリのインストール:**
    Arduino IDEのメニューから `スケッチ` > `ライブラリをインクルード` > `ライブラリを管理...` を開き、上記の3つのライブラリを検索してインストールします。

3.  **設定ファイルの作成:**
    `config.example.h` ファイルをコピーし、`config.h` という名前で新しいファイルを作成します。
    
    リポジトリのディレクトリ内で、以下のコマンドを実行します。
    ```zsh
    cp config.example.h config.h
    ```

4.  **個人情報の設定:**
    作成した `config.h` をテキストエディタで開き、ご自身のWi-FiのSSID・パスワード、およびMQTTブローカーの情報を書き込んで保存します。

5.  **書き込み:**
    Arduino IDEで `M5Stack_LowPower_MQTT_Monitor.ino` を開き、ボードに「M5Stack Core ESP32」を選択してスケッチを書き込みます。

---

## 🔧 カスタマイズ

- **MQTTトピックの変更**: `config.h` ファイル内の `MQTT_TOPIC` の値を変更します。
- **ディスプレイオフ時間**: `.ino` ファイル冒頭の `DISPLAY_OFF_TIMEOUT` の値を変更します（ミリ秒単位）。
- **UIデザイン**: `.ino` ファイル冒頭のカラーパレット定義 (`#define COLOR_...`) の値を変更することで、お好みの配色にカスタマイズできます。

---

## Acknowledgements

このプロジェクトのコード生成、デバッグ、ドキュメント作成の一部は、GoogleのAIアシスタント **Gemini** の支援を受けて行われました。

[![Built with Gemini](https://img.shields.io/badge/Built%20with-Gemini-blue.svg)](https://gemini.google.com)

---

## 📄 ライセンス

このプロジェクトはMITライセンスです。詳細は [LICENSE](LICENSE) ファイルをご覧ください。
