#include <Servo.h>

#define sensorParqueaderoTres 8
#define sensorParqueaderoDos 9
#define sensorParqueaderoUno 10

#define sensorEntrada 7
#define sensorSalida 13

Servo servoMotor;

int distanceThreshold = 100;
int sensorEntradaDigital = HIGH;
int sensorSalidaDigital = HIGH;
int sensorParqueaderoUnoDigital = HIGH;
int sensorParqueaderoDosDigital = HIGH;
int sensorParqueaderoTresDigital = HIGH;

int parqueaderosDisponibles = 3;
int estadoPuerta=0;


void setup() 
{
  Serial.begin (9600);
  servoMotor.attach(6);
  servoMotor.write(0);
}

long distanciaSensores(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void loop() 
{
  sensorEntradaDigital = digitalRead(sensorEntrada);
  sensorSalidaDigital = digitalRead(sensorSalida);
  sensorParqueaderoUnoDigital = digitalRead(sensorParqueaderoUno);
  sensorParqueaderoDosDigital = digitalRead(sensorParqueaderoDos);
  sensorParqueaderoTresDigital = digitalRead(sensorParqueaderoTres);
//0 Puerta esta cerrada
//-1 Puerta esta abierta para entrar
//1 Puerta esta abeirta para salir
//-2  La puerta se cierra después de que el vehículo pasó la puerta de la barrera (Luego de entrar)
//2 La puerta se cierra después de que el vehículo pasó la puerta de la barrera (Luego de salir)

if(estadoPuerta==0){
  Serial.println("Puerta Cerrada");

  if(sensorEntradaDigital==LOW && sensorSalidaDigital == HIGH && parqueaderosDisponibles>0){
    parqueaderosDisponibles-=1;
    estadoPuerta=-1;
    servoMotor.write(90);
   
  }

  
  if(sensorEntradaDigital == HIGH && sensorSalidaDigital == LOW ){
    parqueaderosDisponibles+=1;
    estadoPuerta=1;
    servoMotor.write(90);
    
  }
  delay(600);
  

}

else if (estadoPuerta == -1)
{
  Serial.println("Puerta Abierta para entrada");

  if (sensorEntradaDigital==HIGH && sensorSalidaDigital==LOW)
  {
     estadoPuerta = -2;
     servoMotor.write(0);
  }
  delay(600);
}  
 else if (estadoPuerta == 1)
{
  Serial.println("Puerta Abierta para salir");

    if (sensorSalidaDigital==HIGH && sensorEntradaDigital==LOW)
  {
     estadoPuerta = 2;
     servoMotor.write(0);
  }
  delay(600);
}
 else if (estadoPuerta == -2)
{
  Serial.println("La puerta se cierra después de que el vehículo pasó la puerta de la barrera (Luego de entrar)");

    if (sensorSalidaDigital==HIGH)
  {
     estadoPuerta = 0;
  }
  delay(600);
}  
else if (estadoPuerta == 2)
{
  Serial.println("La puerta se cierra después de que el vehículo pasó la puerta de la barrera (Luego de salir)");

    if (sensorEntradaDigital==HIGH)
  {
     estadoPuerta = 0;

  }
  delay(600);

}

if (parqueaderosDisponibles == 0)
{
  Serial.println("Parqueadero lleno  ");
  delay(600);
}
else
{
  Serial.println("Parqueaderos disponibles "+ parqueaderosDisponibles);
delay(600);
}

  
  
if (sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoDosDigital==HIGH & sensorParqueaderoTresDigital==HIGH)
{

  Serial.println("Parqueaderos 1, 2 y 3 estan disponibles");
delay(600);
  }
else if((sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoDosDigital==HIGH)|(sensorParqueaderoDosDigital==HIGH & sensorParqueaderoTresDigital==HIGH)|(sensorParqueaderoTresDigital==HIGH & sensorParqueaderoUnoDigital==HIGH))
  {

    if(sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoDosDigital==HIGH)
    Serial.println("Parqueader 1 y 2 estan disponibles");
    else if(sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoTresDigital==HIGH)
    Serial.println("Parqueader 1 y 3 estan disponibles");
    else
    Serial.println("Parqueader 2 y 3 estan disponibles");
    delay(600);
  }
else if(sensorParqueaderoUnoDigital==LOW & sensorParqueaderoDosDigital==LOW & sensorParqueaderoTresDigital==LOW)
  {

  Serial.println("Paqueadero lleno  ");
  delay(600);
  }
else if((sensorParqueaderoUnoDigital==LOW & sensorParqueaderoDosDigital==LOW)|(sensorParqueaderoDosDigital==LOW & sensorParqueaderoTresDigital==LOW)|(sensorParqueaderoTresDigital==LOW & sensorParqueaderoUnoDigital==LOW))
  {
  
    if(sensorParqueaderoUnoDigital==HIGH)
      Serial.println("Parqueadero 1 esta disponible ");
  else if (sensorParqueaderoDosDigital==HIGH)
       Serial.println("Parqueadero 2 esta disponible ");
    else
       Serial.println("Parqueadero 3 esta disponible ");
   }
  delay(600);
  
}
