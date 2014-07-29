#include "robotthumb.h"

RobotThumb::RobotThumb()
{

}

RobotThumb::~RobotThumb()
{

}

void RobotThumb::SetRotationParameters(int pin, int max, int min)
{
	maxRotate = max;
	
	minRotate = min;
	
	rotator.attach(pin);
}
	
void RobotThumb::SetFlexorParameters(int pin, int max, int min)
{
	flexor.SetParameters(pin, max, min);
}

void RobotThumb::SetFlexAndOppositionFlags(bool flexesAtMax, bool opposesAtMax)
{
	flexor.SetFlexesAtMaxPosFlag(flexesAtMax);
	
	opposesAtMaxRotation = opposesAtMax;
}

void RobotThumb::RotateMax()
{
	if (opposesAtMaxRotation == true)
	{
		rotator.write(maxRotate);
		
	} else rotator.write(minRotate);
}

void RobotThumb::RotateMin()
{
	if (opposesAtMaxRotation == true)
	{
		rotator.write(minRotate);
		
	} else rotator.write(maxRotate);
}
	
void RobotThumb::FlexMax()
{
	flexor.FlexMax();
}

void RobotThumb::Relax()
{
	flexor.Relax();
}

void RobotThumb::Flex(int percent)
{
	flexor.Flex(percent);
}
	
bool RobotThumb::Rotate(int percent)
{
	    if (percent >= 0 && percent <=100)
    {
    		    int slew = (maxRotate - minRotate) * percent/100;
    
    		    int gotoAngle;
    		    
		   if (opposesAtMaxRotation == true)
		   {
		   	gotoAngle = minRotate + slew;
		   } else
		   {
		   	gotoAngle = maxRotate - slew;
		   }
		   
		   rotator.write(gotoAngle);
		   
		   return true;
        
    } else return false;
}
	
void RobotThumb::RotateAndFlex(int a, int b)
{
	Rotate(a);
	
	Flex(b);
}
