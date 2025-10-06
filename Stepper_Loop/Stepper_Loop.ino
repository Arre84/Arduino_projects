/**
*This scripts performs a loop to move a stepper motor in both directions until
*the user takes the supply voltage of the esp. 
* It is designed to work with esp32 dev kit, stepper motor Nema17 and stepper driver tb6560. 
*Author: Emilio Arredondo Payán 
*Organisation: Universidad de Monterrey
*Contact: emilio.arredondop@udem.edu 
*First created: October 06 2025
*Last updated: October 06 2025
*/
int pasos = 0;       // Número de pasos
bool direccion =true;   // Dirección: 0 o 1
#define STEP_PIN 25
#define DIR_PIN 26

void setup() {
  Serial.begin(115200);  
  while (!Serial) {
    ; // Espera a que se abra el monitor serial
  }
  Serial.println("Programa iniciado");

  pinMode(STEP_PIN, OUTPUT); // STEP
  pinMode(DIR_PIN, OUTPUT); // DIR
  direccion = true;  
  // ---- Preguntar pasos ----
  Serial.println("¿Cuántos pasos quieres?");
  while (Serial.available() == 0) {
    // Espera activa
  }
  pasos = Serial.parseInt();  
      
}

void loop() {
  // Configurar pin 26 según dirección
  if (direccion) {
    digitalWrite(DIR_PIN, HIGH);
  } else {
    digitalWrite(DIR_PIN, LOW);
  }

  delay(100); 

  //Tb6560 max clk frequency = 15KHz @min 30 us min clock pulse width
  //V = 4000 steps/sec = 1200 rpm = 20 rps; 1 step @ 0.25ms
  //F = 4000 Hz; P = 0.25ms = 250 us
  // ---- Generar los pulsos en pin 25 ----
  for (int i = 0; i < pasos; i++) {
    digitalWrite(STEP_PIN, HIGH);   // Pulso ON
    delayMicroseconds(125);                // 10 ms encendido
    digitalWrite(STEP_PIN, LOW);    // Pulso OFF
    delayMicroseconds(125);                // 10 ms apagado
  }
  direccion = !direccion;
}

