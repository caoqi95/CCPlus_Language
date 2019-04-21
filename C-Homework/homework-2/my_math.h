#include <stdio.h>

float myabs(float x) 
{
    if(x<0) x=0-x;
    return x;
}

 
 float mysin(float x)
 {
 	const float B = 1.2732395447; // 4/pi
 	const float C = -0.4052847346; // -4/(pi^2)
 	const float P = 0.225;
 	float y = 0;
 	
 	//always wrap input angle to -PI..PI
 	if (x < -3.14159265)
    	x += 6.28318531;
	else if (x > 3.14159265)
    	x -= 6.28318531;
    
    
 	if(x > 0)
 	{
 		y = B*x + C*x*x;
 		y = y - 0.006;
 	}
	else
	{
 		y = B*x - C*x*x;
 		y = y + 0.06; 		
	}

 	return y; 
 }


float mycos(float x) 
{
	const float Q = 1.5707963268; // pi/2 
	const float PI =3.1415926536;
	x += Q; 

	if(x > PI) 
		x -= 2 * PI; 

 	return( mysin(x));
}


float mytan(float a)
{	
	float res;
	res = mysin(a)/mycos(a);
	return res;
}


float mypow(float a,int b)
{
    float r=a;
    if(b>0)
    {
      while(--b)
         r*=a;

    }
    else if(b<0)
    {
        while(++b)     r*=a;
         r=1.0/r;
    }
    else r=0;
    return r;
}

float myexp(float x)

{
 	x = 1.0 + x/256;

 	x *= x; x *= x; x *= x; x *= x;

 	x *= x; x *= x; x *= x; x *= x;
 
 return x;

}
