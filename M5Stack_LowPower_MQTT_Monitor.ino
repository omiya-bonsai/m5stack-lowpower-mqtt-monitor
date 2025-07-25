/**
 * =================================================================================================
 *
 * M5Stack MQTT Environment Monitor
 * (低電力・常時接続版)
 *
 * =================================================================================================
 *
 * ## 1. このプログラムについて (What is this?)
 * -------------------------------------------------------------------------------------------------
 * このスケッチは、M5Stack Basicを高性能な「環境モニター」に変身させるためのプログラムです。
 * ネットワークを通じて送られてくるCO2濃度、温度、湿度のデータをリアルタイムで受信し、
 * スタイリッシュなダークモードの画面に表示します。
 *
 * 単に表示するだけでなく、長時間の運用を想定した省電力機能や、ユーザーが直感的に操作できる
 * インターフェースを備えているのが大きな特徴です。
 *
 *
 * ## 2. 主な機能 (Core Features)
 * -------------------------------------------------------------------------------------------------
 * - **リアルタイムデータ監視 (Real-time Data Monitoring):**
 * 軽量なメッセージングプロトコルである「MQTT」を利用して、指定された "トピック" (チャンネルの
 * ようなもの) を購読します。これにより、センサーデバイスから送られてくる環境データを
 * リアルタイムに取得し続けます。
 *
 * - **洗練されたUIデザイン (Rich User Interface):**
 * 目に優しいダークモードを基調とし、各データをカード形式で見やすく表示します。
 * 本体下部の3つの物理ボタン（A, B, C）を押すことで、各データの詳細画面に切り替えることができ、
 * より詳しい情報を確認できます。
 *
 * - **高度な省電力機能 (Advanced Power Saving):**
 * ユーザーが設定した時間（デフォルトでは5分）にわたって何も操作がない場合、
 * ディスプレイのバックライトを完全にオフにし、消費電力を大幅に削減します。
 * しかし、この間もM5Stackの "脳" にあたるCPUや通信機能は動作し続けているため、
 * 見えないところでは常に最新のデータを取得しています。
 *
 * - **常時接続と即時復帰 (Persistent Connectivity & Instant Wake-up):**
 * 省電力モード中もWi-FiとMQTTブローカーへの接続は維持されます。そのため、いずれかのボタンを
 * 押すと、スリープから即座に復帰し、待機時間なしで「バックグラウンドで受信していた最新のデータ」
 * を瞬時に画面に表示します。
 *
 * - **安全で簡単な設定 (Safe and Easy Configuration):**
 * Wi-FiのパスワードやMQTTサーバーのIPアドレスといった個人情報は、メインのプログラムから
 * 分離された `config.h` という専用のファイルで管理します。これにより、このプログラム本体を
 * GitHubなどで安全に共有したり、複数の環境で設定を簡単に切り替えたりすることが可能です。
 *
 *
 * ## 3. プログラムの動作の流れ (How it Works)
 * -------------------------------------------------------------------------------------------------
 * このプログラムは、大きく分けて `setup()` と `loop()` の2つの部分で構成されています。
 *
 * - **`setup()` 関数 (起動時の初期化処理):**
 * 1. M5Stackの電源が入ると、まずこの `setup()` 関数が一度だけ実行されます。
 * 2. M5Stackの各種ハードウェア（ディスプレイ、ボタン、電源管理機能など）を初期化します。
 * 3. 起動アニメーション（スプラッシュスクリーン）を表示します。
 * 4. `config.h` の情報を使ってWi-Fiに接続します。
 * 5. MQTTブローカーに接続するための準備を整えます。
 * 6. 最後に、メインとなるダッシュボード画面を初めて表示します。
 *
 * - **`loop()` 関数 (繰り返し実行されるメイン処理):**
 * 1. `setup()` が終わると、次はこの `loop()` 関数が電源が切れるまで無限に繰り返されます。
 * 2. 毎回、M5Stackのボタンが押されたかどうかをチェックします (M5.update())。
 * 3. MQTTブローカーとの接続が万が一切れていたら、再接続を試みます。
 * 4. 新しいMQTTメッセージが届いていないか確認し、あれば受信処理を行います (mqttClient.loop())。
 * 5. 省電力タイマーを監視し、時間が来たらディスプレイをオフにします。
 * 6. 画面がオンの時は、ボタンが押されたかを判断し、対応する詳細画面を表示します。
 * 7. 画面がオフの時は、ボタンが押されたかを判断し、画面を復帰させます。
 *
 *
 * ## 4. 使い方 (How to Use)
 * -------------------------------------------------------------------------------------------------
 * 1. **ライブラリの準備:**
 * Arduino IDEのライブラリマネージャで、以下のライブラリをインストールしてください。
 * - `M5Unified`
 * - `PubSubClient`
 * - `ArduinoJson`
 *
 * 2. **設定ファイルの作成:**
 * このスケッチファイル (`.ino`) と同じ階層に `config.h` という名前でファイルを作成します。
 * `config.example.h` の内容をコピーし、あなた自身のWi-FiとMQTTの情報を書き込んでください。
 *
 * 3. **.gitignoreの設定 (GitHubで共有する場合):**
 * プロジェクトの `.gitignore` ファイルに `config.h` を一行追加してください。
 * これにより、個人情報を含むファイルが誤って公開されるのを防ぎます。
 *
 * 4. **書き込み:**
 * Arduino IDEでM5Stackのボード設定を選び、このスケッチを書き込みます。
 *
 *
 * ## 5. カスタマイズのヒント (Customization)
 * -------------------------------------------------------------------------------------------------
 * - **監視するトピックの変更:** `config.h` の `MQTT_TOPIC` を変更します。
 * - **省電力タイマーの変更:** `DISPLAY_OFF_TIMEOUT` の値を変更します (ミリ秒単位)。
 * - **デザインの変更:** `カラーパレット定義` セクションの色コードを変更したり、`drawMetricCard` などの
 * 描画関数の内部を修正したりすることでお好みのデザインに変更できます。
 *
 * =================================================================================================
 */

