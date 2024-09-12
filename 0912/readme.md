# Game Programming 01

### 커서 위치 제어
- gotoxy라는 함수로 출력할 단어의 위치를 제어한다.
```
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y); //선언문

int main(){
	gotoxy(2, 4);
	printf("Hello");
	gotoxy(40, 20);
	printf("Hello");
	return 0;
}

void gotoxy(int x, int y){
	COORD Pos = {x-1, y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

![image](https://github.com/user-attachments/assets/3311412b-019d-4ce2-b787-7eb34ffba771)
---|


### 원하는 위치에 구구단 3단 출력
- gotoxy 함수로 위치를 원하는 곳으로 제어하여 구구단 3단을 출력한다.
```
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y);

int main(void) {
	for(int i=1;i<=9;i++) {
		gotoxy(35, 5+i); // 위치 제어 
		printf("%d*%d=%2d",3,i,3*i);
	}
	printf("\n");
	
	return 0;
}

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

![image](https://github.com/user-attachments/assets/8cdbd214-13d7-4f4f-897b-a0a7cb10356c)
---|


### 문자 하나 입력 후 화면 지우기
- 문자 하나를 입력 받고, 화면을 지운 후 입력된 문자를 출력한다.
```
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char ch;
	printf("문자를 입력하고 Enter>");
	scanf("%c", &ch);
	system("cls");
	printf("입력된 문자 %c\n", ch);
	
	return 0;
}
```

![image](https://github.com/user-attachments/assets/9e6c74b1-a2f4-469e-a3a1-9be3a827c9fc) | ![image](https://github.com/user-attachments/assets/6b238618-30cd-4443-b79e-0d279f99414a) | ![image](https://github.com/user-attachments/assets/903b1336-b8d4-4286-b349-c0dd69376770)
---|---|---


### 구구단 출력, 키 입력하면 화면 지우고 다음 단 출력
```
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(void) {
	int i, j;
	for(j=1;j<=9;j++) {
		system("cls");
		for(i=1;i<=9;i++)
		printf("%d*%d=%d\n", j, i, j*i);
		printf("아무키나 누르시오.\n");
		getch();
	}
	return 0;
}
```
![image](https://github.com/user-attachments/assets/5d640364-f921-4b09-aca6-9e9caa041ebb) | ![image](https://github.com/user-attachments/assets/78a60935-bf6f-4717-915c-73de92496645) | ![image](https://github.com/user-attachments/assets/4863832c-be50-42b4-bf9d-90577e192fb8)
---|---|---


### 키보드 입력 시 해당 키의 아스키코드 출력
```
#include <stdio.h>
#include <conio.h>

int main(void) {
	int chr;
	do {
		chr=getch();
		
		if (chr==0 || chr == 0xe0) {
			chr=getch();
			printf("확장키 code=%d\n", chr);
		}
		else printf("아스키 code=%d\n", chr);
	} while(1);
	
	return 0;
}
```
![image](https://github.com/user-attachments/assets/a7b70387-70dd-477a-8c0a-cdc19512da09) | ![image](https://github.com/user-attachments/assets/8865daf0-017a-4c67-8924-6c773527b1bc) | ![image](https://github.com/user-attachments/assets/d16cb127-1668-4d46-8d45-3e924272c39f)
---|---|---
아무것도 누르지 않은 상태 | 'a'키를 누른 상태 | '`', 'A'를 차례로 누른 상태


### 방향키로 이동
- system("cls"); 라는 문장을 추가으로 방향키로 이동 후 이전 값은 지운다.
```
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define X_MAX 79 //가로(열)방향의 최대값
#define Y_MAX 24 //세로(행)방향의 최대값

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);

void gotoxy(int x, int y);

int main(void){
	char key;
	int x=10, y=5;
	do {
		gotoxy(x, y);
		printf("P");
		key=getch();
		move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
		system("cls"); //화면 비우기 
	}while(key!=27);
	
	return 0;
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
	switch(key) {
		case 72: //위쪽(상) 방향의 화살표 키 입력
				*y1=*y1-1;
				if (*y1<1) *y1=1; //y좌표의 최소값
				break;
		case 75: //왼쪽(좌) 방향의 화살표 키 입력
				*x1=*x1-1;
				if (*x1<1) *x1=1; //x좌표의 최소값
				break;
		case 77: //오른쪽(우) 방향의 화살표 키 입력
				*x1=*x1+1;
				if (*x1>x_b) *x1=x_b; //x좌표의 최대값
				break;
		case 80: //아래쪽(하) 방향의 화살표 키 입력
				*y1=*y1+1;
				if (*y1>y_b) *y1=y_b; //y좌표의 최대값
				break;
		default:
				return;
	}
}

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

![image](https://github.com/user-attachments/assets/3b37665d-f677-4e9c-8523-07d9391a29cf) | ![image](https://github.com/user-attachments/assets/f28d24c7-246b-487e-84b5-f7596e68f382) | ![image](https://github.com/user-attachments/assets/45919763-b047-46d4-a004-339b53963225)
---|---|---
화면 비우기를 하지 않고 컴파일 | 화면 비우기를 하고 컴파일 | 방향키로 위치를 조정한 상태

