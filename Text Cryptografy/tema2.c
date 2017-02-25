
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
			
int punctuatie(char c)//functie care verifica daca un caracter e semn de punctuatie
{
if(c==' '|| c==','||c=='.'||c=='?'||c=='!'||c==';'||c==':'||c=='-'||c==0)
	return 1;							
else
	return 0;
} 


char *DECODIFICARE(char *txt,int n)//functia pentru subpunctul a
{
int i;
char *text;
if (n>=26)
        n=n%26;//reducerea cheii pentru a ramane in intervalul codului ASCII
for (i=0;i<strlen(txt);i++)
        {
        if ((txt[i]>='a') && (txt[i]<='z'))
                {
                if (txt[i]-n<'a')
                        txt[i]=txt[i]-n+26;		//decodificarea schimband litera cu k litere in oridine descrescatoare
                                else
                                        txt[i]=txt[i]-n;
                }
        if ((txt[i]>='A') && (txt[i]<='Z'))
                {
                if (txt[i]-n<'A')
                        txt[i]=txt[i]-n+26;
                                else
                                        txt[i]=txt[i]-n;
                }
        printf("%c",txt[i]);
        }
printf("\n");
return text=txt;//suprascrie textul initial si l returneaza modificat
}

char *PREFIXE(char *txt,char *pre)//functie pentru subpunctul b
{
int i=0,j=0,a;
char *x,*text,*aux,*result,*tmp,*word_pre[strlen(txt)];
aux=(char*)malloc(strlen(txt));
result=(char*)malloc(strlen(txt));
x=(char*)malloc(strlen(txt));
for(i=0;i<strlen(txt);i++)
       if(txt[i]>='A' && txt[i]<='Z')
         aux[i]=txt[i]+32;
       else					//transformarea majusculelor din text in litere mici
	 if (txt[i]>='a' && txt[i]<='z')
		aux[i]=txt[i];
			else aux[i]=txt[i];
word_pre[0]=strtok(pre," ");
while(word_pre[j]!=NULL)
        {
        j++;
        word_pre[j]=strtok(NULL," ");	//impartirea sirului de prefixe in cuvinte
        a=j;
        }
for(i=1;i<a;i++)
{
        for (j=1;j<a;j++) {
        if (strlen(word_pre[j-1])<strlen(word_pre[j])) {
       char *t=(char*)malloc(500);
       strcpy(t,word_pre[j-1]);			//ordonarea sirului de prefixe in functie de lungime
        word_pre[j-1]=word_pre[j];
        word_pre[j]=t;
       }
        }
        }


for(i=0;i<a;i++)
	{
	tmp=(char*)malloc(10000);
	for(j=0;j<strlen(txt);j++)
		{if (aux[j]>='A' && aux[j]<='Z')
			{aux[j]=aux[j]+32;}} 
	x=strstr(aux,word_pre[i]); 
	while(x!=NULL)
			{
			if (punctuatie(txt[strlen(txt)-strlen(x)-1])==1 && punctuatie(txt[strlen(txt)-strlen(x)+strlen(word_pre[i])])==0 && punctuatie(txt[strlen(txt)-strlen(x)+strlen(word_pre[i])+1])==0)//conditiile ca acel cuvant sa fie prefix(inaintea primei litere semn de punctuatie,dupa ultima litere 2 caractere
				{
				strncpy(tmp,txt,strlen(txt)-strlen(x));//plasam intr un sir ceea ce se afla inainte de prefix
				strcat(tmp,txt+strlen(tmp)+strlen(word_pre[i])); //plasam intr un sir ceea ce se afla dupa prefix
				strcpy(txt,tmp);//suprascriem sirul original cu sirul din care am scos respectivul prefix
				aux=(char*)malloc(10000);
				tmp=(char*)malloc(10000);
				strcpy(aux,txt);//returnam noul sir repetitivei
				strcpy(result,txt);//rezultaul
				}
x=strstr(x+1,word_pre[i]);//trecem la urmatoarea litera	
	}
	}
	
for(i=0;i<strlen(result);i++)
	if(result[i]!=0)
		printf("%c",result[i]);//daca sirul nou format diferit de sirul NULL,il scriem
if(strlen(result)==0)
		printf("%s",txt);//daca nu,scriem sirul initial
printf("\n");

return text=result;//suprascriu textul initial cu noul text fara prefixe
}


void APARITII(char *txt)//functie pentru subpunctul c
{
int cuvantmaxim=0,a=0,i=0,j=0,n=0,b,max=1;
char *word[strlen(txt)];
word[0]=strtok(txt," ,.?;:!-");
while(word[i]!=NULL)
	{
	i++;
	word[i]=strtok(NULL," ,.?!;:-");//separarea textului in cuvinte
	a=i;
	}
for(i=0;i<a;i++)
	for(j=0;j<strlen(word[i]);j++)
		if(word[i][j]>='A' && word[i][j]<='Z')//transformarea majusculelor in litere mici
			word[i][j]=word[i][j]+32;
for (i = 1; i < a; i++) {
      for (j = 1; j < a; j++) {
         if (strcmp(word[j-1], word[j]) > 0) {
            char *t=(char*)malloc(10000);
	     strcpy(t, word[j - 1]);//sortarea alfabetica a cuvintelor din text pentru cautarea in ordine alfabetica
            word[j - 1]=word[j];
            word[j]=t;
         }
      }
   }
for(i=0;i<a-1;i++)
	{
	n=0;
	for(j=i;j<a;j++)
		{
		b=strcmp(word[i],word[j]);//comparam 2 cuvinte din text
		if (b==0)//daca ele sunt identice
			{
			n=n+1;//memoram aceasta aparitia
			  if(n>max)//daca numarul de aparitii e mai mare decat cel precedent
			    {
			     max=n;//el devine numarul maxim de aparitii
			     cuvantmaxim=i;//iar cuvantul respectiv se afla pe pozitia i
			    }				
			}
		}
        }
printf("%s ",word[cuvantmaxim]);
printf("%d\n",max);	

}


int main()
{
char *text,*prefixe;
int k;
scanf("%d",&k);
text=(char*)malloc(7000);
prefixe=(char*)malloc(350);//alocarea memoriei pentru sirul de prefixe si textului
scanf(" %[^\n]s",text);
scanf(" %[^\n]s",prefixe);//citirea celor doua siruri
if ((0<=k) && (k<100000000))
        {
        DECODIFICARE(text,k);//apelarea functiei pt subpunctul a
        PREFIXE(text,prefixe);//apelarea functiei pt subpunctul b
        APARITII(text);//apelarea functiei pt subpunctul c
	}
free(text);
free(prefixe);//eliberarea memoriei pentru cele doua siruri
return 0;
}
