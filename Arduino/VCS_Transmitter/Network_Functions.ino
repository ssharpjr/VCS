// Visual Counter
void tenCountDot() {
  int counter = 20;
  for (byte i = 0; i<counter; i++) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
}



// Print WiFi Data
void printWifiData() {
  // Print the WiFi shield's IP address.
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // Print WiFi shield's MAC Address.
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC Address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
  Serial.println();
}


// Print Current Network Information.
void printCurrentNet() {
  // Print the SSID of the network.
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // Print Router MAC Address.
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);
  
  // Print the received signal strength.
  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  // Print the encryption type.
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption, HEX);
  Serial.println();
}
