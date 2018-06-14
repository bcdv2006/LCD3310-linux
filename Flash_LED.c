#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define OUT 0
#define IN 1
#define LOW 0
#define HIGH 1
int pinMode(unsigned int pin, char Mode);
int digitalWrite(unsigned int pin, char Value);
void delayms(unsigned int time);
void main()
{
        //int fp = open("/sys/class/gpio/gpio102/value",O_RDWR);
/*
        while(1)
        {
                write(fp,"0",1);
                usleep(500000);
                write(fp,"1",1);
                usleep(500000);
        }
        */
        pinMode(20,IN);
        while(1){
        
            digitalWrite(20,HIGH); 
            printf("LED ON");
            delayms(500);
            digitalWrite(20,LOW);
            printf("LED OFF");
            delayms(500);  

        }
       
}

int pinMode(unsigned int pin, char Mode)
{
        int fp;
        switch(pin){
                case 16:
                        fp = open("/gpio/pin16/direction",O_RDWR);
                       break;
                case 17:
                         fp = open("/gpio/pin17/direction",O_RDWR); 
                        break;
                case 18:
                         fp = open("/gpio/pin18/direction",O_RDWR);
                        break;
                case 19:
                         fp = open("/gpio/pin19/direction",O_RDWR);
                        break;
                case 20:
                         fp = open("/gpio/pin20/direction",O_RDWR);
                        break;
                case 21:
                         fp = open("/gpio/pin21/direction",O_RDWR);
                        break;
                case 22:
                         fp = open("/gpio/pin22/direction",O_RDWR);
                        break;
                case 23:
                         fp = open("/gpio/pin23/direction",O_RDWR);
                        break;
                case 24:
                        fp = open("/gpio/pin24/direction",O_RDWR);
                       break;
                case 25:
                         fp = open("/gpio/pin25/direction",O_RDWR); 
                        break;
                case 26:
                         fp = open("/gpio/pin26/direction",O_RDWR);
                        break;
                case 27:
                         fp = open("/gpio/pin27/direction",O_RDWR);
                        break;
                case 28:
                         fp = open("/gpio/pin28/direction",O_RDWR);
                        break;
                case 29:
                         fp = open("/gpio/pin29/direction",O_RDWR);
                        break;
                case 30:
                         fp = open("/gpio/pin30/direction",O_RDWR);
                        break;
                case 31:
                         fp = open("/gpio/pin31/direction",O_RDWR);
                        break;
                case 32:
                        fp = open("/gpio/pin32/direction",O_RDWR);
                       break;
                case 33:
                         fp = open("/gpio/pin33/direction",O_RDWR); 
                        break;
                case 34:
                         fp = open("/gpio/pin34/direction",O_RDWR);
                        break;
                case 35:
                         fp = open("/gpio/pin35/direction",O_RDWR);
                        break;
                case 36:
                         fp = open("/gpio/pin36/direction",O_RDWR);
                        break;
                case 37:
                         fp = open("/gpio/pin37/direction",O_RDWR);
                        break;
                case 38:
                         fp = open("/gpio/pin38/direction",O_RDWR);
                        break;
                case 39:
                         fp = open("/gpio/pin39/direction",O_RDWR);
                        break;        
                case 40:
                        fp = open("/gpio/pin40/direction",O_RDWR);
                        break;
                case 41:
                         fp = open("/gpio/pin41/direction",O_RDWR); 
                        break;
                case 42:
                         fp = open("/gpio/pin42/direction",O_RDWR);
                        break;
                case 43:
                         fp = open("/gpio/pin43/direction",O_RDWR);
                        break;
                case 44:
                         fp = open("/gpio/pin44/direction",O_RDWR);
                        break;
                case 45:
                         fp = open("/gpio/pin45/direction",O_RDWR);
                        break;
                case 46:
                         fp = open("/gpio/pin46/direction",O_RDWR);
                        break;
                case 47:
                         fp = open("/gpio/pin47/direction",O_RDWR);
                        break;
                default:
                        printf("UNKOWN pin\n");
                        return -1;
                
        }
        if(Mode == 0){
                write(fp,"OUT",3);
        }
        else if(Mode == 1){
                write(fp,"IN",3);
        }
        else {
                printf("unknow mode\n.can't set pin %d\n",pin);
                return -1;
        }
        return 1;
}
int digitalWrite(unsigned int pin, char Value)
{
        int fp;
        switch(pin){
                case 16:
                        fp = open("/gpio/pin16/value",O_RDWR);
                       break;
                case 17:
                         fp = open("/gpio/pin17/value",O_RDWR); 
                        break;
                case 18:
                         fp = open("/gpio/pin18/value",O_RDWR);
                        break;
                case 19:
                         fp = open("/gpio/pin19/value",O_RDWR);
                        break;
                case 20:
                         fp = open("/gpio/pin20/value",O_RDWR);
                        break;
                case 21:
                         fp = open("/gpio/pin21/value",O_RDWR);
                        break;
                case 22:
                         fp = open("/gpio/pin22/value",O_RDWR);
                        break;
                case 23:
                         fp = open("/gpio/pin23/value",O_RDWR);
                        break;
                case 24:
                        fp = open("/gpio/pin24/value",O_RDWR);
                       break;
                case 25:
                         fp = open("/gpio/pin25/value",O_RDWR); 
                        break;
                case 26:
                         fp = open("/gpio/pin26/value",O_RDWR);
                        break;
                case 27:
                         fp = open("/gpio/pin27/value",O_RDWR);
                        break;
                case 28:
                         fp = open("/gpio/pin28/value",O_RDWR);
                        break;
                case 29:
                         fp = open("/gpio/pin29/value",O_RDWR);
                        break;
                case 30:
                         fp = open("/gpio/pin30/value",O_RDWR);
                        break;
                case 31:
                         fp = open("/gpio/pin31/value",O_RDWR);
                        break;
                case 32:
                        fp = open("/gpio/pin32/value",O_RDWR);
                       break;
                case 33:
                         fp = open("/gpio/pin33/value",O_RDWR); 
                        break;
                case 34:
                         fp = open("/gpio/pin34/value",O_RDWR);
                        break;
                case 35:
                         fp = open("/gpio/pin35/value",O_RDWR);
                        break;
                case 36:
                         fp = open("/gpio/pin36/value",O_RDWR);
                        break;
                case 37:
                         fp = open("/gpio/pin37/value",O_RDWR);
                        break;
                case 38:
                         fp = open("/gpio/pin38/value",O_RDWR);
                        break;
                case 39:
                         fp = open("/gpio/pin39/value",O_RDWR);
                        break;        
                case 40:
                        fp = open("/gpio/pin40/value",O_RDWR);
                        break;
                case 41:
                         fp = open("/gpio/pin41/value",O_RDWR); 
                        break;
                case 42:
                         fp = open("/gpio/pin42/value",O_RDWR);
                        break;
                case 43:
                         fp = open("/gpio/pin43/value",O_RDWR);
                        break;
                case 44:
                         fp = open("/gpio/pin44/value",O_RDWR);
                        break;
                case 45:
                         fp = open("/gpio/pin45/value",O_RDWR);
                        break;
                case 46:
                         fp = open("/gpio/pin46/value",O_RDWR);
                        break;
                case 47:
                         fp = open("/gpio/pin47/value",O_RDWR);
                        break;
                default:
                        printf("UNKOWN pin\n");
                        return -1;
                
        }
         if(Value == LOW){
                write(fp,"0",2);
        }
        else if(Value == HIGH){
                write(fp,"1",2);
        }
        else {
                printf("unknow mode\n.can't set pin %d\n",pin);
                return -1;
        }
        return 1;
}
void delayms(unsigned int time)
{
        usleep(time*1000);
}