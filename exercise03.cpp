
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VMAX	21		/* ���͂̍ő�l2.1�~10 */
char hito[7];
int hito_i = 0;

/*--- �g�̌����f�[�^�^ ---*/
typedef struct {
	char   name[20];	/* ���� */
	int    height;		/* �g�� */
	int    weight;      // �̏d�i�ǉ��j
	double vision;		/* ���� */
} PhysCheck;





int tallest(const PhysCheck dat[], int n)
{
	int max_i = -1;
	int max = 0;

	for (int i = 0; i < n; i++)
		if (dat[i].height > max)
		{
			max = dat[i].height; // �ő�l
			max_i = i; // �ő�l�̔z��v�f
		}

	return max_i;
}




int med_height(const PhysCheck dat[], int n)
{
	PhysCheck* copy; // �\���̂̔z��
	int med_i=-1; // �����l�̗v�f�̓Y��

	// �����œn���ꂽ�z��̃R�s�[�𐶐�
	copy = (PhysCheck*)calloc(n, sizeof(PhysCheck));
	if (copy == NULL) {
		printf("�z��̓��I�m�ۂɎ��s���܂����B\n");
		return -1;
	} else {

		// �z��f�[�^�̒��g���R�s�[
		for (int i = 0; i < n; i++)
			copy[i] = dat[i];

		// �g�����ő�l�̗v�f�������鏈���� ������
		 //�ő�l���[���ɍX�V���Ȃ��� n/2+1�� �J��Ԃ�
		int max_i;
		for (int i = 0; i < n / 2 + 1; i++) {
			max_i = tallest(copy, n);
			copy[max_i].height = 0;
		}
		// n/2+1�Ԗڂɑ傫�Ȓl�������l
		med_i = max_i;

		free(copy); // ���I�z������

		return med_i;
	}
}

int search_height(const PhysCheck dat[], int n, int key) {
	int i = 0;
	for (i; i < n; i++) {
		if (dat[i].height == key)
			return i;
	}
	//printf("�����g���͂��܂���\n");
	return -1;
}

int search_weight(const PhysCheck dat[], int n, int key) {
	int i = 0;
	for (i; i < n; i++) {
		if (dat[i].weight == key)
			return i;
	}
	//printf("�����̏d�͂��܂���\n");
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
	int nx = sizeof(x) / sizeof(x[0]);		/* �l�� */
	int vdist[VMAX];						/* ���͂̕��z */

		puts("������ �g�̌����ꗗ�\ ������");
	puts("  ����            �g�� �̏d ���� ");
	puts("---------------------------------");

	for (i = 0; i < nx; i++) {
		printf("%-18.18s%4d%4d%5.1f\n",
			x[i].name, x[i].height, x[i].weight, x[i].vision);
	}


	int max_i;
	max_i = tallest(x, nx);
	printf("�ł��g���������̂�%s�����%dcm�ł��B\n", 
		x[max_i].name, x[max_i].height);


	
	int med_i;
	med_i = med_height(x, nx);
	printf("%d�l�̌����҂̂����g����%d�Ԗڂɍ����̂�%s�����%dcm�ł��B\n",
		nx, nx / 2 + 1, x[med_i].name, x[med_i].height);
	
	printf("�T������g��(cm)����͂��Ă������� : ");
	scanf("%d", &f);
	n = search_height(x, nx, f);
	if (n == -1) {
		printf("�g�� %d cm�ɊY������l�͌�����܂���ł����B\n", f);
	}
	else {
		printf("%s���񂪌�����܂����B\n", x[n].name);
	}

	printf("�T������̏d(kg)����͂��Ă������� : ");
	scanf("%d", &g);
	m = search_weight(x, nx, g);
	if (m == -1){
		printf("�̏d %d kg�ɊY������l�͌�����܂���ł����B\n", f);
	}
	else {
		printf("%s���񂪌�����܂����B\n", x[n].name);
	}

	/*char hantei = 'y';
	char* name;
	int step;
	while ('y' == hantei) {
		printf("�T������l�̎��������Ă�������\n");
		scanf("%s", &name);
		step = search_person(x, nx, name);
		if (step != -1) {
			printf("%s����͌�����܂���ł����B\n", name);
		}
		else {
			printf("%s����̃f�[�^�͑��݂��Ă��܂��B\n", name);
			printf("�f�[�^�T���ɂ��������X�e�b�v����%d��ł��B\n", step);
		}
		printf("�T���𑱂��܂����H(y/n)");
		scanf("%s", &hantei);

	}
	*/

	return 0;
}
