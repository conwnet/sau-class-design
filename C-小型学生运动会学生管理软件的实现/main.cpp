#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比赛项目
struct Item {
    char name[31]; // 比赛项目名称
    int score; // 比赛项目成绩
    
    // 构造函数
    Item(const char *name, int score) {
        strcpy(this->name, name);
        this->score = score;
    }
};

// 学院
struct College {
    char name[31]; // 学院名称
    int number; // 学院编号
    Item *item; // 比赛项目
    int size; // 比赛项目数量

    College() {}

    College(const char *name, int number) {
        strcpy(this->name, name);
        this->number = number;
        size = 10;
        item = (Item *)malloc(sizeof(Item) * size);
        item[0] = Item("50米", 0);
        item[1] = Item("100米", 0);
        item[2] = Item("200米", 0);
        item[3] = Item("400米", 0);
        item[4] = Item("1500米", 0);
        item[5] = Item("跳高", 0);
        item[6] = Item("跳远", 0);
        item[7] = Item("标枪", 0);
        item[8] = Item("铅球", 0);
        item[9] = Item("铁饼", 0);
    }

    void input() {
        int option;
        while(true) {
            printf("请选择是数据录入模式：\n\t1.批量录入\n\t2.单项录入\n\t0.返回主菜单\n");
            scanf("%d", &option);
            if (option == 1) {
                for (int i = 0; i < size; i++) {
                    printf("请输入 %s %s 的成绩：\n", name, item[i].name);
                    scanf("%d", &item[i].score);
                }
                break;
            } else if (option == 2) {
                printf("请选择要录入的项目：\n");
                for (int i = 0; i < size; i++) {
                    printf("%d.%s\n", i + 1, item[i].name);
                }
                scanf("%d", &option);
                printf("请输入 %s %s 的成绩：\n", name, item[option - 1].name);
                scanf("%d", &item[option - 1].score);
            } else if (option == 0) {
                break;
            }
        }
    }

    void change() {
        int option;
        printf("您正在修改 %s 的数据，请选择要修改的项目：\n", name);
        for (int i = 0; i < size; i++) {
            printf("%d.%s\n", i + 1, item[i].name);
        }
        scanf("%d", &option);
        printf("%s %s 原成绩为 %d，请输入新成绩：\n", name,
            item[option - 1].name, item[option - 1].score);
        scanf("%d", &item[option - 1].score);
    }

    int sum() {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += item[i].score;
        }
        return sum;
    }
};

// 程序初始化时从文件读入已保存数据
int read(College arr[]) {
    FILE *fp = fopen("data.txt", "r");
    if (!fp) return 0;
    char name[31], _name[31];
    int size, number, _size, score;
    fscanf(fp, "%d", &size);
    for(int i = 0; i < size; i++) {
        fscanf(fp, "%s%d%d", name, &number, &_size);
        arr[i] = College(name, number);
        arr[i].size = _size;
        arr[i].item = (Item *)malloc(sizeof(Item) * _size);
        for (int j = 0; j < _size; j++) {
            fscanf(fp, "%s%d", _name, &score);
            arr[i].item[j] = Item(_name, score);
        }
    }
    fclose(fp);
    return size;
}

// 每次操作后保存数据
void save(College arr[], int size) {
    FILE *fp = fopen("data.txt", "w");
    if (!fp) return;
    fprintf(fp, "%d\n", size);
    for(int i = 0; i < size; i++) {
        fprintf(fp, "%s %d %d\n", arr[i].name, arr[i].number, arr[i].size);
        for (int j = 0; j < arr[i].size; j++) {
            fprintf(fp, "%s %d\n", arr[i].item[j].name, arr[i].item[j].score);
        }
    }
    fclose(fp);
}

/*
输出学院列表，根据 type 修改输出类型
type:
    0 -> 列表
    1 -> 录入
    2 -> 修改
    3 -> 总分
*/
void list(College arr[], int size, int type) {
    int option;
    if (type == 1 || type == 2) printf("请选择学院：\n");
    for (int i = 0; i < size; i++) {
        printf("\t%d\t%d\t%s", i + 1, arr[i].number, arr[i].name);
        if (type == 3) printf("\t%d", arr[i].sum());
        putchar('\n');
    }
    if (type == 1) {
        scanf("%d", &option);
        arr[option - 1].input();
    } else if (type == 2) {
        scanf("%d", &option);
        arr[option - 1].change();
    }
}

// 添加一个学院
College add() {
    char name[31];
    int number;
    printf("请输入学院名称：\n");
    scanf("%s", name);
    printf("请输入学院编号：\n");
    scanf("%d", &number);
    return College(name, number);
}

// 学院排序
College *sort(College arr[], int size) {
    for(int i = size - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j].sum() < arr[j + 1].sum()) {
                College c = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = c;
            }
        }
    }
    return arr;
}

// 打印菜单
int menu() {
    int option;
    printf("\n--------------------\n");
    printf("1.学院列表\n");
    printf("2.添加学院\n");
    printf("3.录入成绩\n");
    printf("4.修改成绩\n");
    printf("5.输出总分\n");
    printf("6.总分排序\n");
    printf("0.退出系统\n");
    printf("--------------------\n");
    scanf("%d", &option);
    return option;
}

// 主函数入口
int main()
{
    College arr[1024];
    int size = read(arr);
    while(true) {
        int option = menu();
        switch (option) {
            case 1: list(arr, size, 0); break;
            case 2: arr[size++] = add(); break;
            case 3: list(arr, size, 1); break;
            case 4: list(arr, size, 2); break;
            case 5: list(arr, size, 3); break;
            case 6: list(sort(arr, size), size, 3); break;
            case 0: return 0;
        }
        save(arr, size);
    }

    return 0;
}

