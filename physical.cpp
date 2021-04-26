#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VMAX	21		
/*--- �g�̌����f�[�^�^ ---*/
typedef struct {
	char   name[20];	
	int    height;		
	int    weight;      
	double vision;		
} PhysCheck;

int CheckBMI(PhysCheck x) {
	double height_m = (double)x.height * 0.01;
	double bmi = x.weight / (height_m * height_m);
	//printf("%f\n", bmi);

	if (bmi < 18.5) {
		return -1;
	}
	else if (bmi < 25.0) {
		return 0;
	}
	else {
		return 1;
	}
}

int main(void)
{
	int i;

	// ��3�v�f�Ɋe���̑̏d�̒l (52,78,66,80 ...) ��ǉ�
	PhysCheck x[] = {
		{"AKASAKA Tadao",	162, 52, 0.3},
		{"KATOH Tomiaki",	173, 78, 0.7},
		{"SAITOH Syouji",	175, 100, 2.0},
		{"TAKEDA Shinya",	171, 80, 1.5},
		{"NAGAHAMA Masaki",	168, 70, 0.4},
		{"HAMADA Tetsuaki",	174, 61, 1.2},
		{"MATSUTOMI Akio",	169, 75, 0.8},
	};
	int nx = sizeof(x) / sizeof(x[0]);		/* �l�� */
	int vdist[VMAX];						/* ���͂̕��z */
	int bmi;
	bmi = 0;

	PhysCheck* y;
	y = (PhysCheck*)calloc(nx, sizeof(PhysCheck));
	if (y == NULL)
		puts("�L����̊m�ۂɎ��s���܂����B");

	puts("������ �g�̌����ꗗ�\ ������");
	puts("  ����            �g�� �̏d ����  BMI");
	puts("--------------------------------------");
	for (i = 0; i < nx; i++) {

		
		
		
		
		printf("%-18.18s%4d%4d%5.1f\n",
			x[i].name, x[i].height, x[i].weight, x[i].vision);
		
		
	}

	for (i = 0; i < nx; i++) {
		if (CheckBMI(x[i]) == 1) {
			printf("%s\n", x[i].name);

			strcpy_s(y[i].name, x[i].name);
			y[i].height = i;
			y[i].weight = i;
			y[i].vision = i;

		}
		
	}
	

	
	free(y);
	return 0;
}