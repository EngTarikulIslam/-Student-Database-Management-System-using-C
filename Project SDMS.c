#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>

#define Student struct Stud

void addRecord(FILE *fp);
void modify(FILE *fp);
void display(FILE *fp);
void Indivisual(FILE *fp);
FILE *delRecord(FILE *fp);
void printChar(char ch,int n);
FILE *tp;


struct Stud{
    char name[100];
    char dept[50];
    int ID;
    float sgpa[12];
    float cgpa;
};


int main(){
    FILE * fp;
    Student s;
    int option;
    printf("\n\n\t\t\t");
    
    printChar('=',49);
    printf("\n\t\t\t");
    printChar('*',49);
    printf("\n\t\t\tWELCOME TO GUB STUDENT DATABASE MANAGEMENT SYSTEM\n\t\t\t");
    printChar('*',49);
    printf("\n\t\t\t");
    printChar('=',49);

    if((fp=fopen("db.txt","rb+"))==NULL){
        if((fp=fopen("db.txt","wb+"))==NULL){
            printf("Can't create or open Database.");
            return 0;
        }
    }
    while(1){
        printf("\n\n1. Add Student Recors\n");
        printf("2. Modify Student Recors\n");
        printf("3. Show All Student Recors\n");
        printf("4. Individual View Recors\n");
        printf("5. Remove Student Recors\n");
        printf("6. Exit Programm\n");
        printf("\nEnter Your Option :==> ");
        scanf("%d",&option);

        switch(option){
            case 1:
                addRecord(fp);
                break;
            case 2:
                modify(fp);
                break;
            case 3:
                display(fp);
                break;
            case 4:
                Indivisual(fp);
                break;
            case 5:
                fp=delRecord(fp);
                break;
            case 6:
                return 1;
                break;
            default:
                printf("\n\t\tNo Action Detected");
                printf("\n\t\tPress Any Key\n\n\n");
                system("pause");
        }
    }
    return 1;
}


void printChar(char ch,int n){
    while(n--)
        putchar(ch);
}

 void addRecord(FILE * fp){
    char another='y';
    Student s;
    int i;
    float cgpa;

    fseek(fp,0,SEEK_END);
    while(another=='y'||another=='Y'){

        printf("\n\tEnter Full Name of Student\t: ");
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';

        printf("\tEnter Depertment Name\t\t: ");
        fflush(stdin);
        fgets(s.dept,50,stdin);
        s.dept[strlen(s.dept)-1]='\0';

        printf("\tEnter Student ID\t\t: ");
        scanf("%d",&s.ID);

        printf("\tEnter GPA for 12 semesters\t: ");
        for(i=0,cgpa=0; i<12; i++){
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];
        }

        cgpa/=12.0;
        s.cgpa=cgpa;
        fwrite(&s,sizeof(s),1,fp);

        printf("\n\tAdd another student?(Y/N): ");
        fflush(stdin);
        another=getchar();
    }
}


FILE * delRecord(FILE * fp){
    Student s;
    int flag=0,tempID,siz=sizeof(s);
    FILE *ft;

    if((ft=fopen("temp.txt","wb+"))==NULL){
        printf("\n\n\t\t\t\t!!! ERROR !!!\n\t\t");
        system("pause");
        return fp;
    }
    printf("\n\n\tEnter Student ID to Delete the Record");
    printf("\n\tStudent ID: ");
    scanf("%d",&tempID);

    rewind(fp);
    while((fread(&s,siz,1,fp))==1){
        if(s.ID==tempID){
            flag=1;
            printf("\n\tRecord Deleted for");
            printf("\n\tName\t\t:%s\n\tDepertment\t:%s\n\tID\t\t:%d\n",s.name,s.dept,s.ID);
            printf("\n\t");
            printChar('-',60);
            printf("\n\n\n\t");
            printChar('*',60);
            printf("\n");
            continue;
        }

        fwrite(&s,siz,1,ft);
    }

    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt","db.txt");

    if((fp=fopen("db.txt","rb+"))==NULL){
        printf("ERROR");
        return  NULL;
    }

    if(flag==0){
        printf("\n\tNO STUDENT FOUND WITH THE INFORMATION\n");
        printf("\n\t");
        system("pause");
        return fp;
    }
}

void modify(FILE * fp){
    Student s;
    int i,flag=0,tempID,siz=sizeof(s);
    float cgpa;

    printf("\n\n\tEnter Student ID to MODIFY the Record : ");
    scanf("%d",&tempID);

    rewind(fp);
    while((fread(&s,siz,1,fp))==1){
        if(s.ID==tempID){
            flag=1;
            break;
        }
    }

    if(flag==1){
        fseek(fp,-siz,SEEK_CUR);
        printf("\n\t\t\tRecord Found\n\t");
        printChar('-',40);
        printf("\n\tStudent Name\t: %s",s.name);
        printf("\n\tStudent ID\t: %d\n\t",s.ID);
        printChar('-',40);
        
        printf("\n\n\tEnter New Data for the Student\n\t");
        printChar('-',40);
    
        printf("\n\tEnter Full Name\t\t: ");
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';

        printf("\tEnter Department\t: ");
        fflush(stdin);
        fgets(s.dept,50,stdin);
        s.dept[strlen(s.dept)-1]='\0';

        printf("\tEnter Student ID\t: ");
        scanf("%d",&s.ID);

        printf("\tEnter GPA for 12 sem.\t: ");
        for(i=0,cgpa=0; i<12; i++){
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];
        }
        cgpa/=12.0;

        fwrite(&s,sizeof(s),1,fp);
    }

    else printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");

    printf("\n\n\t");
    system("pause");

}

void display(FILE * fp){
    Student s;
    int i,siz=sizeof(s);

    rewind(fp);
    while((fread(&s,siz,1,fp))==1){
        printf("\n\tNAME\t\t\t\t: %s",s.name);
        printf("\n\tDepertment\t\t\t: %s",s.dept);
        printf("\n\tID\t\t\t\t: %d",s.ID);
        printf("\n\tGPA\t\t\t\t: ");

        for(i=0; i<12; i++)
            printf("| %.2f |",s.sgpa[i]);
            printf("\n\tCGPA\t\t\t\t: %.2f\n\t",s.cgpa);
            printChar('-',60);
    }
    printf("\n\n\n\t");
    printChar('*',60);
    printf("\n\n\t");
    system("pause");
}

void Indivisual(FILE *fp){
    int tempID,flag,siz,i;
    Student s;
    char another='y';

    siz=sizeof(s);
    while(another=='y'||another=='Y'){
        printf("\n\n\tEnter Student ID: ");
        scanf("%d",&tempID);

        rewind(fp);

        while((fread(&s,siz,1,fp))==1){
            if(s.ID==tempID){
                flag=1;
                break;
            }
        }
        if(flag==1){
            printf("\tNAME \t\t: %s\n",s.name);
            printf("\tDepartment \t: %s\n",s.dept);
            printf("\tID \t\t: %d\n",s.ID);
            printf("\tGPA: ");

            for(i=0; i<12; i++)
                printf("| %.2f |",s.sgpa[i]);
                printf("\n\n\tCGPA \t\t: %.2f\n\t",s.cgpa);
                printChar('-',60);
        }
        else printf("\n\n\t!!!! ERROR RECORD NOT FOUND !!!!");
        printf("\n\n\tShow another student information? (Y/N)?");
        fflush(stdin);
        another=getchar();
    }
}