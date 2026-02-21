#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);

//uint8_t use for save space
uint8_t pk_info[4] = {0, 0, 0, 0};//set of flags to illustrate occupy situation
String buffer = "";

void setup(){
  Serial.begin(9600);
  BT.begin(9600);

}

void loop(){
  while(BT.available()) {
    char c = BT.read();
    if(c == '\n'){
      buffer.trim();
      String header = getHeader(buffer);
      String payload = getPayload(buffer);

      //below is the block to handle messages
      if(header == "req"){
        send_pk_information();
      }
      else if(header == "ocp"){
        if(pk_info[payload.toInt()]!=1){
          pk_info[payload.toInt()-1]=1;
        }
      }


      buffer = "";

    }else{
      buffer += c;
    }
  }

  
}

void send_pk_information(){
  for(int i = 0;i<sizeof(pk_info);i++){
    if(pk_info[i]==0){
      BT.write((uint8_t)(i + 1));
      break;
      }
  }
  
}


String getHeader(String msg) {

  int pos = msg.indexOf(':'); 

  if (pos == -1) {
    return msg;   
  }

  return msg.substring(0, pos); 
}

String getPayload(String msg) {

  int pos = msg.indexOf(':');  

  if (pos == -1) {
    return "";   
  }

  return msg.substring(pos + 1); 
}
