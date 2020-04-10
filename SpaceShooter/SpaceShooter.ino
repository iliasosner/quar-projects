

#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ILI9341.h>     // Hardware-specific library
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader.h> // Image-reading functions
#include <JoyStick.h>



// TFT display and SD card share the hardware SPI interface, using
// 'select' pins for each to identify the active device on the bus.

#define SD_CS   4 // SD card select pin
#define TFT_CS 10 // TFT select pin
#define TFT_DC  9 // TFT display/command pin

SdFat                SD;         // SD card filesystem
Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys


Adafruit_ILI9341     tft    = Adafruit_ILI9341(TFT_CS, TFT_DC); ///Screen object

//image objects (Used in RAM)
Adafruit_Image       P1;        //player 1
Adafruit_Image       E1;        //enemy 1-3
Adafruit_Image       E2;        
Adafruit_Image       E3;        
Adafruit_Image       M1;        //missiles 1-13
Adafruit_Image       M2;        
Adafruit_Image       M3;        
Adafruit_Image       M4;        
Adafruit_Image       M5;        
Adafruit_Image       M6;        
Adafruit_Image       M7;        
Adafruit_Image       M8;        
Adafruit_Image       M9;        
Adafruit_Image       M10;        
Adafruit_Image       M11;        
Adafruit_Image       M12;       
Adafruit_Image       M13;       
Adafruit_Image       EX;       ///explosion
JoyStick Joy;                   //Joystick object 


int32_t              width  = 0, // BMP image dimensions
                     height = 0;

int x_move=0,y_move=0; //Joystick delta x,y
int life=3;            //player life
int level=1;           //current level
int lost=0;            //lost game flag
int bounce=0;          //button debounce
int clockk=0;          //game clock
int ex_count=0;          //explosion animation count
float inc=-0.7;        // motion animation variables
float inc2=0.7;
float inc3=0.2;
int pos[18][3]{       ///position/active array for player, enemy, missiles and explosion image

{128,230,1}, ///P1   xpos,ypos,active flag
{9,9,1},//E1
{200,9,1},//E2
{-60,-60,0},//E3
{-20,-20,0},//M1
{-20,-20,0},//M2
{-20,-20,0},//M3
{-20,-20,0},// M4
{-20,-20,0},//M5
{-20,-20,0},//M6
{-20,-20,0},//M7
{-20,-20,0},//M8
{-20,-20,0},//M9
{-20,-20,0},//M10
{-20,-20,0},//M11
{-20,-20,0},//M12
{-20,-20,0},//M13
{-60,-60,0}//explosion
};

//mapping function that works with floats
float mapff(float x, float in_min, float in_max, float out_min, float out_max){

      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



void setup(void) {

    ImageReturnCode stat; // Status from image-reading functions
    Serial.begin(9600);

    #if !defined(ESP32)
      while(!Serial);       // Wait for Serial Monitor before continuing
    #endif

    tft.begin();          // Initialize screen
    Serial.print(F("Initializing filesystem..."));

      // SD card is pretty straightforward, a single call...
    if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) { // ESP32 requires 25 MHz limit
            Serial.println(F("SD begin() failed"));
            for(;;); // Fatal error, do not continue
    }

    Serial.println(F("OK!"));

    stat = reader.drawBMP("/intro.bmp", tft, 0, 0);
    reader.printStatus(stat);   // How'd we do?


    delay(6000);
    tft.setRotation(0);    // Set rotation
    tft.fillScreen(0);     // and clear screen
    reader.drawBMP("/border.bmp", tft,0,0);

    reader.loadBMP("/Player2.bmp", P1);
    reader.loadBMP("/Enemy.bmp", E1);
    reader.loadBMP("/Enemy.bmp", E2);
    reader.loadBMP("/Enemy.bmp", E3);
    reader.loadBMP("/Bomb_down.bmp", M1);
    reader.loadBMP("/Bomb_down.bmp", M2);
    reader.loadBMP("/Bomb_down.bmp", M3);
    reader.loadBMP("/Bomb_up.bmp", M4);
    reader.loadBMP("/Bomb_up.bmp", M5);
    reader.loadBMP("/Bomb_up.bmp", M6);
    reader.loadBMP("/Bomb_up.bmp", M7);
    reader.loadBMP("/Bomb_up.bmp", M8);
    reader.loadBMP("/Bomb_up.bmp", M9);
    reader.loadBMP("/Bomb_up.bmp", M10);
    reader.loadBMP("/Bomb_up.bmp", M11);
    reader.loadBMP("/Bomb_up.bmp", M12);
    reader.loadBMP("/Bomb_up.bmp", M13);
    reader.loadBMP("/explosion.bmp", EX);


    ////////////////// intro
    tft.fillRect(12, 12, 216, 150,ILI9341_BLACK );////print New Level
    tft.setCursor(40,50);
    tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(4);
    tft.print("Level ");
    tft.println(level);

    delay(4000);

    tft.fillRect(12, 12, 216, 150,ILI9341_BLACK );
    clockk=millis();
    

}



