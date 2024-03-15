//lets show the data from mpu6050 roll pitch and yaw 
//this is first version of fighter flight computer 

import processing.serial.*;

//define the port name 
Serial port;
//calculate  the roll , pitch , yaw angles 
float Roll , Pitch , Yaw ;
//define the accelerometer 
float AccX , AccY , AccZ;
//define the gyroscope
float GyroX , GyroY , GyroZ;

//define the temperature , pressure , altitude 
float Temperature , Pressure , Altitude;


//define the roll , pitch , yaw 
ArrayList<Float> rollHistory = new ArrayList<Float>();
ArrayList<Float> pitchHistory = new ArrayList<Float>();
ArrayList<Float> yawHistory = new ArrayList<Float>();

//define the acceleration x , y , z 
ArrayList<Float>AccXHistory = new ArrayList<Float>();
ArrayList<Float>AccYHistory = new ArrayList<Float>();
ArrayList<Float>AccZHistory = new ArrayList<Float>();

//define the gyroscope x , y ,z 
ArrayList<Float>GyroXHistory = new ArrayList<Float>();
ArrayList<Float>GyroYHistory = new ArrayList<Float>();
ArrayList<Float>GyroZHistory = new ArrayList<Float>();

//define the temperature , pressure , altitude 
ArrayList<Float>TempHistory = new ArrayList<Float>();
ArrayList<Float>PressureHistory = new ArrayList<Float>();
ArrayList<Float>AltitudeHistory = new ArrayList<Float>();



int historylength = 200;
//int yoffset = 100;

//define the offset 
int xoffset = 100;
int yoffset = 100;

//define the serial port name 
String SerialPortName = "COM13";

void setup(){

//define the window size 
size (1500 , 900 , P3D);
background(0);
//define the title
surface.setTitle("PIE.SPACE");
//define the serial monitor
port = new Serial(this , SerialPortName , 9600);

//define the roll , pitch , yaw 
rollHistory = new ArrayList<Float>();
pitchHistory = new ArrayList<Float>();
yawHistory = new ArrayList<Float>();

//define the acceleration x ,y ,z 
AccXHistory = new ArrayList<Float>();
AccYHistory = new ArrayList<Float>();
AccZHistory = new ArrayList<Float>();

//define the gyroscope x,y,z
GyroXHistory = new ArrayList<Float>();
GyroYHistory = new ArrayList<Float>();
GyroZHistory = new ArrayList<Float>();

//define the temp , pressure , altitude 
TempHistory = new ArrayList<Float>();
PressureHistory = new ArrayList<Float>();
AltitudeHistory = new ArrayList<Float>();

noStroke();
}


void draw (){
  
  if(port.available() >0){
    String data = port.readStringUntil('\n');
    if(data != null){
      String[] angles = data.trim().split(" , ");
      if(angles.length == 12 ){
        //define the roll , pitch , yaw 
        Roll = float(angles[0]);
        Pitch = float(angles[1]);
        Yaw = float(angles[2]);
        //define the accelerationX , accelerationY , accelerationZ 
        AccX = float(angles[3]);
        AccY = float(angles[4]);
        AccZ = float(angles[5]);
        //define the gyrox , gyroy , gyroz 
        GyroX = float(angles[6]);
        GyroY = float(angles[7]);
        GyroZ = float(angles[8]);
        
        //define the temperatue pressure altitude 
         Temperature = float(angles[9]);
         Pressure = float(angles[10]);
         Altitude = float(angles[11]);
         
         
        
        //add the roll pitch and yaw 
        rollHistory.add(Roll);
        pitchHistory.add(Pitch);
        yawHistory.add(Yaw);
        //add the accx , accy , accz 
        AccXHistory .add(AccX);
        AccYHistory .add(AccY);
        AccZHistory .add(AccZ);
        
        //add the gyrox , gyroy , gyroz 
        GyroXHistory .add(GyroX);
        GyroYHistory .add(GyroY);
        GyroZHistory .add(GyroZ);
        
        //add the temperature , pressure , altitude 
        TempHistory .add(Temperature);
        PressureHistory .add(Pressure);
        AltitudeHistory .add(Altitude);
        
        
        
        
        
        if(rollHistory.size() > historylength){
          rollHistory.remove(0);
          pitchHistory.remove(0);
          yawHistory.remove(0);
          
        }
        
          
      }
    }
  }
  //calling the function 
  text_data();
  frame_roll ();
  frame_pitch();
  frame_yaw();
  //rocket_model();
  acceleromter();
  gyroscope();
  bmp280();
  

  

 
}

void text_data(){
  background(0); //background color is black
  //display the roll and pitch  and yaw degree  b
  fill(255); //background color is white 
  textSize(20);
  text("Roll :-  " + Roll  + "  Degree ", 30, 50);
  text("Pitch :- " + Pitch + "  Degree ", 30, 100);
  text("Yaw :-   " + Yaw   + "  Degree ", 30 , 150);
  //define the box for roll pitch and yaw degree 
  stroke(255);
  strokeWeight(2);
  line(20 , 20 , 20 , 180);
  line(20 , 180 , 250 , 180);
  line(250, 180 , 250 , 20);
  line(250, 20 , 20 , 20);
}

