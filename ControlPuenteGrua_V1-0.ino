//Control Puente Grua Version 1.0 by Gustavo F. Paredes Delaloye

// Arduino MEGA

#include <Stepper.h>


// Define pines salida Motor Adelante Atras (pines 22 a 25).
#define salMotAdAtr1 22
#define salMotAdAtr2 23
#define salMotAdAtr3 24
#define salMotAdAtr4 25

// Define pines salida Motor Izquierda Derecha (pines 26 a 29).
#define salMotIzqDer1 26
#define salMotIzqDer2 27
#define salMotIzqDer3 28
#define salMotIzqDer4 29

// Define pines salida Motor Arriba Abajo (pines 30 a 33).
#define salMotArrAbaj1 30
#define salMotArrAbaj2 31
#define salMotArrAbaj3 32
#define salMotArrAbaj4 33

// Define pin salida Electro Iman (8)
#define salidaElectroIman 8

// Define pines sensores
#define sensorAtras 2
#define sensorAdelante 3
#define sensorDerecha 4
#define sensorIzquierda 5


const int stepsPerRevolution = 200;  // cambie este valor por el numero de pasos de su motor

// Crea el objeto motorAdelanteAtras del tipo/clase Stepper
Stepper motorAdelanteAtras(stepsPerRevolution, salMotAdAtr1, salMotAdAtr2, salMotAdAtr3, salMotAdAtr4);

// Crea el objeto motorIzquierdaDerecha del tipo/clase Stepper
Stepper motorIzquierdaDerecha(stepsPerRevolution,salMotIzqDer1,salMotIzqDer2,salMotIzqDer3,salMotIzqDer4);

int state;
int pasoSubeBaja;

//**************************************************************************************************************

void setup() {
// Setea el pin de salida del Electro Iman como OUTPUT.
  pinMode(salidaElectroIman, OUTPUT);

// Setea los pines de los sensores como INPUT
  pinMode (sensorAtras, INPUT);
  pinMode (sensorAdelante, INPUT);
  pinMode (sensorDerecha, INPUT);
  pinMode (sensorIzquierda, INPUT);

// Establece la velocidad en 100rpm
  motorAdelanteAtras.setSpeed(100);
  motorIzquierdaDerecha.setSpeed(100);

  state = 0;
  pasoSubeBaja = 0;

 Serial.begin(9600); // Velocidad por defecto para el modulo Bluetooth.
}

//**************************************************************************************************************

