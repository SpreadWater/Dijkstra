#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define SIZE 8
#define INF 1000000//表示无穷大的数

typedef struct node {
    int status;//节点的状态标识符，1表示访问，0表示未访问
    int length;//表示该节点到源节点的距离
    int ID;//表示该节点的位置
    struct node *preNode[SIZE];//表示连接该节点的前一个节点
} Node;

//由于C语言中没有容器的概念，所以设计用链表的方式记录多条路径
typedef struct pathLinkList {
    char *path;
    struct pathLinkList *next;
} PATHLINKLIST;

Node dijkstra(int source, int destination);//定义最短路径算法

void initData();//初始化操作

void collectNode(Node node, char *path,PATHLINKLIST *paths);//收集每条最短路径

void IdName(int id);//ID转名字输出

void printLoad(char *path);//打印单条路径

int isEnd(Node node);//判断是否是最后一个节点,返回1表示不是最后一个节点，返回0表示是最后一个节点

char *addPath(char *path,char point);//由于C语言的字符拼接不是返回一个新的地址，所以需要自己实现JAVA的字符串“+”操作


/*
 * 使用邻接矩阵的方法来存储无向图
 */
int dataSource[SIZE][SIZE];

Node nodes[SIZE];//用于表示节点的状态和距离源节点的长度

//由于C语言没有容器这个封装好的工具，用DFS+递归算法遍历类似于树的最短路径，

char path[20];//记录单条路径

int source, destination;

int main() {
    //初始化
    PATHLINKLIST *paths=(PATHLINKLIST *)malloc(sizeof(PATHLINKLIST));
    paths->next=NULL;
    initData();
    //最短路径算法计算
    Node result = dijkstra(source - 1, destination - 1);

    printf("The Shortest path length:%d\n", result.length);
    printf("The Shortest path:\n");
    //输出最短路径
    collectNode(result, path,paths);
    paths=paths->next;
    while (paths!=NULL){
        printLoad(paths->path);
        paths=paths->next;
    }
    return 0;
}

void initData() {
    /*
     * 初始化数据
     */
    //开始时，设置每一个点都不可达
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            dataSource[i][j] = INF;
        }
    }
    printf("-----Welcome to The Dijkstra Test--------\n");
    while (1) {
        printf("Please input the source of the city\n");
        scanf("%d", &source);
        printf("Please input the destination of the city\n");
        scanf("%d", &destination);
        if (source == destination) {
            printf("Please input the correct source and destination");
        } else {
            break;
        }
    }
    path[0]=destination+'0';
//    dataSource[0][1] = 24;    //测试数据
//    dataSource[0][2] = 47;
//    dataSource[0][5] = 70;
//    dataSource[1][2] = 25;
//    dataSource[1][4] = 120;
//    dataSource[2][3] = 23;
//    dataSource[2][4] = 88;
//    dataSource[2][5] = 66;
//    dataSource[3][5] = 31;
//    dataSource[3][6] = 42;
//    dataSource[4][5] = 31;
//    dataSource[4][7] = 29;
//    dataSource[5][6] = 74;
//    dataSource[5][7] = 79;
//    dataSource[6][7] = 66;


// 测试多路径情况
    dataSource[0][1] = 2;
    dataSource[0][2] = 3;
    dataSource[1][3] = 3;
    dataSource[2][3] = 2;
    dataSource[3][4] = 2;
    dataSource[3][5] = 3;
    dataSource[4][6] = 3;
    dataSource[5][6] = 2;


    nodes[0].ID = 1;
    nodes[1].ID = 2;
    nodes[2].ID = 3;
    nodes[3].ID = 4;
    nodes[4].ID = 5;
    nodes[5].ID = 6;
    nodes[6].ID = 7;
    nodes[7].ID = 8;
    int temp = INF;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (dataSource[i][j] == temp)
                dataSource[i][j] = dataSource[j][i];
        }
    }
}

/*
 * 广度遍历每个节点，计算出每个节点到源节点的最短路径长度和最短路径
 */
