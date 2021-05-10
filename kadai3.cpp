

#include <stdio.h>
#include <stdlib.h>

#define VMAX	21		/* ���͂̍ő�l2.1�~10 */

/*--- �g�̌����f�[�^�^ ---*/
typedef struct {
	char   name[20];	/* ���� */
	int    height;		/* �g�� */
	int    weight;      // �̏d�i�ǉ��j
	double vision;		/* ���� */
} PhysCheck;

/*--- �g���̕��ϒl�����߂� ---*/
double ave_height(const PhysCheck dat[], int n)
{
	int i;
	double sum = 0;

	for (i = 0; i < n; i++)
		sum += dat[i].height;

	return sum / n;
}

/*--- ���͂̕��z�����߂� ---*/
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

	// bmi�̌v�Z
	double height_m = (double)person.height * 0.01;
	double bmi = person.weight / (height_m * height_m);

	if (bmi < 18.5) return -1; // ��������
	else if (bmi < 25.0) return 0; // �W���̏d
	else return 1; // ���肷��
}

// bmi�̒l���|�C���^�n���ŏo�͂���o�[�W����
// �������O��CheckBMI�֐��𑽏d��` (C++�̋@�\)
int CheckBMI(PhysCheck person, double* bmi) {

	// bmi�̌v�Z
	double height_m = (double)person.height * 0.01;
	*bmi = person.weight / (height_m * height_m);

	if (*bmi < 18.5) return -1; // ��������
	else if (*bmi < 25.0) return 0; // �W���̏d
	else return 1; // ���肷��
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
} //��{�ۑ�1

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
	int nx = sizeof(x) / sizeof(x[0]);		/* �l�� */
	int vdist[VMAX];						/* ���͂̕��z */


	

	puts("������ �g�̌����ꗗ�\ ������");
	puts("  ����            �g�� �̏d ���� ");
	puts("---------------------------------");

	int fatList[64]; // �얞�҃��X�g (�z��x�̓Y��)
	int nFat = 0; // �얞�ƕ]�����ꂽ�l��

	// �\�����[�v
	for (i = 0; i < nx; i++) {
		int result = CheckBMI(x[i]); // �Ώێ҂�BMI���`�F�b�N

		// �얞�ƕ]�����ꂽ�l��������\��
		if (result == 1) {
			printf("%-18.18s%4d%4d%5.1f\n", 
				x[i].name, x[i].height, x[i].weight, x[i].vision);

			fatList[nFat] = i; // �z��x�̓Y����얞�҃��X�g�ɓo�^
			nFat++;
		}
	}


	

	PhysCheck* y; // �\���̂̃|�C���^

	// PhysCheck�^�̔z��y�𓮓I����
	y = (PhysCheck*)calloc(nFat, sizeof(PhysCheck));

	// ���̔z��x���� �얞�҃��X�g�̃f�[�^��z��y�ɃR�s�[
	for (i = 0; i < nFat; i++) 
		y[i] = x[ fatList[i] ];

	// �z��y�̕\��
	printf("\n�얞�̏d�̐l���̃f�[�^��z��y�ɃR�s�[���܂���\n");
	for (i = 0; i < nFat; i++) {
		printf("y[%d]=%-18.18s%4d%4d%5.1f\n",
			i, y[i].name, y[i].height, y[i].weight, y[i].vision);
	}


	

	printf("\n�S��(n=%d)�̕��ϑ̏d��%3.1f[kg]�ł�\n", 
		nx, ave_weight(x, nx));

	printf("\n�얞��(n=%d)�̕��ϑ̏d��%3.1f[kg]�ł�\n",
		nFat, ave_weight(y, nFat));

	printf("�ł��g���������̂� %s ����� %d cm�ł��D\n", x[tallest(x, nx)].name, x[tallest(x, nx)].height); //��{�ۑ�2

	printf("%d���̌����҂̂����g����%d�Ԗڂɍ����̂� %s ����� %d cm�ł��D", nx, (med_height(x, nx) + 1), x[med_height(x, nx)].name, x[med_height(x, nx)].height);

	
	
	free(y); 

	return 0;
}
