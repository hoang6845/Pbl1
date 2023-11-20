#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <time.h>
#include<conio.h>
#include<string.h>  
#include <unistd.h>

typedef struct Element Word;

int n;
int Score=0;
int RecordC;
int RecordR;

struct Element{
    char English[100];
    char Mean[100];
    char Context[100];
};
int CheckSame(char FirstStr[], char SecondStr[]);
void GetData(Word Vocab[]);
void gotoxy(int x, int y);
void CleanScreen();
void InsertNewWord(Word Vocab[]);
char* RecoWord(Word Vocab[], char Word[]);
void LookUpWord(Word Vocab[]);
void MixingString(char str[],char vocab[]);
void RewriteWord(Word Vocab[]);
int RandomExcept(int x[],int k);
void HeadControl(int Pos, int Row);
void RenewHead(int Row);;
void SolWhatMeaning(char Chose[][20],int k);
void WhatMeaning(Word Vocab[]);
void SetTextColor(int color);
void MenuGame(int k);
void ChooseGame(Word Vocab[]);
void effect();
void Run(Word Vocab[]);
void Wall();
void MenuGame(int k);
int min(int a,int b);
void SetTextColor(int color);


int main()
{
	effect();
    SetTextColor(7);
    Word Vocab[100];
    GetData(Vocab);
    Run(Vocab);
    return 0;
}
void SetTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int CheckSame(char FirstStr[], char SecondStr[]){//kiem tra 2 xau co giong nhau khong  
    int i;
    for(i=0;i<=strlen(FirstStr);i++){
        if(FirstStr[i]!=SecondStr[i]){
            return 0;
        }
    }
    return 1;
}
void GetData(Word Vocab[]){
    FILE *file1;
    file1 = fopen("asset.data","r");
    if(file1==NULL){
        printf("Open File Error!");
        exit(1);
    }
    fscanf(file1, "%d %d %d", &n, &RecordC, &RecordR);
	fclose(file1);
    int Comma[3],count,i,j;//comma: dau phay
    char Inp[100][100];
    FILE *file;
    file = fopen("PBL1.data","r");
    if(file==NULL){
        printf("Open File Error!");
        exit(1);
    }
    for(i=0;i<n;i++){
        count=0;
        fgets(Inp[i],100,file);
        for(j=0;j<strlen(Inp[i]);j++){//vong lay tim vi tri dau phay
            if(Inp[i][j]==','){
                Comma[count]=j;
                count++;
            }
        }
        for(j=0;j<Comma[0];j++){
            Vocab[i].English[j]=Inp[i][j];
        }//tu` dau den dau phay thu 1 la english 
        for(j=Comma[0]+1;j<Comma[1];j++){
            Vocab[i].Mean[j-Comma[0]-1]=Inp[i][j];
        }//tu dau phay 1 den dau phay 2 la meaning
        for(j=Comma[1]+1;j<strlen(Inp[i]);j++){
            Vocab[i].Context[j-Comma[1]-1]=Inp[i][j];
        }//tu dau phay 2 tro di la context
    }
    fclose(file);

}
void gotoxy(int x, int y){//de lay toa do 
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x-1;
    pos.Y = y-1;
    SetConsoleCursorPosition(hCon, pos);
}
void CleanScreen(){//xoa du lieu trong wall()
    int i,j;
    for(i=12;i<70;i++){
        for(j=6;j<20;j++){
            gotoxy(i,j);
            printf(" ");
        }
    }
}
void Run(Word Vocab[]);
void InsertNewWord(Word Vocab[]){
    char NewEnglish[100];
    char NewMean[100];
    char NewContext[100];
    char NewWord[100];// ==newenglish,newmean,newcontext
    int i,j;
    gotoxy(17,9);
    printf("Enter For New Vocabulary : ");
    gets(NewEnglish);
    for(i=0;i<n;i++){
        if(CheckSame(NewEnglish,Vocab[i].English)==1){
            CleanScreen();
            gotoxy(14,7);
            printf("This Word Was Already In Dictionary!, Please Re-Enter");
            InsertNewWord(Vocab);
            return;
        }
    }
    gotoxy(22,11);
    printf("Meaning : ");
    gets(NewMean);
    gotoxy(22,13);
    printf("Context : ");
    gets(NewContext);
    for(i=0;i<strlen(NewEnglish);i++){
        NewWord[i]=NewEnglish[i];
    }
    NewWord[i]=',';
    j=i+1;
    for(i=0;i<strlen(NewMean);i++){
        NewWord[j+i]=NewMean[i];
    }
    NewWord[j+i]=',';
    j+=i+1;
    for(i=0;i<strlen(NewContext);i++){
        NewWord[j+i]=NewContext[i];
    }
    FILE *file;
    file = fopen("PBL1.data","a");
    if(file==NULL){
        printf("\nOpen File Error!");
        exit(1);
    }
    fprintf(file,"\n%s",NewWord);
    fclose(file);
    n++;
    FILE *file1;
    file1 = fopen("asset.data","w");
    if(file1==NULL){
        printf("\nOpen File Error!");
        exit(1);
    }
    fprintf(file1,"%d",n);
    fprintf(file1,"\n%d",RecordC);
    fprintf(file1,"\n%d",RecordR);
    fclose(file1);
    GetData(Vocab);
    gotoxy(43,17);
    printf("Type c To Continue");
    gotoxy(43,18);
    printf("Type b To Back");
    gotoxy(17,15);
    printf("Enter New Vocabulary Success!");
    while(1){
        char c=getch();
        if(c=='b'){
            CleanScreen();
            Run(Vocab);
            return;
        }
        if(c=='c'){
            CleanScreen();
            InsertNewWord(Vocab);
            return;
        }
    }
}

