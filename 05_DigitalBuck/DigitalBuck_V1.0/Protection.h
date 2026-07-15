#ifndef PROTECTION_H
#define PROTECTION_H
void Protection_Run(Feedback_TypeDef *feedback, Buck_Typedef *buck);
void OUT_OVP_Check(void);
void OUT_OCP_Check(void);
void IN_OVP_Check(void);
void IN_OCP_Check(void);
#endif