// M5Unifiedライブラリが内部で利用するPNG画像表示機能は、今回のスケッチでは不要なため無効化します。
// これにより、コンパイルエラーを防ぎ、プログラムのサイズを少し小さくできます。
#define NO_PNG

// --- ライブラリの読み込み ---
#include <M5Unified.h>     // M5Stackのハードウェアを簡単に扱うための統合ライブラリ
#include <WiFi.h>          // WiFi機能を利用するためのライブラリ
#include <PubSubClient.h>  // MQTT通信を行うためのライブラリ
#include <ArduinoJson.h>   // MQTTで受信したJSON形式のデータを解析するためのライブラリ
#include "config.h"        // Wi-FiやMQTTの接続情報を記述した設定ファイルを読み込む

// =============================================================================
// デザインに関する設定 (色やレイアウト)
// =============================================================================
// 見た目を定義するセクションです。ダークモードを基調とした色の設定や、
// 画面部品のサイズなどをここで決めています。

// --- カラーパレット定義 (16bit RGB565形式) ---
// 色を名前で管理することで、後からデザイン変更がしやすくなります。
#define COLOR_HEADER_DARK 0x18C3       // ヘッダーの色 (深いチャコールグレー)
#define COLOR_SUCCESS_GREEN 0x2E44     // 成功・良好状態の色 (深い緑)
#define COLOR_WARNING_AMBER 0xAA60     // 警告状態の色 (琥珀色)
#define COLOR_DANGER_CRIMSON 0x9000    // 危険状態の色 (真紅)
#define COLOR_ACCENT_TEAL 0x4E79       // アクセントカラー (青緑)
#define COLOR_BACKGROUND_DARK 0x0841   // 背景色 (非常に暗いグレー)
#define COLOR_SURFACE_DARK 0x1082      // カードなどの部品の背景色
#define COLOR_SURFACE_ELEVATED 0x18C3  // 立体感を出すための少し明るいグレー
#define COLOR_TEXT_PRIMARY 0xFFFF      // メインの文字色 (白)
#define COLOR_TEXT_SECONDARY 0xBDF7    // サブの文字色 (明るいグレー)
#define COLOR_TEXT_TERTIARY 0x8410     // さらに補助的な文字色 (ミドルグレー)
#define COLOR_BORDER_SUBTLE 0x2945     // 境界線の色 (控えめなグレー)

