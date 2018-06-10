#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
char variables[5];
int  values[5];
//stack yapým için struck top degerim stackin en üstünün bir fazlasýný gösterir yani boþ gösterir her zaman
struct stack{

    int top=0;
    char deger[100];
    

};
//Bu fonksiyon txtden aldýgým deðiþkenleri anlayabilmem için mesala txtde de iki kez b var bunu iki farklý b olarak algýlamamak için
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
//stackin içine push eden fonksiyon
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
//string içindeki boþluklarý silen fonksiyon
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

//Bu stackin içini düzenlerken kullandýgým  fonksiyon amacý gelen iþlemlerin önceligini belirlemek yani + mý önceliklidir * mý sorusuna cevap veren fonksiyonum
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
//String içinde gelen bir iþlemi infixden postfixe çeviren fonksiyonum
char* postfix(char buffer[]){
	bool tut=true,tut2=true;//while döngümü kýrmak için kulladýgým deðiþkenler bir nevi flag gibi kullandým
	struct stack sta;//stackýmý tanýmladým
	char degiskenler[100],tmp;//degiskenler adlý dizim postfix ifademin yazýldýgý dizi içi sürekli deðiþrigi için deðiþkenler dedim yanlýþ anlaþýlmasýn tmp ise iþlemlerde bana yardýmcý oldu
	degiskenler[0]=' ';//postfix ifademde boþluklar olmasý için yaptým
	int i=0,j=0,y=0;//iterator olarak kulladýgým 3 deðiþken
      removeSpaces(buffer);//stringimin içindeki boþluklarý sildim
   for(i=1;i<strlen(buffer)-2;i++)//teker teker stringimin içindeki charlarý alarak kontrol ettim switch case ile burada sayýmý,iþlem mi deðiþken mi diye kontrol edilip ona  göre üzerinde
	{                             //iþlemler yapýlýp kimisi stacke kimiside postfix ifadeye yazýlýyor
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
	printf("postfix=%s     stack=%s\n",degiskenler,sta.deger);// her adýmda yazdýrma iþlemimi gerçekleþtirdim

	}
	while(sta.top != 0){//en son stackde kalan iþlemleri sýrasý ile postfixe ekledim
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
	char readtxt[5][100],*postfix1,*postfix2,*postfix3;//readtxt matrisden okuyup yazdýgým alan postfix 1 2 3 ise readtxtden infix ifadeyi alýp postfixe çevirdikden sonra yazdýgým yerler 
	postfix1=(char*)malloc(100);                       //3 adet postfix ifade oldugu için 3 tane kullandým 
	postfix1[99]='\0';                                 //yer açtým malloc ile ve sonunu string  bitirme ifadesini ekledim
	postfix2=(char*)malloc(100);
	postfix2[99]='\0';
	postfix3=(char*)malloc(100);
	postfix3[99]='\0';
	
	int  i=0;//iteratör için
	FILE *InputFile;
	InputFile = fopen("input.txt", "r");//dosyamý okuma modunda açtým
	while(!feof(InputFile)){            //burda dosyadan okuyup readtxtde adlý matrise yazdýrdým yazdýrýrkende ayný anada her satýrýn baþýndaki harfi alýp deðiþken olarak kabul ettim
	fgets(readtxt[i],100,InputFile);    
	variables[i]=variablecheck(readtxt[i][0]);
	values[i]=atoi(&readtxt[i][4]); //ayný zamanda deðiþken olarak alýrkende eger direk deðeri verilmiþ ise onu alýp atama yapýyor ikisini ayrý ayrýp dizilerde tutdum
	i++;
	}
	//Buradada yazdýrma iþlemlerimi gerçekleþtirdim
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
