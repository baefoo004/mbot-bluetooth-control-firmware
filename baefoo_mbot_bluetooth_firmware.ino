#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4
int cur_direction = 0;
int cur_speed = 50;

#define INT_MAX 32767
#define INT_MIN -32768

#define COMMAND_MOTOR_STOP      0
#define COMMAND_MOVE_FORWARD    1
#define COMMAND_MOVE_BACKWARD   2
#define COMMAND_MOVE_LEFT       3
#define COMMAND_MOVE_RIGHT      4
#define COMMAND_SPEED_UP        5
#define COMMAND_SPEED_DOWN      6

void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      if(direction == 1){
        	leftSpeed = speed;
        	rightSpeed = speed;
      }else if(direction == 2){
        	leftSpeed = -speed;
        	rightSpeed = -speed;
      }else if(direction == 3){
        	leftSpeed = -speed;
        	rightSpeed = speed;
      }else if(direction == 4){
        	leftSpeed = speed;
        	rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
				
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;

void setup(){
    Serial.begin(115200);
}

void loop(){
    if(Serial.available() > 0) {
      int cn = Serial.parseInt();
      switch(cn) {
        case COMMAND_MOTOR_STOP: {
          cur_direction = 0;
          move(DIRECTION_FORWARD, 0);
          break;
        }
        case COMMAND_MOVE_FORWARD: {
          cur_direction = DIRECTION_FORWARD;
          move(DIRECTION_FORWARD, cur_speed);
          break;
        }
        case COMMAND_MOVE_BACKWARD: {
          cur_direction = DIRECTION_BACKWARD;
          move(DIRECTION_BACKWARD, cur_speed);
          break;
        }
        case COMMAND_MOVE_LEFT: {
          cur_direction = DIRECTION_LEFT;
          move(DIRECTION_LEFT, cur_speed);
          break;
        }
        case COMMAND_MOVE_RIGHT: {
          cur_direction = DIRECTION_RIGHT;
          move(DIRECTION_RIGHT, cur_speed);
          break;
        }
        case COMMAND_SPEED_UP: {
          if(cur_speed < 250) {
            cur_speed += 50;
            move(cur_direction, cur_speed);
          }
          break;
        }
        case COMMAND_SPEED_DOWN: {
          if(cur_speed > 100) {
            cur_speed -= 50;
            move(cur_direction, cur_speed);
          }
          break;
        }
      }
    }
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

