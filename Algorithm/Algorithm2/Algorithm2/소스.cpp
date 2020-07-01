#include <stdio.h>
#include <string.h>

char parent[] = "it is hard to write down codes right away from brain"; //11
char pattern[] = "ri"; //3

void FindString(char* parent, char* pattern) {
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);

	int parentHash = 0, patternHash = 0;
	int power = 1;

	for (int i = 0; i <= parentSize - patternSize; i++)
	{
		if (i == 0) {
			for (int j = 0; j < patternSize; j++) {
				parentHash += parent[patternSize - 1 - j] * power;
				patternHash += pattern[patternSize - 1 - j] * power;

				if (j < patternSize - 1) {
					power *= 2;
				}
			}
		}
		else{
			parentHash = 2 * (parentHash - parent[i - 1] * power) + parent[patternSize - 1 + i];
		}
		if (parentHash == patternHash) {
			int finded = 1;
			for (int j = 0; j < patternSize; j++) {
				if (parent[i + j] != pattern[j]) {
					finded = 0;
					break;
				}
			}
			if (finded) {
				printf("%d번째 인덱스에서 발견\n", i);
				printf("해시 값 비교 [%d : %d]\n", parentHash, patternHash);
			}
		}
	}
}
int main(void) {
	FindString(parent, pattern);
	return 0;
}