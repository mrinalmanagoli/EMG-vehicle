/*
 * This code is for reading input from the EMG sensors, performing signal processing and sending it to the vehicle over the "Chatter" topic
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int64.h>


ros::NodeHandle nh;
std_msgs::Int64 str_msg;
ros::Publisher chatter("chatter", &str_msg);

float read_0 = 0.0;
float thresh_0 = 450;
int out00 = 0;
int out01 = 0;
int out02 = 0;
int signal0 = 0;

float read_1 = 0.0;
float thresh_1 = 500;
int out10 = 0;
int out11 = 0;
int out12 = 0;
int signal1 = 0;

float read_2 = 0.0;
float thresh_2 = 400;
int out20 = 0;
int out21 = 0;
int out22 = 0;
int signal2 = 0;

float read_3 = 0.0;
float thresh_3 = 450;
int out30 = 0;
int out31 = 0;
int out32 = 0;
int signal3 = 0;

// 0 is back, 1 is neutral and 2 is forward
int old_fb_state = 1;
int fb_state = 1;
int fb_signal = 0;

int old_lr_state = 1;
int lr_state = 1;
int lr_signal = 0;

int fixed_msg = 69;

//char hello[13] = "hello world!";
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_0 = analogRead(A0);
  read_1 = analogRead(A1);
  read_2 = analogRead(A2);
  read_3 = analogRead(A3);
  out02 = out01;
  out01 = out00;
  out00 = 0;
  if(read_0 > thresh_0){
    out00 = 1;
  }
  signal0 = 0;
  if((out00 + out01 + out02) >=1 ){
    signal0 = 1;
  }
/////////////////////////////
  out12 = out11;
  out11 = out10;
  out10 = 0;
  if(read_1 > thresh_1){
    out10 = 1;
  }
  signal1 = 0;
  if((out10 + out11 + out12) >=1 ){
    signal1 = 1;
  }
  ///////////////////////
  out22 = out21;
  out21 = out20;
  out20 = 0;
  if(read_2 > thresh_2){
    out20 = 1;
  }
  signal2 = 0;
  if((out20 + out21 + out22) >=1 ){
    signal2 = 1;
  }
/////////////////////////////
  out32 = out31;
  out31 = out30;
  out30 = 0;
  if(read_3 > thresh_3){
    out30 = 1;
  }
  signal3 = 0;
  if((out30 + out31 + out32) >=1 ){
    signal3 = 1;
  }

///////////////////////////////////
// 0 and 1 are for front/back, 2 and 3 are for left/right respectively

//fb_signal = signal0 - signal1;// front - back. 1 if go front, -1 if go back
fb_signal = out00 - out10;
if(fb_signal == 0){
  old_fb_state = fb_state;
}

else if(fb_signal == 1){
  if(fb_state == 1){
    fb_state = 2;
    old_fb_state = 1;
  }
  else if(fb_state == 0){
    fb_state = 1;
    old_fb_state = 0;
  }
  else{
    fb_state = 2;
    old_fb_state = 2;
  }
  fb_signal = 0;
  delay(50);
}

else if(fb_signal == -1){
  if(fb_state == 1){
    fb_state = 0;
    old_fb_state = 1;
  }
  else if(fb_state == 0){
    fb_state = 0;
    old_fb_state = 0;
  }
  else{
    fb_state = 1;
    old_fb_state = 2;
  }
  fb_signal = 0;
  delay(50);
}

// 0 and 1 are for front/back, 2 and 3 are for left/right respectively

//fb_signal = signal0 - signal1;// front - back. 1 if go front, -1 if go back
lr_signal = out30 - out20;
if(lr_signal == 0){
  old_lr_state = lr_state;
}

else if(lr_signal == 1){
  if(lr_state == 1){
    lr_state = 2;
    old_lr_state = 1;
  }
  else if(lr_state == 0){
    lr_state = 1;
    old_lr_state = 0;
  }
  else{
    lr_state = 2;
    old_lr_state = 2;
  }
  lr_signal = 0;
  delay(100);
}

else if(lr_signal == -1){
  if(lr_state == 1){
    lr_state = 0;
    old_lr_state = 1;
  }
  else if(lr_state == 0){
    lr_state = 0;
    old_lr_state = 0;
  }
  else{
    lr_state = 1;
    old_lr_state = 2;
  }
  lr_signal = 0;
  delay(100);
}

  //str_msg.data = 1000*signal0 + 100*signal1 + 10 * signal2 + signal3;
  str_msg.data = 10 * fb_state + lr_state;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(5);

  Serial.println(lr_state);

  
  
//  Serial.println(read_1)

}
