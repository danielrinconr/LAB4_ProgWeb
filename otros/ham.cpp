// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License
//
// This example shows how to deserialize a JSON document with ArduinoJson.

#include <iostream>
#include "ArduinoJson.h"

int main() {
  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the capacity of the memory pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<300> doc;

  // StaticJsonDocument<N> allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument doc(200);

  // JSON input string.
  //
  // Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
  // the minimal amount of memory because the JsonDocument stores pointers to
  // the input buffer.
  // If you use another type of input, ArduinoJson must copy the strings from
  // the input to the JsonDocument, so you need to increase the capacity of the
  // JsonDocument.
  //char json[] =
    //  "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  //char json[] = "{\"left\":500,\"top\":700,\"iden\":1,\"maxbullets\":50,\"shoot\":1}";
  char json[] = "{\"Heros\":[{\"left\":500,\"top\":700,\"iden\":1,\"maxbullets\":50,\"shoot\":1}]}";
  char json[] = {"left":500,"top":700,"iden":1,"maxbullets":50,"shoot":1}
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    std::cerr << "deserializeJson() failed: " << error.c_str() << std::endl;
    return 1;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();
  auto h1 = doc["Heros"][0];
    // Deserialize the JSON document
  error = deserializeJson(doc, h1);

  // Test if parsing succeeds.
  if (error) {
    std::cerr << "deserializeJson() failed: " << error.c_str() << std::endl;
    return 1;
  }
  auto h1_l = doc["left"];
  // Print values.
  
  std::cout << h1 << std::endl;
  std::cout << h1_l << std::endl;

  return 0;
}
