#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <Arduino_JSON.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "pin_config.h"

// Wifi Config
const char* ssidList[] = {"SSID_1", "SSID_2", "SSID_3"};
const char* passwordList[] = {"SSID_Pwd_1", "SSID_Pwd_2", "SSID_Pwd_3"};
const int numNetworks = sizeof(ssidList) / sizeof(ssidList[0]);

// TFT Config
TFT_eSPI tft;

void connectToWiFi() {
    int attempt = 0;

    while (WiFi.status() != WL_CONNECTED && attempt < numNetworks) {
        Serial.printf("Attempting to connect to SSID: %s\n", ssidList[attempt]);
        WiFi.begin(ssidList[attempt], passwordList[attempt]);

        // Wait 10 sec 
        int attemptTimeout = 0;
        while (WiFi.status() != WL_CONNECTED && attemptTimeout < 10) {
            delay(1000);
            Serial.print(".");
            attemptTimeout++;
        }
        Serial.println();

        // Verifica o resultado da conexão
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to WiFi");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
        } else {
            Serial.printf("Failed to connect to SSID: %s\n", ssidList[attempt]);
        }

        attempt++;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to connect to any WiFi network");
    }
}

// Crypto API Addr
const char* apiUrlBase = "https://api.gateio.ws/api/v4/spot/tickers?currency_pair=";

// Variables for currency pairs
String token1 = "BTC_USDT";
String token2 = "ETH_USDT";
String token3 = "LINK_USDT";
String token4 = "DOG_USDT";  
String token5 = "MATIC_USDT";  
String token6 = "SOL_USDT";   
String token7 = "RNDR_USDT";   
String token8 = "SEI_USDT";   
String token9 = "ONDO_USDT"; 
String token10 = "INJ_USDT"; 
String token11 = "PENDLE_USDT";
String token12 = "FTM_USDT";
String token13 = "RON_USDT";
String token14 = "MKR_USDT";
String token15 = "NEAR_USDT";

// Complete URLs for cryptocurrency APIs
String apiUrlToken1 = apiUrlBase + token1;
String apiUrlToken2 = apiUrlBase + token2;
String apiUrlToken3 = apiUrlBase + token3;
String apiUrlToken4 = apiUrlBase + token4;
String apiUrlToken5 = apiUrlBase + token5;
String apiUrlToken6 = apiUrlBase + token6;
String apiUrlToken7 = apiUrlBase + token7;
String apiUrlToken8 = apiUrlBase + token8;
String apiUrlToken9 = apiUrlBase + token9;
String apiUrlToken10 = apiUrlBase + token10;
String apiUrlToken11 = apiUrlBase + token11;
String apiUrlToken12 = apiUrlBase + token12;
String apiUrlToken13 = apiUrlBase + token13;
String apiUrlToken14 = apiUrlBase + token14;
String apiUrlToken15 = apiUrlBase + token15;

// NTP Settings
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -4 * 3600); // Configurado para GMT-4

AsyncWebServer server(80);  // Port 80 - HTTP

struct CoinData {
    String name;
    String* currencyPair;
};

// Structure to store coin data
CoinData coins[] = {
    {"", &token1},
    {"", &token2},
    {"", &token3},
    {"", &token4},
    {"", &token5},
    {"", &token6},
    {"", &token7},
    {"", &token8},
    {"", &token9},
    {"", &token10},
    {"", &token11},
    {"", &token12},
    {"", &token13},
    {"", &token14},
    {"", &token15},
};

bool showFirstScreen = true;   // Control variable to switch between screens
bool showSecondScreen = false; // Control variable for the second screen


