/*
This example takes range measurements with the VL53L1X and displays additional 
details (status and signal/ambient rates) for each measurement, which can help
you determine whether the sensor is operating normally and the reported range is
valid. The range is in units of mm, and the rates are in units of MCPS (mega 
counts per second).
*/
#include <M5Stack.h>
#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

void setup()
{
  M5.begin();


  // text print
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("Display Test!");

  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  
  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);
}

void loop()
{
  sensor.read();
  
//  Serial.print("range: ");
//  Serial.print(sensor.ranging_data.range_mm);
//  Serial.print("\tstatus: ");
//  Serial.print(VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));
//  Serial.print("\tpeak signal: ");
//  Serial.print(sensor.ranging_data.peak_signal_count_rate_MCPS);
//  Serial.print("\tambient: ");
//  Serial.print(sensor.ranging_data.ambient_count_rate_MCPS);
  
  Serial.println();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(90, 100);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(20);
  M5.Lcd.print(sensor.ranging_data.range_mm);
  M5.Lcd.setTextSize(5);
  M5.Lcd.print("mm");
  delay(500);

  M5.update();
}
