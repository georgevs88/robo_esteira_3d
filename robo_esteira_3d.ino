#include <IRremote.h>

#define pinSensor 7
#define pinSentido1MotorA 6
#define pinSentido2MotorA 9
#define pinSentido1MotorB 10
#define pinSentido2MotorB 11

IRrecv sensorIR (pinSensor);
decode_results   comando;

// DECLARAÇÃO DAS VARIÁVEIS GLOBAIS
bool ligado = false;
String ultEstado = "F";

void setup() {
  Serial.begin(9600);
  pinMode(pinSentido1MotorA, OUTPUT);
  pinMode(pinSentido2MotorA, OUTPUT);
  pinMode(pinSentido1MotorB, OUTPUT);
  pinMode(pinSentido2MotorB, OUTPUT);
  
  // HABILITANDO SENSOR IR
  sensorIR.enableIRIn();
  Serial.println("Sensor IR Habilitado");
}

void loop() {
// QUANDO RECEBER UM COMANDO DO CONTROLE INICIA O BLOCO
  if (sensorIR.decode(&comando)) {
    //Serial.println(comando.value, HEX);

    switch (comando.value) {
      case (0xFFA25D): {
        Serial.println("ON/OFF");
        if(ligado)
          ligado = false;
        else
          ligado = true;
        break;
      }  
      case (0xFFA857): {
        Serial.println("MEIO");
        ultEstado = "M";
        break;
      }  
      case (0xFF02FD): {
        Serial.println("FRENTE");
        ultEstado = "F";
        break;
      }  
      case (0xFF9867): {
        Serial.println("TRAS");
        ultEstado = "T";
        break;
      } 
      case (0xFFE01F): {
        Serial.println("ESQUERDA");
        ultEstado = "E";
        break;
      } 
      case (0xFF906F): {
        Serial.println("DIREITA");
        ultEstado = "D";
        break;
      } 
    }    
    sensorIR.resume();// ENCERRA PARA AGUARDAR NOVO COMANDO
  }

    //BLOCO DE CONTROLE DOS MOTORES
    if(ligado){
      if(ultEstado == "F"){
        Serial.println("ANDANDO FRENTE");
        digitalWrite(pinSentido1MotorA, HIGH);
        digitalWrite(pinSentido2MotorA, LOW);   
        digitalWrite(pinSentido1MotorB, LOW);
        digitalWrite(pinSentido2MotorB, HIGH);
      } else if(ultEstado == "T"){
        Serial.println("ANDANDO TRÁS");
        digitalWrite(pinSentido1MotorA, LOW);
        digitalWrite(pinSentido2MotorA, HIGH);   
        digitalWrite(pinSentido1MotorB, HIGH);
        digitalWrite(pinSentido2MotorB, LOW);
      } else if(ultEstado == "E"){
        Serial.println("VIRANDO ESQUERDA");
        digitalWrite(pinSentido1MotorA, LOW);
        digitalWrite(pinSentido2MotorA, HIGH);   
        digitalWrite(pinSentido1MotorB, LOW);
        digitalWrite(pinSentido2MotorB, HIGH);
      } else if(ultEstado == "D"){
        Serial.println("VIRANDO DIREITA");
        digitalWrite(pinSentido1MotorA, HIGH);
        digitalWrite(pinSentido2MotorA, LOW);  
        digitalWrite(pinSentido1MotorB, HIGH);
        digitalWrite(pinSentido2MotorB, LOW);
      }
    } else {
      Serial.println("PARADO");
      digitalWrite(pinSentido1MotorA, LOW);
      digitalWrite(pinSentido2MotorA, LOW);   
      digitalWrite(pinSentido1MotorB, LOW);
      digitalWrite(pinSentido2MotorB, LOW);
    }
    delay(250);
}