// --- 画面レイアウト定数 ---
// 画面部品のサイズをピクセル単位で指定します。
const int HEADER_HEIGHT = 50;      // 画面上部のヘッダーの高さ
const int CARD_WIDTH = 80;         // 各データ表示カードの幅
const int CARD_HEIGHT = 100;       // 各データ表示カードの高さ
const int BOTTOM_NAV_HEIGHT = 40;  // 画面下部のボタンガイドの高さ
const int SCREEN_WIDTH = 320;      // M5Stackの画面幅
const int SCREEN_HEIGHT = 240;     // M5Stackの画面高さ

// --- データ表示に関する設定値 ---
const int CO2_EXCELLENT_THRESHOLD = 400;  // CO2濃度の「優秀」レベルの上限値
const int CO2_GOOD_THRESHOLD = 800;       // CO2濃度の「良好」レベルの上限値
const int CO2_FAIR_THRESHOLD = 1200;      // CO2濃度の「普通」レベルの上限値
const int AUTO_RETURN_DELAY = 3000;       // 詳細画面からメイン画面へ自動で戻るまでの時間 (ミリ秒)

// --- 省電力機能に関する設定値 ---
const unsigned long DISPLAY_OFF_TIMEOUT = 300000;  // 何も操作がない場合にディスプレイをオフにするまでの時間 (ミリ秒, 300000 = 5分)
const int ACTIVE_BRIGHTNESS = 200;                 // 通常時の画面の明るさ (0〜255)

// =============================================================================
// グローバル変数 (プログラム全体で共有して使う情報)
// =============================================================================
// ここで定義された変数は、プログラムのどこからでもアクセスできます。
// M5Stackの状態や受信したデータなどを保存するために使います。

// --- 通信関連のオブジェクト ---
WiFiClient wifiClient;                // WiFi通信の基盤となるオブジェクト
PubSubClient mqttClient(wifiClient);  // WiFi通信を利用してMQTT通信を行うためのオブジェクト

// --- 受信データ保存用の変数 ---
String lastUpdateTime = "";      // 最後にデータを受信した時刻を文字列で保存
int currentCO2Value = 0;         // 最新のCO2濃度を整数で保存
float currentTemperature = 0.0;  // 最新の温度を小数で保存
float currentHumidity = 0.0;     // 最新の湿度を小数で保存
bool hasReceivedData = false;    // 一度でもデータを受信したかどうかを記録 (true/false)

// --- 画面表示モード管理 ---
// 現在どの画面を表示しているかを管理するための仕組み
enum DisplayMode {
  MODE_MAIN_DASHBOARD,      // 0: メインのダッシュボード画面
  MODE_CO2_DETAIL,          // 1: CO2詳細画面
  MODE_TEMPERATURE_DETAIL,  // 2: 温度詳細画面
  MODE_HUMIDITY_DETAIL      // 3: 湿度詳細画面
};
DisplayMode currentDisplayMode = MODE_MAIN_DASHBOARD;  // プログラム開始時はメイン画面から

// --- 省電力機能関連の変数 ---
unsigned long lastButtonPressTime = 0;  // 最後にボタンが押された時刻を記録
bool isDisplayOff = false;              // ディスプレイがオフかどうかを記録 (true/false)

