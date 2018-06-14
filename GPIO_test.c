#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1

int pinMode(unsigned int pin, char Mode);
int digitalWrite(unsigned int pin, char Value);
int fd24,fd25,fd26,fd27,fd28,fd29,fd30;
int fo24,fo25,fo26,fo27,fo28,fo29,fo30;

int main()
{
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

    pinMode(30,OUTPUT);

    while(1){
        digitalWrite(30,LOW);
        usleep(500000);
        digitalWrite(30,HIGH);
        usleep(500000);
        printf("--------\n");
    }
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