void acceleromter(){
  //background(0); //background color is black 
  fill(255);
  textSize(20);
  text("Accelerometer value " , 300 , 50);
  stroke(255);
  line(300 , 55 , 470 , 55);
  text("AccX :- " + AccX , 300 , 100);
  text("AccY :- " + AccY , 300 , 150);
  text("AccZ :- " + AccZ , 300 , 200);
  
  
  //define the frame 
  stroke(255);
  strokeWeight(2);
  line(280 , 20 , 280 , 230);
  line(280 , 230 , 500 , 230);
  line(500 , 230 , 500 , 20);
  line(280 , 20 , 500 , 20);
  
}

void gyroscope(){
  fill(255);
  textSize(20);
  text("Gyroscope value ", 600 , 50);
  stroke(255);
  line(600 , 55 , 740 , 55);
  text("GyroX :- " + GyroX , 600 , 100);
  text("GyroY :- " + GyroY , 600 , 150);
  text("GyroZ :- " + GyroZ , 600 , 200);
  
  //define the frame 
  stroke(255);
  strokeWeight(2);
  line(580 , 20 , 580 , 230);
  line(580 , 230 , 800 , 230);
  line(800 , 230 , 800 , 20);
  line (580 , 20 , 800 , 20);
  
  
}

void bmp280(){
  fill(255);
  textSize(20);
  text("Pressure :-" + Altitude + "PA", 900 , 100);
  text("Altitude:- " + Temperature + "M", 900 , 150);
  text("Temperature :-" + Pressure + "C" ,  900 , 200);
}




void drawGraph(ArrayList<Float> data , color lineColor , int xoffset , int yoffset ){
  stroke(lineColor);
  strokeWeight(2);
  noFill();
  beginShape();
  for(int i =0 ; i< data.size(); i++){
    float x = xoffset + i ;
    float y = map(data.get(i) , -280 , 280 , height -yoffset , yoffset);
    vertex(x , y );
  }
  endShape();
}

void frame_roll (){
  
  //define the graph for roll , pitch and yaw 
   drawGraph(rollHistory , color(200 , 200 , 0) , 100 , yoffset);
   
   
  stroke(255);
  line(100, 300, 100, 600);
  line(100, 600, 300, 600);
  fill(255);
  textSize(20);
  text("Time(s)", 180, 620);
  //draw a rectange frame 
  stroke(255);
  line (50 , 250 , 50 , 650);
  line (50 , 650 , 370 , 650);
  line (370 , 650 , 370 , 250);
  line (370 , 250 , 50 , 250);
  fill(255);
  textSize(20);
  text("Roll in Degree" , 70 , 280);
  stroke(255);
  line(70 , 290 , 190 , 290);
}

void frame_pitch(){
  //define the graph for pitch angles 
  drawGraph(pitchHistory , color(255 , 0 , 0) , 500 , yoffset);
  
  //create a frame for pitch 
  stroke(255);
  line(500 , 300 , 500 , 600);
  line(500, 600 , 700 , 600);
  fill(255);
  textSize(20);
  text("Time(s)" , 600 , 620);
  
  //draw a rectange
  stroke(255);
  line(450 , 250 , 450 , 650);
  line(450 , 650 , 770 , 650);
  line(770 , 650 , 770 , 250);
  line(450 , 250 , 770 , 250);
  fill(255);
  textSize(20);
  text("Pitch in Degree" , 470 , 280);
  stroke(255);
  line(470 , 290 , 600 , 290);
}

void frame_yaw(){
//define the graph for yaw 
   drawGraph(yawHistory , color(200,255,0), 900 , yoffset);
   
   //create a frame for yaw 
   stroke(255);
   line(900 , 300 , 900 , 600);
   line(900 , 600 , 1100 , 600);
   fill(255);
   textSize(20);
   text("Time(s)" , 1000 , 620);
   
   //draw a rectange 
   stroke(255);
   line(850 , 250 , 850 , 650);
   line(850 , 650 , 1170 , 650);
   line(1170 , 650 , 1170 , 250);
   line(850 , 250 , 1170 , 250);
   fill(255);
   textSize(20);
   text("Yaw in Degree" , 870, 280);
   stroke(255);
   line(870 , 290 , 1000 , 290);
}

void rocket_model(){
     //background(255);
  lights();
 

  translate(1300 , 500 , 0 );

  rotateX(radians(Pitch)); // Convert roll degree to radians
  rotateY(radians(Roll)); // Convert pitch degree to radians 
  //rotateZ(radians(Yaw));
  
  

  //// Draw a simple 3D cube
  float size = 100;
  stroke(255);
  fill(200,0,0);
  box(size);
  
  //draw a rocket shape 
  
  
  
}