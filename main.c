#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define SIZE 8
#define INF 1000000//��ʾ��������

typedef struct node {
    int status;//�ڵ��״̬��ʶ����1��ʾ���ʣ�0��ʾδ����
    int length;//��ʾ�ýڵ㵽Դ�ڵ�ľ���
    int ID;//��ʾ�ýڵ��λ��
    struct node *preNode[SIZE];//��ʾ���Ӹýڵ��ǰһ���ڵ�
} Node;

//����C������û�������ĸ���������������ķ�ʽ��¼����·��
typedef struct pathLinkList {
    char *path;
    struct pathLinkList *next;
} PATHLINKLIST;

Node dijkstra(int source, int destination);//�������·���㷨

void initData();//��ʼ������

void collectNode(Node node, char *path, PATHLINKLIST *paths);//�ռ�ÿ�����·��

void IdName(int id);//IDת�������

void printLoad(char *path);//��ӡ����·��

int isEnd(Node node);//�ж��Ƿ������һ���ڵ�,����1��ʾ�������һ���ڵ㣬����0��ʾ�����һ���ڵ�

char *addPath(char *path, char point);//����C���Ե��ַ�ƴ�Ӳ��Ƿ���һ���µĵ�ַ��������Ҫ�Լ�ʵ��JAVA���ַ�����+������


/*
 * ʹ���ڽӾ���ķ������洢����ͼ
 */
int dataSource[SIZE][SIZE];

Node nodes[SIZE];//���ڱ�ʾ�ڵ��״̬�;���Դ�ڵ�ĳ���

//����C����û�����������װ�õĹ��ߣ���DFS+�ݹ��㷨�����������������·����

char path[20];//��¼����·��

int source, destination;

int main() {
    //��ʼ��
    PATHLINKLIST *paths = (PATHLINKLIST *) malloc(sizeof(PATHLINKLIST));
    paths->next = NULL;
    initData();
    //���·���㷨����
    Node result = dijkstra(source - 1, destination - 1);

    printf("The Shortest path length:%d\n", result.length);
    printf("The Shortest path:\n");
    //������·��
    collectNode(result, path, paths);
    paths = paths->next;
    while (paths != NULL) {
        printLoad(paths->path);
        paths = paths->next;
    }
    return 0;
}

void initData() {
    /*
     * ��ʼ������
     */
    //��ʼʱ������ÿһ���㶼���ɴ�
    int i, j;
    int cityId, targetCityId, length;
    int temp = INF;
    FILE *fp;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            dataSource[i][j] = INF;
        }
    }
    if ((fp = fopen("D://seconddata//data2.txt", "r")) == NULL) {
        printf("���ļ�ʧ��!");
        exit(0);
    } else {
//        printf("���ļ��ɹ�");
        while (fscanf(fp, "%d %d %d", &cityId, &targetCityId, &length) != EOF) {
            dataSource[cityId - 1][targetCityId - 1] = length;
        }
        fclose(fp);
    }
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (dataSource[i][j] == temp)
                dataSource[i][j] = dataSource[j][i];
        }
        nodes[i].ID = i + 1;
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
    path[0] = destination + '0';
// ���Զ�·�����
//    dataSource[0][1] = 2;
//    dataSource[0][2] = 3;
//    dataSource[1][3] = 3;
//    dataSource[2][3] = 2;
//    dataSource[3][4] = 2;
//    dataSource[3][5] = 3;
//    dataSource[4][6] = 3;
//    dataSource[5][6] = 2;
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

    nodes[source].status = 1;
    //Ĭ��Դ�ڵ㱻�����ˡ�����������Դ�ڵ㻹��ǰ�̽ڵ��bug
    for (int m = 0; m < SIZE; ++m) {
        nodes[source].preNode[m] = NULL;
    }

    /*
     * ѡ���м�ڵ㣨��Դ�ڵ������̵�һ���ڵ㣩ע��������SIZE-1����Ϊֻ��ҪѰ�ҳ�Դ������ĵ�
     */
    for (j = 0; j < SIZE - 1; j++) {
        int min = INF;
        int postion;//��¼�ýڵ��λ��

        for (k = 0; k < SIZE; ++k) {
            if (!nodes[k].status && nodes[k].length < min) {
                //����ýڵ�Ϊ�����ʣ����Ҹýڵ�ĳ���С����С����
                postion = k;//�ҵ����м�ڵ�
                min = nodes[k].length;
            }
        }
        //����ýڵ���̣���������������ֱ�������ľ��롣����ʾ�õ���Դ��ֱ��������
        if (nodes[postion].length == dataSource[source][postion]) {
            for (int m = 0; m < SIZE; ++m) {
                if (nodes[postion].preNode[m] == NULL) {
                    nodes[postion].preNode[m] = &nodes[source];
                    break;
                }
            }
        }
        nodes[postion].status = 1;//���ø��м�ڵ��ѱ�����

        /*
         * �ҵ����м�ڵ㣬��ȥ���������ڵ㣨��Դ�ڵ���м�ڵ㣩��Դ�ڵ�ľ���
         */
        for (l = 0; l < SIZE; ++l) {
            if (!nodes[l].status && (nodes[l].length >= (nodes[postion].length + dataSource[postion][l]))) {
                //�ýڵ㵽Դ��ľ������   �ýڵ㵽�м�ڵ�ľ���+�м�ڵ㵽Դ�ڵ�ľ���

                //���½ڵ�l��Դ�ڵ�ľ���
                nodes[l].length = nodes[postion].length + dataSource[postion][l];
                //ͨ����ѯ��ѯ�ķ���ȥ����ǰ�̽ڵ�
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

//��ӡ����·��
void printLoad(char *path) {
    int length = strlen(path);
    for (int i = length - 1; i >= 0; i--) {
        printf("�ڵ�%c", path[i]);
//        IdName(path[i]-'0');
        if (i != 0) {
            printf("---->");
        }
    }
    printf("\n");
}

void IdName(int id) {
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

//�ж��Ƿ������һ���ڵ�
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

char *addPath(char *path, char point) {

    int before = strlen(path);

    char *newpath = (char *) malloc(before + 2);//�����һ���ط���ӽ�����ʶ��

    for (int i = 0; i < before + 2; ++i) {
        if (i <= before - 1) {
            newpath[i] = path[i];
        }
        if (before - 1 < i && i <= before) {
            newpath[i] = point;
        }
        if (i == before + 1) {
            newpath[i] = '\0';
        }
    }
    return newpath;
}

void collectNode(Node node, char *path, PATHLINKLIST *paths) {
    for (int i = 0; i < SIZE; ++i) {
        if (!isEnd(node)) {
            //pathLink��ƴ��
            PATHLINKLIST *temp = (PATHLINKLIST *) malloc(sizeof(PATHLINKLIST));
            temp->next = NULL;
            temp->path = path;
            //����·��������
            while (paths != NULL) {
                if (paths->next == NULL) {
                    paths->next = temp;
                    paths = paths->next;
                }
                paths = paths->next;
            }
        }
        if (node.preNode[i] == NULL) {
            return;
        } else {
            //�����ڵ��ƴ�ӣ������������·���ķ���ȥ��������·��
            collectNode(*node.preNode[i], addPath(path, node.preNode[i]->ID + '0'), paths);
        }
    }
}



