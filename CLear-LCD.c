#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RES 35

#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1


#define DELETE 0
#define MIRROR 1
#define NO_MIRROR 0
#define CLEAR 0
#define BLACK 1
#define WHITE 0
#define black 1
#define  white 0
#define LCDWIDTH 84
#define LCDHEIGHT 48
#define X_MAX 83
#define Y_MAX 47

#define CMD_DISPLAY_OFF   0xAE
#define CMD_DISPLAY_ON    0xAF


#define PCD8544_POWERDOWN 0x04
#define PCD8544_ENTRYMODE 0x02
#define PCD8544_EXTENDEDINSTRUCTION 0x01

#define PCD8544_DISPLAYBLANK 0x0
#define PCD8544_DISPLAYNORMAL 0x4
#define PCD8544_DISPLAYALLON 0x1
#define PCD8544_DISPLAYINVERTED 0x5

#define CMD_SET_DISP_NORMAL 0xC

#define MASK_Y_ADDRESS 0x40
#define MASK_X_ADDRESS 0x80

#define CMD_SET_DISP_REVERSE 0xD

#define CMD_SET_DISP_REVERSE 0xD

// H = 0
#define PCD8544_FUNCTIONSET 0x20
#define PCD8544_DISPLAYCONTROL 0x08
#define PCD8544_SETYADDR 0x40
#define PCD8544_SETXADDR 0x80

// H = 1
#define PCD8544_SETTEMP 0x04
#define PCD8544_SETBIAS 0x10
#define PCD8544_SETVOP 0x80
#define PCD8544_SPI_CLOCK_DIV SPI_CLOCK_DIV4

#define _rst  24
#define _cs   25
#define _dc   26
#define _din  27
#define _clk  28 
#define _bl   30

int pinMode(unsigned int pin, char Mode);
int digitalWrite(unsigned int pin, char Value);
int delayMicroseconds(unsigned int time);

