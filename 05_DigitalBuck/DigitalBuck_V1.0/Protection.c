
#include "Adc.h"
#include "Protection.h"


void Protection_Run(Feedback_TypeDef *feedback, Buck_Typedef *buck)
{
    buck->fault_flag.all = 0;
    
    OUT_OVP_Check();
    OUT_OCP_Check();
    IN_OVP_Check();
    IN_OCP_Check();
}
void OUT_OVP_Check(void)
{
    ;
}
void OUT_OCP_Check(void)
{
    ;
}
void IN_OVP_Check(void)
{
    ;
}
void IN_OCP_Check(void)
{
    ;
}
