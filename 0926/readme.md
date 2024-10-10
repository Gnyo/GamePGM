# Game Programming 03

## 숫자의 변환과 표현

### 숫자에 대한 자리 수 분리
- 숫자를 단위 별로 분리하여 순서대로 출력하는 방법
- 입력된 금액 또는 숫자가 756826 이라면 순서대로 출력하는 방법에는 다음과 같이 두 가지 방법을 생각할 수 있다.

<p align="center">
<img src="https://github.com/user-attachments/assets/754b203e-49ea-4cda-876f-b59f4eb1bd53" />
</p>

### 입력될 숫자를 문자열로 처리
- 입력된 내용을 충분한 크기의 문자형 배열에 저장하여 문자열의 길이를 계산한 다음 순서대로 또는 역순으로 배열요소를 출력
- 만약 입력될 숫자 756896을 scanf를 이용하여 문자형 배열 number[]에 저장한다고 가정하면 저장된 각 첨자에 저장된 내용은 다음과 같다.

<p align="center">
<img src="https://github.com/user-attachments/assets/e387281c-dfbf-4c91-a893-89480e7c5fe0" />

</p>

▶ 높은 단위부터출력
```c
#include <stdio.h>
#include <string.h>

int main() {
	char number[20];
	int length, i;
	
	printf("금액을 입력하고 Enter>");
	scanf("%s", number);
	
	length=strlen(number);
	for(i=0;i<length;i++)
	printf("%c\n", number[i]);
	
	return 0;
}
```

▶ 낮은 단위부터 출력
```c
#include <stdio.h>
#include <string.h>

int main() {
	char number[20];
	int length, i;
	
	printf("금액을 입력하고 Enter>");
	scanf("%s", number);
	
	length=strlen(number);
	for(i=length;i>=0;i--)
	printf("%c\n", number[i]);
	
	return 0;
}
```

### 입력된 숫자를 정수형으로 처리
- 문자열은 첨자로 구분하여 문자별로 출력이 가능하지만 숫자는 해당 단위수로 나누어야 하기에 나눗셈과 나머지 연산이 필요함
- 예를 들어 입력된 정수가 756896이라면 다음과 같이 나누어 가면서 각 자릿수의 숫자를 출력

<p align="center">
<img src="https://github.com/user-attachments/assets/bfbccf7d-b2ad-448c-b29f-35a444742334" />
</p>

### 높은 단위부터 출력
- 높은 단위부터 출력하려면 입력된 숫자가 최대 몇 자리의 정수인지를 계산해야 하는데 이를 계산하는 방법으로 라이브러리 함수 log10을 이용
- 몇 자리숫자인지를 계산했다면 위의 [방법 1]과 같이 단위별 숫자로 나누어주는데 이때 x, y를 계산하는 라이브러리 함수 pow(x,y)를 이용

```c
void serial_number(long number) {
  int num;
  int i, length=0;
  length=(int)(log10(number)+1); //최대 자리수 계산
  for(i=length;i>=1;i--) {
    num=number/(long) pow(10, i-1);
    printf("%ld\n", num);
    number=number-num*(long) pow(10,i-1);
  }
  printf("\n");
}
```

### 낮은 단위부터 출력
- 낮은 단위부터 출력하는 [방법 2]는 나머지 연산자를 이용하여 10으로 나눈 나머지를 이용

```c
void reverse_number(long number) {
  while(number > 0) {
    printf("%ld\n", number%10);
    number/=10;
  }
}
```

▶ 전체적인 코드
```c
#include <stdio.h>
#include <conio.h>
#include <math.h>

void serial_number(long number);
void reverse_number(long number);

int main() {
	long number=12345698;
	printf("입력 숫자 : %ld\n\n", number);
	
	printf("높은 단위부터 출력\n");
	serial_number(number);
	
	printf("\n낮은 단위부터 출력\n");
	reverse_number(number);
	
	printf("press any key to continue.......");
	getch();
	
	return 0;
}

void serial_number(long number) {
	int num;
	int i, length=0;
	length=(int)(log10(number)+1); //최대 자리수 계산
	for(i=length;i>=1;i--) {
		num=number/(long) pow(10, i-1);
		printf("%ld\n", num);
		number=number-num*(long) pow(10,i-1);
	}
	printf("\n");
}

void reverse_number(long number) {
	while(number>0) {
		printf("%ld\n", number%10);
		number/=10;
	}
}
```

![image](https://github.com/user-attachments/assets/07190e2e-eab9-4637-a8ec-921dba5b2c44) | ![image](https://github.com/user-attachments/assets/4ad58559-6e1b-40c6-af43-3cda73b53d20)
---|---
출력 | 아무 키 입력 후

### 재귀적 호출
- 높은 단위부터 출력:
  + 10으로 나누어가는 과정을 재귀적으로 호출함으로써 처리
  + 재귀 함수를 serial이라 가정하면 자기 자신을 호출하면서 printf부분이 보류되고, 반환 과정에서 보류된 부분이 역순으로 처리.
  + 입력된 숫자는 123이고 변수 n에 저장되었다고 가정
 
- 낮은 단위부터 출력:
  + 0으로 나누어가는 과정을 재귀적으로 호출함으로써 처리
  
```c
#include <stdio.h>
#include <conio.h>
#include <math.h>

void serial_number(long number);
void reverse_number(long number);

int main() {
	long number=12345698;
	printf("입력 숫자 : %ld\n\n", number);
	printf("높은 단위부터 출력\n");
	serial_number(number);
	printf("\n낮은 단위부터 출력\n");
	reverse_number(number);
	printf("press any key to continue.......");
	getch();
	return 0;
}

void serial_number(long number) {
	if (number>0) {
		serial_number(number/10);
		printf("%ld\n", number%10);
	}
	else return;
}

void reverse_number(long number) {
	printf("%ld\n", number%10);
	if((number/10)>0) reverse_number(number/10);
	else return;
}
```