void loop() {

// RESETEAMOS STATE.
 // state = 0;
   
 if(Serial.available() > 0){ // Chequea cuando hay un dato en el puerto serial.
  state = Serial.read(); // Lee el dato desde el puerto serial.
 }
  
// RETARDO GENERAL QUE INFLUYE EN EL LOOP Y POR ENDE EN LA VELOCIDAD DE LOS MOTORES.
// SACARLO Y PONER RETARDOS EN CADA CASE PARA QUE SEAN INDIVIDUALES Y DIFERENTES.
  delay(10);

 switch (state){

// AVANCE Y RETROCESO
  case 49:// letra 1 (49) ADELANTE
  
       motorAdelanteAtras.step(1); // MOTOR ADELANTEATRAS AVANZA 1 PASO
       //Serial.println("AVANZAR"); // Enviar devuelta, al telefono, la cadena "AVANZAR"
       
  break;
  
  case 51:// letra 3 (51) ATRAS
  
       motorAdelanteAtras.step(-1); // MOTOR ADELANTEATRAS RETROCEDE 1 PASO
       //Serial.println("RETROCEDER"); // Enviar devuelta, al telefono, la cadena "RETROCEDER"
       
  break;

// IZQUIERDA Y DERECHA
  case 52:// letra 4 (52) IZQUIERDA
  
       motorIzquierdaDerecha.step(1); // MOTOR IZQUIERDADERECHA AVANZA A LA IZQUIERDA 1 PASO
       //Serial.println("IZQUIERDA"); // Enviar devuelta, al telefono, la cadena "IZQUIERDA"
       
  break;
  
  case 50:// letra 2 (50) DERECHA
  
       motorIzquierdaDerecha.step(-1); // MOTOR IZQUIERDADERECHA AVANZA A LA DERECHA 1 PASO
       //Serial.println("DERECHA"); // Enviar devuelta, al telefono, la cadena "DERECHA"
       
  break;

// ARRIBA Y ABAJO
  case 85:// letra U (85) BAJAR ELECTROIMAN 85
  
       // MOTOR ARRIBAABAJO BAJA 1 PASO
       
      switch (pasoSubeBaja){
        
        case 0: //INICIO PASO 1
        case 4:
          digitalWrite(salMotArrAbaj1, LOW);
          digitalWrite(salMotArrAbaj2, HIGH);
          digitalWrite(salMotArrAbaj3, HIGH);
          digitalWrite(salMotArrAbaj4, LOW);
       break;

       case 1: //INICIO PASO 2
          digitalWrite(salMotArrAbaj1, LOW);
          digitalWrite(salMotArrAbaj2, HIGH);
          digitalWrite(salMotArrAbaj3, LOW);
          digitalWrite(salMotArrAbaj4, HIGH);
       break;

       case 2: //INICIO PASO 3
          digitalWrite(salMotArrAbaj1, HIGH);
          digitalWrite(salMotArrAbaj2, LOW);
          digitalWrite(salMotArrAbaj3, LOW);
          digitalWrite(salMotArrAbaj4, HIGH);
       break;

       case 3: //INICIO PASO 4
          digitalWrite(salMotArrAbaj1, HIGH);
          digitalWrite(salMotArrAbaj2, LOW);
          digitalWrite(salMotArrAbaj3, HIGH);
          digitalWrite(salMotArrAbaj4, LOW);
          pasoSubeBaja = -1;
       break;

       default:
       
          // NADA POR DEFECTO.
          
       break;
       
      }
       pasoSubeBaja++;
       //Serial.println("BAJAR"); // Enviar devuelta, al telefono, la cadena "BAJAR"
       
  break;
  
  case 68:// letra D (68) SUBIR ELECTROIMAN
  
       // MOTOR ARRIBAABAJO SUBE 1 PASO
       
      switch (pasoSubeBaja){
        
        case 0: //INICIO PASO 1
        case 1:
          digitalWrite(salMotArrAbaj1, HIGH);
          digitalWrite(salMotArrAbaj2, LOW);
          digitalWrite(salMotArrAbaj3, HIGH);
          digitalWrite(salMotArrAbaj4, LOW);
          pasoSubeBaja = 5;
       break;

       case 4: //INICIO PASO 3
          digitalWrite(salMotArrAbaj1, HIGH);
          digitalWrite(salMotArrAbaj2, LOW);
          digitalWrite(salMotArrAbaj3, LOW);
          digitalWrite(salMotArrAbaj4, HIGH);
       break;

       case 3: //INICIO PASO 2
          digitalWrite(salMotArrAbaj1, LOW);
          digitalWrite(salMotArrAbaj2, HIGH);
          digitalWrite(salMotArrAbaj3, LOW);
          digitalWrite(salMotArrAbaj4, HIGH);
       break;

       case 2: //INICIO PASO 1
          digitalWrite(salMotArrAbaj1, LOW);
          digitalWrite(salMotArrAbaj2, HIGH);
          digitalWrite(salMotArrAbaj3, HIGH);
          digitalWrite(salMotArrAbaj4, LOW);
       break;

       default:
       
          // NADA POR DEFECTO.
          
       break;
       
      }
       pasoSubeBaja--;
       //Serial.println("SUBIR"); // Enviar devuelta, al telefono, la cadena "SUBIR"
       
  break;

// ENCENDIDO Y APAGADO ELECTROIMAN
  case 83: // letra S (83) ENCENDER ELECTROIMAN
       
       digitalWrite(salidaElectroIman, HIGH); // ELECTROIMAN ENCENDIDO.
       //Serial.println("ELECTROIMAN ON"); // Enviar devuelta, al telefono, la cadena "ELECTROIMAN ON"
       
  break;
  case 78:// letra N (78) APAGAR ELECTROIMAN
       
       digitalWrite(salidaElectroIman, LOW); // ELECTROIMAN NO ENCENDIDO.
      
       //DESENERGIZA BOBINAS MOTOR SUBE BAJA.
       digitalWrite(salMotArrAbaj1, LOW);
       digitalWrite(salMotArrAbaj2, LOW);
       digitalWrite(salMotArrAbaj3, LOW);
       digitalWrite(salMotArrAbaj4, LOW);
       pasoSubeBaja = 0;
       //Serial.println("ELECTROIMAN OFF"); // Enviar devuelta, al telefono, la cadena "ELECTROIMAN OFF"
       
  break;

// BOTON PAUSA
  case 88: // letra X (88)
       
       //Serial.println("PAUSA"); // Enviar devuelta, al telefono, la cadena "PAUSA"
       
  break;

// BOTON STOP
  case 80: // letra P (80)
  
       state = 0;
       //Serial.println("PARO TOTAL"); // Enviar devuelta, al telefono, la cadena "PARO TOTAL"
       
  break;

// CASE 0 PARA TODO DESENERGIZANDO BOBINAS.
  case 0: // valor 0 de state DESACTIVA TODAS LAS BOBINAS (CERO CONSUMO)

       // DESENERGIZA BOBINAS MOTOR ADELANTE ATRAS.
       digitalWrite(salMotAdAtr1, LOW);
       digitalWrite(salMotAdAtr2, LOW);
       digitalWrite(salMotAdAtr3, LOW);
       digitalWrite(salMotAdAtr4, LOW);

       // DESENERGIZA BOBINAS MOTOR IZQUIERDA DERECHA.
       digitalWrite(salMotIzqDer1, LOW);
       digitalWrite(salMotIzqDer2, LOW);
       digitalWrite(salMotIzqDer3, LOW);
       digitalWrite(salMotIzqDer4, LOW);

  break;
  
// RUTINA POR DEFECTO SI NO MATCHEA NINGUN CODIGO.
  default:
         
          // NADA POR DEFECTO.
 
  break;
  
 }
}