char* RecoWord(Word Vocab[], char Word[]);

void LookUpWord(Word Vocab[]){
    char Word[100];
    gotoxy(17,9);
    printf("Enter A Word : ");
    gets(Word);
    for (int i=0;i<n;i++){
        if(CheckSame(Word,Vocab[i].English)==1){//kiem tra xem Word co trong tu dien khong
        
            gotoxy(13,7);
            printf("                                                       ");
            gotoxy(17,15);
            printf("Type c To Continue");
            gotoxy(17,16);
            printf("Type b To Back");
            gotoxy(17,11);
            printf("Meaning : %s",Vocab[i].Mean);
            gotoxy(17,12);
            printf("Context : %s",Vocab[i].Context);
            gotoxy(13,17);
            printf("                                                       ");
            while(1){
                gotoxy(1,1);
                char c=getch();
                if(c=='b'){
                    CleanScreen();
                    Run(Vocab);
                    return;
                }
                if(c=='c'){
                    CleanScreen();
                    LookUpWord(Vocab);
                    return;
                }
            }
        }
    }
	
    CleanScreen();
    gotoxy(20,17);
    printf("Did you mean %s ?",RecoWord(Vocab, Word));
    gotoxy(13,7);
    printf("This Word Wasn't Already In Dictionary!,Please Re-Enter");
    LookUpWord(Vocab);
    return;

}

void MixingString(char str[],char vocab[]) {
    int len = strlen(str);
    srand((int)time(NULL));
    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    if (CheckSame(str,vocab)==1) MixingString(str,vocab);
}
void ChooseGame(Word Vocab[]);
void RewriteWord(Word Vocab[]){
	char Ans[100];//==dap an
    srand((int)time(NULL));
	int RandomNumber=(rand()%n);
	char RandomWord[100];
	for (int i=0;i<=strlen(Vocab[RandomNumber].English);i++){//luu lai tu` random
		RandomWord[i]=Vocab[RandomNumber].English[i];
	}
	MixingString(RandomWord,Vocab[RandomNumber].English);
    gotoxy(47,16);
	printf("Score : %d",Score);//diem
	gotoxy(47,17);
	printf("Record : %d",RecordR);//ki luc
	gotoxy(13,7);
	printf("Mixed Word : %s",RandomWord);//tu random da~ xao"
    gotoxy(13,8);
	printf("Context : %s",Vocab[RandomNumber].Context);//dinh nghia
	gotoxy(13,16);
    printf("Type ./ to back!");
	gotoxy(13,13);
	printf("Your Answer : ");
	gets(Ans);
	if(CheckSame(Ans,"./")){
        CleanScreen();
        Score=0;
	    FILE *file1;
	    file1 = fopen("asset.data","w");
	    if(file1==NULL){
	        printf("\nOpen File Error!");
	        exit(1);
	    }
	    fprintf(file1,"%d",n);
	    fprintf(file1,"\n%d",RecordC);
	    fprintf(file1,"\n%d",RecordR); 
		fclose(file1);       
        ChooseGame(Vocab);
        return;
	}
	if(CheckSame(Ans,Vocab[RandomNumber].English)){
        Score++;
        if (Score>RecordR) RecordR=Score;
        CleanScreen();
        gotoxy(47,13);
        SetTextColor(10);
        printf("Correct!");
        SetTextColor(7);
        gotoxy(47,14);
        printf("Solution : %s",Vocab[RandomNumber].English);
        for (int i=1000;i<4000;i+=500) Beep(i, 50);
        CleanScreen();
        RewriteWord(Vocab);
        return;
	}
	else {
        CleanScreen();
        gotoxy(47,13);
        SetTextColor(12);
        printf("Incorrect!");
        SetTextColor(7);
		gotoxy(47,14);
		printf("Solution : %s",Vocab[RandomNumber].English);
        Beep(400,1000);
        CleanScreen();
        RewriteWord(Vocab);
        return;
	}
}

