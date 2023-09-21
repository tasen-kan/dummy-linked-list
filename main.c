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
                puts("Всего доброго!");
                exit(EXIT_SUCCESS);
                break;
            default:
                puts("Некорректный ввод.");
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
        puts("Невозможно выделить память под новый элемент списка!\n");
        system("pause");
        exit(1);
    }
    return tempCpu;
}

int menu(void)
{
    int ch = 0;
    printf("S - показать список, A - добавить элемент, "
           "D - удалить элемент, I - вставить элемент в выбранную позицию, H - помощь, "
           "Q - выход\n");
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
    printf("Введите название модели процессора (не более 14 символов): ");
    s_gets(current->model, 15);
    printf("Введите тактовую частоту процессора в Гц (не более 10 символов): ");
    s_gets(current->freq, 11);
    current->next = NULL;

    puts("Узел успешно добавлен в конец списка.\n");
    puts("Нажмите Enter чтобы вернуться в меню.");
    getch();
    system("clear");
}

void showList(void)
{
    int count = 1;

    if(first == NULL)
    {
        puts("Список пуст! Сперва добавьте в него элементы.\n");
        puts("Нажмите Enter чтобы вернуться в меню.");
        getch();
        system("clear");
        return;
    }
    puts("Список:");
    current = first;
    while(current != NULL)
    {
        printf("Запись №%d: %s %s\n", count, current->model, current->freq);
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
        puts("Список пустой - удалять нечего!");
        return;
    }
    puts("Пожалуйста, выберите узел для удаления:");
    showList();
    printf("Удалить узел: ");
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
            puts("Такой записи в списке нет.");
            return;
        }
    }
    if(previous == NULL)
        first = current->next;
    else
        previous->next = current->next;

    printf("Запись №%u удалена\n\n", delNum);
    free(current);
    puts("Нажмите Enter чтобы вернуться в меню.");
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
        puts("Список пустой! Добавьте хотя бы один элемент.");
        puts("Нажмите Enter чтобы вернуться в меню.");
        getch();
        system("clear");
        return;
    }
    puts("Пожалуйста, выберите позицию куда нужно добавить новый узел:");
    showList(); // выводим список
    printf("Выберите номер узла на место которого вы хотите добавить новый узел (введите целое число): ");
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
            puts("Такой записи в списке нет.");
            return;
        }
    }

    newNode = makeNode();

    if (current == first) {
        newNode->next = current;
        first = newNode;
        printf("Введите название модели процессора (не более 14 символов): ");
        s_gets(newNode->model, 15);
        printf("Введите тактовую частоту процессора в Гц (не более 10 символов): ");
        s_gets(newNode->freq, 11);
    } else {
        previous->next = newNode;
        newNode->next = current;
        printf("Введите название модели процессора (не более 14 символов): ");
        s_gets(newNode->model, 15);
        printf("Введите тактовую частоту процессора в Гц (не более 10 символов): ");
        s_gets(newNode->freq, 11);
    }

    printf("Запись добавлена в список на позицию №%u\n\n", position);
    puts("Нажмите Enter чтобы вернуться в меню.");
    getch();
    system("clear");
    return;
}

void showHelp(void) {
    puts("Интерактивная программа для работы с односвязным списком.");
    puts("S - показать список.");
    puts("A - добавить элемент.");
    puts("D - удалить элемент.");
    puts("I - добавление нового узла в произвольную его часть.");
    puts("H - помощь.");
    puts("Q - выход.\n");
    puts("Нажмите Enter чтобы вернуться в меню.");
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
