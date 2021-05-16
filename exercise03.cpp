
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VMAX	21		/* 視力の最大値2.1×10 */
char hito[7];
int hito_i = 0;

/*--- 身体検査データ型 ---*/
typedef struct {
	char   name[20];	/* 氏名 */
	int    height;		/* 身長 */
	int    weight;      // 体重（追加）
	double vision;		/* 視力 */
} PhysCheck;





int tallest(const PhysCheck dat[], int n)
{
	int max_i = -1;
	int max = 0;

	for (int i = 0; i < n; i++)
		if (dat[i].height > max)
		{
			max = dat[i].height; // 最大値
			max_i = i; // 最大値の配列要素
		}

	return max_i;
}




int med_height(const PhysCheck dat[], int n)
{
	PhysCheck* copy; // 構造体の配列
	int med_i=-1; // 中央値の要素の添字

	// 引数で渡された配列のコピーを生成
	copy = (PhysCheck*)calloc(n, sizeof(PhysCheck));
	if (copy == NULL) {
		printf("配列の動的確保に失敗しました。\n");
		return -1;
	} else {

		// 配列データの中身をコピー
		for (int i = 0; i < n; i++)
			copy[i] = dat[i];

		// 身長が最大値の要素を見つける処理を 見つけた
		 //最大値をゼロに更新しながら n/2+1回 繰り返す
		int max_i;
		for (int i = 0; i < n / 2 + 1; i++) {
			max_i = tallest(copy, n);
			copy[max_i].height = 0;
		}
		// n/2+1番目に大きな値が中央値
		med_i = max_i;

		free(copy); // 動的配列を解放

		return med_i;
	}
}

int search_height(const PhysCheck dat[], int n, int key) {
	int i = 0;
	for (i; i < n; i++) {
		if (dat[i].height == key)
			return i;
	}
	//printf("同じ身長はいません\n");
	return -1;
}

int search_weight(const PhysCheck dat[], int n, int key) {
	int i = 0;
	for (i; i < n; i++) {
		if (dat[i].weight == key)
			return i;
	}
	//printf("同じ体重はいません\n");
	return -1;
}

int search_person(PhysCheck dat[], int n, char* key) {
	int i = 0;
	int stp = 0;
	for (i; i < n; i++) {
		stp++;
		if (strcmp(dat[i].name, key) == 0) {
			if (i != 0 && strcmp(dat[i].name, dat[i - 1].name) < 0) {
				PhysCheck temp = dat[i - 1];
				dat[i - 1] = dat[i];
				dat[i] = temp;
			}
			else {
				PhysCheck temp = dat[i];
				dat[i] = dat[i - 1];
				dat[i] = temp;
			}
			return stp;
		}
	}

	return -1;
}

int main(void)
{
	int i;
	int f, n, g, m;
	PhysCheck x[] = {
		{"AKASAKA Tadao",	162, 52, 0.3},
		{"KATOH Tomiaki",	173, 78, 0.7},
		{"SAITOH Syouji",	175, 66, 2.0},
		{"TAKEDA Shinya",	171, 80, 1.5},
		{"NAGAHAMA Masaki",	168, 70, 0.4},
		{"HAMADA Tetsuaki",	174, 61, 1.2},
		{"MATSUTOMI Akio",	169, 75, 0.8},
	};
	int nx = sizeof(x) / sizeof(x[0]);		/* 人数 */
	int vdist[VMAX];						/* 視力の分布 */

		puts("■□■ 身体検査一覧表 ■□■");
	puts("  氏名            身長 体重 視力 ");
	puts("---------------------------------");

	for (i = 0; i < nx; i++) {
		printf("%-18.18s%4d%4d%5.1f\n",
			x[i].name, x[i].height, x[i].weight, x[i].vision);
	}


	int max_i;
	max_i = tallest(x, nx);
	printf("最も身長が高いのは%sさんの%dcmです。\n", 
		x[max_i].name, x[max_i].height);


	
	int med_i;
	med_i = med_height(x, nx);
	printf("%d人の検査者のうち身長が%d番目に高いのは%sさんの%dcmです。\n",
		nx, nx / 2 + 1, x[med_i].name, x[med_i].height);
	
	printf("探索する身長(cm)を入力してください : ");
	scanf("%d", &f);
	n = search_height(x, nx, f);
	if (n == -1) {
		printf("身長 %d cmに該当する人は見つかりませんでした。\n", f);
	}
	else {
		printf("%sさんが見つかりました。\n", x[n].name);
	}

	printf("探索する体重(kg)を入力してください : ");
	scanf("%d", &g);
	m = search_weight(x, nx, g);
	if (m == -1){
		printf("体重 %d kgに該当する人は見つかりませんでした。\n", f);
	}
	else {
		printf("%sさんが見つかりました。\n", x[n].name);
	}

	/*char hantei = 'y';
	char* name;
	int step;
	while ('y' == hantei) {
		printf("探索する人の氏名を入れてください\n");
		scanf("%s", &name);
		step = search_person(x, nx, name);
		if (step != -1) {
			printf("%sさんは見つかりませんでした。\n", name);
		}
		else {
			printf("%sさんのデータは存在しています。\n", name);
			printf("データ探索にかかったステップ数は%d回です。\n", step);
		}
		printf("探索を続けますか？(y/n)");
		scanf("%s", &hantei);

	}
	*/

	return 0;
}
