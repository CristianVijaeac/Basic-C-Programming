#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void reducere (int *k)
{
    *k=*k%26;
}

int litera_mica (char c)
{
    if ( c >= 'a' && c<='z' ) return 1;
			else  return 0;
}

int litera_mare (char c)
{
    if ( c >= 'A' && c<='Z' ) return 1;
			else  return 0;
}

void sortare_dupa_lungime ( char *v[], int nrp )
{ int i,j;
char *aux=malloc(100*sizeof(char));
for ( i=0; i<nrp; i++ )
    for( j=i+1; j<nrp; j++ )
	if ( strlen(v[i]) < strlen(v[j]) )
	    {
	    strcpy(aux,v[i]);
	    strcpy(v[i],v[j]);
	    strcpy(v[j],aux);
	    }
}

int verif_semn_punct (char c)
{
switch (c)
{
    case '.':
 	return 1;
    case ';':
	return 1;
    case ',':
	return 1;
    case '!':
	return 1;
    case '?':
	return 1;
    case '-':
	return 1;
    case ':':
	return 1;
    case ' ':
	return 1;
    case '\0':
	return 1;
    default: return 0;
}
}

void delete( char * s, char *p, int m)
{ int i;
for(i=p-s; i<strlen(s); i++)
	if (i+m<=strlen(s)) s[i]=s[i+m];
		else break;
s[strlen(s)-m]='\0';
}

int main()
{
char *s=malloc(10000*sizeof(char));
char **v=malloc(10000*sizeof(char *));
char *prefix=malloc(10000*sizeof(char));
char *p=malloc(10000*sizeof(char));
char *aux=malloc(10000*sizeof(char));
char *s2=malloc(10000*sizeof(char));
char *cuvant=malloc(10000*sizeof(char));
char *cuvantmax, *s1;
int k,n,i,nr_pref,m,poz,nr,nrmax;
scanf("%d\n",&k);
fgets(s,10000,stdin);
reducere(&k);
n=strlen(s)-1;
s[strlen(s)-1]='\0';

fgets(s2,10000,stdin);
s2[strlen(s2)-1]=' ';
m=0; poz=0;
nr_pref=0;
for( i=0; i<strlen(s2); i++)
	if ( s2[i]==' ' )
		{v[nr_pref]=malloc(10000*sizeof(char));
		strncpy(v[nr_pref],s2+poz,m);
		poz=poz+m+1;
		m=0;
		nr_pref++;
		}
	else m++;

			
//punctul a):
for ( i = 0; i < n; i++)
    { if ( litera_mica (s[i]) ) 
		if ( s[i]-k >= 'a' ) s[i]=s[i]-k;
				else s[i]=s[i]+26-k;
      if ( litera_mare (s[i]) ) 
		if ( s[i]-k >= 'A' ) s[i]=s[i]-k;
				else s[i]=s[i]+26-k;
    }	
printf("%s\n",s);
//punctul b):
sortare_dupa_lungime(v,nr_pref);
strcpy(s2,s);
for(i=0;i<n;i++)
	if( litera_mare(s2[i]) ) s2[i]=s2[i]+32;
for ( i=0; i<nr_pref; i++ )
    {
    strcpy(prefix,v[i]);
    p=strstr(s2,prefix);
    m=strlen(prefix);
    if ( p != NULL )
	{
	if (( verif_semn_punct(s2[p-s2-1])==1 ) && (verif_semn_punct(s2[p-s2+m+1])==0 )&& (verif_semn_punct(s2[p-s2+m])==0))
		{
		strncpy(aux,s2,p-s2);
		printf("%s ",aux);
	/*	aux[p-s2]='\0';
		strcat(aux,p+m);
		strcpy(s2,aux);
		s2[p-s2]-=95;
		strncpy(aux,s,p-s2);
		aux[p-s2]='\0';
		strcat(aux,s+(p-s2+m));
		strcpy(s,aux);
		}*/
	
	}
    }
}
//printf("%s\n",s);
for(i=0;i<strlen(s2); i++) if (s2[i]<30) s2[i]+=95;
// punctul c)
strcpy(s,s2);
s1=malloc(10000*sizeof(char));
strcpy(s1,s2);
nrmax=1;
cuvantmax=malloc(10000*sizeof(char));
cuvant=strtok(s," ,:;.!?-");
strcpy(cuvantmax,cuvant);
while(cuvant!=NULL)
	{
	p=strstr(s1,cuvant);
	m=strlen(cuvant);
	nr=0;
	while(p!=NULL)
	        {
		if(verif_semn_punct(s1[p-s1+m])&&(verif_semn_punct(s1[p-s1-1])))
		{
		nr++;
		for(i=p-s1; i<strlen(s2); i++)
			if (i+m<=strlen(s2)) s2[i]=s2[i+m];
			else break;
		s2[strlen(s2)-m]='\0';
		}
		p=strstr(p+1,cuvant);
		}
	if(nrmax<nr)
		{nrmax=nr;
		strcpy(cuvantmax,cuvant);
		}
		else if((nrmax==nr)&&(strcmp(cuvantmax,cuvant)==1)) 
				{nrmax=nr;
				strcpy(cuvantmax,cuvant);
				}
	cuvant=strtok(NULL," ,:;.!?-");
	}
printf("%s ",cuvantmax);
printf("%d\n",nrmax);  
return 0;
}	