int RandomExcept(int x[],int k){//ham de luu nhung chu da chon(tranh random lap. tu`)
    int i;int m;
    int RandomNumber;
    RandomNumber=(rand()%n);//random so bat ky
    for(i=0;i<k;i++){
        if(RandomNumber==x[i]) {
            RandomNumber=RandomExcept(x,k);//neu co thi goi ham de lay so khac
            
        }
    }
	return RandomNumber;
}
void HeadControl(int Pos, int Row);
void RenewHead(int Row);

void SolWhatMeaning(char Chose[][20],int k){//ham in dap an de chon
	if (k==12){
		SetTextColor(6);
    	gotoxy(13,12);
		printf("%c",62);
		gotoxy(15,12);
	}
	else gotoxy(16,12);
	printf(" A. %s ",Chose[0]);
	SetTextColor(7);
	if (k==13) { gotoxy(15,13) ;SetTextColor(6);
	}
	else gotoxy(16,13);
	printf(" B. %s ",Chose[1]);
	SetTextColor(7);
	if (k==14) { gotoxy(15,14) ;SetTextColor(6);
	}
	else gotoxy(16,14);
	printf(" C. %s ",Chose[2]);
	SetTextColor(7);
	if (k==15) { gotoxy(15,15) ;SetTextColor(6);
	}
	else gotoxy(16,15);
	printf(" D. %s ",Chose[3]);
	SetTextColor(7);
	if (k==16) { gotoxy(15,16) ;SetTextColor(6);
	}
	else gotoxy(16,16);
	printf(" E. Back ");
	SetTextColor(7);
	
	
}
void WhatMeaning(Word Vocab[]){
	srand((int)time(NULL));
	int RandomNumber=(rand()%n);//lay tu` de hoi
	int Answer[5]={0,0,0,0};
	int Except[5];
	int Count=0;
	int RightAnswer=(rand()%4);//de lay vi tri dap an
	Answer[RightAnswer]=1;//danh dau dap an dung
    gotoxy(50,13);
    printf("Score : %d",Score);
    gotoxy(50,15);
    printf("Record : %d",RecordC);
	gotoxy(18,8);
	printf("Meaning of \033[7m%s\033[0m ?",Vocab[RandomNumber].English);
	gotoxy(15,12);
	Except[Count]=RandomNumber;//Expect[0] la dap an
	Count++;
	
	char Chose[4][20];// luu du lieu cua A B C D
	
// luu dap an vao mang 2 chieu sau do in dap an
    if (Answer[0]==1) strcpy(Chose[0],Vocab[RandomNumber].Mean);//printf("A. %s",Vocab[RandomNumber].Mean)
    else {
        Except[Count]=RandomExcept(Except,Count+1);
        strcpy(Chose[0],Vocab[Except[Count]].Mean) ;//printf("A. %s",Vocab[Except[Count]].Mean);
        Count++;
    }
 
    if (Answer[1]==1) strcpy(Chose[1],Vocab[RandomNumber].Mean);//printf("B. %s",Vocab[RandomNumber].Mean);
    else {
        Except[Count]=RandomExcept(Except,Count+1);
        strcpy(Chose[1],Vocab[Except[Count]].Mean) ; //printf("B. %s",Vocab[Except[Count]].Mean);
        Count++;
    }

    if (Answer[2]==1) strcpy(Chose[2],Vocab[RandomNumber].Mean);//printf("C. %s",Vocab[RandomNumber].Mean);
    else {
        Except[Count]=RandomExcept(Except,Count+1);
        strcpy(Chose[2],Vocab[Except[Count]].Mean) ; //printf("C. %s",Vocab[Except[Count]].Mean);
        Count++;
    }
  
    if (Answer[3]==1) strcpy(Chose[3],Vocab[RandomNumber].Mean);//printf("D. %s",Vocab[RandomNumber].Mean);
    else {
        Except[Count]=RandomExcept(Except,Count+1);
        strcpy(Chose[3],Vocab[Except[Count]].Mean) ;//printf("D. %s",Vocab[Except[Count]].Mean);
        Count++;
    }
    SolWhatMeaning(Chose,12);//chay ham in dap an de chon

    
    int Pos=12,Above=12,Under=16;
    while(1){
        char c=getch();
        if(c==72){//phim mui ten di len
            RenewHead(12);Pos--;
            if(Pos<Above) Pos=Under;
            HeadControl(Pos,13);
            SolWhatMeaning(Chose,Pos);

        }
        if(c==80){//phim mui ten di xuong
            RenewHead(12);Pos++;
            if(Pos>Under) Pos=Above;
            HeadControl(Pos,13);
            SolWhatMeaning(Chose,Pos);
        }
        if(c==13){//phim enter
            Beep(2000, 100);
            if(Pos==Under){
                CleanScreen();
				Score=0;
			    FILE *file1;
			    file1 = fopen("asset.data","w");
			    if(file1==NULL){
			        printf("\nOpen File Error!");
			        exit(1);
			    }
			    fprintf(file1,"%d",n);
			    fprintf(file1,"\n%d",RecordC);
			    fprintf(file1,"\n%d",RecordR);
				fclose(file1);				
                ChooseGame(Vocab);
                return;
            }
            if(Pos==RightAnswer+12){
                CleanScreen();
                gotoxy(50,8);
                SetTextColor(10);
                printf("Correct!");
                
                SetTextColor(7);
                for (int i=1000;i<4000;i+=500) Beep(i, 50);
                CleanScreen();
                Score++;
                if (Score>RecordC) RecordC=Score;
                WhatMeaning(Vocab);
                return;
            }
            else {
                CleanScreen();
                gotoxy(50,8);
                SetTextColor(12);
                printf("Incorrect!");
                SetTextColor(7);
                Beep(400,1000);
                CleanScreen();
                WhatMeaning(Vocab);
                return;
            }
        }
    }
}



