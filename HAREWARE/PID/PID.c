#include "stm32f10x.h" 
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "pid.h"

float PP=0,II=0,DD=0;
//-------------------------------------
void  PID_SetPoint(PID * s_PID, PID_VAR_TYPE set_point) 
{
   s_PID->SetPoint = set_point;
}      
//-----------------------------------

/*
//λ��ʽPID
PID_VAR_TYPE Position_PID_Cal(PID * s_PID,PID_VAR_TYPE now_point,float icm_gyro_m)
{
	PID_VAR_TYPE IOutValue;
    s_PID->LastResult = s_PID->Result;			     
    //?��2?????
    s_PID->Error = s_PID->SetPoint - now_point;
    s_PID->SumError += s_PID->Error;                          
    //?y��??T����
    IOutValue = s_PID->SumError * s_PID->Integral;
    if(IOutValue > s_PID->IntegralMax)IOutValue = s_PID->IntegralMax;
    else if(IOutValue < s_PID->IntegralMin)IOutValue = s_PID->IntegralMin;
	  II=IOutValue;
    //PID????
   // s_PID->Result =  s_PID->Proportion  *  s_PID->Error                      
    //               + IOutValue                                                    
      //             + s_PID->Derivative  * (s_PID->Error - s_PID->LastError); 
    
	  PP=s_PID->Proportion  *  s_PID->Error;
	  DD=s_PID->Derivative  * icm_gyro_m;
	  s_PID->Result =  s_PID->Proportion  *  s_PID->Error                      
                   + IOutValue                                                    
                   + s_PID->Derivative  * icm_gyro_m;   
    s_PID->PrevError = s_PID->LastError;		              
    s_PID->LastError = s_PID->Error; 		
 
    //��?3??T����
//    if(s_PID->Result > s_PID->OutMax)s_PID->Result = s_PID->OutMax;
//    else if(s_PID->Result < s_PID->OutMin)s_PID->Result = s_PID->OutMin;
    
    return s_PID->Result;	
}
*/

//����ʽPID--------------------------------------
PID_VAR_TYPE Increment_PID_Cal(PID * s_PID,PID_VAR_TYPE now_point)
{
    s_PID->LastResult = s_PID->Result;					       //�򵥸�ֵ����
    //������  
    s_PID->Error = s_PID->SetPoint - now_point;
    //PID����  
    s_PID->Result = s_PID->LastResult 
                  + s_PID->Proportion  * (s_PID->Error - s_PID->LastError)                          //P
                  + s_PID->Integral    *  s_PID->Error	                                            //I 
                  + s_PID->Derivative  * (s_PID->Error - 2*(s_PID->LastError) + s_PID->PrevError);  //D
   
    s_PID->PrevError = s_PID->LastError;		               //�򵥸�ֵ����
    s_PID->LastError = s_PID->Error; 				       //�򵥸�ֵ����
//    //����޷�
//    if(s_PID->Result > s_PID->OutMax)s_PID->Result = s_PID->OutMax;
//    else if(s_PID->Result < s_PID->OutMin)s_PID->Result = s_PID->OutMin;
	    //����޷�
    if(s_PID->Result > 25)s_PID->Result = 25;
    else if(s_PID->Result < 0)s_PID->Result = 0;

    
    return s_PID->Result;	
}
//---------------------------------------
void PID_Init(PID * s_PID,PID_VAR_TYPE set_point,PID_VAR_TYPE Proportion,PID_VAR_TYPE Integral, PID_VAR_TYPE Derivative)
{
   s_PID->SetPoint = set_point;                         //Ŀ��ֵ 
   s_PID->Proportion = Proportion;                      //P
   s_PID->Integral = Integral;                          //I
   s_PID->Derivative = Derivative;                      //D
   s_PID->Error = 0;                                    //���
   s_PID->LastError = 0;                                //��һ�����
   s_PID->PrevError = 0;                                //ǰ��������
   s_PID->SumError = 0;                                 //֮ǰ������
   s_PID->LastResult = 0;                               //��һ�ν��
   s_PID->Result = 0;                                   //���
   s_PID->OutMax = DEFAULT_PID_OUT_MAX;
   s_PID->OutMin = DEFAULT_PID_OUT_MIN;
   s_PID->IntegralMax = DEFAULT_PID_INTEGRAL_OUT_MAX;
   s_PID->IntegralMin = DEFAULT_PID_INTEGRAL_OUT_MIN;
}