// --- 自動再起動のための変数 ---
unsigned long reboot_timer = 0;

// =============================================================================
// 関数プロトタイプ宣言
// =============================================================================
// Arduinoでは、setup()やloop()より後で定義された関数を呼び出す際に、
// 「その関数はまだ定義されていません」というエラーが出ることがあります。
// それを防ぐために、あらかじめ「これからこういう名前の関数を使います」と宣言しておきます。
void showApplicationSplashScreen();
void connectToWiFiNetwork();
void initializeMQTTConnection();
void onMqttMessageReceived(char* topic, byte* payload, unsigned int length);
void reconnectToMQTTBroker();
void displayMainDashboardScreen();
uint16_t getCO2StatusColor();
void drawApplicationHeader();
void displayDataWaitingScreen();
void displayLastUpdateTime();
void drawMetricCard(int x, int y, String label, String value, String unit, uint16_t accentColor);
void drawBottomNavigationBar();
void displayConnectionScreen(String connectionType);
void displayDetailScreen(String title, String value, String unit, uint16_t accentColor);
void displayCO2EnvironmentStatus();
void updateLastButtonPressTime();

// =============================================================================
// setup()関数 : 電源投入時に一度だけ実行される初期化処理
// =============================================================================
void setup() {
  // M5Stackのハードウェア（画面、ボタン、電源など）を初期化します。
  // M5Unifiedライブラリの推奨する、設定を自動で読み込む方法です。
  auto cfg = M5.config();
  M5.begin(cfg);

  // 画面の明るさを通常時の明るさに設定します。
  M5.Display.setBrightness(ACTIVE_BRIGHTNESS);
  // 画面全体を指定した背景色で塗りつぶします。
  M5.Display.fillScreen(COLOR_BACKGROUND_DARK);

  // --- 起動処理を順番に実行 ---
  showApplicationSplashScreen();  // 起動ロゴ画面を表示
  connectToWiFiNetwork();         // WiFiに接続
  initializeMQTTConnection();     // MQTTブローカーに接続する準備

  // 少し待機
  delay(1000);
  // メインのダッシュボード画面を初回表示（この時点では "Waiting for data..." と表示されます）
  displayMainDashboardScreen();

  // 省電力タイマーを現在の時刻で初期化します。
  lastButtonPressTime = millis();
  // 自動再起動タイマーも現在の時刻で初期化します。
  reboot_timer = millis();
}

