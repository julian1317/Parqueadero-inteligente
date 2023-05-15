#include <Servo.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define t1 10
#define t2 9
#define t3 8

#define t4 7
#define t5 13

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
  lcd.begin(16,2);
  lcd.setCursor(0,0);
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
  
  

}

else if (estadoPuerta == -1)
{
  Serial.println("Puerta Abierta para entrada");

  if (sensorEntradaDigital==HIGH && sensorSalidaDigital==LOW)
  {
     estadoPuerta = -2;
     servoMotor.write(0);
  }
  
}  
 else if (estadoPuerta == 1)
{
  Serial.println("Puerta Abierta para salir");

    if (sensorSalidaDigital==HIGH && sensorEntradaDigital==LOW)
  {
     estadoPuerta = 2;
     servoMotor.write(0);
  }
  
}
 else if (estadoPuerta == -2)
{
  Serial.println("La puerta se cierra después de que el vehículo pasó la puerta de la barrera (Luego de entrar)");

    if (sensorSalidaDigital==HIGH)
  {
     estadoPuerta = 0;
  }
  
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





lcd.setCursor(0,0);
if (parqueaderosDisponibles == 0)
{
  lcd.print("  *Parq.. lleno* ");
  delay(600);
}
else
{
  lcd.print("    Parqueaderos  "+ parqueaderosDisponibles);
delay(600);
}

  
  
if (sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoDosDigital==HIGH & sensorParqueaderoTresDigital==HIGH)
{
  lcd.setCursor(0,1);
  lcd.print("dispo..1, 2 y 3     ");
  delay(600);

}


else if((sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoDosDigital==HIGH)|(sensorParqueaderoDosDigital==HIGH & sensorParqueaderoTresDigital==HIGH)|(sensorParqueaderoTresDigital==HIGH & sensorParqueaderoUnoDigital==HIGH))
  {
    lcd.setCursor(0,1);
    if(sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoDosDigital==HIGH)
    lcd.print("dispo.. 1 y 2    ");
    else if(sensorParqueaderoUnoDigital==HIGH & sensorParqueaderoTresDigital==HIGH)
    lcd.print("dispo.. 1 y 3    ");
    else
    lcd.print("dispo.. 2 y 3    ");
    delay(600);
  }
else if(sensorParqueaderoUnoDigital==LOW & sensorParqueaderoDosDigital==LOW & sensorParqueaderoTresDigital==LOW)
  {
    lcd.setCursor(0,1);
    lcd.print("Paqueadero lleno  ");
    delay(600);
  }
else if((sensorParqueaderoUnoDigital==LOW & sensorParqueaderoDosDigital==LOW)|(sensorParqueaderoDosDigital==LOW & sensorParqueaderoTresDigital==LOW)|(sensorParqueaderoTresDigital==LOW & sensorParqueaderoUnoDigital==LOW))
  {
      lcd.setCursor(0,1);
    if(sensorParqueaderoUnoDigital==HIGH)
      lcd.print("    dispo.. 1     ");
  else if (sensorParqueaderoDosDigital==HIGH)
       lcd.print("   dispo.. 2     ");
    else
       lcd.print("   dispo.. 3     ");
  }
  

  delay(600);
  
  Serial.println(servoMotor.read());
  

}