void MenuGame(int k){
    gotoxy(12,6);
    printf("Catalogue : ");
    if (k==7){
    	gotoxy(12,7);
    	SetTextColor(6);
		printf("%c",62);
		gotoxy(13,7);}
    else gotoxy(14,7);
    printf(" Choose Word ");
    SetTextColor(7); 
    if (k==8)	{SetTextColor(6); gotoxy(13,8);}
    else gotoxy(14,8);
    printf(" Rewrite ");
    if (k==8)	SetTextColor(7);
    if (k==9)	{SetTextColor(6); gotoxy(13,9);}    
    else gotoxy(14,9);
    printf(" Back ");
    if (k==9)	SetTextColor(7);
    gotoxy(1,1);
}

void ChooseGame(Word Vocab[]){
    CleanScreen();
    MenuGame(7);
    int Pos=7,Above=7,Under=9;//pos:vi tri >,above: tren,under: duoi
    while(1){
        char c=getch();
        if(c==72){//phim di len
            RenewHead(12);Pos--;
            if(Pos<Above) Pos=Under;
            HeadControl(Pos,12);
            MenuGame(Pos);
        }
        if(c==80){//phim di xuong
            RenewHead(12);Pos++;
            if(Pos>Under) Pos=Above;
            HeadControl(Pos,12);
            MenuGame(Pos);
        }
        if(c==13){//phim enter
            Beep(2000, 100);
            if(Pos==7){
                CleanScreen();
                WhatMeaning(Vocab);
                return;
            }
            if(Pos==8){
                CleanScreen();
                RewriteWord(Vocab);
                return;
            }
            if(Pos==9){
                Run(Vocab);
                return;
            }
        }
    }
}

void MainMenu(int k){
    gotoxy(12,6);
    printf("Catalogue :   ");
    if (k==7){
    	gotoxy(12,7);
    	SetTextColor(6);
		printf("%c",62);
		gotoxy(13,7);}
    else gotoxy(14,7);
    printf(" Play Game      ");
    SetTextColor(7);
    if (k==8){	SetTextColor(6);gotoxy(13,8);}
    else gotoxy(14,8);
    printf(" Add New Word    ");
    if (k==8)	SetTextColor(7);
    if (k==9){	SetTextColor(6);gotoxy(13,9);}
    else gotoxy(14,9);
    printf(" Look Up    ");
    if (k==9)	SetTextColor(7);
    if (k==10){	SetTextColor(6);gotoxy(13,10);}
    else gotoxy(14,10);
    printf(" Close    ");
    if (k==10)	SetTextColor(7);
    gotoxy(1,1);
}

