#include <stdio.h>

#define SIZE 8
#define INF 1000000//表示无穷大的数

typedef struct node {
    int status;//节点的状态标识符，1表示访问，0表示未访问
    int length;//表示该节点到源节点的距离
    int ID;//表示该节点的位置
    struct node *preNode;//表示连接该节点的前一个节点
} Node;

Node dijkstra(int source, int destination);//定义最短路径算法

void initData();

void IdName(int id);

/*
 * 使用邻接矩阵的方法来存储无向图
 */
int dataSource[SIZE][SIZE];

Node nodes[SIZE];//用于表示节点的状态和距离源节点的长度


int source, destination;

int main() {
    initData();
    Node result = dijkstra(source - 1, destination - 1);
    printf("The Shortest path length:%d\n", result.length);
    printf("The Shortest path:");
    while (result.preNode != NULL) {
        IdName(result.ID);
        printf("<-----");
        result = *result.preNode;
    }
    IdName(result.ID);
    return 0;
}

void initData() {
    /*
     * 初始化数据
     */
    //开始时，设置没一个点都不可达
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            dataSource[i][j] = INF;
        }
    }
    printf("-----Welcome to The Dijkstra Test--------\n");
    while (1){
        printf("Please input the source of the city\n");
        scanf("%d", &source);
        printf("Please input the destination of the city\n");
        scanf("%d", &destination);
        if (source==destination){
            printf("Please input the correct source and destination");
        }else{
            break;
        }
    }
    dataSource[0][1] = 24;    //测试数据
    dataSource[0][2] = 47;
    dataSource[0][5] = 70;
    dataSource[1][2] = 25;
    dataSource[1][4] = 120;
    dataSource[2][3] = 23;
    dataSource[2][4] = 88;
    dataSource[2][5] = 66;
    dataSource[3][5] = 31;
    dataSource[3][6] = 42;
    dataSource[4][5] = 31;
    dataSource[4][7] = 29;
    dataSource[5][6] = 74;
    dataSource[5][7] = 79;
    dataSource[6][7] = 66;

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
    nodes[source].status = 1;//默认源节点被访问了。避免后面出现源节点还有前继节点的bug
    nodes[source].preNode = NULL;
    /*
     * 选择中间节点（到源节点距离最短的一个节点）
     */
    for (j = 0; j < SIZE; j++) {
        int min = INF;
        int postion;//记录该节点的位置

        for (k = 0; k < SIZE; ++k) {
            if (!nodes[k].status && nodes[k].length < min) {
                //如果该节点为被访问，并且该节点的长度小于最小长度
                postion = k;//找到该中间节点
                min = nodes[k].length;
            }
        }
        //如果该中间节点的前继节点为空，则它的前继节点是源节点
        if (nodes[postion].preNode == NULL) {
            nodes[postion].preNode = &nodes[source];
        }
        nodes[postion].status = 1;//设置该中间节点已被访问

        /*
         * 找到了中间节点，再去更新其他节点（除源节点和中间节点）到源节点的距离
         */
        for (l = 0; l < SIZE; ++l) {
            if (!nodes[l].status && (nodes[l].length > (nodes[postion].length + dataSource[postion][l]))) {
                //该节点到源点的距离大于   该节点到中间节点的距离+中间节点到源节点的距离

                //更新节点l到源节点的距离
                nodes[l].length = nodes[postion].length + dataSource[postion][l];
                //记录前继节点
                nodes[l].preNode = &nodes[postion];
            }
        }
    }
    return nodes[destination];
}
void IdName(int id){
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


