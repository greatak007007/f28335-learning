
#include "Protection.h"
#include "epwm.h"

Protection protection;
void Protection_Run(Feedback_TypeDef *feedback, Buck_Typedef *buck, Protection *protect0)
{
    buck->fault_flag.all = 0;
    
    OUT_OVP_Check(feedback, buck, protect0);
    OUT_OCP_Check();
    IN_OVP_Check();
    IN_OCP_Check();
}
void OUT_OVP_Check(Feedback_TypeDef *feedback, Buck_Typedef *buck, Protection *protect0)
{
    if(feedback->voltage.vout > protect0->OutOVP.param.threshold)
    {
        if(protect0->OutOVP.state.cnt < protect0->OutOVP.param.delay)
        {
            protect0->OutOVP.state.cnt++;
        } 
        
        if(protect0->OutOVP.state.cnt >= protect0->OutOVP.param.delay) 
        {
            buck->fault_flag.bit.OUT_OVP = 1;
        }
    }
    else 
    {
        protect0->OutOVP.state.cnt = 0;
    }

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
void Protection_Init(Protection *protect)
{
    protect->OutOVP.param.threshold = 15;
    protect->OutOVP.param.delay = OUT_OVP_DELAY_TIME * PWM_FRQ; //20ms respect to numbers of switch period

    protect->OutOVP.state.cnt = 0;
}
