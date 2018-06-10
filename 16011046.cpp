#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
char variables[5];
int  values[5];
//stack yap�m i�in struck top degerim stackin en �st�n�n bir fazlas�n� g�sterir yani bo� g�sterir her zaman
struct stack{

    int top=0;
    char deger[100];
    

};
//Bu fonksiyon txtden ald�g�m de�i�kenleri anlayabilmem i�in mesala txtde de iki kez b var bunu iki farkl� b olarak alg�lamamak i�in
char variablecheck(char variable){
	int i=0,index=6;
	char bos=' ';
	for(i=0;i<5;i++){
	if(variable==variables[i]){
		index=i;
	}	
	}
	
	if(index==6){
		return variable;
	}
	else{
		return bos;
	}
}
//stackin i�ine push eden fonksiyon
void push(struct stack *ps, char x){
    
    if(ps->top==99)
    {	   
    printf("stack dolu");
    }
    else
	{	
    ps->deger[(ps->top)]=x;
    ps->top++;
    }
}
//stackden pop eden fonksiyon 
char pop(struct stack *ps){
	char tmp;
    if(ps->top==0)
	{   
    printf("stack bos");
    }
    else
    {
    ps->top--;
    tmp= ps->deger[ps->top];
    ps->deger[ps->top]=' ';
    return tmp ;
    }
}
//string i�indeki bo�luklar� silen fonksiyon
void removeSpaces(char *p)
{
	if(NULL==p)
	return;
	
	int n = 0 ;
	
	for ( int i = 0; i < strlen(p); ++i){
		if(p[i] != ' ')
		 p[n++]=p[i];
	}
	p[n]='\0';
}

//Bu stackin i�ini d�zenlerken kulland�g�m  fonksiyon amac� gelen i�lemlerin �nceligini belirlemek yani + m� �nceliklidir * m� sorusuna cevap veren fonksiyonum
bool kontrol1(char x){
	switch(x)
	{
		case '+':case'-':case'(':
		return true;	
			break;
		case'*':case'/':
			return false;
				break;
		default:
			printf("ISLEM HATASI!!!!!!!!!!!");
		break;		
	}
	
}
//String i�inde gelen bir i�lemi infixden postfixe �eviren fonksiyonum
char* postfix(char buffer[]){
	bool tut=true,tut2=true;//while d�ng�m� k�rmak i�in kullad�g�m de�i�kenler bir nevi flag gibi kulland�m
	struct stack sta;//stack�m� tan�mlad�m
	char degiskenler[100],tmp;//degiskenler adl� dizim postfix ifademin yaz�ld�g� dizi i�i s�rekli de�i�rigi i�in de�i�kenler dedim yanl�� anla��lmas�n tmp ise i�lemlerde bana yard�mc� oldu
	degiskenler[0]=' ';//postfix ifademde bo�luklar olmas� i�in yapt�m
	int i=0,j=0,y=0;//iterator olarak kullad�g�m 3 de�i�ken
      removeSpaces(buffer);//stringimin i�indeki bo�luklar� sildim
   for(i=1;i<strlen(buffer)-2;i++)//teker teker stringimin i�indeki charlar� alarak kontrol ettim switch case ile burada say�m�,i�lem mi de�i�ken mi diye kontrol edilip ona  g�re �zerinde
	{                             //i�lemler yap�l�p kimisi stacke kimiside postfix ifadeye yaz�l�yor
  	  switch(buffer[i])
		{
			
			case '+':case '-':
			if(sta.top==0){
			push(&sta,buffer[i]);	
			}
			else
			{
			while(tut)
				{
			if(sta.top != 0)
		     	{					
			  tmp=pop(&sta);
				}
				else
				{
				tut=false;
				break;	
				}
				if(kontrol1(tmp))
				{
				push(&sta,tmp);
				tut=false;	
				}
				else			
				{
				degiskenler[j]=tmp;
				degiskenler[j+1]=' ';
    	    	j++;
				j++;	
				}
			}
			push(&sta,buffer[i]);
			tut=true;
			}
				
			break;	
					
			case '*':case '/':
			push(&sta,buffer[i]);
			break;	
						
			case '(':			
			push(&sta,buffer[i]);		
			break;	
					
			case ')':
			while(tut2){
			if(sta.top != 0)
		     	{					
			  tmp=pop(&sta);
				}
				else
				{
				tut2=false;	
				break;
				}
				if(tmp != '('){
				degiskenler[j]=tmp;
				degiskenler[j+1]=' ';
    	   		j++;
				j++;	
				}
				else
				{
				tut2=false;	
				}					
			}
			tut2=true;	
			break;
			
			case '\n':case '=':case ' ':case ';':
			
			break;	
						
    	    default:
    	    if(buffer[i]=='0'||buffer[i]=='1'||buffer[i]=='2'||buffer[i]=='3'||buffer[i]=='4'||buffer[i]=='5'||buffer[i]=='6'||buffer[i]=='7'||buffer[i]=='8'||buffer[i]=='9'){
    	    	if(buffer[i+1]=='0'||buffer[i+1]=='1'||buffer[i+1]=='2'||buffer[i+1]=='3'||buffer[i+1]=='4'||buffer[i+1]=='5'||buffer[i+1]=='6'||buffer[i+1]=='7'||buffer[i+1]=='8'||buffer[i+1]=='9'){
    	    	degiskenler[j]=buffer[i];
    	    	degiskenler[j+1]=buffer[i+1];
    	    	degiskenler[j+2]=' ';
    	    	buffer[i+1]=' ';
    	    	j=j+3;	
				}
				else
				{
				degiskenler[j]=buffer[i];
    	    	degiskenler[j+1]=' ';
    	    	j++;
    	    	j++;	
				}
			}
			else{	
    	    degiskenler[j]=buffer[i];
    	    degiskenler[j+1]=' ';
    	    j++;
    	    j++;
    	    }
			break;
		        	
		}
	printf("postfix=%s     stack=%s\n",degiskenler,sta.deger);// her ad�mda yazd�rma i�lemimi ger�ekle�tirdim

	}
	while(sta.top != 0){//en son stackde kalan i�lemleri s�ras� ile postfixe ekledim
		tmp=pop(&sta);
		degiskenler[j]=tmp;
		degiskenler[j+1]=' ';
		j=j+2;
		printf("postfix=%s     stack=%s\n",degiskenler,sta.deger);
	}
	degiskenler[j]=' ';
   degiskenler[j+1]='\0';
 //   printf("%s",degiskenler); 	
return degiskenler;	
}

