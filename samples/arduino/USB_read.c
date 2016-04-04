#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

int L_C = 0;
int R_C = 0;


int init_serial()
{
  int fd;
  struct termios toptions;

  /* open serial port */
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  printf("fd opened as %i\n", fd);
  
  /* wait for the Arduino to reboot */
  usleep(3500000);
  
  /* get current serial port settings */
  tcgetattr(fd, &toptions);
  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B9600);
  cfsetospeed(&toptions, B9600);
  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  /* Canonical mode */
  toptions.c_lflag |= ICANON;
  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);

  return fd;
}
void start_serial(char* buf, int fd){
  /* Send byte to trigger Arduino to send string back */
  write(fd, "0", 1);
}
void read_serial(char* buf, int fd){

int n;
  n = read(fd, buf, 1);
  buf[n] = 0;
  /* insert terminating zero in the string */
  printf("%i bytes read, buffer contains: %s\n", n, buf);
  //click = strtol(buf,pEnd,10);
	if(isalpha(buf[0])){

		int str_L = strcmp(buf, "L");
		if(str_L == 0){

			system("xdotool click 1");
		}
		int str_L_Hold = strcmp(buf, "l");
		if(str_L_Hold == 0){

			system("xdotool mousedown 1");
			L_C = 1;
		}

		int str_R = strcmp(buf, "R");
		if(str_R == 0){

			system("xdotool click 3");
		}
		int str_R_Hold = strcmp(buf, "r");
		if(str_R_Hold == 0){

			system("xdotool mousedown 3");
			R_C = 1;
		}
		int str_reset = strcmp(buf, "O");
		if(str_reset == 0){
			if(L_C == 1){
				system("xdotool mouseup 1");
			}
			if(R_C == 1){
				system("xdotool mouseup 1");
			}
		}

	}

}
int main(){
int fd, i; 

char buf[3];

fd = init_serial();

start_serial(buf, fd);

while(fd){

read_serial(buf, fd);

}

}