void loop() {

    if(pos[0][2]==1){
      /////Player joystick Position
            x_move= (int)(Joy.X()*5.0);
            pos[0][0]=pos[0][0]+x_move;
            y_move= (int)(Joy.Y()*5.0);
            pos[0][1]=pos[0][1]+y_move;

    }
            ////Frame Limits
    if (pos[0][0]<7){
            pos[0][0]=7;
    }

    if (pos[0][0]>(174)){
            pos[0][0]=174;
    }

              
    if (pos[0][1]<13){
            pos[0][1]=13;
    }

    if (pos[0][1]>(248)){
            pos[0][1]=248;
    }

    ///player missile fire


    if (Joy.Z()&&((millis()-bounce)>300)){
        
        bounce=millis();

        if(pos[7][2]==0){
                pos[7][2]=1;
                pos[7][0]=pos[0][0]+18;
                pos[7][1]=pos[0][1]+27;
        }

        else if(pos[8][2]==0){
                pos[8][2]=1;
                pos[8][0]=pos[0][0]+27;
                pos[8][1]=pos[0][1]-12;
        }

        else if(pos[9][2]==0){
                pos[9][2]=1;
                pos[9][0]=pos[0][0]+27;
                pos[9][1]=pos[0][1]-12;
        }

        else if(pos[10][2]==0){
                pos[10][2]=1;
                pos[10][0]=pos[0][0]+27;
                pos[10][1]=pos[0][1]-12;
        }

        else if(pos[11][2]==0){
                pos[11][2]=1;
                pos[11][0]=pos[0][0]+27;
                pos[11][1]=pos[0][1]-12;
        }

        else if(pos[12][2]==0){
                pos[12][2]=1;
                pos[12][0]=pos[0][0]+27;
                pos[12][1]=pos[0][1]-12;
        }

        else if(pos[13][2]==0){
                pos[13][2]=1;
                pos[13][0]=pos[0][0]+27;
                pos[13][1]=pos[0][1]-12;
        }

        else if(pos[14][2]==0){
                pos[14][2]=1;
                pos[14][0]=pos[0][0]+27;
                pos[14][1]=pos[0][1]-12;
        }

        else if(pos[15][2]==0){
                pos[15][2]=1;
                pos[15][0]=pos[0][0]+27;
                pos[15][1]=pos[0][1]-12;
        }

        else if(pos[16][2]==0){
                pos[16][2]=1;
                pos[16][0]=pos[0][0]+27;
                pos[16][1]=pos[0][1]-12;
        }
    }

    ///incriment and deactivate player missles

    if (pos[7][2]==1){

            pos[7][1]=pos[7][1]-3;

            if(pos[7][1]<-20){
              pos[7][2]=0; ///deactivate missile    
            }
    }

    if (pos[8][2]==1){

            pos[8][1]=pos[8][1]-3;

            if(pos[8][1]<-20){
              pos[8][2]=0; ///deactivate missile    
            }
    }

    if (pos[9][2]==1){

            pos[9][1]=pos[9][1]-3;

            if(pos[9][1]<-20){
              pos[9][2]=0; ///deactivate missile    
            }
    }

    if (pos[10][2]==1){

            pos[10][1]=pos[10][1]-3;

            if(pos[10][1]<-20){
              pos[10][2]=0; ///deactivate missile    
            }
    }

    if (pos[11][2]==1){

            pos[11][1]=pos[11][1]-3;

            if(pos[11][1]<-20){
              pos[11][2]=0; ///deactivate missile    
            }
    }

    if (pos[12][2]==1){

            pos[12][1]=pos[12][1]-3;

            if(pos[12][1]<-20){
              pos[12][2]=0; ///deactivate missile    
            }
    }

    if (pos[13][2]==1){

            pos[13][1]=pos[13][1]-3;

            if(pos[13][1]<-20){
              pos[13][2]=0; ///deactivate missile    
            }
    }

    if (pos[14][2]==1){

            pos[14][1]=pos[14][1]-3;

            if(pos[14][1]<-20){
              pos[14][2]=0; ///deactivate missile    
            }
    }

    if (pos[15][2]==1){

            pos[15][1]=pos[15][1]-3;

            if(pos[15][1]<-20){
              pos[15][2]=0; ///deactivate missile    
            }
    }

    if (pos[16][2]==1){

            pos[16][1]=pos[16][1]-3;

            if(pos[16][1]<-20){
              pos[16][2]=0; ///deactivate missile    
            }
    }




    ///Enemy position animation
    if(level==1){

            if(pos[1][2]==1){
                    inc=inc+0.025;
                    pos[1][0]=(int)mapff(sin(inc),-1.0,1.0,9,55);
                    pos[1][1]=(int)mapff(sin(inc),-1.0,1.0,9,160);
            }
            else delay(3); //keeps game speed steady when enemy ships are not being rendered. 


            if(pos[2][2]==1){
                    inc2=inc2+0.030;
                    pos[2][0]=(int)mapff(sin(inc2),-1.0,1.0,105,174);
                    pos[2][1]=(int)mapff(cos(inc2),-1.0,1.0,9,160);
            }
            else delay(3);

    }

    ///////////////////////////////////

    if(level==2){

            if(pos[1][2]==1){
                    inc=inc+0.030;
                    pos[1][0]=(int)mapff(sin(inc),-1.0,1.0,9,174);
                    pos[1][1]=(int)mapff(cos(inc2),-1.0,1.0,9,30);
            }
            else delay(3); //keeps game speed steady when enemy ships are not being rendered. 


            if(pos[2][2]==1){
                    inc2=inc2+0.029;
                    pos[2][0]=(int)mapff(sin(inc2),-1.0,1.0,9,174);
                    pos[2][1]=(int)mapff(sin(inc),-1.0,1.0,80,110);
            }
            else delay(3);


            if(pos[3][2]==1){
                    inc3=inc3+0.035;
                    pos[3][0]=(int)mapff(sin(inc3),-1.0,1.0,9,174);
                    pos[3][1]=(int)mapff(sin(inc),-1.0,1.0,160,170);
            }
            else delay(3);

    }


    if(level==3){

            if(pos[1][2]==1){
                  inc=inc+0.045;
                  pos[1][0]=(int)mapff(sin(inc),-1.0,1.0,9,174);
                  pos[1][1]=(int)mapff(cos(inc),-1.0,1.0,9,40);
            }
            else delay(3); //keeps game speed steady when enemy ships are not being rendered. 


            if(pos[2][2]==1){ 
                  inc2=inc2+0.035;
                  pos[2][0]=(int)mapff(sin(inc2),-1.0,1.0,9,174);
                  pos[2][1]=(int)mapff(sin(inc2),-1.0,1.0,80,120);
            }
            else delay(3);


            if(pos[3][2]==1){
                  inc3=inc3+0.030;
                  pos[3][0]=(int)mapff(sin(inc3),-1.0,1.0,9,174);
                  pos[3][1]=(int)mapff(sin(inc3),-1.0,1.0,160,190);
            }
            else delay(3);
    }

    ///enemy 1 shoots if inline with player. one missile at a time on screen.
    if ((pos[1][0]==pos[0][0]) && (pos[4][2]==0)){

            pos[4][2]=1; ///activate missile
            pos[4][0]=pos[1][0]+27;
            pos[4][1]=pos[1][1]+60;
    }

    if(pos[4][2]==1){

            pos[4][1]=pos[4][1]+3;

            if (pos[4][1]>321){
              pos[4][2]=0; ///deactivate missile
            }
    }


    ///enemy 2 shoots if inline with player. one missile at a time on screen.
    if ((pos[2][0]==pos[0][0]) && (pos[5][2]==0)){

            pos[5][2]=1; ///activate missile
            pos[5][0]=pos[2][0]+27;
            pos[5][1]=pos[2][1]+60;
    }

            if(pos[5][2]==1){
              pos[5][1]=pos[5][1]+3;

              if (pos[5][1]>321){
                pos[5][2]=0; ///deactivate missile
              }
    }


    ///enemy 3 shoots if inline with player. one missile at a time on screen.
    if ((pos[3][0]==pos[0][0]) && (pos[6][2]==0)){

          pos[6][2]=1; ///activate missile
          pos[6][0]=pos[3][0]+27;
          pos[6][1]=pos[3][1]+60;
    }

    if(pos[6][2]==1){

          pos[6][1]=pos[6][1]+3;

          if (pos[6][1]>321){
            pos[6][2]=0; ///deactivate missile
          }
    }

    ////hit detection for player

    if((pos[4][0]>=(pos[0][0]+6))&&(pos[4][0]<=(pos[0][0]+48))&&(pos[4][1]>=(pos[0][1]+10))&&(pos[4][1]<=pos[0][1]+50)){


            pos[0][2]=0;
            pos[17][2]=1;
            pos[17][0]=pos[0][0];
            pos[17][1]=pos[0][1];
            pos[4][2]=0;
            pos[4][0]=-20;
            pos[4][1]=-20;
            life=life-1;

    }


    if((pos[5][0]>=(pos[0][0]+6))&&(pos[5][0]<=(pos[0][0]+48))&&(pos[5][1]>=(pos[0][1]+10))&&(pos[5][1]<=pos[0][1]+50)){


            pos[0][2]=0;
            pos[17][2]=1;
            pos[17][0]=pos[0][0];
            pos[17][1]=pos[0][1];
            pos[5][2]=0;
            pos[5][0]=-20;
            pos[5][1]=-20;
            life=life-1;

    }


    if((pos[6][0]>=(pos[0][0]+6))&&(pos[6][0]<=(pos[0][0]+48))&&(pos[6][1]>=(pos[0][1]+10))&&(pos[6][1]<=pos[0][1]+50)){


            pos[0][2]=0;
            pos[17][2]=1;
            pos[17][0]=pos[0][0];
            pos[17][1]=pos[0][1];
            pos[6][2]=0;
            pos[6][0]=-20;
            pos[6][1]=-20;
            life=life-1;

    }

    /////hit detection for enemy



    ////hit detection for enemy 1 from any missile////////////////////////////////////////////////////////////////////////////////////////////////////
    if((pos[7][2]==1)&&(pos[7][0]>=(pos[1][0]+6))&&(pos[7][0]<=(pos[1][0]+48))&&(pos[7][1]>=(pos[1][1]))&&(pos[7][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[7][2]=0; ///turn missile off and set position to be off screen
            pos[7][0]=-20;
            pos[7][1]=-20;

            ex_count=0;
    }

    if((pos[8][2]==1)&&(pos[8][0]>=(pos[1][0]+6))&&(pos[8][0]<=(pos[1][0]+48))&&(pos[8][1]>=(pos[1][1]))&&(pos[8][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[8][2]=0; ///turn missile off and set position to be off screen
            pos[8][0]=-20;
            pos[8][1]=-20;

            ex_count=0;
    }

    if((pos[9][2]==1)&&(pos[9][0]>=(pos[1][0]+6))&&(pos[9][0]<=(pos[1][0]+48))&&(pos[9][1]>=(pos[1][1]))&&(pos[9][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[9][2]=0; ///turn missile off and set position to be off screen
            pos[9][0]=-20;
            pos[9][1]=-20;

            ex_count=0;
    }

    if((pos[10][2]==1)&&(pos[10][0]>=(pos[1][0]+6))&&(pos[10][0]<=(pos[1][0]+48))&&(pos[10][1]>=(pos[1][1]))&&(pos[10][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[10][2]=0; ///turn missile off and set position to be off screen
            pos[10][0]=-20;
            pos[10][1]=-20;

            ex_count=0;
    }

    if((pos[11][2]==1)&&(pos[11][0]>=(pos[1][0]+6))&&(pos[11][0]<=(pos[1][0]+48))&&(pos[11][1]>=(pos[1][1]))&&(pos[11][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[11][2]=0; ///turn missile off and set position to be off screen
            pos[11][0]=-20;
            pos[11][1]=-20;

            ex_count=0;
    }

    if((pos[12][2]==1)&&(pos[12][0]>=(pos[1][0]+6))&&(pos[12][0]<=(pos[1][0]+48))&&(pos[12][1]>=(pos[1][1]))&&(pos[12][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[12][2]=0; ///turn missile off and set position to be off screen
            pos[12][0]=-20;
            pos[12][1]=-20;

            ex_count=0;
    }

    if((pos[13][2]==1)&&(pos[13][0]>=(pos[1][0]+6))&&(pos[13][0]<=(pos[1][0]+48))&&(pos[13][1]>=(pos[1][1]))&&(pos[13][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[13][2]=0; ///turn missile off and set position to be off screen
            pos[13][0]=-20;
            pos[13][1]=-20;

            ex_count=0;
    }

    if((pos[14][2]==1)&&(pos[14][0]>=(pos[1][0]+6))&&(pos[14][0]<=(pos[1][0]+48))&&(pos[14][1]>=(pos[1][1]))&&(pos[14][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[14][2]=0; ///turn missile off and set position to be off screen
            pos[14][0]=-20;
            pos[14][1]=-20;

            ex_count=0;
    }

    if((pos[15][2]==1)&&(pos[15][0]>=(pos[1][0]+6))&&(pos[15][0]<=(pos[1][0]+48))&&(pos[15][1]>=(pos[1][1]))&&(pos[15][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[15][2]=0; ///turn missile off and set position to be off screen
            pos[15][0]=-20;
            pos[15][1]=-20;

            ex_count=0;
    }

    if((pos[16][2]==1)&&(pos[16][0]>=(pos[1][0]+6))&&(pos[16][0]<=(pos[1][0]+48))&&(pos[16][1]>=(pos[1][1]))&&(pos[16][1]<=pos[1][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[1][0];///positions explosion to where the enemy is
            pos[17][1]=pos[1][1];

            pos[1][2]=0; ///turns off enemy active flag
            pos[1][0]=-60;
            pos[1][1]=-60;

            pos[16][2]=0; ///turn missile off and set position to be off screen
            pos[16][0]=-20;
            pos[16][1]=-20;

            ex_count=0;
    }



    ////hit detection for enemy 2 from any missile///////////////////////////////////////////////////////////////////////////////////////////////////
    if((pos[7][2]==1)&&(pos[7][0]>=(pos[2][0]+6))&&(pos[7][0]<=(pos[2][0]+48))&&(pos[7][1]>=(pos[2][1]))&&(pos[7][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[7][2]=0; ///turn missile off and set position to be off screen
            pos[7][0]=-20;
            pos[7][1]=-20;

            ex_count=0;
    }

    if((pos[8][2]==1)&&(pos[8][0]>=(pos[2][0]+6))&&(pos[8][0]<=(pos[2][0]+48))&&(pos[8][1]>=(pos[2][1]))&&(pos[8][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[8][2]=0; ///turn missile off and set position to be off screen
            pos[8][0]=-20;
            pos[8][1]=-20;

            ex_count=0;
    }

    if((pos[9][2]==1)&&(pos[9][0]>=(pos[2][0]+6))&&(pos[9][0]<=(pos[2][0]+48))&&(pos[9][1]>=(pos[2][1]))&&(pos[9][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[9][2]=0; ///turn missile off and set position to be off screen
            pos[9][0]=-20;
            pos[9][1]=-20;

            ex_count=0;
    }

    if((pos[10][2]==1)&&(pos[10][0]>=(pos[2][0]+6))&&(pos[10][0]<=(pos[2][0]+48))&&(pos[10][1]>=(pos[2][1]))&&(pos[10][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[10][2]=0; ///turn missile off and set position to be off screen
            pos[10][0]=-20;
            pos[10][1]=-20;

            ex_count=0;
    }

    if((pos[11][2]==1)&&(pos[11][0]>=(pos[2][0]+6))&&(pos[11][0]<=(pos[2][0]+48))&&(pos[11][1]>=(pos[2][1]))&&(pos[11][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[11][2]=0; ///turn missile off and set position to be off screen
            pos[11][0]=-20;
            pos[11][1]=-20;

            ex_count=0;
    }

    if((pos[12][2]==1)&&(pos[12][0]>=(pos[2][0]+6))&&(pos[12][0]<=(pos[2][0]+48))&&(pos[12][1]>=(pos[2][1]))&&(pos[12][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[12][2]=0; ///turn missile off and set position to be off screen
            pos[12][0]=-20;
            pos[12][1]=-20;

            ex_count=0;
    }

    if((pos[13][2]==1)&&(pos[13][0]>=(pos[2][0]+6))&&(pos[13][0]<=(pos[2][0]+48))&&(pos[13][1]>=(pos[2][1]))&&(pos[13][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[13][2]=0; ///turn missile off and set position to be off screen
            pos[13][0]=-20;
            pos[13][1]=-20;

            ex_count=0;
    }

    if((pos[14][2]==1)&&(pos[14][0]>=(pos[2][0]+6))&&(pos[14][0]<=(pos[2][0]+48))&&(pos[14][1]>=(pos[2][1]))&&(pos[14][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[14][2]=0; ///turn missile off and set position to be off screen
            pos[14][0]=-20;
            pos[14][1]=-20;

            ex_count=0;
    }

    if((pos[15][2]==1)&&(pos[15][0]>=(pos[2][0]+6))&&(pos[15][0]<=(pos[2][0]+48))&&(pos[15][1]>=(pos[2][1]))&&(pos[15][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[15][2]=0; ///turn missile off and set position to be off screen
            pos[15][0]=-20;
            pos[15][1]=-20;

            ex_count=0;
    }

    if((pos[16][2]==1)&&(pos[16][0]>=(pos[2][0]+6))&&(pos[16][0]<=(pos[2][0]+48))&&(pos[16][1]>=(pos[2][1]))&&(pos[16][1]<=pos[2][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[2][0];///positions explosion to where the enemy is
            pos[17][1]=pos[2][1];

            pos[2][2]=0; ///turns off enemy active flag
            pos[2][0]=-60;
            pos[2][1]=-60;

            pos[16][2]=0; ///turn missile off and set position to be off screen
            pos[16][0]=-20;
            pos[16][1]=-20;

            ex_count=0;
    }



    ////hit detection for enemy 3 from any missile
    if((pos[7][2]==1)&&(pos[7][0]>=(pos[3][0]+6))&&(pos[7][0]<=(pos[3][0]+48))&&(pos[7][1]>=(pos[3][1]))&&(pos[7][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[7][2]=0; ///turn missile off and set position to be off screen
            pos[7][0]=-20;
            pos[7][1]=-20;

            ex_count=0;
    }

    if((pos[8][2]==1)&&(pos[8][0]>=(pos[3][0]+6))&&(pos[8][0]<=(pos[3][0]+48))&&(pos[8][1]>=(pos[3][1]))&&(pos[8][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[8][2]=0; ///turn missile off and set position to be off screen
            pos[8][0]=-20;
            pos[8][1]=-20;

            ex_count=0;
    }

    if((pos[9][2]==1)&&(pos[9][0]>=(pos[3][0]+6))&&(pos[9][0]<=(pos[3][0]+48))&&(pos[9][1]>=(pos[3][1]))&&(pos[9][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[9][2]=0; ///turn missile off and set position to be off screen
            pos[9][0]=-20;
            pos[9][1]=-20;

            ex_count=0;
    }

    if((pos[10][2]==1)&&(pos[10][0]>=(pos[3][0]+6))&&(pos[10][0]<=(pos[3][0]+48))&&(pos[10][1]>=(pos[3][1]))&&(pos[10][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[10][2]=0; ///turn missile off and set position to be off screen
            pos[10][0]=-20;
            pos[10][1]=-20;

            ex_count=0;
    }

    if((pos[11][2]==1)&&(pos[11][0]>=(pos[3][0]+6))&&(pos[11][0]<=(pos[3][0]+48))&&(pos[11][1]>=(pos[3][1]))&&(pos[11][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[11][2]=0; ///turn missile off and set position to be off screen
            pos[11][0]=-20;
            pos[11][1]=-20;

            ex_count=0;
    }

    if((pos[12][2]==1)&&(pos[12][0]>=(pos[3][0]+6))&&(pos[12][0]<=(pos[3][0]+48))&&(pos[12][1]>=(pos[3][1]))&&(pos[12][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[12][2]=0; ///turn missile off and set position to be off screen
            pos[12][0]=-20;
            pos[12][1]=-20;

            ex_count=0;
    }

    if((pos[13][2]==1)&&(pos[13][0]>=(pos[3][0]+6))&&(pos[13][0]<=(pos[3][0]+48))&&(pos[13][1]>=(pos[3][1]))&&(pos[13][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[13][2]=0; ///turn missile off and set position to be off screen
            pos[13][0]=-20;
            pos[13][1]=-20;

            ex_count=0;
    }

    if((pos[14][2]==1)&&(pos[14][0]>=(pos[3][0]+6))&&(pos[14][0]<=(pos[3][0]+48))&&(pos[14][1]>=(pos[3][1]))&&(pos[14][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[14][2]=0; ///turn missile off and set position to be off screen
            pos[14][0]=-20;
            pos[14][1]=-20;

            ex_count=0;
    }

    if((pos[15][2]==1)&&(pos[15][0]>=(pos[3][0]+6))&&(pos[15][0]<=(pos[3][0]+48))&&(pos[15][1]>=(pos[3][1]))&&(pos[15][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[15][2]=0; ///turn missile off and set position to be off screen
            pos[15][0]=-20;
            pos[15][1]=-20;

            ex_count=0;
    }

    if((pos[16][2]==1)&&(pos[16][0]>=(pos[3][0]+6))&&(pos[16][0]<=(pos[3][0]+48))&&(pos[16][1]>=(pos[3][1]))&&(pos[16][1]<=pos[3][1]+35)){

            pos[17][2]=1; ///turns on explosion flag
            pos[17][0]=pos[3][0];///positions explosion to where the enemy is
            pos[17][1]=pos[3][1];

            pos[3][2]=0; ///turns off enemy active flag
            pos[3][0]=-60;
            pos[3][1]=-60;

            pos[16][2]=0; ///turn missile off and set position to be off screen
            pos[16][0]=-20;
            pos[16][1]=-20;

            ex_count=0;
    }


    //Draw Life level

    tft.setCursor(14,310);
    tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
    tft.print("Life:");
    tft.println(life);

    //Draw missiles
    if(pos[4][2]==1){
    
      M1.draw(tft,pos[4][0],pos[4][1]); 

    }

    if(pos[5][2]==1){
      M2.draw(tft,pos[5][0],pos[5][1]);  
    }

    if(pos[6][2]==1){
      M3.draw(tft,pos[6][0],pos[6][1]);     
      }
      
    if(pos[7][2]==1){
      M4.draw(tft,pos[7][0],pos[7][1]);     
      }


    if(pos[8][2]==1){
      M5.draw(tft,pos[8][0],pos[8][1]);     
      }

    if(pos[9][2]==1){
      M6.draw(tft,pos[9][0],pos[9][1]);     
      }

    if(pos[10][2]==1){
      M7.draw(tft,pos[10][0],pos[10][1]);     
      }

    if(pos[11][2]==1){
      M8.draw(tft,pos[11][0],pos[11][1]);     
      }

    if(pos[12][2]==1){
      M9.draw(tft,pos[12][0],pos[12][1]);     
      }

    if(pos[13][2]==1){
      M10.draw(tft,pos[13][0],pos[13][1]);     
      }

    if(pos[14][2]==1){
      M11.draw(tft,pos[14][0],pos[14][1]);     
      }

    if(pos[15][2]==1){
      M12.draw(tft,pos[15][0],pos[15][1]);     
      }   

    if(pos[16][2]==1){
      M13.draw(tft,pos[16][0],pos[16][1]);     
      }                


      if(pos[0][2]==1){
        P1.draw(tft,pos[0][0],pos[0][1]);   
      }



    //Draw explosion
    if((pos[17][2]==1) && (ex_count<10)){
        ex_count=ex_count+1;
        EX.draw(tft,pos[17][0],pos[17][1]);
        if(ex_count>=10) {
          tft.fillRect(pos[17][0], pos[17][1], 64, 64,ILI9341_BLACK );
          pos[17][2]=0;
          pos[0][2]=1;
          ex_count=0;
          tft.fillRect(30, 310, 24, 12,ILI9341_BLACK );
          }
    }

    //Draw enemy
    E1.draw(tft,pos[1][0],pos[1][1]);
    E2.draw(tft,pos[2][0],pos[2][1]);   
    E3.draw(tft,pos[3][0],pos[3][1]); 
    


    //Player loses game

    if(life<=0){

        tft.fillRect(12, 12, 216, 150,ILI9341_BLACK );////print New Level
        tft.setCursor(40,50);
        tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(3);
        tft.println("You Lose!");

            while (1){
              delay(10000);
            }
      }



    /////Player wins a level
    if(pos[1][2]==0 && pos[2][2]==0 && pos[3][2]==0){
      
        level=level+1;///level up

        if(level==4){

              tft.fillRect(12, 12, 216, 150,ILI9341_BLACK );////print New Level
              tft.setCursor(40,50);
              tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(3);
              tft.println("You Win!");

              tft.setCursor(20,100);
              tft.print("Time: ");
              tft.println((float)((millis()-clockk)/1000.00));


                while (1){
                    delay(10000);
                }
            }     


        tft.fillRect(12, 12, 216, 75,ILI9341_BLACK );////print New Level
        tft.setCursor(40,50);
        tft.setTextColor(ILI9341_YELLOW);  tft.setTextSize(4);
        tft.print("Level ");
        tft.println(level);
        delay(4000);
        tft.fillRect(12, 12, 216, 150,ILI9341_BLACK );

              if(level==2){
                  pos[1][2]=1;
                  pos[2][2]=1;
                  pos[3][2]=1;
              }

              if(level==3){
                  pos[1][2]=1;
                  pos[2][2]=1;
                  pos[3][2]=1;
              }
      }


}