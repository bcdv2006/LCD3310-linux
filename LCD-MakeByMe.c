#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1

#define _RST 24
#define _CE  25
#define _DC  26
#define _DIN 27
#define _CLK 28
#define _BL  30

unsigned char font5[][5] = 
{ 
    { 0x00, 0x00, 0x00, 0x00, 0x00 },  // sp 
    { 0x00, 0x00, 0x2f, 0x00, 0x00 },   // ! 
    { 0x00, 0x07, 0x00, 0x07, 0x00 },   // " 
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // # 
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $ 
    { 0xc4, 0xc8, 0x10, 0x26, 0x46 },   // % 
    { 0x36, 0x49, 0x55, 0x22, 0x50 },   // & 
    { 0x00, 0x05, 0x03, 0x00, 0x00 },   // ' 
    { 0x00, 0x1c, 0x22, 0x41, 0x00 },   // ( 
    { 0x00, 0x41, 0x22, 0x1c, 0x00 },   // ) 
    { 0x14, 0x08, 0x3E, 0x08, 0x14 },   // * 
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },   // + 
    { 0x00, 0x00, 0x50, 0x30, 0x00 },   // , 
    { 0x10, 0x10, 0x10, 0x10, 0x10 },   // - 
    { 0x00, 0x60, 0x60, 0x00, 0x00 },   // . 
    { 0x20, 0x10, 0x08, 0x04, 0x02 },   // / 
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0 
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1 
    { 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2 
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3 
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4 
    { 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5 
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6 
    { 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7 
    { 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8 
    { 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9 
    { 0x00, 0x36, 0x36, 0x00, 0x00 },   // : 
    { 0x00, 0x56, 0x36, 0x00, 0x00 },   // ; 
    { 0x08, 0x14, 0x22, 0x41, 0x00 },   // < 
    { 0x14, 0x14, 0x14, 0x14, 0x14 },   // = 
    { 0x00, 0x41, 0x22, 0x14, 0x08 },   // > 
    { 0x02, 0x01, 0x51, 0x09, 0x06 },   // ? 
    { 0x32, 0x49, 0x59, 0x51, 0x3E },   // @ 
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A 
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B 
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C 
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D 
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E 
    { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F 
    { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G 
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H 
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I 
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J 
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K 
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L 
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M 
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N 
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O 
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P 
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q 
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R 
    { 0x46, 0x49, 0x49, 0x49, 0x31 },   // S 
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T 
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U 
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V 
    { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W 
    { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X 
    { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y 
    { 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z 
    { 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [ 
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55 
    { 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ] 
    { 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^ 
    { 0x40, 0x40, 0x40, 0x40, 0x40 },   // _ 
    { 0x00, 0x01, 0x02, 0x04, 0x00 },   // ' 
    { 0x20, 0x54, 0x54, 0x54, 0x78 },   // a 
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b 
    { 0x38, 0x44, 0x44, 0x44, 0x20 },   // c 
    { 0x38, 0x44, 0x44, 0x48, 0x7F },   // d 
    { 0x38, 0x54, 0x54, 0x54, 0x18 },   // e 
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f 
    { 0x0C, 0x52, 0x52, 0x52, 0x3E },   // g 
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h 
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i 
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j 
    { 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k 
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l 
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m 
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n 
    { 0x38, 0x44, 0x44, 0x44, 0x38 },   // o 
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p 
    { 0x08, 0x14, 0x14, 0x18, 0x7C },   // q 
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r 
    { 0x48, 0x54, 0x54, 0x54, 0x20 },   // s 
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t 
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u 
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v 
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w 
    { 0x44, 0x28, 0x10, 0x28, 0x44 },   // x 
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y 
    { 0x44, 0x64, 0x54, 0x4C, 0x44 }    // z 
};

int pinMode(unsigned int pin, char Mode);
int digitalWrite(unsigned int pin, char Mode);
void Ghi_du_lieu(unsigned char du_lieu, unsigned char Chon_du_lieu);
void Khoi_tao_lcd(void);
void Toa_do(unsigned char x, unsigned char y);
void In_ky_tu(unsigned char x,unsigned char y,char dat);
void In_chuoi_ky_tu(unsigned char x,unsigned char y,char *s);
void Xoa_trang(void);

int initIO();

int main()
{
    initIO();
    Khoi_tao_lcd();
    Xoa_trang();
    In_chuoi_ky_tu(1,5,"Hi.! Nhan");
}
//////////////////// Xoa LCD ///////////////////////////////////	
void Xoa_trang(void)     
		{  
			unsigned char t;  
			unsigned char k;  
			Toa_do(0,0);  
      for(t=0;t<6;t++)  
{    
for(k=0;k<84;k++)   
	{     
		Ghi_du_lieu(0x00,1);        
		}   
		} 
		}

//////////////////// In chuoi ky tu ///////////////////////////////////
void In_chuoi_ky_tu(unsigned char x,unsigned char y,char *s) 
{    
	while(*s)     
		{       
			In_ky_tu(x,y,*s);      
			s++;      
			x += 6; // Vi chu co do rong la 5 nên ta dih 6 de tao dan cah chu    
			} 
			}

//////////////////// In ky tu ///////////////////////////////////
void In_ky_tu(unsigned char x,unsigned char y,char dat) 
			{
	unsigned char v;
	if((dat >= 0x20) && (dat <= 0x7a)){
		dat=dat-32;
			Toa_do(x,y);
		for(v=0;v<5;v++)
			Ghi_du_lieu(font5[dat][v],1);
	}
}

//////////////////// Ham dinh vi vi tri ///////////////////////////////////	
void Toa_do(unsigned char x, unsigned char y) 
{ 
	Ghi_du_lieu(0x80|x, 0);    
	Ghi_du_lieu(0x40|y, 0); 
	}

////////////////////Khoi tao GLCD///////////////////////////////////
void Khoi_tao_lcd(void) 
{ 
// Ham khoi tao dua tren datasheet de chinh sua cho hop ly
    digitalWrite(_RST,LOW);
    digitalWrite(_RST,HIGH);      
	Ghi_du_lieu(0x21, 0);     // Mo che do o rong
	Ghi_du_lieu(0x80+45, 0);  // Set do tuong phan
	Ghi_du_lieu(0x04+0, 0);   // Set thong so nhiet
	Ghi_du_lieu(0x10+4, 0);   // Set thong so BIAS
	Ghi_du_lieu(0x20, 0);     // Dong che do o rong
	Ghi_du_lieu(0x0C, 0);     // Hien thi binh thuong ,0x0D Am ban
}
//////////////////// Ham ghi du lieu ///////////////////////////////////	
void Ghi_du_lieu(unsigned char du_lieu, unsigned char Chon_du_lieu) 
{    
	unsigned char i;   
	digitalWrite(_CE,LOW); 
	if (Chon_du_lieu == 0)digitalWrite(_DC,LOW);           
	else digitalWrite(_DC,HIGH);  
	for(i=0;i<8;i++) 
	{         
		if(du_lieu&0x80) digitalWrite(_DIN,HIGH);       
    else digitalWrite(_DIN,LOW);       
      digitalWrite(_CLK,LOW);     
      du_lieu = du_lieu << 1;       
      digitalWrite(_CLK,HIGH);    
      usleep(500);
  }     
  digitalWrite(_CE,HIGH);
}

int initIO()
{
    pinMode(_RST,OUTPUT);
    pinMode(_CE,OUTPUT);
    pinMode(_DC,OUTPUT);
    pinMode(_DIN,OUTPUT);
    pinMode(_CLK,OUTPUT);
    pinMode(_BL,OUTPUT);


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
        if(Mode == OUTPUT){
                write(fp,"OUT",3);
        }
        else if(Mode == INPUT){
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
