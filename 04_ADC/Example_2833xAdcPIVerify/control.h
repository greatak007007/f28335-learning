typedef struct
{
    Uint16 initialized;
    float kp;
    float ki;

    float error_last;
    
    float output;
}PI_TypeDef;

float PI_Cal(float error);
void PI_Init(void);


