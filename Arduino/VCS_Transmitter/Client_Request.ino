// Client Request
void clientRequest() {
  Serial.println("\nConnecting to server...");
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make HTTP request.
    Serial.println("Sending HTTP request");
    client.print("GET /vcs/input.php?press_id=");
    client.print(press_id);
    client.print("&status_id=");
    client.print(status_id);
    client.print("&startup_id=");
    client.print(startup_id);
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.10.106");
    client.println("Connection: close");
    client.println();
    Serial.println("Request sent");
  }
  else {
    // If you did not get a connection to the server.
    Serial.println("Connection Failed");
  }

  // If there are incoming bytes available
  // from the server, read and print them.
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  
  // If the server's disconnected, stop the client.
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server.");
    client.stop();
    Serial.println("Disconnected from server.");
  }
}


