//Buck State macro

typedef struct 
{
    float kp;
    float ki;

}PI_ParamDef;

typedef enum
{
    NO,
    YES
}PI_Error_Init_State;

typedef struct
{
    float ref;

    float feedback;

    float error;
    float error_last;

    float output_unlimit;
    float control_output;
    

    PI_Error_Init_State is_initialized;
}PI_StateDef;



typedef struct
{
    
    PI_ParamDef param;

    PI_StateDef state;

}PI_TypeDef;

typedef enum
{
    INIT,
    STOP,
    SOFTSTART,
    RUN,
    FAULT

}BuckState_e;

typedef struct 
{
    Uint16 duty;

    BuckState_e state;

    Uint16 enable;

}Buck_Typedef;


void PI_Run(PI_TypeDef * pi);
void PI_Init(void);
void DutyLimit(Buck_Typedef *buck);
void Control_Run(void);