Node dijkstra(int source, int destination) {

    int i, j, k, l;
    /*
     * 初始化
     */
    for (i = 0; i < SIZE; i++) {
        nodes[i].status = 0;//初始化nodes都没有被访问
        nodes[i].length = dataSource[source][i];//初始化每个节点到源节点的距离
    }

    nodes[source].status = 1;
    //默认源节点被访问了。避免后面出现源节点还有前继节点的bug
    for (int m = 0; m < SIZE; ++m) {
        nodes[source].preNode[m] = NULL;
    }

    /*
     * 选择中间节点（到源节点距离最短的一个节点）注意这里是SIZE-1，因为只需要寻找除源点以外的点
     */
    for (j = 0; j < SIZE - 1; j++) {
        int min = INF;
        int postion;//记录该节点的位置

        for (k = 0; k < SIZE; ++k) {
            if (!nodes[k].status && nodes[k].length < min) {
                //如果该节点为被访问，并且该节点的长度小于最小长度
                postion = k;//找到该中间节点
                min = nodes[k].length;
            }
        }
        //如果该节点最短，并且这个距离等于直接相连的距离。（表示该点与源点直接相连）
        if (nodes[postion].length == dataSource[source][postion]) {
            for (int m = 0; m < SIZE; ++m) {
                if (nodes[postion].preNode[m] == NULL) {
                    nodes[postion].preNode[m] = &nodes[source];
                    break;
                }
            }
        }
        nodes[postion].status = 1;//设置该中间节点已被访问

        /*
         * 找到了中间节点，再去更新其他节点（除源节点和中间节点）到源节点的距离
         */
        for (l = 0; l < SIZE; ++l) {
            if (!nodes[l].status && (nodes[l].length >= (nodes[postion].length + dataSource[postion][l]))) {
                //该节点到源点的距离大于   该节点到中间节点的距离+中间节点到源节点的距离

                //更新节点l到源节点的距离
                nodes[l].length = nodes[postion].length + dataSource[postion][l];
                //通过轮询查询的方法去插入前继节点
                for (int m = 0; m < SIZE; ++m) {
                    if (nodes[l].preNode[m] == NULL) {
                        nodes[l].preNode[m] = &nodes[postion];
                        break;
                    }
                }

            }
        }
    }
    return nodes[destination];
}
//打印单条路径
void printLoad(char *path){
    int length=strlen(path);
    for (int i = length-1; i >=0; i--) {
        printf("%c",path[i]);
//        IdName(path[i]-'0');
        if (i!=0){
            printf("---->");
        }
    }
    printf("\n");
}

void IdName(int id) {
    switch (id) {
        case 0:
            printf("重庆");
            break;
        case 1:
            printf("北京");
            break;
        case 2:
            printf("成都");
            break;
        case 3:
            printf("上海");
            break;
        case 4:
            printf("深圳");
            break;
        case 5:
            printf("杭州");
            break;
        case 6:
            printf("广州");
            break;
        case 7:
            printf("武汉");
            break;
    }
}

//判断是否是最后一个节点
int isEnd(Node node) {
    int result = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (node.preNode[i] != NULL) {
            result = 1;
            break;
        }
    }
    return result;
}

char *addPath(char *path,char point){

    int before=strlen(path);

    char *newpath=(char *)malloc(before+2);//给最后一个地方添加结束标识符

    for (int i = 0; i <before+2 ; ++i) {
        if (i<=before-1){
            newpath[i]=path[i];
        }
        if (before-1<i&&i<=before){
            newpath[i]=point;
        }
        if (i==before+1){
            newpath[i]='\0';
        }
    }
    return newpath;
}
void collectNode(Node node, char *path,PATHLINKLIST *paths) {
    for (int i = 0; i < SIZE; ++i) {
        if (!isEnd(node)) {
            //pathLink的拼接
            PATHLINKLIST *temp=(PATHLINKLIST *)malloc(sizeof(PATHLINKLIST));
            temp->next=NULL;
            temp->path=path;
            //多条路径的连接
            while (paths!=NULL){
                if (paths->next==NULL){
                    paths->next=temp;
                    paths=paths->next;
                }
                paths=paths->next;
            }
        }
        if (node.preNode[i] == NULL) {
            return;
        } else {
            //单个节点的拼接，中序遍历保存路径的方法去遍历所有路径
            collectNode(*node.preNode[i], addPath(path,node.preNode[i]->ID + '0'),paths);
        }
    }
}



