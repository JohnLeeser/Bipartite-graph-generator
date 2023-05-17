
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 500

int main() {
    int num_left_vertices, num_right_vertices;
    double edge_probability;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};
    int has_edge = 0;
    int i, j;

	for(int o=0;0<20;o++){
		for(int i=0;i<num_left_vertices;i++){
			for(int j=0;j<num_right_vertices;j++){
				graph[i][j]=0;
			}
		}
		
		srand(time(NULL)); // 设置随机种子

    printf("请输入左部点集的大小（1-500）：");
    scanf("%d", &num_left_vertices);


    printf("请输入右部点集的大小（1-500）：");
    scanf("%d", &num_right_vertices);


    printf("请输入每两点之间存在边的概率（0.0-1.0）：");
    scanf("%lf", &edge_probability);

    // 确保 L 点集与 R 点集中的每个点至少有一条边
    for (i = 0; i < num_left_vertices; i++) {
        has_edge = 0;
        for (j = num_left_vertices; j < num_left_vertices + num_right_vertices; j++) {
            if ((double) rand() / RAND_MAX < edge_probability) {
                graph[i][j] = 1;
                has_edge = 1;
            }
        }
        if (!has_edge) {
            graph[i][num_left_vertices] = 1;
        }
    }

    for (i = 0; i < num_right_vertices; i++) {
        has_edge = 0;
        for (j = 0; j < num_left_vertices; j++) {
            if ((double) rand() / RAND_MAX < edge_probability) {
                graph[j][num_left_vertices + i] = 1;
                has_edge = 1;
            }
        }
        if (!has_edge) {
            graph[0][num_left_vertices + i] = 1;
        }
    }

    // 继续随机生成边
    for (i = 0; i < num_left_vertices; i++) {
        for (j = num_left_vertices; j < num_left_vertices + num_right_vertices; j++) {
            if ((double) rand() / RAND_MAX < edge_probability && !graph[i][j]) {
                graph[i][j] = 1;
            }
        }
    }

    // 将结果写入文件
    char filename[100];
    sprintf(filename, "C:\\Users\\WYLS\\Desktop\\edges_test\\edge_%d_%d_%.1f.txt", num_left_vertices, num_right_vertices, edge_probability);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法创建文件 %s\n", filename);
        exit(1);
    }

    // 输出结果到文件中
    for (i = 0; i < num_left_vertices; i++) {
        for (j = num_left_vertices; j < num_left_vertices + num_right_vertices; j++) {
            if (graph[i][j]) {
                fprintf(fp, "%d %d\n", i+1, j+1);
            }
        }
    }

    fclose(fp);

    printf("生成的二分图已保存在文件 %s 中。\n", filename);
	}

    return 0;
}
