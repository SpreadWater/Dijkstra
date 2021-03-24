#include <stdio.h>

#define SIZE 8
#define INF 1000000//��ʾ��������

typedef struct node {
    int status;//�ڵ��״̬��ʶ����1��ʾ���ʣ�0��ʾδ����
    int length;//��ʾ�ýڵ㵽Դ�ڵ�ľ���
    int ID;//��ʾ�ýڵ��λ��
    struct node *preNode;//��ʾ���Ӹýڵ��ǰһ���ڵ�
} Node;

Node dijkstra(int source, int destination);//�������·���㷨

void initData();

void IdName(int id);

/*
 * ʹ���ڽӾ���ķ������洢����ͼ
 */
int dataSource[SIZE][SIZE];

Node nodes[SIZE];//���ڱ�ʾ�ڵ��״̬�;���Դ�ڵ�ĳ���


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
     * ��ʼ������
     */
    //��ʼʱ������ûһ���㶼���ɴ�
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
    dataSource[0][1] = 24;    //��������
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
 * ��ȱ���ÿ���ڵ㣬�����ÿ���ڵ㵽Դ�ڵ�����·�����Ⱥ����·��
 */
Node dijkstra(int source, int destination) {

    int i, j, k, l;
    /*
     * ��ʼ��
     */
    for (i = 0; i < SIZE; i++) {
        nodes[i].status = 0;//��ʼ��nodes��û�б�����
        nodes[i].length = dataSource[source][i];//��ʼ��ÿ���ڵ㵽Դ�ڵ�ľ���
    }
    nodes[source].status = 1;//Ĭ��Դ�ڵ㱻�����ˡ�����������Դ�ڵ㻹��ǰ�̽ڵ��bug
    nodes[source].preNode = NULL;
    /*
     * ѡ���м�ڵ㣨��Դ�ڵ������̵�һ���ڵ㣩
     */
    for (j = 0; j < SIZE; j++) {
        int min = INF;
        int postion;//��¼�ýڵ��λ��

        for (k = 0; k < SIZE; ++k) {
            if (!nodes[k].status && nodes[k].length < min) {
                //����ýڵ�Ϊ�����ʣ����Ҹýڵ�ĳ���С����С����
                postion = k;//�ҵ����м�ڵ�
                min = nodes[k].length;
            }
        }
        //������м�ڵ��ǰ�̽ڵ�Ϊ�գ�������ǰ�̽ڵ���Դ�ڵ�
        if (nodes[postion].preNode == NULL) {
            nodes[postion].preNode = &nodes[source];
        }
        nodes[postion].status = 1;//���ø��м�ڵ��ѱ�����

        /*
         * �ҵ����м�ڵ㣬��ȥ���������ڵ㣨��Դ�ڵ���м�ڵ㣩��Դ�ڵ�ľ���
         */
        for (l = 0; l < SIZE; ++l) {
            if (!nodes[l].status && (nodes[l].length > (nodes[postion].length + dataSource[postion][l]))) {
                //�ýڵ㵽Դ��ľ������   �ýڵ㵽�м�ڵ�ľ���+�м�ڵ㵽Դ�ڵ�ľ���

                //���½ڵ�l��Դ�ڵ�ľ���
                nodes[l].length = nodes[postion].length + dataSource[postion][l];
                //��¼ǰ�̽ڵ�
                nodes[l].preNode = &nodes[postion];
            }
        }
    }
    return nodes[destination];
}
void IdName(int id){
    switch (id) {
        case 0:
            printf("����");
            break;
        case 1:
            printf("����");
            break;
        case 2:
            printf("�ɶ�");
            break;
        case 3:
            printf("�Ϻ�");
            break;
        case 4:
            printf("����");
            break;
        case 5:
            printf("����");
            break;
        case 6:
            printf("����");
            break;
        case 7:
            printf("�人");
            break;
    }
}


