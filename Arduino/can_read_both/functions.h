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


bool isEven(int number) {
  return (number % 2) == 0;
}


bool check_all_numb_of_arr_same( int arr[]){
  const int size_arr = sizeof(arr) / sizeof(arr[0]); 

  if (size_arr <=1)
  {
    return true;
  }

  for (size_t i = 0; i < size_arr; i++)
  {
    if (arr[i] != arr[0])
    {
      return false;
    }
    
  }

  return true; //all elements of the array are the same
}

bool check_all_numb_of_arr_in_range( int arr[]){
  const int size_arr = sizeof(arr) / sizeof(arr[0]); 


  if (size_arr <=1)
  {
    return true;
  }

  for (size_t i = 0; i < size_arr; i++)
  {
    if ( arr[i] > (arr[0] + 10 ) ||  arr[i] < (arr[0] - 10 ) )
    {
      return false;
    }
    
  }
  
  return true; //all elements of the array are at least in the range of +/- 10 degres
}

bool arr_outof_range(int arr[], int range){
  const int size_arr = sizeof(arr) / sizeof(arr[0]); 

  for (size_t i = 0; i < size_arr; i++)
  {
    if (arr[i] > arr[0] +10 || arr[i] < arr[0] -10)
    {
      // out of range
      return true;
    }
    
  }
  
}

bool sign_func(bool num){
  // sign function, switches betwenn 0 and 1 
  if (num == true)
  {
    return false
  } else
  {
    return true
  }
  
}