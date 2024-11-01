
#include <AccelStepper.h>
#include <Servo.h>
String code;
String product_names[3]={"Box A","Box B","Box C"};
int prices[3]={500,600,700};
String product_id[3]={"H14697825312","C1584GJK5645","B64859648542"};
//int base_reduction[3]={120,700,100};
//int arm_reduction[3]={0,100,0};
AccelStepper base(1,4,7);
AccelStepper arm(1,2,5);
AccelStepper z_axis(1,3,6);

Servo air_pump;
Servo solenoid_valve;
int angle_base[3]={250,350,-300};
int angle_arm[3]={200,450,-150};
int index=0;
char ch;
int count=0;

void barcode_scan()
{
  Serial.begin(9600);
  while(1){

    if (Serial.available()>0)
    break;
  }

code=Serial.readString();

ch=code[0];

if (ch=='H')
index=0;

else if(ch=='C')
index=1;

else
index=2;

count=count+1;

 Serial.print(count);

    Serial.print("\t");

    Serial.print(product_id[index]);

     Serial.print("\t");

     Serial.print(product_names[index]);

    Serial.print("\t\t");

    Serial.print(prices[index]);

    Serial.println();
    
Serial.end();
}

void suction_pickup()
{

        air_pump.write(180);
        solenoid_valve.write(0);
        delay(1500);

     /*   air_pump.write(0);
        solenoid_valve.write(0);

        delay(100);*/

}

void suction_drop()
{
        air_pump.write(0);
        solenoid_valve.write(180);

         /*delay(200);

          air_pump.write(0);
          solenoid_valve.write(0);

          delay(100);*/

}

void z_axis_forward()
{
  
 z_axis.moveTo(-1100);  

  while(1){

    z_axis.run();

    if(z_axis.distanceToGo()==0)
        return;
  }

  
}
void z_axis_backward()
{
  z_axis.moveTo(-z_axis.currentPosition());

  while(1){
      z_axis.run();
      if (z_axis.distanceToGo()==0)
          return;
  }
           
  }
  


void base_forward()
{
  base.moveTo(angle_base[index]);

  while(1){
      base.run();
      if (base.distanceToGo()==0)
            return;

  }
}
void base_backward(){
  base.moveTo(-(base.currentPosition()));

   while(1){
        base.run();

        if(base.distanceToGo()==0)
              return;
   }

   base.setCurrentPosition(0);
}

void arm_forward(){
  arm.moveTo(angle_arm[index]);

    while(1){
        arm.run();

        if(arm.distanceToGo()==0)
            return;
    }
  
}
void arm_backward(){
   arm.moveTo(-(arm.currentPosition()));

   while(1){
      arm.run();
      if(arm.distanceToGo()==0)
      return;

   }
}


void setup() {
  // put your setup code here, to run once:

   base.setMaxSpeed(500);
   base.setAcceleration(300);
  
   arm.setMaxSpeed(500);
   arm.setAcceleration(300);
   
  z_axis.setMaxSpeed(500);
  z_axis.setAcceleration(300);

  air_pump.attach(9);
  solenoid_valve.attach(10);



  air_pump.write(0);
  solenoid_valve.write(0);
  
 
 Serial.begin(9600);

Serial.println("Count\tProduct ID\tProduct Name\tPrice");
Serial.end();

 base.setCurrentPosition(0);
 arm.setCurrentPosition(0);
 z_axis.setCurrentPosition(0);
   
}

void loop() {
  // put your main code here, to run repeatedly:

    barcode_scan();
   
   
    z_axis_forward();

     suction_pickup();
    
   // delay(1000);
    z_axis_backward();
   // delay(1000);
    base_forward();
    //delay(1000);
    arm_forward();
   // delay(1000);
    z_axis_forward();

    suction_drop();
    
   // delay(1000);
    z_axis_backward();
    //delay(1000);
    arm_backward();
    
    base_backward();

    

   // delay(1000); }
