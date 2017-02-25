#include <stdio.h>
#include <math.h>

int INTERSCHIMBARE(int *x1,int *y1,int *x2,int *y2)  //Functie creata pentru ordonarea coordonatelor terenului 
                {
int aux,aux1;
if (*x1>*x2)	//Compararea coordonatelor x
                        {
			aux=*x1;
                        *x1=*x2;
                        *x2=aux;	//x-ul mai mic trece pe primul loc
			}
if (*y1>*y2)	//Compararea coordonatelor y
                        {
			aux1=*y1;
                         *y1=*y2;	//y-ul mai mic trece pe primul loc
                        *y2=aux1;
			}

return 0;
}


double DISTANTA(double a,double b) //Functie creata pentru aflarea distantei dintre 2 puncte aflate pe o perpendiculara
{
return fabs(a-b);//Distanta=modulul scaderii coordonatelor de acelasi tip
}


double distanta_gard(int x1,int x2,int y1,int y2,double x,double y,int unghi,double lungime) //Functie creata pentru aflarea distantei dintre pom si gard
{
double d_gard,x_gard=0,y_gard=0;
 		while ( unghi > 360)
                        unghi = unghi - 360;//Toate unghiurile >360 sunt trecute pe intervalul(o,360]
                while ( unghi < -360)
                        unghi = unghi + 360;//Toate unghiurile negative <-360 sunt trecut pe intervalul(-360,0]
                if ( unghi < 0)
			unghi = unghi + 360;//Unghiurilor negative li se atribuie valoarea pozitiva de pe cerc
		if ((unghi==0) || (unghi==360))                                             
                        {d_gard = x2-x; 											
                	x_gard = x2;    //Calcularea cazului de egalitate
			y_gard = y;}
		if (( unghi > 0) && ( unghi < 90))			//Primul cadran				 
                        {
			x_gard = (y2-y) / tan((unghi*M_PI)/180) + x;//Presupunem ca punctul de intersectie se afla pe o dreapta paralela cu OY
			y_gard = (x2-x) * tan((unghi*M_PI)/180) + y;//Presupunem ca punctul de intersectie se afla pe o dreapta paralela cu OX
			if ((x_gard <= x2)||(y_gard==y2)) //Daca conditia e indeplinita,prima presupunere e adevarata
                                {
				y_gard = y2;//y-ul de intersectie primeste valoare y-ului terenului
                                d_gard = (y2-y) / sin((unghi*M_PI)/180);//distanta de la pom la gard  calculata in functie de unghi
				}
			if (y_gard < y2)//Daca conditia e indeplinita,a doua presupunere e adevarata
				{
				 x_gard = x2;//x-ul de intersectie primeste valoarea x-ului terenului                  		                  
                 		 d_gard=(x2-x) / cos((unghi*M_PI)/180);//distanta de la pom la gard calculata in functie de unghi
				}
			}
		if (unghi==90)		  					       
                        {
			d_gard = y2-y;                                                                              
			x_gard = x;    //Calcularea cazului de egalitate
			y_gard = y2;
			}
		if ((unghi > 90) && ( unghi < 180))    			//Al doilea cadran						
                        {
			x_gard= x - (tan((unghi*M_PI/180)-(M_PI/2)) * (y2-y));
			y_gard=((x-x1) / tan((unghi*M_PI/180)-(M_PI/2))) + y;             //Acelasi algoritm ca la primul cadran                                       
                	if ((x_gard >= x1)||(y_gard==y2))
				{
				y_gard = y2;
				d_gard = (y2-y) / cos((unghi*M_PI/180)-(M_PI/2));
				}
			if (y_gard < y2)
				{
				x_gard = x1;
				d_gard= (x-x1) / sin((unghi*M_PI/180)-(M_PI/2));
				}
			}
		if (unghi==180)                                                                                    
                        {
			d_gard = x - x1;
			x_gard = x1;		//Cazul de egalitate
			y_gard = y;
			}
                if ((unghi > 180) && (unghi < 270))		//Al treilea cadran
			{
			x_gard= x - ( (y-y1) / tan(((unghi*M_PI)/180)-M_PI));
                        y_gard= y - tan(((unghi*M_PI)/180)-M_PI) * (x-x1);
                        if ((x_gard >= x1)||(y_gard==y1)) 					
                                { 				//Acelasi algoritm ca la primul si al doilea cadran
                                y_gard = y1;
                                d_gard = (y-y1) / sin(((unghi*M_PI)/180)-M_PI);
                                }
                        if (y_gard > y1)
                                {
                                x_gard = x1;
                                d_gard= (x-x1) / cos(((unghi*M_PI)/180)-M_PI);
                                }
                	}	
		if (unghi==270)
                        {
			d_gard = y-y1;
			x_gard = x;		//Cazul de egalitate
			y_gard = y1;
			}
                if ((unghi > 270) && (unghi < 360))		//Al patrulea cadran
                        {
			x_gard= tan(((unghi*M_PI)/180) - (3*M_PI)/2) * (y-y1) + x;
			y_gard= y - (x2-x) / tan(((unghi*M_PI)/180) - (3*M_PI)/2);
			if ((x_gard <= x2)||(y_gard==y1))
				{
				y_gard = y1;
				d_gard = (y-y1) / cos(((unghi*M_PI)/180)-(3*M_PI)/2);	//Acelasi algoritm ca la primul,al doilea si al treilea cadran
				}
			if (y_gard > y1)
				{
				x_gard = x2;
				d_gard = (x2-x)/ sin(((unghi*M_PI)/180)-(3*M_PI)/2);
				}
			}
               
 		if (d_gard >= lungime)//Daca distanta pana la gard  e mai mare sau egala cu lungimea
                                printf("Pomul ramane in livada!\n");//Afisam acest mesaj
                        else
                        	printf("%.3lf %.3lf %.3lf\n",lungime-d_gard,x_gard,y_gard);
				//Daca nu,afisam lungimea care iese din teren si coordonatele punctului de intersectie cu gardul
                      
return d_gard;//Se foloseste la rezolvarea urmatorului subpunct
}		




