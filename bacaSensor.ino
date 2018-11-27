
void bacaSensor(){
    Wire.begin(0, 2);
//=================================================================
//SET MODE
//=================================================================
  unsigned int data[6];
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Set bandwidth rate register, lihat datasheet
  Wire.write(0x2C);
  // Set Normal mode, Output data rate = 100 Hz
  Wire.write(0x0A);
  // Stop I2C transmission
    Wire.endTransmission();
//=================================================================
//SET POWER CONTROL, SLEEP 
//=================================================================
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select power control register
  Wire.write(0x2D);
  // Auto-sleep disable
  Wire.write(0x08);
  // Stop I2C transmission
  Wire.endTransmission();

//=================================================================
//SET DATA FORMAT
//=================================================================
// Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data format register
  Wire.write(0x31);

//=================================================================
// SET NILAI G:  0x00 = 2G, 0x01 = 4G, 0x02 = 8G, 0x03 = 16G
//=================================================================  
  // Self test disabled, 4-wire interface, Full resolution, Range = +/-2g
  Wire.write(0x03);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(1000);
  for (int i = 0; i < 6; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write((50 + i));
    // Stop I2C transmission
    Wire.endTransmission();
    // Request 1 byte of data
    Wire.requestFrom(Addr, 1);
    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }
  // Convert the data to 10-bits
  int xAccl = (((data[1] & 0x03) * 256) + data[0]);
  if (xAccl > 511)
  {
    xAccl -= 1024;
  }
  int yAccl = (((data[3] & 0x03) * 256) + data[2]);
  if (yAccl > 511)
  {
    yAccl -= 1024;
  }
  int zAccl = (((data[5] & 0x03) * 256) + data[4]);
  if (zAccl > 511)
  {
    zAccl -= 1024;
  }
  // Output data to serial monitor
 
  Serial.print(xAccl); Serial.print("\t"); 
  Serial.print(yAccl); Serial.print("\t");
  Serial.println(zAccl);

String xData = String(xAccl);
String yData = String(yAccl);
String zData = String(zAccl);
  char charX[58];
   char charY[58];
    char charZ[58];
  xData.toCharArray(charX,58);
  yData.toCharArray(charY,58);
  zData.toCharArray(charZ,58);


   client.publish(dataX, charX);
   client.publish(dataY, charY);
   client.publish(dataZ, charZ);
   

    
}