void setup() {
    Serial.begin(115200);

    // Initialize TFT screen
    tft.init();
    tft.setRotation(3); // Rotate 180 degrees


    connectToWiFi(); // Call function to connect to WiFi

    // Display IP address on serial monitor
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Initialize NTP client
    timeClient.begin();
    timeClient.update();

// Initialize web server
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String content = "<html><head><style>";
    content += "@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap');";
    content += "body { font-family: 'Roboto', sans-serif; background-color: #000; color: #fff; margin: 0; padding: 20px; }";
    content += ".container { display: flex; justify-content: center; align-items: flex-start; }";
    content += ".column { flex: 1; max-width: 300px; margin: 10px; }";
    content += ".form-wrapper { background-color: #222; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.5); padding: 20px; }";
    content += "h1, h2 { text-align: center; margin-bottom: 20px; }";
    content += "label { display: block; margin-bottom: 5px; }";
    content += "input[type='text'] { width: calc(100% - 12px); padding: 10px; margin-bottom: 10px; background-color: #333; color: #fff; border: 1px solid #555; border-radius: 5px; }";
    content += "input[type='submit'] { width: 100%; padding: 10px; background-color: #007bff; color: #fff; border: none; cursor: pointer; border-radius: 5px; }";
    content += "input[type='submit']:hover { background-color: #0056b3; }";
    content += "</style></head><body>";
    content += "<h1>Monitor Crypto</h1>";
    content += "<div class='container'>";
    
    // Column 1: Coins 1 to 5
    content += "<div class='column'>";
    content += "<div class='form-wrapper'>";
    content += "<h2>Screen 1</h2>";
    content += "<form action='/set-coins' method='get' onsubmit='return confirm(\"Deseja realmente alterar os tokens?\");'>";
    content += "<label>Token 1:</label> <input type='text' name='token1' value='" + token1.substring(0, token1.length() - 5) + "'><br>";
    content += "<label>Token 2:</label> <input type='text' name='token2' value='" + token2.substring(0, token2.length() - 5) + "'><br>";
    content += "<label>Token 3:</label> <input type='text' name='token3' value='" + token3.substring(0, token3.length() - 5) + "'><br>";
    content += "<label>Token 4:</label> <input type='text' name='token4' value='" + token4.substring(0, token4.length() - 5) + "'><br>";
    content += "<label>Token 5:</label> <input type='text' name='token5' value='" + token5.substring(0, token5.length() - 5) + "'><br>";
    content += "<input type='submit' value='Save'>";
    content += "</form>";
    content += "</div>"; 
    content += "</div>"; 
    
    // Column 2: Coins 6 to 10
    content += "<div class='column'>";
    content += "<div class='form-wrapper'>";
    content += "<h2>Tela 2</h2>";
    content += "<form action='/set-coins' method='get' onsubmit='return confirm(\"Deseja realmente alterar os tokens?\");'>";
    content += "<label>Token 6:</label> <input type='text' name='token6' value='" + token6.substring(0, token6.length() - 5) + "'><br>";
    content += "<label>Token 7:</label> <input type='text' name='token7' value='" + token7.substring(0, token7.length() - 5) + "'><br>";
    content += "<label>Token 8:</label> <input type='text' name='token8' value='" + token8.substring(0, token8.length() - 5) + "'><br>";
    content += "<label>Token 9:</label> <input type='text' name='token9' value='" + token9.substring(0, token9.length() - 5) + "'><br>";
    content += "<label>Token 10:</label> <input type='text' name='token10' value='" + token10.substring(0, token10.length() - 5) + "'><br>";
    content += "<input type='submit' value='Save'>";
    content += "</form>";
    content += "</div>"; 
    content += "</div>";
    
    /// Column 2: Coins 11 to 15
    content += "<div class='column'>";
    content += "<div class='form-wrapper'>";
    content += "<h2>Tela 3</h2>";
    content += "<form action='/set-coins' method='get' onsubmit='return confirm(\"Deseja realmente alterar os tokens?\");'>";
    content += "<label>Token 11:</label> <input type='text' name='token11' value='" + token11.substring(0, token11.length() - 5) + "'><br>";
    content += "<label>Token 12:</label> <input type='text' name='token12' value='" + token12.substring(0, token12.length() - 5) + "'><br>";
    content += "<label>Token 13:</label> <input type='text' name='token13' value='" + token13.substring(0, token13.length() - 5) + "'><br>";
    content += "<label>Token 14:</label> <input type='text' name='token14' value='" + token14.substring(0, token14.length() - 5) + "'><br>";
    content += "<label>Token 15:</label> <input type='text' name='token15' value='" + token15.substring(0, token15.length() - 5) + "'><br>";
    content += "<input type='submit' value='Save'>";
    content += "</form>";
    content += "</div>"; 
    content += "</div>"; 
    
    content += "</div>";
    content += "</body></html>";
    request->send(200, "text/html", content);
});

