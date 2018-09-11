
#include <Adafruit_BMP085.h>
#include <EEPROM.h>

int addr = 0; 
byte value;
  
Adafruit_BMP085 bmp180;

int erro;
int altitude;
int apogeu;

void setup() {

//Modificar o código, colocando o while que verifique a o apogeu e teste quando o apogeu for maior que a altitude, n executar mais o laço.

  //LED de sinalização e controle de frequecia da leitura.
  pinMode(12, OUTPUT);
  
  digitalWrite(12, 1);
  
  value = EEPROM.read(addr);
  apogeu = value; //Altitude máxima gravada na EEPROM.
  
  Serial.begin(9600);

  //Estratégia para calibração da altitude local em relação ao nível do mar como autitude ZERO.
  bmp180.begin();
  //Espera 2 segundos para posicionamento junto a base e leitura de sua altitude.
  delay(2000);
  erro = bmp180.readAltitude();
  Serial.print("Erro medido: ");
  Serial.println(erro);
  //Espera 2 segundos para posicionamento dentro do mini foguete.
  delay(2000); 
  Serial.println(""); 
  
  digitalWritesd(12,0);
  
}

void getApogeu(){      
  Serial.println("");
  Serial.println("");
  Serial.print("Verificando apogeu via monitor serial: ");
  Serial.print(apogeu);
  Serial.println("m");
  Serial.println("");
  Serial.println("");     
}

void getEeprom(){     
  Serial.println("");
  Serial.println("");
  Serial.print("Verificando apogeu gravado na EEPROM via monitor serial: ");
  value = EEPROM.read(addr);
  Serial.print(value,DEC);
  Serial.println("m");
  Serial.println("");
  Serial.println("");     
}

void eraseEeprom(){
  EEPROM.write(addr, 0);
  Serial.println("");
  Serial.println("");
  Serial.print(" EEPROM apagada, reset o arduino!!!");
  Serial.println("");
  Serial.println("");
}


// INICIO DO LOOP
void loop() {
  
  altitude = bmp180.readAltitude() - erro;
  
  if(altitude > apogeu){
    apogeu = altitude;
    EEPROM.write(addr, apogeu);
  }

  if (Serial.available()){    
    switch(Serial.read()){
      case 'm':      
        getApogeu();        
      break;
      
      case'a':
        getEeprom();
      break;
      case'e':
        eraseEeprom();
      break;   
    }    
  }

  digitalWrite(12, 1);
  delay(250);
  digitalWrite(12, 0);
  delay(250);

  /*
  Serial.println("Nova leitura:");
  delay(1000);
  
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("m");
  delay(100);  
  Serial.print("Apogeu: ");
  Serial.print(apogeu);
  Serial.println("m");
  delay(100);
  Serial.println("");      
  */
  
 }
