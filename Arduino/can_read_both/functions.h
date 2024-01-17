int binaryToSignedInt(uint16_t binaryValue) {
  if (binaryValue & 0x8000) {  // Check the sign bit (most significant bit)
    // If sign bit is 1 (negative), convert using two's complement
    return -((~binaryValue + 1) & 0xFFFF);
  } else {
    // If sign bit is 0 (positive), return the positive value
    return binaryValue;
  }
}

float binaryBytesToInt(const String& highByteString, const String& lowByteString) {
  // Extrahiere die Werte aus den Strings
  int highByte = strtol(highByteString.substring(1).c_str(), NULL, 2);  // substr(1) überspringt das 'B'-Präfix
  int lowByte = strtol(lowByteString.substring(1).c_str(), NULL, 2);

  // Kombiniere die Bytes und interpretiere das MSB des Highbytes als Vorzeichen
  int result = (highByte & 0x80) ? -(0x100 - ((highByte << 8) | lowByte)) : ((highByte << 8) | lowByte);

  if (result < 0 ){
    result += 256; 
  }
    
    

  return result*0.1;
}

String intToBinaryString(int value) {
  const int bits = 8;
  String binaryString = "B";

  for (int i = bits - 1; i >= 0; i--) {
    binaryString += (value & (1 << i)) ? '1' : '0';
  }

  return binaryString;
}
void writeToMatlab (float number){
  byte *b = (byte *) &number;
  Serial.write(b, 4);
  Serial.write(13);  //CR   \r
  Serial.write(10);  //LF   \n
}