// =============================================================================
// loop()関数 : プログラムの本体。setup()完了後、繰り返し実行される
// =============================================================================
void loop() {
  // M5Stackの状態（特にボタンの押下状態）を毎回更新します。
  M5.update();

  // --- MQTT接続の維持 ---
  // MQTTブローカーとの接続が切れていないか確認します。
  if (!mqttClient.connected()) {
    // 接続が切れていた場合
    if (isDisplayOff) {
      // もし画面がオフなら、強制的にオンにします。
      isDisplayOff = false;
      M5.Display.wakeup();
      M5.Display.setBrightness(ACTIVE_BRIGHTNESS);
      updateLastButtonPressTime();
    }
    // 再接続処理を呼び出します。
    reconnectToMQTTBroker();
  }
  // MQTTメッセージの受信待ちや、接続を維持するための処理です。常に実行する必要があります。
  mqttClient.loop();

  // --- 省電力（ディスプレイオフ）の管理 ---
  // 現在、画面がオンの場合のみチェックします。
  if (!isDisplayOff) {
    // 最後のボタン操作から指定した時間(DISPLAY_OFF_TIMEOUT)が経過したかチェックします。
    // millis()は起動してからの経過時間をミリ秒で返します。
    if (millis() - lastButtonPressTime >= DISPLAY_OFF_TIMEOUT) {
      // 指定時間が経過していたら、画面をオフにします。
      isDisplayOff = true;
      M5.Display.sleep();           // ディスプレイコントローラをスリープモードに
      M5.Display.setBrightness(0);  // バックライトを完全に消灯
    }
  }

  // --- ボタン入力の処理 ---
  // 画面がオンの場合のみ、ボタン操作を受け付けます。
  if (!isDisplayOff) {
    bool buttonPressed = false;  // いずれかのボタンが押されたかを記録するフラグ

    // 左のAボタンが押された場合
    if (M5.BtnA.wasPressed()) {
      currentDisplayMode = MODE_CO2_DETAIL;  // 表示モードを「CO2詳細」に設定
      // CO2詳細画面を表示する関数を呼び出す
      displayDetailScreen("CO2", String(currentCO2Value), "ppm", getCO2StatusColor());
      buttonPressed = true;
    }
    // 中央のBボタンが押された場合
    if (M5.BtnB.wasPressed()) {
      currentDisplayMode = MODE_TEMPERATURE_DETAIL;  // 表示モードを「温度詳細」に設定
      displayDetailScreen("Temperature", String(currentTemperature, 1), "C", COLOR_SUCCESS_GREEN);
      buttonPressed = true;
    }
    // 右のCボタンが押された場合
    if (M5.BtnC.wasPressed()) {
      currentDisplayMode = MODE_HUMIDITY_DETAIL;  // 表示モードを「湿度詳細」に設定
      displayDetailScreen("Humidity", String(currentHumidity, 1), "%", COLOR_ACCENT_TEAL);
      buttonPressed = true;
    }

    // いずれかのボタンが押されていたら、省電力タイマーをリセットします。
    if (buttonPressed) {
      updateLastButtonPressTime();
    }
  }
  // 画面がオフの場合
  else {
    // いずれかのボタンが押されたら、画面を復帰させます。
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
      isDisplayOff = false;                         // 画面オン状態にする
      M5.Display.wakeup();                          // ディスプレイコントローラを復帰
      M5.Display.setBrightness(ACTIVE_BRIGHTNESS);  // 画面を明るくする
      updateLastButtonPressTime();                  // 省電力タイマーをリセット
      displayMainDashboardScreen();                 // 最新のデータでメイン画面を再描画
    }
  }

  // 24時間 (86,400,000ミリ秒) ごとに再起動
  if (millis() - reboot_timer > 86400000UL) {
    ESP.restart();
  }

  // CPUに少し休憩時間を与え、プログラムを安定させるための短い待機時間です。
  delay(50);
}

// =============================================================================
// 初期化関数群
// =============================================================================

/**
 * @brief MQTTブローカーへの接続設定を初期化します。
 */
void initializeMQTTConnection() {
  // 接続先のサーバーIPとポート番号を設定します。
  mqttClient.setServer(MQTT_SERVER_IP, MQTT_PORT);
  // MQTTメッセージを受信したときに呼び出される関数（コールバック関数）を指定します。
  mqttClient.setCallback(onMqttMessageReceived);
}

/**
 * @brief アプリケーション起動時にスプラッシュ（ロゴ）画面を表示します。
 */
void showApplicationSplashScreen() {
  M5.Display.fillScreen(COLOR_SURFACE_DARK);
  M5.Display.fillRect(0, 0, SCREEN_WIDTH, 80, COLOR_HEADER_DARK);
  M5.Display.setTextColor(COLOR_TEXT_PRIMARY);
  M5.Display.setTextSize(3);
  M5.Display.setCursor(60, 25);
  M5.Display.println("AirSense");
  M5.Display.setTextSize(1);
  M5.Display.setCursor(110, 55);
  M5.Display.println("Environmental Monitor");
  M5.Display.setTextColor(COLOR_ACCENT_TEAL);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(80, 120);
  M5.Display.println("Low Power");
  M5.Display.setTextColor(COLOR_TEXT_SECONDARY);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(130, 150);
  M5.Display.println("v3.0");
  delay(2000);  // 2秒間表示
}

