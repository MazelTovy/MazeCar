#ifndef __LENGTH1_
#define __LENGTH1_

#define TRIG_Send PBout(14) //输出端口为PA6
#define ECHO_Reci PBin(15) //输入端口为PA7

float Senor_Using1(void);
void TIM2_Int_Init(void);


#endif