server.on("/set-coins", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasArg("token1") && request->arg("token1") != "") token1 = request->arg("token1") + "_USDT";
    if (request->hasArg("token2") && request->arg("token2") != "") token2 = request->arg("token2") + "_USDT";
    if (request->hasArg("token3") && request->arg("token3") != "") token3 = request->arg("token3") + "_USDT";
    if (request->hasArg("token4") && request->arg("token4") != "") token4 = request->arg("token4") + "_USDT";
    if (request->hasArg("token5") && request->arg("token5") != "") token5 = request->arg("token5") + "_USDT";
    if (request->hasArg("token6") && request->arg("token6") != "") token6 = request->arg("token6") + "_USDT";
    if (request->hasArg("token7") && request->arg("token7") != "") token7 = request->arg("token7") + "_USDT";
    if (request->hasArg("token8") && request->arg("token8") != "") token8 = request->arg("token8") + "_USDT";
    if (request->hasArg("token9") && request->arg("token9") != "") token9 = request->arg("token9") + "_USDT";
    if (request->hasArg("token10") && request->arg("token10") != "") token10 = request->arg("token10") + "_USDT";
    if (request->hasArg("token11") && request->arg("token11") != "") token11 = request->arg("token11") + "_USDT";
    if (request->hasArg("token12") && request->arg("token12") != "") token12 = request->arg("token12") + "_USDT";
    if (request->hasArg("token13") && request->arg("token13") != "") token13 = request->arg("token13") + "_USDT";
    if (request->hasArg("token14") && request->arg("token14") != "") token14 = request->arg("token14") + "_USDT";
    if (request->hasArg("token15") && request->arg("token15") != "") token15 = request->arg("token15") + "_USDT";

    // Update Addr
    apiUrlToken1 = apiUrlBase + token1;
    apiUrlToken2 = apiUrlBase + token2;
    apiUrlToken3 = apiUrlBase + token3;
    apiUrlToken4 = apiUrlBase + token4;
    apiUrlToken5 = apiUrlBase + token5;
    apiUrlToken6 = apiUrlBase + token6;
    apiUrlToken7 = apiUrlBase + token7;
    apiUrlToken8 = apiUrlBase + token8;
    apiUrlToken9 = apiUrlBase + token9;
    apiUrlToken10 = apiUrlBase + token10;
    apiUrlToken11 = apiUrlBase + token11;
    apiUrlToken12 = apiUrlBase + token12;
    apiUrlToken13 = apiUrlBase + token13;
    apiUrlToken14 = apiUrlBase + token14;
    apiUrlToken15 = apiUrlBase + token15;

    // 
    request->redirect("/");
});


    // Show SplashScreen
    displaySplashScreen();

    // Start webserver
    server.begin();

    // Clean the screen
    tft.fillScreen(TFT_BLACK);

    // Show title
    int titleWidth = tft.textWidth("CRYPTOS");
    int centerX = tft.width() / 2;
    int centerY = 20; // Adjust pos
    tft.setCursor(centerX - titleWidth / 2, centerY);
    tft.setTextColor(TFT_BLUE);
    tft.setTextSize(3);
    tft.setTextDatum(MC_DATUM);  // adjust pos
    tft.drawString("CRYPTOS", centerX, centerY);


}

void loop() {
    if (showFirstScreen) {
        // Show first screen
        for (int i = 0; i < 5; ++i) {
            displayCryptoData(*coins[i].currencyPair, 43 + (i * 28));
            delay(10); // Wait 10ms to update coins
        }
    } else if (showSecondScreen) {
        // show second screen
        for (int i = 5; i < 10; ++i) {
            displayCryptoData(*coins[i].currencyPair, 43 + ((i - 5) * 28));
            delay(10); // Wait 10ms to update coins
        }
    } else {
        // Show third screen
        for (int i = 10; i < 15; ++i) {
            displayCryptoData(*coins[i].currencyPair, 43 + ((i - 10) * 28));
            delay(10); // Wait 10ms to update coins
        }
    }

    // Show Date and time
    displayCurrentTime();

    // Change screen 
    delay(5000);
    if (showFirstScreen) {
        showFirstScreen = false;
        showSecondScreen = true;
    } else if (showSecondScreen) {
        showSecondScreen = false;
    } else {
        showFirstScreen = true;
    }
}