/**
 * @brief WiFiネットワークへの接続を行います。
 */
void connectToWiFiNetwork() {
  M5.Display.fillScreen(COLOR_BACKGROUND_DARK);
  M5.Display.setTextColor(COLOR_TEXT_PRIMARY);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(80, 80);
  M5.Display.println("Connecting");
  M5.Display.setCursor(100, 110);
  M5.Display.println("WiFi...");
  M5.Display.setTextColor(COLOR_ACCENT_TEAL);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(150, 140);

  // config.hで設定したSSIDとパスワードを使ってWiFi接続を開始します。
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // 接続が完了するまで待ちます。
  int dotCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);             // 0.5秒待つ
    M5.Display.print(".");  // 接続中であることを示すドットを表示
    dotCount++;
    // ドットが増えすぎたらクリアする
    if (dotCount > 10) {
      M5.Display.fillRect(150, 140, 60, 10, COLOR_BACKGROUND_DARK);
      M5.Display.setCursor(150, 140);
      dotCount = 0;
    }
  }
}

// =============================================================================
// MQTT通信関連の関数
// =============================================================================

/**
 * @brief MQTTメッセージを受信した時に自動的に呼び出される関数です。
 * @param topic メッセージがどのトピックから来たか
 * @param payload メッセージの本体データ
 * @param length メッセージの長さ
 */
void onMqttMessageReceived(char* topic, byte* payload, unsigned int length) {
  // 受信したデータをString（文字列）型に変換します。
  String receivedMessage = "";
  for (int i = 0; i < length; i++) {
    receivedMessage += (char)payload[i];
  }

  // これが最初のデータ受信かどうかを判断するために、現在の状態を保存しておきます。
  bool isFirstData = !hasReceivedData;

  // JSONデータを解析するためのオブジェクトを用意します。
  DynamicJsonDocument jsonDocument(1024);
  // 文字列をJSONとして解析します。
  DeserializationError parseError = deserializeJson(jsonDocument, receivedMessage);

  // JSONの解析に成功した場合のみ、データを更新します。
  if (!parseError) {
    // JSONオブジェクトから各キーに対応する値を取り出し、グローバル変数に保存します。
    lastUpdateTime = jsonDocument["time"].as<String>();
    currentCO2Value = jsonDocument["co2"];
    currentTemperature = jsonDocument["temp"];
    currentHumidity = jsonDocument["hum"];
    hasReceivedData = true;  // データ受信フラグをtrueにします。

    // もしこれが最初のデータ受信で、かつ画面がオフでなければ、
    // 「Waiting for data...」画面からメインダッシュボードへ自動で切り替えます。
    if (isFirstData && !isDisplayOff) {
      displayMainDashboardScreen();
    }
  }
}

/**
 * @brief MQTTブローカーへの接続が切れた場合に再接続を試みます。
 */
void reconnectToMQTTBroker() {
  // 接続できるまで無限に繰り返します。
  while (!mqttClient.connected()) {
    displayConnectionScreen("MQTT");  // 「MQTT接続中...」画面を表示

    // 接続を試行します。
    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      // 接続に成功した場合
      mqttClient.subscribe(MQTT_TOPIC);  // 指定したトピックの購読を開始
      delay(1000);
      displayMainDashboardScreen();  // メイン画面に戻る
    } else {
      // 接続に失敗した場合
      delay(5000);  // 5秒待ってから再試行
    }
  }
}

// =============================================================================
// 画面表示関数群
// =============================================================================

/**
 * @brief メインのダッシュボード画面を描画します。
 */
