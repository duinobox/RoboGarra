/////
//  Esse codigo é para usar o Joystick Dabble com os botões Digitais
/////
// Esse é possivel escolher a porta RX e TX  - Dabble.begin(9600, 2, 4); 2 é RX e 4 é TX

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#include <Servo.h>
#define SERVO_PIN 12     // Pino de controle do servo 9

Servo servoMotor;
int servoPosition = 90;  // Posição inicial do servo

#include <Stepper.h>
int steps = 2048;
Stepper stepper(steps, A0, A2, A1, A3);

bool isButtonPressedForward = false; // Flag para indicar se o botão de avanço está pressionado
bool isButtonPressedReverse = false; // Flag para indicar se o botão de retrocesso está pressionado

#define led 12
const int pinoM1 = 4;
const int pinoM2 = 5;
const int pinoPWMa = 6;
//const int vel = 0;
const int pinoM3 = 9;
const int pinoM4 = 8;
const int pinoPWMb = 11;

int velAtual;
int velEstado = LOW;
int velMini = 110;
int velMax = 240;
int velMedia = 175;

void moveFrente();
void moveTras();
void moveEsquerda();
void moveDireita();
void parar();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  //Dabble.begin(9600);      //Enter baudrate of your bluetooth.Connect bluetooth on Bluetooth port present on evive.
  Dabble.begin(9600, 2, 3); 
  pinMode(led, OUTPUT);
  pinMode(pinoM1, OUTPUT);
  pinMode(pinoM2, OUTPUT);
  pinMode(pinoPWMa, OUTPUT);
  pinMode(pinoM3, OUTPUT);
  pinMode(pinoM4, OUTPUT);
  pinMode(pinoPWMb, OUTPUT);
  velAtual = velMedia;
  analogWrite(pinoPWMa, velAtual);
  analogWrite(pinoPWMb, velAtual);
  
  
  stepper.setSpeed(14);
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(servoPosition);  // Configura a posição inicial do servo
}

void loop() {
  
  isButtonPressedForward = false; // Ambos os botões soltos
  isButtonPressedReverse = false;
  Dabble.processInput();             
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
    moveFrente();
    
  }else if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
    moveTras();
  }
  
  else if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
    moveEsquerda();
  }

  else if (GamePad.isRightPressed())
  {
    Serial.print("Right");
    moveDireita();
  }
  else{
    parar();
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    servoPosition = constrain(servoPosition + 1, 0, 178);
    servoMotor.write(servoPosition);  // Gira o servo no sentido horário
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    servoPosition = constrain(servoPosition - 1, 0, 178);
    servoMotor.write(servoPosition);  // Gira o servo no sentido anti-horário
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    isButtonPressedForward = false; // Botão de avanço solto
    isButtonPressedReverse = true; // Botão de retrocesso pressionado
      
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    isButtonPressedForward = true; // Botão de avanço pressionado
    isButtonPressedReverse = false; // Botão de retrocesso solto
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
    velEstado = !velEstado;
    if(velEstado ==HIGH){
      velAtual = velMax;
    }else{
      velAtual = velMedia;
    }
  }


  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
    velEstado = !velEstado;
    if(velEstado ==HIGH){
      velAtual = velMini;
    }else{
      velAtual = velMedia;
    }

  } 
    
    
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();


if (isButtonPressedForward) {
  stepper.step(-1); // Avança um passo no motor
  }
if (isButtonPressedReverse) {
    stepper.step(1); // Retrocede um passo no motor
    }
//
}


void moveFrente(){
  digitalWrite(pinoM1, LOW);
  digitalWrite(pinoM2, HIGH);
  analogWrite(pinoPWMa, velAtual);
  digitalWrite(pinoM3, LOW);
  digitalWrite(pinoM4, HIGH);
  analogWrite(pinoPWMb, velAtual);
    
}
void moveTras(){
  digitalWrite(pinoM1, HIGH);
  digitalWrite(pinoM2, LOW);
  analogWrite(pinoPWMa, velAtual);
  digitalWrite(pinoM3, HIGH);
  digitalWrite(pinoM4, LOW);
  analogWrite(pinoPWMb, velAtual);
  
 
}
void parar(){
  digitalWrite(pinoM1, LOW);
  digitalWrite(pinoM2, LOW);
  analogWrite(pinoPWMa, 0);
  digitalWrite(pinoM3, LOW);
  digitalWrite(pinoM4, LOW);
  analogWrite(pinoPWMb, 0);
  
}
void moveEsquerda(){
  digitalWrite(pinoM1, HIGH);
  digitalWrite(pinoM2, LOW);
  analogWrite(pinoPWMa, velAtual);
  digitalWrite(pinoM3, LOW);
  digitalWrite(pinoM4, HIGH);
  analogWrite(pinoPWMb, velAtual);
}
void moveDireita(){
  digitalWrite(pinoM1, LOW);
  digitalWrite(pinoM2, HIGH);
  analogWrite(pinoPWMa, velAtual);
  digitalWrite(pinoM3, HIGH);
  digitalWrite(pinoM4, LOW);
  analogWrite(pinoPWMb, velAtual);
}
