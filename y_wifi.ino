void setupNetwork()
{
  Serial.println("");
  Serial.print("WiFi start");

  wifi_init(gc_hostname);

  Serial.println("");
  Serial.println("WiFi connected");

}