char buffer_PCD8544[504] = {};
char clear[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int bird_high[]={112,136,776,1292,1290,2194,2145,2049,2333,2723,1345,1345,1370,1348,1400,832,128};
char bird[] = { 112, 136, 8, 12, 10, 146, 97, 1, 29, 163, 65, 65, 90, 68, 120, 64, 128,
                  0,   0, 3,  5,  5,   8,  8, 8,  9,  10,  5,  5,  5,  5,   5,  3,   0}; 


unsigned char backgroud [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0x60, 0x38, 0x0C, 0x04, 0x06, 0x02, 0x02,
0x03, 0x01, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x80, 0x80, 0x80, 0x60, 0x30, 0x18,
0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x02, 0x06, 0x0C, 0x18, 0x30,
0x60, 0x40, 0x40, 0x60, 0x30, 0x10, 0x18, 0x08, 0x08, 0x04, 0x04, 0x06, 0x03, 0x01, 0x01, 0x01,
0x03, 0x06, 0x0C, 0x18, 0x10, 0x30, 0x20, 0x60, 0x40, 0x40, 0x40, 0x40, 0x20, 0x30, 0x10, 0x08,
0x0C, 0x06, 0x03, 0x03, 0x06, 0x0C, 0x18, 0x60, 
};


////////////////////////////////////////////////////////
char i=0;char j = 0;

////////////////////////////////////////////////////////

void send_DATA(char DATA);
void send_COMMAND(char COMMAND);
void LCD_init();
void draw_pixel(char col, char row, char data);
void picture(char _xsize, char _xpos, char _ypos, char _ysize, char *pic);
void gotoXY_pixel(char x, char y);
void show_bird(char _xsize, char _ysize, char _xpos, char _ypos, char num, int *object);
void show_backgroud();
int fd24,fd25,fd26,fd27,fd28,fd29,fd30;
int fo24,fo25,fo26,fo27,fo28,fo29,fo30;
void main(void)
{
        int i = 0;
        int j = 0;
    fd24 = open("/gpio/pin24/direction",O_RDWR);
    fd25 = open("/gpio/pin25/direction",O_RDWR);
    fd26 = open("/gpio/pin26/direction",O_RDWR);
    fd27 = open("/gpio/pin27/direction",O_RDWR);
    fd28 = open("/gpio/pin28/direction",O_RDWR);
    fd29 = open("/gpio/pin29/direction",O_RDWR);
    fd30 = open("/gpio/pin30/direction",O_RDWR);

    fo24 = open("/gpio/pin24/value",O_RDWR);
    fo25 = open("/gpio/pin25/value",O_RDWR);
    fo26 = open("/gpio/pin26/value",O_RDWR);
    fo27 = open("/gpio/pin27/value",O_RDWR);
    fo28 = open("/gpio/pin28/value",O_RDWR);
    fo29 = open("/gpio/pin29/value",O_RDWR);
    fo30 = open("/gpio/pin30/value",O_RDWR);
        LCD_init();

        printf("modify v2.13\n");

        gotoXY_pixel(0,0);
        for(i=0;i<504;i++){
                send_DATA(0);
                printf("cleared <i = %d>\n",i);
                usleep(500);
        }
        printf("cleared creen\n");
/*
        gotoXY_pixel(0,0);
        for(i=0;i<34;i++){
                send_DATA(bird[i]);
                printf("i = %d, <%d>\n",i,bird[i]);
                usleep(100000);
        }
        gotoXY_pixel(0,1);
        for(i=0;i<34;i++){
                send_DATA(bird[i]);
                printf("i = %d, <%d>\n",i,bird[i]);
                usleep(100000);
        }
*/     
        digitalWrite(_bl,LOW);
       printf("draw pixel\n");
       
  
}
void send_DATA(char DATA)
{
  char i = 0;
  digitalWrite(_cs,LOW);
  digitalWrite(_dc,HIGH);
  for(i=0;i<8;i++){
    if(DATA&(0x80))digitalWrite(_din,HIGH);
    else digitalWrite(_din,LOW);
    digitalWrite(_clk,HIGH);
    usleep(100);
    DATA = DATA << 1;
    digitalWrite(_clk,LOW);
    usleep(100);
  }
  digitalWrite(_cs,HIGH);

}
void send_COMMAND(char COMMAND)
{
  
  digitalWrite(_cs,LOW);
  digitalWrite(_dc,LOW);
  for(i = 0;i<8;i++){
    if((COMMAND&(0x80>>i)) == (0x80>>i))digitalWrite(_din,HIGH);
    else digitalWrite(_din,LOW);
  digitalWrite(_clk,HIGH);
    delayMicroseconds(1);
    digitalWrite(_clk,LOW);
    delayMicroseconds(1);
  }
  digitalWrite(_cs,HIGH);
}
void LCD_init() 
{
  pinMode(_rst, OUTPUT);
  pinMode(_cs, OUTPUT);
  pinMode(_din,OUTPUT);
  pinMode(_clk,OUTPUT);
  pinMode(_dc, OUTPUT);
  pinMode(_bl, OUTPUT);

  //digitalWrite(_rst,LOW);      
  digitalWrite(_bl,HIGH);
  digitalWrite(_rst,HIGH);       
  digitalWrite(_cs,LOW);

  send_COMMAND(0x21);
  send_COMMAND(0x80|RES);
  send_COMMAND(0x04+0);
  send_COMMAND(0x10+4);
  send_COMMAND(0x20);
  send_COMMAND(0x0C);

  digitalWrite(_cs,HIGH);
}
void draw_pixel(char col, char row, char data)
{
  int i = 0;
  if(col > 83)col = 83;
  if(row >5)row = 5;

  buffer_PCD8544[(row*84)+col] = data;

  for(i = 0; i<504;i++){
    send_DATA(buffer_PCD8544[i]);
  }  
}
void picture(char _xsize, char _ysize, char _xpos, char _ypos, char *pic  )
{
  char x = 0, y= 0;
  for(y = 0; y<_ysize; y++){
    for(x = 0; x <_xsize; x++){
      gotoXY_pixel(x+_xpos,y+_ypos);
      send_DATA(*(pic + x + (y*_xsize)));
    }
  }
}
void gotoXY_pixel(char x, char y)
{
  /////////////////////SET Y-ADDRESS OF RAM/////////////////
  digitalWrite(_cs,LOW);
  digitalWrite(_dc,LOW);
  if(y<0)y=0;
  if(y>5)y=5;
  send_COMMAND(MASK_Y_ADDRESS|y);
  digitalWrite(_cs,HIGH);
  /////////////////////SET X-ADDRESS OF RAM/////////////////
  digitalWrite(_cs,LOW);
  digitalWrite(_dc,LOW);
  if(x<0)x=0;
  if(x>83)x=83;
  send_COMMAND(MASK_X_ADDRESS|x);
  digitalWrite(_cs,HIGH);
}
void show_bird(char _xsize, char _ysize, char _xpos, char _ypos,char num, int *object)
{
  char pos = 0;
  int temp = 0;
  for(pos = 0; pos<_xsize; pos++){
  temp = *(object+pos);
  temp = temp<<num;
  gotoXY_pixel(_xpos+pos,0+_ypos);
  send_DATA((char)(temp));
  gotoXY_pixel(_xpos+pos, 1+_ypos);
  send_DATA((char)(((temp)& 0xff00)>>8));
  }
}
void show_backgroud()
{   
  int i = 0;
   gotoXY_pixel(5,0);
   for(i = 419;i<504;i++){ 
     send_DATA(backgroud[i]);
   }
   for(i=419;i<503;i++){
    backgroud[i]= backgroud[i+1];
   }
   backgroud[503]=backgroud[419];
   delayMicroseconds(10);
  
}

int pinMode(unsigned int pin, char Mode)
{
        switch(pin){
                case 24:
                        if(Mode == OUTPUT){
                                write(fd24,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd24,"IN",3);
                        }
                        break;
                case 25:
                        if(Mode == OUTPUT){
                                write(fd25,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd25,"IN",3);
                        }
                        
                        break;
                case 26:
                        if(Mode == OUTPUT){
                                write(fd26,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd26,"IN",3);
                        }
                        
                        break;
                case 27:
                        if(Mode == OUTPUT){
                                write(fd27,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd27,"IN",3);
                        }
                        
                        break;
                case 28:
                        if(Mode == OUTPUT){
                                write(fd28,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd28,"IN",3);
                        }
                        
                        break;
                case 29:
                        if(Mode == OUTPUT){
                                write(fd29,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd29,"IN",3);
                        }
                        
                        break;
                case 30:
                        if(Mode == OUTPUT){
                                write(fd30,"OUT",3);
                        }
                        else if(Mode == INPUT){
                        write(fd30,"IN",3);
                        }
                        
                        break;
                
                default:
                        printf("UNKOWN pin\n");
                        return -1;
        }
        
        return 1;
}
int digitalWrite(unsigned int pin, char Value)
{
        switch(pin){
                
                case 24:
                        if(Value == LOW){
                                write(fo24,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo24,"1",2);
                        }
                       break;
                case 25:
                        if(Value == LOW){
                                write(fo25,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo25,"1",2);
                        }
                        break;
                case 26:
                        if(Value == LOW){
                                write(fo26,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo26,"1",2);
                        }
                        break;
                case 27:
                        if(Value == LOW){
                                write(fo27,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo27,"1",2);
                        }
                        break;
                case 28:
                        if(Value == LOW){
                                write(fo28,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo28,"1",2);
                        }
                        break;
                case 29:
                        if(Value == LOW){
                                write(fo29,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo29,"1",2);
                        }
                        break;
                case 30:
                        if(Value == LOW){
                                write(fo30,"0",2);
                        }
                        else if(Value == HIGH){
                                write(fo30,"1",2);
                        }
                        break;
                
                default:
                        printf("UNKOWN pin\n");
                        return -1;
                
        }
        return 1;
}
int delayMicroseconds(unsigned int time)
{
  usleep(time*1000);
}