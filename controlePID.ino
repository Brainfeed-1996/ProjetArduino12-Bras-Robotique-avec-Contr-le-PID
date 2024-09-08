#include <Servo.h>

Servo servo;
int potPin = A0;  // Broche du potentiomètre
int setPoint = 90;  // Position cible du servomoteur
double Kp = 2.0, Ki = 0.5, Kd = 1.0;  // Coefficients PID
double previousError = 0, integral = 0;

void setup() {
  servo.attach(9);  // Connecte le servomoteur à la broche 9
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);  // Lecture de la position actuelle
  int currentPosition = map(potValue, 0, 1023, 0, 180);  // Conversion en degrés
  double error = setPoint - currentPosition;
  integral += error;
  double derivative = error - previousError;
  double output = Kp * error + Ki * integral + Kd * derivative;
  servo.write(constrain(output, 0, 180));  // Commande du servomoteur
  previousError = error;

  // Affichage des données sur le moniteur série
  Serial.print("Position actuelle : ");
  Serial.print(currentPosition);
  Serial.print(" | Position cible : ");
  Serial.print(setPoint);
  Serial.print(" | Commande PID : ");
  Serial.println(output);

  delay(100);  // Attente de 100 ms avant la prochaine lecture
}