void displayMainDashboardScreen() {
  M5.Display.fillScreen(COLOR_BACKGROUND_DARK);
  currentDisplayMode = MODE_MAIN_DASHBOARD;
  drawApplicationHeader();

  // まだ一度もデータを受信していない場合は、待機画面を表示して処理を終えます。
  if (!hasReceivedData) {
    displayDataWaitingScreen();
    return;
  }

  // データがある場合は、各部品を描画します。
  displayLastUpdateTime();
  drawMetricCard(20, 85, "CO2", String(currentCO2Value), "ppm", getCO2StatusColor());
  drawMetricCard(120, 85, "TEMP", String(currentTemperature, 1), "C", COLOR_SUCCESS_GREEN);
  drawMetricCard(220, 85, "HUMID", String(currentHumidity, 1), "%", COLOR_ACCENT_TEAL);
  drawBottomNavigationBar();
}

/**
 * @brief 画面上部のヘッダー部分を描画します。
 */
void drawApplicationHeader() {
  M5.Display.fillRect(0, 0, SCREEN_WIDTH, HEADER_HEIGHT, COLOR_HEADER_DARK);
  M5.Display.setTextColor(COLOR_TEXT_PRIMARY);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(20, 18);
  M5.Display.println("AirSense Dashboard");
}

/**
 * @brief 最終データ更新時刻を画面に表示します。
 */
void displayLastUpdateTime() {
  M5.Display.setTextColor(COLOR_TEXT_SECONDARY);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(20, 60);
  M5.Display.print("Last Update: ");
  M5.Display.println(lastUpdateTime);
}

/**
 * @brief CO2, 温度, 湿度の各データを表示するカードを描画します。
 */
void drawMetricCard(int x, int y, String label, String value, String unit, uint16_t accentColor) {
  M5.Display.fillRoundRect(x, y, CARD_WIDTH, CARD_HEIGHT, 8, COLOR_SURFACE_DARK);
  M5.Display.drawRoundRect(x, y, CARD_WIDTH, CARD_HEIGHT, 8, accentColor);
  M5.Display.drawRoundRect(x + 1, y + 1, CARD_WIDTH - 2, CARD_HEIGHT - 2, 7, COLOR_SURFACE_ELEVATED);
  M5.Display.setTextColor(COLOR_TEXT_SECONDARY);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(x + 10, y + 10);
  M5.Display.println(label);
  M5.Display.setTextColor(accentColor);
  // 値の文字数が多い場合はフォントサイズを小さく調整
  if (value.length() > 3) {
    M5.Display.setTextSize(2);
    M5.Display.setCursor(x + 10, y + 40);
  } else {
    M5.Display.setTextSize(3);
    M5.Display.setCursor(x + 10, y + 35);
  }
  M5.Display.println(value);
  M5.Display.setTextColor(COLOR_TEXT_TERTIARY);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(x + 10, y + 75);
  M5.Display.println(unit);
}

/**
 * @brief ボタンを押した後の詳細画面を描画します。
 */
void displayDetailScreen(String title, String value, String unit, uint16_t accentColor) {
  M5.Display.fillScreen(COLOR_BACKGROUND_DARK);
  M5.Display.setTextColor(accentColor);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(20, 20);
  M5.Display.println("< Dashboard");
  M5.Display.setTextColor(COLOR_TEXT_PRIMARY);
  M5.Display.setTextSize(3);
  M5.Display.setCursor(20, 50);
  M5.Display.println(title);
  M5.Display.setTextColor(accentColor);
  M5.Display.setTextSize(6);
  int valueWidth = value.length() * 36;
  M5.Display.setCursor((SCREEN_WIDTH - valueWidth) / 2, 100);
  M5.Display.println(value);
  M5.Display.setTextColor(COLOR_TEXT_SECONDARY);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(140, 160);
  M5.Display.println(unit);
  if (title == "CO2") {
    displayCO2EnvironmentStatus();
  }
  // 指定時間(AUTO_RETURN_DELAY)後に自動でメイン画面に戻ります。
  delay(AUTO_RETURN_DELAY);
  displayMainDashboardScreen();
}