int main (){//main fonksiyonum
	char readtxt[5][100],*postfix1,*postfix2,*postfix3;//readtxt matrisden okuyup yazd�g�m alan postfix 1 2 3 ise readtxtden infix ifadeyi al�p postfixe �evirdikden sonra yazd�g�m yerler 
	postfix1=(char*)malloc(100);                       //3 adet postfix ifade oldugu i�in 3 tane kulland�m 
	postfix1[99]='\0';                                 //yer a�t�m malloc ile ve sonunu string  bitirme ifadesini ekledim
	postfix2=(char*)malloc(100);
	postfix2[99]='\0';
	postfix3=(char*)malloc(100);
	postfix3[99]='\0';
	
	int  i=0;//iterat�r i�in
	FILE *InputFile;
	InputFile = fopen("input.txt", "r");//dosyam� okuma modunda a�t�m
	while(!feof(InputFile)){            //burda dosyadan okuyup readtxtde adl� matrise yazd�rd�m yazd�r�rkende ayn� anada her sat�r�n ba��ndaki harfi al�p de�i�ken olarak kabul ettim
	fgets(readtxt[i],100,InputFile);    
	variables[i]=variablecheck(readtxt[i][0]);
	values[i]=atoi(&readtxt[i][4]); //ayn� zamanda de�i�ken olarak al�rkende eger direk de�eri verilmi� ise onu al�p atama yap�yor ikisini ayr� ayr�p dizilerde tutdum
	i++;
	}
	//Buradada yazd�rma i�lemlerimi ger�ekle�tirdim
	printf("%s\n\n",readtxt[0]);
	printf("%s\n\n",readtxt[1]);
	
	printf("%s",readtxt[2]);
	postfix1=postfix(readtxt[2]);
	printf("%s\n\n",postfix1);
	
	printf("%s",readtxt[3]);
	postfix2=postfix(readtxt[3]);
	printf("%s\n\n",postfix2);
	
	printf("%s",readtxt[4]);
	postfix3=postfix(readtxt[4]);
	printf("%s\n\n",postfix3);	
	
}
