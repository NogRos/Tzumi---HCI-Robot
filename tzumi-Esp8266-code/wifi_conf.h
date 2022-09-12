// WiFi
//const char *ssid = "Tzumi"; // Enter your WiFi name
//const char *password = "12345678";  // Enter WiFi password
//const char *ssid = "vita43"; // Enter your WiFi name
//const char *password = "tiger1tiger2";  // Enter WiFi password
//const char *ssid = "AndroidAP5F5D"; // Enter your WiFi name
//const char *password = "ppau3000";  // Enter WiFi password
const char *ssid = "LAPTOP-AOJBCGV6 3699"; // Enter your WiFi name
const char *password = "12344321";  // Enter WiFi password


void connectToWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
