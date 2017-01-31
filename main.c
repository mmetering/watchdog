#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "6106"

int main (int argc, char *argv[]);
void EnableWDT(int);
void DisableWDT(void);

int main (int argc, char *argv[]) {
  unsigned char bBuf;
  unsigned char bTime;
  char **endptr;
  // char SIO;
  printf("6106 watch dog program\n");
  bTime = strtol (argv[1], endptr, 10);
  printf("System will reset after %d seconds\n", bTime);
  if (bTime) { 
    EnableWDT(bTime); 
  } else { 
    DisableWDT(); 
  }
  
  if (bTime > 0 && bTime < 256) {
    int A;
    A=2;
    do {
      unsigned char result;
      Set_6106_LD(0x08); //switch to logic device 8
      result=Get_6106_Reg(0xF1);
      gotoxy(1,12);
      printf("Timer is %i \n",result);
    } while(A!=1);
  }
  return 0;
}

void EnableWDT(int interval) {
  unsigned char bBuf;
  Set_6106_LD(0x08); //switch to logic device 8
  Set_6106_Reg(0x30, 0x01); //enable timer
  Set_6106_Reg(0xF1, interval); //set timer
}

void DisableWDT(void) {
  unsigned char bBuf;
  Set_6106_LD(0x08); //switch to logic device 7
  Set_6106_Reg(0x30, 0x00); //enable timer
}
