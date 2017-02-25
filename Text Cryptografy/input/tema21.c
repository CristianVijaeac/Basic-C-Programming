
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int punctuatie(char c)
{
if(c==' '|| c==','||c=='.'||c=='?'||c=='!'||c==';'||c==':'||c=='-')
	return 1;
else
	return 0;
} 


char *DECODIFICARE(char *txt,int n)
{
int i;
char *text;
if (n>=26)
        n=n%26;
for (i=0;i<strlen(txt);i++)
        {
        if ((txt[i]>='a') && (txt[i]<='z'))
                {
                if (txt[i]-n<'a')
                        txt[i]=txt[i]-n+26;
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
return text=txt;
}

void PREFIXE(char *txt,char *pre)
{
int i=0,j=0,a;
char *result,*x,*tmp,*aux,*word_pre[10000];
aux=(char*)malloc(10000);
result=(char*)malloc(10000);
for(i=0;i<strlen(txt);i++)
       if(txt[i]>='A' && txt[i]<='Z')
         aux[i]=txt[i]+32;
       else
	 if (txt[i]>='a' && txt[i]<='z')
		aux[i]=txt[i];
			else aux[i]=txt[i];
word_pre[0]=strtok(pre," ");
while(word_pre[j]!=NULL)
        {
        j++;
        word_pre[j]=strtok(NULL," ");
        a=j;
        }

for(i=1;i<a;i++)
{
        for (j=1;j<a;j++) {
        if (strlen(word_pre[j-1])<strlen(word_pre[j])) {
       char *t=(char*)malloc(10000);
       strcpy(t,word_pre[j-1]);
        word_pre[j-1]=word_pre[j];
        word_pre[j]=t;
       }
        }
        }
for(i=0;i<a;i++)
	{tmp=(char*)malloc(10000);
	 x=strstr(aux,word_pre[i]);
		while(x!=NULL)
			{if (punctuatie(aux[strlen(aux)-strlen(x)-1])==1 && punctuatie(aux[strlen(aux)-strlen(x)+strlen(word_pre[i])])==0 && punctuatie(aux[strlen(aux)-strlen(x)+strlen(word_pre[i])+1])==0)
				{
				strncpy(tmp,aux,strlen(aux)-strlen(x));
				strcat(tmp,x+strlen(word_pre[i]));
				strncpy(aux,tmp,strlen(aux));
				strcpy(result,aux);
				}
		
x=strstr(x+1,word_pre[i]);
			}
	}
printf("%s",result);
}

int main()
{
char *text,*prefixe;
int k;
scanf("%d",&k);
text=(char*)malloc(10000);
prefixe=(char*)malloc(10000);
scanf(" %[^\n]s",text);
scanf(" %[^\n]s",prefixe);
if ((1<=k)&&(k<=1000000))
        {
        DECODIFICARE(text,k);
        PREFIXE(text,prefixe);
        }
free(text);
free(prefixe);
return 0;
}
