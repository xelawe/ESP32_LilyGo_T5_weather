void init_tick(){
//  MinTick.attach(60, tick_min); //abgelöst durch MQTT

}

void tick_min() {
  min_count++;

  if (min_count >= 60) {
    hour_tick = true;
    min_count = 0;
  }

  min_tick = true;

}
