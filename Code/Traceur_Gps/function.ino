void SendData(String trame){
  LoraSendCommand("AT+SEND=2:"+ trame +"\r\n");
}


void LoraConnection(){
  LoraSendCommand("AT+JOIN=1:0:10:8\r\n");
}

void LoraSetup(String APPKEY,String APPEUI,String DEVEUI){
  LoraSendCommand("AT+APPKEY="+ APPKEY + "\r\n");
  LoraSendCommand("AT+APPEUI="+ APPEUI+ "\r\n"); 
  LoraSendCommand("AT+DEVEUI="+ DEVEUI + "\r\n"); 
}

String LoraSendCommand(String atComm){
   String response = ""; 
   lora.print(atComm); 
    while(lora.available()){ 
     char ch = lora.read(); 
     response += ch; 
    } 
    return response;
}

void DataMesurement(){
  
  while(GPS.available()){
    if(gps.encode(GPS.read())){  
      gps.f_get_position(&latitude,&longitude);
    }
  }
}
void SendMesurement(){
  SendData(("00" + String(longitude,HEX)));    //Send the first data starting by a 0 if it's the longitude or 1 for latitude
  SendData(("01" + String(latitude,HEX)));
}

String message_incomming(){
  String messageRecu ="";
  String messagetuner = "";
  String retour = "";
  messageRecu = LoraSendCommand("AT+RECV=?\r\n");
  for(int i=0;i<=messageRecu.length();i++){
    if(messageRecu[i] != '\n'){
      messagetuner += messageRecu[i];
    }
  }
  for(int i=0;i<=messagetuner.length();i++){
    if((messagetuner[i] == '0')&&(messagetuner[i+1] == ':')){
      retour = "";
    }
    else if((messagetuner[i] == '9')&&(messagetuner[i+1] == ':')){
      for(byte j=0;j<8;j++){
        retour += messagetuner[i+2+j];
      }
    }
  }
  return retour;
}

void IncommingTraitement(){
  String Code = message_incomming();
  switch (Code[1]) {
  case 1:
    DelayTwoMesurementMS = 1000*60*(Code[2]+Code[3]*16);  
    break;


  }
}
