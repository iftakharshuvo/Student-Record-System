#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct student{
    char ID[15];
    char name[20];
    char add[20];
    char parname[20];
    char Class[5];
    char phoneno[20];
    float subject[5];
};

struct student stu;

///This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void window(){
    drawRectangle();
    gotoxy(28,2);
    SetColor(35);
    printf("STUDENT RECORD SYSTEM");
    gotoxy(25,3);
    printf("Iftakarul Islam Suvo's Project");
    gotoxy(27,4);
    printf("Console reference GOOGLE");
    gotoxy(25,24);
    SetColor(17);

}

void print_heading(const char st[]){
    SetColorAndBackground(31,28);
    gotoxy(45,8);printf("SRS : %s",st);
    SetColorAndBackground(17,15);
}

int conf_record(char id[]){
   // left for you
   //it checks whether the entered id for
   //new record is already in the database.
}

void add_student(){
    clearWindow();
    print_heading("Add Record");
    int print = 37;
    FILE *fp;
    fp = fopen("Suvo.txt","w");
    SetColor(45);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        gotoxy(print,10);printf("ID: ");gets(stu.ID);
        //here you can confirms the ID
        gotoxy(print,12);printf("Name: ");gets(stu.name);
        gotoxy(print,14);printf("Address: ");gets(stu.add);
        gotoxy(print,16);printf("Parent's name: ");gets(stu.parname);
        gotoxy(print,18);printf("Class: ");gets(stu.Class);
        gotoxy(print,20);printf("Phone Number: ");gets(stu.phoneno);
        fwrite(&stu, sizeof(stu), 1, fp);
        gotoxy(40,22); printf("The record is successfully added");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void search_student(){
    clearWindow();
    print_heading("Search Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0;
    gotoxy(37,10);printf("Enter ID to Search: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("Suvo.txt","r");
    while(fread(&stu,sizeof(stu),1,fp) == 1){
        if(strcmp(s_id,stu.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(37,12);printf("The record is Found");
        gotoxy(37,14);printf("ID: %s",stu.ID);
        gotoxy(37,15);printf("Name: %s",stu.name);
        gotoxy(37,16);printf("Address: %s",stu.add);
        gotoxy(37,17);printf("Parent's Name: %s",stu.parname);
        gotoxy(37,18);printf("Class: %d",stu.Class);
        gotoxy(37,19);printf("Phone No: %d",stu.phoneno);
    }else{
        gotoxy(37,12);printf("Sorry, No record found in the database");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void mod_student(){
    clearWindow();
    print_heading("Modify Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("Suvo.txt","w");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(s_id, stu.ID) == 0){
            fflush(stdin);
            gotoxy(print,12);printf("ID: ");gets(stu.ID);
            gotoxy(print,13);printf("Name: ");gets(stu.name);
            gotoxy(print,14);printf("Address: ");gets(stu.add);
            gotoxy(print,15);printf("Parent's name: ");gets(stu.parname);
            gotoxy(print,16);printf("Class: ");gets(stu.Class);
            gotoxy(print,17);printf("Phone Number: ");gets(stu.phoneno);
            fseek(fp,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        gotoxy(print, 12);printf("No Record Found");
    }
    fclose(fp);
    SetColor(28);
    return;
}

void cgpa(){
     clearWindow();
    print_heading("CGPA");
    int print = 37;
    FILE *fp;
    fp = fopen("Suvo.txt","w");
    SetColor(45);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        gotoxy(print,10);printf("ID: ");gets(stu.ID);
        //here you can confirms the ID
        gotoxy(print,12);printf("Name: ");gets(stu.name);
        gotoxy(print,14);printf("1st subject:");scanf("%f",&stu.subject[0]);
        gotoxy(print,16);printf("2nd subject: ");scanf("%f",&stu.subject[1]);
        gotoxy(print,18);printf("3rd subject: ");scanf("%f",&stu.subject[2]);
        gotoxy(print,20);printf("4th subject: ");scanf("%f",&stu.subject[3]);
        gotoxy(print,22);printf("5th subject: ");scanf("%f",&stu.subject[4]);
        float result=stu.subject[0]+stu.subject[1]+stu.subject[2]+stu.subject[3]+stu.subject[4];
        fwrite(&stu, sizeof(stu), 1, fp);
        if(result/5>=80){
                 clearWindow();
            gotoxy(print,16);printf("CGPA is 5.00 & Grade A+");
        }
        else if ((result/5>=70)&&(result/5<=80)){
             clearWindow();
            gotoxy(print,16); printf("CGPA is 4.00& Grade A ");
        }
        else if ((result/5>=60)&&(result/5<=70)){
             clearWindow();
             gotoxy(print,16);printf("CGPA is 3.50 & Grade A-");
        }
        else if ((result/5>=50)&&(result/5<=60)){
             clearWindow();
             gotoxy(print,16);printf("CGPA is 3.00 & Grade B");
        }
        else if ((result/5>=40)&&(result/5<=50)){
             clearWindow();
             gotoxy(print,16);printf("CGPA is 2.00 & Grade C");
        }
        else if ((result/5>=33)&&(result/5<=40)){
             clearWindow();
             gotoxy(print,16);printf("CGPA is 1.00 & Grade D");

        }
        else {
             clearWindow();
             gotoxy(print,16);printf("CGPA is 0.00& Grade F");
        }

    }
    //left for further enhancement
}

void delete_student(){
    clearWindow();
    print_heading("Delete Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp, *temp;
    fp = fopen("Suvo.txt","w");
    temp = fopen("temp.txt", "w");
    while(fread(&stu, sizeof(stu),1,fp) == 1){
        if(strcmp(s_id, stu.ID) == 0){
            fwrite(&stu,sizeof(stu),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Suvo.txt");
    rename("temp.txt","Suvo.txt");
    gotoxy(37,12);printf("The record is successfully deleted");
    SetColor(28);
    return;
}

void main_window(){
    int choice;
    SetColor(28);
    int x = 2;
    while(1){
        gotoxy(x,8);printf("1. Press 1 To Add Student");
        gotoxy(x,10);printf("2. Press 2 To Search Student");
        gotoxy(x,12);printf("3. Press 3 To Modify Record");
        gotoxy(x,14);printf("4. Press 4 To Delete Record");
        gotoxy(x,16);printf("5.Press 5 to Count CGPA");
        gotoxy(x,18);printf("6. Press 0 To Exit");
        gotoxy(x,20);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_student();
                break;
            case 2:
                search_student();
                break;
            case 3:
                mod_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                cgpa();
                break;
            case 0:
                exit(0);
                break;
            default:
                break;
        }

    }

}

int main(){
    ClearConsoleToColors(17,15);
    SetConsoleTitle("Iftakar Suvo - Student Record System");
    window();
    //use_pass_field();
    main_window();
    return 0;
}