int main()
{
int x1,x2,y1,y2,numar_taieturi,i,n,unghi;
double d_gard,x,y,d_min,lungime,ultima_taietura;
scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&n);
INTERSCHIMBARE(&x1,&y1,&x2,&y2);//Apelarea functiei de interschimbare pt aranjarea coordonatelor
	for (i=1;i<=n;i++) //Repetitiva care citeste valorile fiecarui pom
		{
		scanf("%lf%lf%lf%d",&x,&y,&lungime,&unghi);
		if ( (x<=x1)||(x>=x2)||(y<=y1)||(y>=y2) )	//Daca una din conditii e indeplinita,se afiseaza mesajul de mai jos
			printf("Pomul nu se afla in livada!\n\n");
		   else
		   {
	//Comparam fiecare distanta aflata in functia DISTANTA cu celelalte trei pentru aflarea minimei
			if ((DISTANTA(x,x1)<=DISTANTA(x2,x)) && (DISTANTA(x,x1)<=DISTANTA(y,y1)) && (DISTANTA(x,x1)<=DISTANTA(y2,y)))
					d_min=DISTANTA(x,x1);
			 if ((DISTANTA(x2,x)<=DISTANTA(x,x1)) && (DISTANTA(x2,x)<=DISTANTA(y,y1) )&& (DISTANTA(x2,x)<=DISTANTA(y2,y)))
					d_min=DISTANTA(x2,x);
			 if ((DISTANTA(y,y1)<=DISTANTA(x,x1)) && (DISTANTA(y,y1)<=DISTANTA(x2,x)) && (DISTANTA(y,y1)<=DISTANTA(y2,y)))
                                        d_min=DISTANTA(y,y1);//Daca conditia e indeplinita,aceasta e noua distanta minima
			 if ((DISTANTA(y2,y)<=DISTANTA(x,x1)) && (DISTANTA(y2,y)<=DISTANTA(x2,x) )&& (DISTANTA(y2,y)<=DISTANTA(y,y1)))
                                        d_min=DISTANTA(y2,y);
				numar_taieturi=lungime/d_min;//Numarul de taieturi reprezinta impartirea lungimii totale la distanta minima
				ultima_taietura=lungime-d_min*numar_taieturi;//Ultima taietura reprezinta restul in urma operatiei de mai sus
		 if (lungime<=d_min)//Daca conditia este indeplinita
				printf("%d %.3lf\n",1,lungime);//Singura taietura este cea egala cu lungimea
				else
				{
				if (ultima_taietura==0)//Daca ultima taietura nu exista,adica lungimea se imparte exact la d_min
				printf("%d %.3lf\n",numar_taieturi,d_min);//Se afiseaza asta
				else
				printf("%d %.3lf %d %.3lf\n",numar_taieturi,d_min,1,ultima_taietura);//Daca ultima taietura exista,se afiseaza asta
	         		}	
			d_gard=distanta_gard(x1,x2,y1,y2,x,y,unghi,lungime);//Aflam distanta pana la gard un functie de unghi apeland functia distanta_gard	
			
		if (d_gard>=lungime) //Aplicam acelasi algoritm ca mai sus,pentru aflarea numarului de taieturi,insa cu noua distanta(d_gard)
			
			printf("%d %.3lf\n\n",1,lungime); 
			else  //Daca conditia nu este indeplinita,atunci se trece la aflarea valorilor dorite
			{
			numar_taieturi=lungime/d_gard;
                	ultima_taietura=lungime-d_gard*numar_taieturi;
		 		if (ultima_taietura==0) //Daca lungimea se imparte exact la d_gard
                                	printf("%d %.3lf\n\n",numar_taieturi,d_gard);//Se afiseaza asta
                                	else
                                		printf("%d %.3lf %d %.3lf\n\n",numar_taieturi,d_gard,1,ultima_taietura);//Daca ultima taietura exista,se afiseaza asta
}
}	
}
return 0;
}