void displayCryptoData(const String& currencyPair, int yPos) {
    // Clean the screen
    tft.fillRect(0, yPos, tft.width(), 25, TFT_BLACK);

    // URL Construction
    String apiUrl = apiUrlBase + currencyPair;

    // API request
    JSONVar data = getJsonData(apiUrl.c_str());

    // Data verification
    if (JSON.typeof(data) == "undefined") {
        // Caso não consiga obter os dados da API
        tft.setCursor(10, yPos + 10);
        tft.setTextColor(TFT_RED);
        tft.setTextSize(2);
        tft.println("Erro ao obter dados");
        return;
    }

    // Crypto price
    float price = atof(data[0]["last"]);
    // 24 hours token variation
    float change = atof(data[0]["change_percentage"]);

    // Coin and price
    tft.setCursor(10, yPos);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.print(currencyPair.substring(0, currencyPair.length() - 5) + " ");
    tft.setCursor(80, yPos);
    tft.setTextSize(2);
    tft.setTextColor(TFT_ORANGE);
    tft.print("$");
    tft.setTextColor(TFT_LIGHTGREY);
    if (currencyPair == token4) {
        tft.print(price, 6); // 6 decimals to token 4
    } else {
        tft.print(price, 4); // 4 decimals to other coins
    }
    tft.print(" (");
    if (change >= 0) {
        tft.setTextColor(TFT_GREEN);
        tft.print("+");
    } else {
        tft.setTextColor(TFT_RED);
    }
    tft.print(change, 2); // 2 decimals
    tft.print("%");
    tft.setTextColor(TFT_LIGHTGREY); 
    tft.print(")");
}

// HTTP - JSON
JSONVar getJsonData(const char* url) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        JSONVar data = JSON.parse(payload);
        http.end();
        return data;
    } else {
        Serial.printf("HTTP Failure: %d\n", httpCode);
        http.end();
        return JSONVar(); // Empty JSON if failure
    }
}

// Date/Hour function
void displayCurrentTime() {
    int yPos = 12; // position

    // Real time
    unsigned long epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);

    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon + 1;
    int currentYear = ptm->tm_year + 1900;
    int currentHour = ptm->tm_hour;
    int currentMinute = ptm->tm_min;

    // date format
    char dateString[10];
    sprintf(dateString, "%02d/%02d", monthDay, currentMonth);

    // Hour format
    char timeString[10];
    sprintf(timeString, "%02d:%02d", currentHour, currentMinute);

    // clean the area
    tft.fillRect(tft.width() / 2 - 155, yPos -2, 75, 20, TFT_BLACK);

    // clean the area
    tft.fillRect(tft.width() / 2 + 80, yPos -2, 80, 20, TFT_BLACK);

    // show date
    tft.setTextColor(TFT_ORANGE);
    tft.setTextSize(2);
    tft.setTextDatum(TC_DATUM); // position
    tft.drawString(dateString, tft.width() / 2 - 120, yPos);

    // show hour
    tft.setTextColor(TFT_YELLOW);
    tft.setTextSize(2);
    tft.setTextDatum(TC_DATUM); // position
    tft.drawString(timeString, tft.width() / 2 + 120, yPos);
}

// splash screen function
void displaySplashScreen() {
    tft.fillScreen(TFT_BLACK);

    // Coded by...
    tft.setTextColor(TFT_LIGHTGREY);
    tft.setTextSize(3);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Coded by", tft.width() / 2, tft.height() / 2 - 40);
    tft.drawString("@guilhermegiorgi", tft.width() / 2, tft.height() / 2 - 10);

    // Show IP addr 
    tft.setTextColor(TFT_GREEN);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("IP: " + WiFi.localIP().toString(), tft.width() / 2, tft.height() / 2 + 50);

    // wait 5 secs
    delay(5000);
}

