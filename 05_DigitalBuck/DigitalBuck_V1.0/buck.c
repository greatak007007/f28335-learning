#include "buck.h"
#include "global.h"

Buck_Typedef Buck;

void Buck_Init(Buck_Typedef *buck)
{
    buck->duty = 0;
    buck->request_duty = 0;
    buck->enable = BOOL_YES;
    buck->fault_flag.all = 0;
    buck->state = RUN;
}
