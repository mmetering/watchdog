#include "6106.H"
#include <dos.h>

unsigned int 6106_BASE;
void Unlock_6106 (void);
void Lock_6106 (void);

unsigned int Init_6106(void) {
  unsigned int result;
  unsigned char ucDid;
  6106_BASE = 0x4E;
  result = 6106_BASE;
  ucDid = Get_6106_Reg(0x20);
  
  if (ucDid == 0x07) //6106 {
    goto Init_Finish; 
  }
  
  6106_BASE = 0x2E;
  result = 6106_BASE;
  ucDid = Get_6106_Reg(0x20);
  
  if (ucDid == 0x07) { //6106
    goto Init_Finish; 
  }
  
  6106_BASE = 0x00;
  result = 6106_BASE;
  
Init_Finish:
  return (result);
}

void Unlock_6106 (void) {
  outportb(6106_INDEX_PORT, 6106_UNLOCK);
  outportb(6106_INDEX_PORT, 6106_UNLOCK);
}

void Lock_6106 (void) {
  outportb(6106_INDEX_PORT, 6106_LOCK);
}

void Set_6106_LD( unsigned char LD) {
  Unlock_6106();
  
  outportb(6106_INDEX_PORT, 6106_REG_LD);
  outportb(6106_DATA_PORT, LD);
  
  Lock_6106();
}

void Set_6106_Reg( unsigned char REG, unsigned char DATA) {
  Unlock_6106();
  
  outportb(6106_INDEX_PORT, REG);
  outportb(6106_DATA_PORT, DATA);
  
  Lock_6106();
}

unsigned char Get_6106_Reg(unsigned char REG) {
  unsigned char Result;
  Unlock_6106();
  outportb(6106_INDEX_PORT, REG);
  
  Result = inportb(6106_DATA_PORT);
  Lock_6106();
  
  return Result;
}
