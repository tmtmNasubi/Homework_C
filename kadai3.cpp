

#include <stdio.h>
#include <stdlib.h>

#define VMAX	21		/* 視力の最大値2.1×10 */

/*--- 身体検査データ型 ---*/
typedef struct {
	char   name[20];	/* 氏名 */
	int    height;		/* 身長 */
	int    weight;      // 体重（追加）
	double vision;		/* 視力 */
} PhysCheck;

/*--- 身長の平均値を求める ---*/
double ave_height(const PhysCheck dat[], int n)
{
	int i;
	double sum = 0;

	for (i = 0; i < n; i++)
		sum += dat[i].height;

	return sum / n;
}

/*--- 視力の分布を求める ---*/
void dist_vision(const PhysCheck dat[], int n, int dist[])
{
	int i;

	for (i = 0; i < VMAX; i++)
		dist[i] = 0;

	for (i = 0; i < n; i++)
		if (dat[i].vision >= 0.0 && dat[i].vision <= VMAX / 10.0)
			dist[(int)(dat[i].vision * 10)]++;
}


int CheckBMI(PhysCheck person) {

	// bmiの計算
	double height_m = (double)person.height * 0.01;
	double bmi = person.weight / (height_m * height_m);

	if (bmi < 18.5) return -1; // 痩せすぎ
	else if (bmi < 25.0) return 0; // 標準体重
	else return 1; // 太りすぎ
}

// bmiの値をポインタ渡しで出力するバージョン
// 同じ名前のCheckBMI関数を多重定義 (C++の機能)
int CheckBMI(PhysCheck person, double* bmi) {

	// bmiの計算
	double height_m = (double)person.height * 0.01;
	*bmi = person.weight / (height_m * height_m);

	if (*bmi < 18.5) return -1; // 痩せすぎ
	else if (*bmi < 25.0) return 0; // 標準体重
	else return 1; // 太りすぎ
}



double ave_weight(const PhysCheck dat[], int n)
{
	int i;
	double sum = 0;

	for (i = 0; i < n; i++)
		sum += dat[i].weight;

	return sum / n;
}

int tallest(const PhysCheck dat[], int n) {
	int tallest;
	int num;
	tallest = dat[0].height;
	num = 0;
	
	for (int i = 0; i < n; i++) {
		if (dat[i].height > tallest) {
			num = i;
			tallest = dat[num].height;
		}
	}
	return num;
} //基本課題1

int med_height(PhysCheck dat[], int n) {
	int med, num;
	num = 0;
	med = dat[0].height;
	int y[];

	for (int i = 0; i < n; i++) {
		int j = i;
		for (int k = i; k < n; k++) {
			if (y[k] < y[j]) {
				j = k;
			}
			if (i < j) {
				int v = y[i];
				y[i] = y[j];
				y[j] = v;
			}
		}
		if ((n % 2) == 0) {
			num = (((n / 2) + ((n / 2) + 1)) / 2);
		}
		else {
			num = (n / 2);
		}
	}
	return y[num];


}

int main(void)
{
	int i;
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

	int fatList[64]; // 肥満者リスト (配列xの添字)
	int nFat = 0; // 肥満と評価された人数

	// 表示ループ
	for (i = 0; i < nx; i++) {
		int result = CheckBMI(x[i]); // 対象者のBMIをチェック

		// 肥満と評価された人物だけを表示
		if (result == 1) {
			printf("%-18.18s%4d%4d%5.1f\n", 
				x[i].name, x[i].height, x[i].weight, x[i].vision);

			fatList[nFat] = i; // 配列xの添字を肥満者リストに登録
			nFat++;
		}
	}


	

	PhysCheck* y; // 構造体のポインタ

	// PhysCheck型の配列yを動的生成
	y = (PhysCheck*)calloc(nFat, sizeof(PhysCheck));

	// 元の配列xから 肥満者リストのデータを配列yにコピー
	for (i = 0; i < nFat; i++) 
		y[i] = x[ fatList[i] ];

	// 配列yの表示
	printf("\n肥満体重の人物のデータを配列yにコピーしました\n");
	for (i = 0; i < nFat; i++) {
		printf("y[%d]=%-18.18s%4d%4d%5.1f\n",
			i, y[i].name, y[i].height, y[i].weight, y[i].vision);
	}


	

	printf("\n全員(n=%d)の平均体重は%3.1f[kg]です\n", 
		nx, ave_weight(x, nx));

	printf("\n肥満者(n=%d)の平均体重は%3.1f[kg]です\n",
		nFat, ave_weight(y, nFat));

	printf("最も身長が高いのは %s さんの %d cmです．\n", x[tallest(x, nx)].name, x[tallest(x, nx)].height); //基本課題2

	printf("%d名の検査者のうち身長が%d番目に高いのは %s さんの %d cmです．", nx, (med_height(x, nx) + 1), x[med_height(x, nx)].name, x[med_height(x, nx)].height);

	
	
	free(y); 

	return 0;
}
