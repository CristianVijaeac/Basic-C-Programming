#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   imageDataOffset; /* Offset to the start of image data */
}header;

typedef struct 
{
    unsigned int   biSize; /* Size of the info header - 40 bytes */
    signed int     width; /* Width of the image */
    signed int     height; /* Height of the image */
    unsigned short planes;
    unsigned short bitPix;
    unsigned int   biCompression;
    unsigned int   biSizeImage; /* Size of the image data */
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
}infoheader;

typedef struct {
	unsigned char B,G,R;
	}PIXEL;

int VERIFICARE(int Rr,int Gr,int Br,int Ro,int Go,int Bo,int b,int g,int r)
	{
	if (Br-Bo<=b && b<=Br+Bo)
		if (Gr-Go<=g && g<=Gr+Go)
			if (Rr-Ro<=r && r<=Rr+Ro)
				return 1;
			else	return 0;
		else 	return 0;
	else 	return 0;
	}
			
int RECURSIV (int z,int *w,int **tmp,int i,int j,int m,int n)
	{
	if(((j+1)<m)&&(tmp[i][j+1]==1))
			{
			w[z]++;
			tmp[i][j+1]=z;
			RECURSIV(z,w,tmp,i,j+1,m,n);
			}
	if(((j-1)>=0) &&(tmp[i][j-1]==1))
			{
			w[z]++;
			tmp[i][j-1]=z;
			RECURSIV(z,w,tmp,i,j-1,m,n);
			}
	if(((i-1)>=0) &&(tmp[i-1][j]==1))
			{
			w[z]++;
			tmp[i-1][j]=z;
			RECURSIV(z,w,tmp,i-1,j,m,n);
			}
	if(((i+1)<n)&&(tmp[i+1][j]==1))
			{
			w[z]++;
			tmp[i+1][j]=z;
			RECURSIV(z,w,tmp,i+1,j,m,n);
			}
			
		return 0;
			}


int main ()
{
int **tmp,i,j,n,m,Rr,Gr,Br,Ro,Go,Bo;
unsigned char ***b;
float proc;
FILE *f1,*f2;
f1=fopen("input.txt","rb");
fscanf(f1,"%d%d%d%d%d%d%f",&Rr,&Gr,&Br,&Ro,&Go,&Bo,&proc);
fclose(f1);
f2=fopen("input.bmp","rb");
header H1;
infoheader H2;
fread(&H1.fileMarker1,sizeof(char),1,f2);
fread(&H1.fileMarker2,sizeof(char),1,f2);
fread(&H1.bfSize,4,1,f2);
fread(&H1.unused1,2,1,f2);
fread(&H1.unused2,2,1,f2);
fread(&H1.imageDataOffset,4,1,f2);
fread(&H2.biSize,4,1,f2);
fread(&H2.width,4,1,f2);
fread(&H2.height,4,1,f2);
fread(&H2.planes,2,1,f2);
fread(&H2.bitPix,2,1,f2);
fread(&H2.biCompression,4,1,f2);
fread(&H2.biSizeImage,4,1,f2);
fread(&H2.biXPelsPerMeter,4,1,f2);
fread(&H2.biYPelsPerMeter,4,1,f2);
fread(&H2.biClrUsed,4,1,f2);
fread(&H2.biClrImportant,4,1,f2);
//printf("%c %c %d %hu %hu %d %d %d %d %hu %hu %d %d %d %d %d %d",H1.fileMarker1,H1.fileMarker2,H1.bfSize,H1.unused1,H1.unused2,H1.imageDataOffset,H2.biSize,H2.width,H2.height,H2.planes,H2.bitPix,H2.biCompression,H2.biSizeImage,H2.biXPelsPerMeter,H2.biYPelsPerMeter,H2.biClrUsed,H2.biClrImportant);
n=H2.height;
m=H2.width;
b=malloc(n * sizeof(unsigned char**));
for (i=n-1;i>=0;i--)
	{b[i]=malloc(m*sizeof(unsigned char*));
	for(j=0;j<m;j++)
		b[i][j]=malloc(3*sizeof(unsigned char));}
for(i=n-1;i>=0;i--)
	{
	for(j=0;j<m;j++)
		{fread(&b[i][j][0],1,1,f2);	  	
		fread(&b[i][j][1],1,1,f2);
		fread(&b[i][j][2],1,1,f2);		
		}
	fseek(f2,m%4,SEEK_CUR);  //ignorare padding	
	}
fclose(f2);

//subpunct a
tmp=malloc(n*sizeof(int**));
for (i=0;i<n;i++)
	tmp[i]=malloc(m*sizeof(int*));


for(i=n-1;i>=0;i--)
	for (j=0;j<m;j++)
		if (VERIFICARE(Rr,Gr,Br,Ro,Go,Bo,b[i][j][0],b[i][j][1],b[i][j][2])==1)
			tmp[i][j]=1;
			else
				tmp[i][j]=0;
int z=0,*w;
w=calloc(1000,sizeof (int));
z=0;
for(i=0;i<n-1;i++)
	for (j=0;j<m;j++)
		if(tmp[i][j]==1)
			{
			tmp[i][j]=0;
			w[z]++;			
			RECURSIV(z,w,tmp,i,j,m,n);
			z++;			
			}
int a;				
	for(i=0;i<z;i++)
		for (j=i+1;j<=z;j++)		
			if (w[i]>w[j])
			{
			a=w[i];
			w[i]=w[j];
			w[j]=a;
			}		
FILE *f3;
f3=fopen("output.txt","wb");	
	for(i=0;i<=z;i++)
		if (w[i]>=proc*m*n)		
			fprintf(f3,"%d ",w[i]);
fclose(f3);
				







/*FILE *f3,*f4;
int v[100];
f3=fopen("output.bmp","wb");
f4=fopen("input1.bmp","rb");
fread(v,1,54,f4);
fwrite(v,1,54,f3);
for(i=n-1;i>=0;i--)
	for(j=0;j<m;j++)
		{aux[0]=b[i][j][0];
		aux[1]=b[i][j][1];
		aux[2]=b[i][j][2];
		fwrite(aux,1,3,f3);}
fclose(f3);
fclose(f4);
*/
return 0;



}