void Wall(){
    int i;
    for(i=10;i<=70;i++){
        gotoxy(i,5);
        printf("%c",223);
    }
    for(i=5;i<=20;i++){
        gotoxy(10,i);
        printf("%c",219);
    }
    for(i=5;i<=20;i++){
        gotoxy(70,i);
        printf("%c",219);
    }
    for(i=10;i<=70;i++){
        gotoxy(i,20);
        printf("%c",223);
    }
    
    
}

void RenewHead(int Row){//xoa vi tri mui ten da~ di 
    int i;
    for(i=7;i<20;i++){
        gotoxy(Row,i);
        printf("  ");
    }
}

void HeadControl(int Pos, int Row){//ghi vi tri mui ten moi
    gotoxy(Row,Pos);
    SetTextColor(6);
    printf("%c",62);
    SetTextColor(7);
    gotoxy(1,1);
    Beep(1500, 50);
}

void effect(){
/*	int i;
    for (i = 0; i <= 5; i++) {
        printf("Loading... %d%%\r", i * 20);
        fflush(stdout); // Flush the output buffer

        // Sleep for a short period to simulate delay
        usleep(500000); // Sleep for 0.5 seconds
    }
    gotoxy(0,0) ;
	printf("               ");*/
    for (int i=1;i<=5;i++){
		SetTextColor(i+1);
    	gotoxy(85,i);
    	printf("DO AN LAP TRINH TINH TOAN");
    	usleep(250000);
    	gotoxy(85,i);
    	printf("                          ");
	}
	gotoxy(85,5);
	printf("\033[30;47mDO AN LAP TRINH TINH TOAN\033[0m");
	gotoxy(72,7);
	printf("\033[4m\033[1mChu de\033[0m\033[0m: \033[1mHoc tu vung tieng anh thong qua tro choi\033[0m");
	gotoxy(72,9);
	printf("\033[4m\033[1mThanh vien\033[0m\033[0m:");
	gotoxy(84,9);
	printf("Duong Quang Minh Hoang");
	gotoxy(84,10);
	printf("Nguyen Thanh Trung");
	
}
void Run(Word Vocab[]){
    CleanScreen();
    SetTextColor(7);
    Wall();
    MainMenu(7);
    int Pos=7,Above=7,Under=10;
    while(1){
        char c=getch();
        if(c==72){// Phím lên (ASCII code: 72)
            RenewHead(12);Pos--;
            if(Pos<Above) Pos=Under;
            HeadControl(Pos,12);
            MainMenu(Pos);
        }
        if(c==80){// Phím xuong (ASCII code: 80)
            RenewHead(12);Pos++;
            if(Pos>Under) Pos=Above;
            HeadControl(Pos,12);
            MainMenu(Pos);
        }
        if(c==13){
        	Beep(2000, 100);
            if(Pos==7){
                CleanScreen();
                ChooseGame(Vocab);
                return;
            }
            if(Pos==8){
                CleanScreen();
                InsertNewWord(Vocab);
                return;
            }
            if(Pos==9){
                CleanScreen();
                LookUpWord(Vocab);
                return;
            }
            if(Pos==10){
                break;
            }
        }
    }
    gotoxy(1,22);
}

int min(int a,int b){
	if (a>b) return b;
	return a;
}
char* RecoWord(Word Vocab[], char Word[]){
	int i,j;
	int Count[100];int Distance[100];
	int Site;float Compare, Max = 0;
	for(j=0;j<'z'-'a';j++){
		Count[j]=0;
		Distance[j]=0;}
	for(i=0;i<strlen(Word);i++){
		Count[(int)Word[i]-'a']++;
	}
	for(i=0;i<n;i++){
		Compare = 0;
		for(j=0;j<strlen(Vocab[i].English);j++){
			Distance[(int)Vocab[i].English[j]-'a']++;}
			for(j=0;j<'z'-'a';j++){
				Compare+=min(Distance[j],Count[j]);
			}
			Compare/=strlen(Vocab[i].English);
			if(Compare>Max){
				Site = i;Max = Compare;}
			for(j=0;j<'z'-'a';j++){
				Distance[j]=0;
			}
	}
	return Vocab[Site].English;
}

