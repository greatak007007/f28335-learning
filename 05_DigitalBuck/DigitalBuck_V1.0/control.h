//Buck State macro
#define STOP 0x0
#define RUN 0x1
#define FAULT 0x2
#define SOFTSTART 0x3

typedef struct 
{
    float kp;
    float ki;

}PI_ParamDef;

typedef struct
{
    float ref;

    float feedback;

    float error;
    float error_last;

    float output_raw;
    float control_output;
    

    Uint16 is_initialized;
}PI_StateDef;

typedef struct
{
    
    PI_ParamDef param;

    PI_StateDef state;

}PI_TypeDef;

typedef struct 
{

}Buck_Output_Typedef;

typedef struct 
{

}Buck_Enable_Typedef;

typedef struct 
{
    Buck_Output_Typedef output;

    Uint16 state;

    Buck_Enable_Typedef enable;

}Buck_Typedef;


void PI_Run(PI_TypeDef * pi);
void PI_Init(void);
float Out_Limit(float out);
void Control_Run(void);




