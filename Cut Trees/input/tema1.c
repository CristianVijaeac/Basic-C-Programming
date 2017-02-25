#include <stdio.h>
#include <math.h>

int INTERSCHIMBARE(int *x1,int *y1,int *x2,int *y2)    
                {
int aux,aux1;
if (*x1>*x2)
                        {aux=*x1;
                        *x1=*x2;
                        *x2=aux;}
if (*y1>*y2)
                        {aux1=*y1;
                         *y1=*y2;
                        *y2=aux1;}

return 0;
}


double DISTANTA(double a,double b)
{
return fabs(a-b);
}


double distanta_gard(int x1,int x2,int y1,int y2,double x,double y,int unghi,double lungime)
{
double d_gard,x_gard=0,y_gard=0;
 		while (unghi>360)
                        unghi=unghi-360;
                while (unghi<-360)
                        unghi=unghi+360;
                if (unghi<0)
			unghi=unghi+360;
		if ((unghi==0) || (unghi==360))                                             
                        {d_gard=x2-x; 											
                	x_gard=x2;
			y_gard=y;}
		if ((unghi>0)&&(unghi<90))							 
                        {
			x_gard=(y2-y)/tan((unghi*M_PI)/180)+x;
			y_gard=(x2-x)*tan((unghi*M_PI)/180)+y;
			if ((x_gard<=x2)||(y_gard==y2))
                                {y_gard=y2;
                                d_gard=(y2-y)/sin((unghi*M_PI)/180);}
			if (y_gard<y2)
				{
				 x_gard=x2;                  		                  
                 		 d_gard=(x2-x)/cos((unghi*M_PI)/180);}
			}
		if (unghi==90)		  					       
                        {d_gard=y2-y;                                                                              
			x_gard=x;
			y_gard=y2;}
		if ((unghi>90)&&(unghi<180))    									
                        {
			x_gard=x-(tan((unghi*M_PI/180)-(M_PI/2))*(y2-y));
			y_gard=((x-x1)/tan((unghi*M_PI/180)-(M_PI/2)))+y;                                                    
                	if (x_gard>=x1)
				{
				y_gard=y2;
				d_gard=(y2-y)/cos((unghi*M_PI/180)-(M_PI/2));
				}
			if (y_gard<y2)
				{
				x_gard=x1;
				d_gard=(x-x1)/sin((unghi*M_PI/180)-(M_PI/2));
				}
			}
		if (unghi==180)                                                                                    
                        {d_gard=x-x1;
			x_gard=x1;
			y_gard=y;}
                if ((unghi>180)&&(unghi<270))
			{
			x_gard=x-((y-y1)/tan(((unghi*M_PI)/180)-M_PI));
                        y_gard=y-tan(((unghi*M_PI)/180)-M_PI)*(x-x1);
                        if (x_gard>=x1)
                                {
                                y_gard=y1;
                                d_gard=(y-y1)/sin(((unghi*M_PI)/180)-M_PI);
                                }
                        if (y_gard>y1)
                                {
                                x_gard=x1;
                                d_gard=(x-x1)/cos(((unghi*M_PI)/180)-M_PI);
                                }
                	}	
		if (unghi==270)
                        {d_gard=y-y1;
			x_gard=x;
			y_gard=y1;}
                if ((unghi>270) && (unghi<360))
                        {
			x_gard=tan(((unghi*M_PI)/180)-(3*M_PI)/2)*(y-y1)+x;
			y_gard=y-(x2-x)/tan(((unghi*M_PI)/180)-(3*M_PI)/2);
			if (x_gard<=x2)
				{
				y_gard=y1;
				d_gard=(y-y1)/cos(((unghi*M_PI)/180)-(3*M_PI)/2);
				}
			if (y_gard>y1)
				{
				x_gard=x2;
				d_gard=(x2-x)/sin(((unghi*M_PI)/180)-(3*M_PI)/2);
				}
			}
               
 		if (d_gard>=lungime)
                                printf("Pomul ramane in livada!\n");
                        else
                        	printf("%.3lf %.3lf %.3lf\n",lungime-d_gard,x_gard,y_gard);
                      
return d_gard;
}		




int main()
{
int x1,x2,y1,y2,numar_taieturi,i,n,unghi;
double d_gard,x,y,d_min,lungime,ultima_taietura;
scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&n);
INTERSCHIMBARE(&x1,&y1,&x2,&y2);
	for (i=1;i<=n;i++)
		{
		scanf("%lf%lf%lf%d",&x,&y,&lungime,&unghi);
		if ( (x<=x1)||(x>=x2)||(y<=y1)||(y>=y2) )
			printf("Pomul nu se afla in livada!\n\n");
		   else
		   {
			if ((DISTANTA(x,x1)<=DISTANTA(x2,x)) && (DISTANTA(x,x1)<=DISTANTA(y,y1)) && (DISTANTA(x,x1)<=DISTANTA(y2,y)))
					d_min=DISTANTA(x,x1);
			 if ((DISTANTA(x2,x)<=DISTANTA(x,x1)) && (DISTANTA(x2,x)<=DISTANTA(y,y1) )&& (DISTANTA(x2,x)<=DISTANTA(y2,y)))
					d_min=DISTANTA(x2,x);
			 if ((DISTANTA(y,y1)<=DISTANTA(x,x1)) && (DISTANTA(y,y1)<=DISTANTA(x2,x)) && (DISTANTA(y,y1)<=DISTANTA(y2,y)))
                                        d_min=DISTANTA(y,y1);
			 if ((DISTANTA(y2,y)<=DISTANTA(x,x1)) && (DISTANTA(y2,y)<=DISTANTA(x2,x) )&& (DISTANTA(y2,y)<=DISTANTA(y,y1)))
                                        d_min=DISTANTA(y2,y);
				numar_taieturi=lungime/d_min;
				ultima_taietura=lungime-d_min*numar_taieturi;
		 if (lungime<=d_min)
				printf("%d %.3lf\n",1,lungime);
				else
				{
				if (ultima_taietura==0)
				printf("%d %.3lf\n",numar_taieturi,d_min);
				else
				printf("%d %.3lf %d %.3lf\n",numar_taieturi,d_min,1,ultima_taietura);
	         		}	
			d_gard=distanta_gard(x1,x2,y1,y2,x,y,unghi,lungime);	
			
		if (d_gard>=lungime)
			
			printf("%d %.3lf\n\n",1,lungime);
			else
			{
			numar_taieturi=lungime/d_gard;
                	ultima_taietura=lungime-d_gard*numar_taieturi;
		 		if (ultima_taietura==0)
                                	printf("%d %.3lf\n\n",numar_taieturi,d_gard);
                                	else
                                		printf("%d %.3lf %d %.3lf\n\n",numar_taieturi,d_gard,1,ultima_taietura);
}
}	
}
return 0;
}
