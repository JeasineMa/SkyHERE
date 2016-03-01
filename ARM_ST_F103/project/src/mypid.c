/****************************************
Դ�ļ����ã�PID����������
����ʱ�䣺20150515
****************************************/
#include "mypid.h"
#define MAX_INTEGRATION_ERROR                2500
#define MAX_PID_OUTPUT                       4000
/****************************************************
�������ܣ�PID����������
���������input����Ҫ����PID��������
�����������
��    ע����
****************************************************/
void calcPID(PID *pid, int input)
{
int output,error;
error=pid->targetValue-input;
if (pid->Ki != 0)
        {
                pid->integrationError += error;
                // Limit the maximum integration error
                if (pid->integrationError > MAX_INTEGRATION_ERROR)
                {
                        pid->integrationError = MAX_INTEGRATION_ERROR;
                }
                else if (pid->integrationError < -MAX_INTEGRATION_ERROR)
                {
                        pid->integrationError = -MAX_INTEGRATION_ERROR;
                }
        }

        output = pid->Kp * error + pid->Ki * pid->integrationError + pid->Kd * (error - pid->lastError);

        // Limit the maximum output
        if (output > MAX_PID_OUTPUT)
        {
                output = MAX_PID_OUTPUT;
        }
        else if (output < -MAX_PID_OUTPUT)
        {
                output = -MAX_PID_OUTPUT;
        }

        pid->lastError = error;
		pid->PWM+=output;
}
