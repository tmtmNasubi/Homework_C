#include <stdio.h>

int main() {
	int max, sum, add;
	sum = 0;
	add = 0;
	scanf_s("%d", &max);

	while (true) {
		if (max > sum) {
			sum = sum + add;
		}
		else{
			break;
		}
		scanf_s("%d", &add);
	}

	printf("‚·‚×‚Ä‚Ìadd‚Ì‡Œv’l(< max)‚Í%d‚Å‚·B\n", sum);
}