#define LS 13    // left sensor
#define RS 12      // right sensor
//Joystick Pins
int x_key = A0;                                               
int y_key = A1;                                               
int x_pos;
int y_pos;
//Motor Pins
int IN1 = 10;       //control pin for first motor
int IN2 = 9;       //control pin for first motor
int IN3 = 6;        //control pin for second motor
int IN4 = 5;        //control pin for second motor
//Initializing variables to store data
int motor_speed;
int motor_speed1;
void setup ( ) {
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  //Initializng the joystick pins as input
  pinMode (x_key, INPUT) ;                     
  pinMode (y_key, INPUT) ;                      
}
void loop () {
    x_pos = analogRead (x_key) ;  //Reading the horizontal movement value
    y_pos = analogRead (y_key) ;  //Reading the vertical movement value
   
if (x_pos < 400 && 400 < y_pos < 600){     //Rotating the left motor in clockwise direction
    motor_speed = map(x_pos, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
    analogWrite(IN1, 0);
    analogWrite(IN2, 150);
    analogWrite(IN3, 0);
    analogWrite(IN4, 150);
  }
else if (x_pos > 600 && 400 < y_pos < 600){     //Rotating the left motor in clockwise direction
    motor_speed = map(x_pos, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
    analogWrite(IN1, 150);
    analogWrite(IN2, 0);
    analogWrite(IN3, 150);
    analogWrite(IN4, 0);
  }
else if (y_pos < 400 && 400 < x_pos < 600){     //Rotating the left motor in clockwise direction
    motor_speed = map(x_pos, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
    analogWrite(IN1, 150);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 150);
  }
else if (y_pos > 600 && 400 < x_pos < 600){     //Rotating the left motor in clockwise direction
    motor_speed = map(x_pos, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
    analogWrite(IN1, 0);
    analogWrite(IN2, 150);
    analogWrite(IN3, 150);
    analogWrite(IN4, 0);
  }
else if (400 < x_pos < 600 && 400 < y_pos < 600){     //Rotating the left motor in clockwise direction
    motor_speed = map(x_pos, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
  }
}
