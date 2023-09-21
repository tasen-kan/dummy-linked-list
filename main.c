#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

struct cpu
{
    char model[15];
    char freq[11];
    struct cpu * next;
};

struct cpu * first;
struct cpu * newNode;
struct cpu * current;

struct cpu * makeNode(void);
void addNode(void);
void deleteNode(void);
void showList(void);
int menu(void);
char * s_gets(char * st, int n);
void showHelp(void);
void insertNodeInSelectedPosition(void);

int main()
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);

    int choice  = 0;
    first = NULL;

    while(1)
    {
        choice = menu();
        system("clear");

        switch(choice)
        {
            case 'S':
                showList();
                break;
            case 'A':
                addNode();
                break;
            case 'D':
                deleteNode();
                break;
            case 'H':
                showHelp();
                break;
            case 'I':
                insertNodeInSelectedPosition();
                break;
            case 'Q':
                puts("����� �������!");
                exit(EXIT_SUCCESS);
                break;
            default:
                puts("������������ ����.");
                break;
        }
    }
    return 0;
}

struct cpu * makeNode(void)
{
    struct cpu * tempCpu;
    tempCpu = (struct cpu *) malloc(sizeof (struct cpu));
    if(tempCpu == NULL)
    {
        puts("���������� �������� ������ ��� ����� ������� ������!\n");
        system("pause");
        exit(1);
    }
    return tempCpu;
}

int menu(void)
{
    int ch = 0;
    printf("S - �������� ������, A - �������� �������, "
           "D - ������� �������, I - �������� ������� � ��������� �������, H - ������, "
           "Q - �����\n");
    ch = getch();
    putchar(ch); putch('\n');
    ch = toupper(ch);
    return ch;
}

void addNode(void)
{
    if(first == NULL)
    {
        first = makeNode();
        current = first;
    }
    else
    {
        current = first;
        while(current->next != NULL)
            current = current->next;
        newNode = makeNode();
        current->next = newNode;
        current = newNode;
    }
    printf("������� �������� ������ ���������� (�� ����� 14 ��������): ");
    s_gets(current->model, 15);
    printf("������� �������� ������� ���������� � �� (�� ����� 10 ��������): ");
    s_gets(current->freq, 11);
    current->next = NULL;

    puts("���� ������� �������� � ����� ������.\n");
    puts("������� Enter ����� ��������� � ����.");
    getch();
    system("clear");
}

void showList(void)
{
    int count = 1;

    if(first == NULL)
    {
        puts("������ ����! ������ �������� � ���� ��������.\n");
        puts("������� Enter ����� ��������� � ����.");
        getch();
        system("clear");
        return;
    }
    puts("������:");
    current = first;
    while(current != NULL)
    {
        printf("������ �%d: %s %s\n", count, current->model, current->freq);
        current = current->next;
        count++;
    }
}

void deleteNode(void)
{
    struct cpu * previous;
    unsigned delNum;
    unsigned num = 1;

    if(first == NULL)
    {
        puts("������ ������ - ������� ������!");
        return;
    }
    puts("����������, �������� ���� ��� ��������:");
    showList();
    printf("������� ����: ");
    scanf("%u", &delNum);
    fflush(stdin);
    current = first;
    previous = NULL;
    while(num != delNum)
    {
        previous = current;
        current = current->next;
        num++;
        if(current == NULL)
        {
            puts("����� ������ � ������ ���.");
            return;
        }
    }
    if(previous == NULL)
        first = current->next;
    else
        previous->next = current->next;

    printf("������ �%u �������\n\n", delNum);
    free(current);
    puts("������� Enter ����� ��������� � ����.");
    getch();
    system("clear");
    return;
}

void insertNodeInSelectedPosition(void)
{
    struct cpu * previous;
    unsigned position;
    unsigned num = 1;

    if(first == NULL)
    {
        puts("������ ������! �������� ���� �� ���� �������.");
        puts("������� Enter ����� ��������� � ����.");
        getch();
        system("clear");
        return;
    }
    puts("����������, �������� ������� ���� ����� �������� ����� ����:");
    showList(); // ������� ������
    printf("�������� ����� ���� �� ����� �������� �� ������ �������� ����� ���� (������� ����� �����): ");
    scanf("%u", &position);
    fflush(stdin);

    current = first;
    previous = NULL;
    while(num != position)
    {
        previous = current;
        current = current->next;
        num++;
        if(current == NULL)
        {
            puts("����� ������ � ������ ���.");
            return;
        }
    }

    newNode = makeNode();

    if (current == first) {
        newNode->next = current;
        first = newNode;
        printf("������� �������� ������ ���������� (�� ����� 14 ��������): ");
        s_gets(newNode->model, 15);
        printf("������� �������� ������� ���������� � �� (�� ����� 10 ��������): ");
        s_gets(newNode->freq, 11);
    } else {
        previous->next = newNode;
        newNode->next = current;
        printf("������� �������� ������ ���������� (�� ����� 14 ��������): ");
        s_gets(newNode->model, 15);
        printf("������� �������� ������� ���������� � �� (�� ����� 10 ��������): ");
        s_gets(newNode->freq, 11);
    }

    printf("������ ��������� � ������ �� ������� �%u\n\n", position);
    puts("������� Enter ����� ��������� � ����.");
    getch();
    system("clear");
    return;
}

void showHelp(void) {
    puts("������������� ��������� ��� ������ � ����������� �������.");
    puts("S - �������� ������.");
    puts("A - �������� �������.");
    puts("D - ������� �������.");
    puts("I - ���������� ������ ���� � ������������ ��� �����.");
    puts("H - ������.");
    puts("Q - �����.\n");
    puts("������� Enter ����� ��������� � ����.");
    getch();
    system("clear");
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            fflush(stdin);
    }
    return ret_val;
}
