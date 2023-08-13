#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct student
{
    int roll_no;
    char class[10];
    char name[30];
    char date[12];
} s; // structure of student entity

FILE *fp = NULL;       // file pointer
long size = sizeof(s); // size of structure

// prototypes of various functions used inside this project
void input();
void display();
void search();
void search_by_roll();
void search_by_name();
void modify();
void delete ();
void sort();
int main()
{
    int choice;
    while (1) // this loop will repeat the specified task infinite times
    {
        system("cls");
        printf("<--SCHOOL MANAGEMENT-->\n\n");
        printf("1.Take Admission\n");
        printf("2.Student data\n");
        printf("3.Search student\n");
        printf("4.Modify Data Record\n");
        printf("5.Delete stored Record\n");
        printf("6.Sort the data by roll_no.\n");
        printf("0.Exit\n\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n");
            input();
            break;
        case 2:
            display();
            break;
        case 3:
            search();
            break;
        case 4:
            printf("\n");
            modify();
            break;
        case 5:
            delete ();
            break;
        case 6:
            sort();
            break;
        case 0:
            exit(0);
        }
        printf("\n\nPress any key to continue.....");
        getch();
    }
    return 0;
}
void input()
{
    char my_date[10];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(my_date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, my_date);
    fp = fopen("stud.txt", "ab");
    printf("Enter Student name: ");
    fflush(stdin);
    gets(s.name); // allow space between name
    printf("Enter class: ");
    fflush(stdin);
    gets(s.class);
    printf("Enter roll number: ");
    scanf("%d", &s.roll_no);
    fwrite(&s, size, 1, fp);
    printf("\nRecord saved successfully.....");
    fclose(fp);
}

void display()
{
    system("cls");
    printf(">--STUDENT INFO--<\n\n");
    printf("%-30s %-20s %-10s %s\n", "NAME", "CLASS", "ROLL NO.", "DATE");
    fp = fopen("stud.txt", "rb");
    while (fread(&s, size, 1, fp) == 1)
    {
        printf("%-30s %-20s %-10d %s\n", s.name, s.class, s.roll_no, s.date);
    }
    fclose(fp);
}

void search()
{
    int ch;
    while (1)
    {
        system("cls");
        printf("<--SEARCH-->\n\n");
        printf("0.Main menu\n");
        printf("1.Search by Roll\n");
        printf("2.Search by Name\n");
        printf("\n Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            return;
        case 1:
            printf("\n");
            search_by_roll();
            break;
        case 2:
            printf("\n");
            search_by_name();
            break;
        }
        printf("\n\npress any key to continue.....");
        getch();
    }
}
void search_by_roll()
{
    int roll, flag = 0;
    printf("Enter Roll no. to search: ");
    fflush(stdin);
    scanf("%d", &roll);
    fp = fopen("stud.txt", "rb");
    while (fread(&s, size, 1, fp) == 1)
    {
        if (roll == s.roll_no)
        {
            flag = 1;
            printf("\n");
            printf("%-30s %-20s %-10s %s\n", "NAME", "CLASS", "ROLL NO.", "DATE");
            printf("%-30s %-20s %-10d %s\n", s.name, s.class, s.roll_no, s.date);
            break;
        }
    }
    fclose(fp);
    if (flag == 0)
    {
        printf("\n\nRecord not found.....\n");
    }
    else
    {
        printf("\n\nSearch successfull.....\n");
    }
}
void search_by_name()
{
    char nme[30];
    int f = 0;
    printf("Enter name to search: ");
    fflush(stdin);
    gets(nme);
    fp = fopen("stud.txt", "rb");
    while (fread(&s, size, 1, fp) == 1)
    {
        if (strcmpi(nme, s.name) == 0)
        {
            f = 1;
            printf("\n");
            printf("%-30s %-20s %-10s %s\n", "NAME", "CLASS", "ROLL NO.", "DATE");
            printf("%-30s %-20s %-10d %s\n", s.name, s.class, s.roll_no, s.date);
            break;
        }
    }
    fclose(fp);
    if (f == 0)
    {
        printf("\n\nRecord not found.....\n");
    }
    else
    {
        printf("\n\nSearch successfull.....\n");
    }
}
void modify()
{
    int roll, flag = 0;
    printf("Enter roll to modify: ");
    fflush(stdin);
    scanf("%d", &roll);
    fp = fopen("stud.txt", "rb+");
    while (fread(&s, size, 1, fp) == 1)
    {
        if (roll == s.roll_no)
        {
            flag = 1;
            printf("\n");
            printf("Enter student's new name: ");
            fflush(stdin);
            gets(s.name);
            printf("Enter new class: ");
            fflush(stdin);
            gets(s.class);
            printf("Enter new roll number: ");
            scanf("%d", &s.roll_no);
            fseek(fp, -size, 1);
            fwrite(&s, size, 1, fp);
            fclose(fp);
            break;
        }
    }
    if (flag == 0)
    {
        printf("\n\nStudent does not exist\n");
    }
    else
    {
        printf("\n\nRecord modified successfully\n");
    }
}
void delete ()
{
    int roll, flag = 0;
    printf("\n");
    printf("Enter Roll no. to delete from record: ");
    fflush(stdin);
    scanf("%d", &roll);
    FILE *ft = NULL;
    fp = fopen("stud.txt", "rb");
    ft = fopen("temp.txt", "ab");
    while (fread(&s, size, 1, fp) == 1)
    {
        if (roll == s.roll_no)
        {
            flag = 1;
        }
        else
        {
            fwrite(&s, size, 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("stud.txt");
    rename("temp.txt", "stud.txt");
    if (flag == 0)
    {
        printf("\n\nRoll no. does not exist\n");
    }
    else
    {
        printf("\n\nRecord deleted successfully\n");
    }
}
void sort()
{
    int index = 0;
    struct student s1[50];
    fp = fopen("stud.txt", "rb");
    while (fread(&s, size, 1, fp))
    {
        s1[index++] = s;
    }

    for (int i = 0; i < index - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < index; j++)
        {
            if (s1[min].roll_no > s1[j].roll_no)
                min = j;
        }

        if (min != i)
        {
            struct student temp = s1[min];
            s1[min] = s1[i];
            s1[i] = temp;
        }
    }
    system("cls");
    printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
    for (int i = 0; i < index; i++)
    {
        printf("%-30s %-20s %-10d %s\n", s1[i].name, s1[i].class, s1[i].roll_no, s1[i].date);
    }
}