/**
 * @brief CO2濃度のレベルに応じて「Excellent」などの状態を表示します。
 */
void displayCO2EnvironmentStatus() {
  String statusText;
  uint16_t statusColor;
  if (currentCO2Value < CO2_EXCELLENT_THRESHOLD) {
    statusText = "Excellent";
    statusColor = COLOR_SUCCESS_GREEN;
  } else if (currentCO2Value < CO2_GOOD_THRESHOLD) {
    statusText = "Good";
    statusColor = COLOR_SUCCESS_GREEN;
  } else if (currentCO2Value < CO2_FAIR_THRESHOLD) {
    statusText = "Fair";
    statusColor = COLOR_WARNING_AMBER;
  } else {
    statusText = "Poor";
    statusColor = COLOR_DANGER_CRIMSON;
  }
  M5.Display.setTextColor(statusColor);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(120, 190);
  M5.Display.println(statusText);
}

/**
 * @brief MQTTからの初回データ受信を待っている間の画面を描画します。
 */
void displayDataWaitingScreen() {
  M5.Display.setTextColor(COLOR_TEXT_SECONDARY);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(70, 120);
  M5.Display.println("Waiting for");
  M5.Display.setCursor(110, 150);
  M5.Display.println("data...");
  M5.Display.setTextColor(COLOR_ACCENT_TEAL);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(140, 170);
  M5.Display.println("●");
  drawBottomNavigationBar();
}

/**
 * @brief WiFiやMQTTへの接続中画面を描画します。
 */
void displayConnectionScreen(String connectionType) {
  M5.Display.fillScreen(COLOR_BACKGROUND_DARK);
  M5.Display.setTextColor(COLOR_TEXT_PRIMARY);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(60, 100);
  M5.Display.println("Connecting");
  M5.Display.setCursor(80, 130);
  M5.Display.print(connectionType);
  M5.Display.println("...");
  M5.Display.setTextColor(COLOR_ACCENT_TEAL);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(160, 160);
  M5.Display.println("●");
}

/**
 * @brief 画面下部のボタン機能ガイドを描画します。
 */
void drawBottomNavigationBar() {
  M5.Display.fillRect(0, SCREEN_HEIGHT - BOTTOM_NAV_HEIGHT, SCREEN_WIDTH, BOTTOM_NAV_HEIGHT, COLOR_SURFACE_DARK);
  M5.Display.drawFastHLine(0, SCREEN_HEIGHT - BOTTOM_NAV_HEIGHT, SCREEN_WIDTH, COLOR_BORDER_SUBTLE);
  M5.Display.setTextColor(COLOR_TEXT_SECONDARY);
  M5.Display.setTextSize(1);
  M5.Display.setCursor(35, 215);
  M5.Display.println("CO2");
  M5.Display.setCursor(140, 215);
  M5.Display.println("TEMP");
  M5.Display.setCursor(260, 215);
  M5.Display.println("HUMID");
  M5.Display.drawFastVLine(106, 205, 30, COLOR_BORDER_SUBTLE);
  M5.Display.drawFastVLine(213, 205, 30, COLOR_BORDER_SUBTLE);
}

// =============================================================================
// ユーティリティ関数 (補助的な役割の関数)
// =============================================================================

/**
 * @brief CO2濃度に応じて表示色を返します。
 * @return 状態に応じた色コード
 */
uint16_t getCO2StatusColor() {
  if (currentCO2Value < CO2_GOOD_THRESHOLD) {
    return COLOR_SUCCESS_GREEN;
  } else if (currentCO2Value < CO2_FAIR_THRESHOLD) {
    return COLOR_WARNING_AMBER;
  } else {
    return COLOR_DANGER_CRIMSON;
  }
}

/**
 * @brief 最終ボタン操作時刻を現在の時刻に更新します。
 */
void updateLastButtonPressTime() {
  lastButtonPressTime = millis();
}