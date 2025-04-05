# Game Programming 01

### 1. 커서 위치 제어
- gotoxy라는 함수로 출력할 단어의 위치를 제어한다.
```c
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

---

### 2. 원하는 위치에 구구단 3단 출력
- gotoxy 함수로 위치를 원하는 곳으로 제어하여 구구단 3단을 출력한다.
```c
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

---

### 3. 문자 하나 입력 후 화면 지우기
- 문자 하나를 입력 받고, 화면을 지운 후 입력된 문자를 출력한다.
```c
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

---

### 4. 구구단 출력, 키 입력하면 화면 지우고 다음 단 출력
```c
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

---

### 5. 키보드 입력 시 해당 키의 아스키코드 출력
```c
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

---

### 6. 방향키로 이동
- system("cls"); 라는 문장을 추가으로 방향키로 이동 후 이전 값은 지운다.
```c
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
화면 비우기 문장이 없음: 컴파일한 후 방향키 이동 | 화면 비우기 문장이 있음 | 방향키로 위치를 조정한 상태

---

### 7. 길이가 n인 정사각형 출력
- 길이가 n인 표준 정사각형은 다음과 같이 반복적인 방법으로 정사각형의 크기를 표현 할 수 있다.
- 아래의 그림에서 숫자는 출력할 순서를 의미

![image](https://github.com/user-attachments/assets/00c05ca6-7b88-465f-a4e9-4cd64bb2153e)
---|

```c
#include <stdio.h>

void draw_square(int size);

int main(void) {
	int n;
	
	printf("정사각형 그리기\n\n");
	printf("정사각형의 길이(최대 37)를\n");
	printf("입력하고 Enter>");
	scanf("%d", &n);
	draw_square(n);
	
	return 0;
}

void draw_square(int size) {
	int i, j;
	unsigned char a=0xa6;
	unsigned char b[7];
	
	for(i=1;i<7;i++) b[i]=0xa0+i;
	printf("%c%c",a, b[3]);
	for(i=0;i<size;i++) printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);
	printf("\n");
	for(i=0;i<size;i++) {
		printf("%c%c", a, b[2]);
		for(j=0;j<size;j++) printf(" ");
		printf("%c%c",a, b[2]);
		printf("\n");
	}
	printf("%c%c", a, b[6]);
	for(i=0;i<size;i++) printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");
}
```

![image](https://github.com/user-attachments/assets/6e6d11a4-70b9-4389-b9a4-49dd25a98676) | ![image](https://github.com/user-attachments/assets/0bb6a14b-cedc-46df-ad63-c4c5e3e94263)
---|---

---

### 8. 메뉴 만들기(1)
- 키보드로 값을 입력하면 아스키코드로 받아진다.
- select=getch()-48; 라는 문장을 추가하여 키보드로 받은 값에서 아스키코드 0의 값(48)을 뺀다.
```c
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu_display(void);

void hamburger(void);

void spaghetti(void);

void press_any_key(void);

int main(void) {
	int c;
	while((c=menu_display()) != 3) {
		switch(c) {
			case 1 : hamburger();
					break;
			case 2 : spaghetti();
					break;
			default : break;
		}
	}
	
	return 0;
}

int menu_display(void) {
	int select;
	system("cls");
	printf("간식 만들기\n\n");
	printf("1. 햄버거 \n");
	printf("2. 스파게티\n");
	printf("3. 프로그램 종료\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void hamburger(void) {
	system("cls");
	printf("햄버거 만드는 방법\n");
	printf("나도 모르지롱\n");
	press_any_key();
}

void spaghetti(void) {
	system("cls");
	printf("스파게티 만드는 방법\n");
	printf("면 불리고 소스 넣고 데치면 끝\n");
	press_any_key();
}

void press_any_key(void) {
	printf("\n\n");
	printf("아무키나 누르면 메인 메뉴로...");
	getch();
}
```

![image](https://github.com/user-attachments/assets/8fb2a277-db01-4cf2-88bb-34fdf7a77e96) |
---|

![image](https://github.com/user-attachments/assets/3b02dbda-dab2-48db-87cd-aaf289d81850) | ![image](https://github.com/user-attachments/assets/ca949d82-b61b-4757-a405-839ae9a929aa) | ![image](https://github.com/user-attachments/assets/d1ecc357-9f27-4269-851a-a079c626df2e)
---|---|---
1번을 누른 상태 | 2번을 누른 상태 | 3번을 눌러 프로그램을 종료한 상태

---

### 9. 더 다양한 메뉴 만들기
```c
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu_display(void);
int sub_menu_display01(void); //햄버거에 대한 서브 메뉴 출력과 번호 입력
int sub_menu_display02(void); //스파게티에 대한 서브 메뉴 출력과 번호 입력
void sub_main01(void); //햄버거에 대한 서브 메뉴 제어
void sub_main02(void); //스파게티에 대한 서브 메뉴 제어
void chicken_burger(void);
void cheese_burger(void);
void tomato_spaghetti(void);
void cream_spaghetti(void);
void press_any_key(void); //아무키나 누르면 이전 메뉴로

int main(void) {
	int c;
	while((c=menu_display())!=3) {
		switch(c) {
			case 1 : sub_main01();
					break;
			case 2 : sub_main02();
					break;
			default : break;
		}
	}
	return 0;
}

int menu_display(void) {
	int select;
	system("cls");
	
	printf("간식 만들기\n\n");
	printf("1. 햄버거 \n");
	printf("2. 스파게티\n");
	printf("3. 프로그램 종료\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void sub_main01(void) {
	int c;
	while((c=sub_menu_display01())!= 3) {
		switch(c) {
			case 1 : chicken_burger();
					break;
			case 2 : cheese_burger();
					break;
			default : break;
		}
	}
}

int sub_menu_display01(void) {
	int select;
	system("cls");
	
	printf("햄버거 만들기\n\n");
	printf("1. 치킨버거\n");
	printf("2. 치즈버거\n");
	printf("3. 메인 메뉴로 이동\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void chicken_burger(void) {
	system("cls");
	printf("치킨버거 만드는 방법\n");
	printf("치킨을 먹고 햄버거를 먹는다.\n");
	press_any_key();
}

void cheese_burger(void) {
	system("cls");
	printf("치즈버거 만드는 방법\n");
	printf("치즈를 먹고 햄버거를 먹는다.\n");
	press_any_key();
}

void sub_main02(void) {
	int c;
	while((c=sub_menu_display02())!= 3) {
		switch(c) {
			case 1 : tomato_spaghetti();
					break;
			case 2 : cream_spaghetti();
					break;
			default : break;
		}
	}
}

int sub_menu_display02(void) {
	int select;
	system("cls");
	
	printf("스파게티 만들기\n\n");
	printf("1. 토마토 스파게티 \n");
	printf("2. 크림 스파게티 \n");
	printf("3. 메인 메뉴로 이동\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void tomato_spaghetti(void) {
	system("cls");
	printf("토마토 스파게티 만드는 방법\n");
	printf("면이랑 토마토 소스랑 섞어 먹는다.\n");
	press_any_key();
}

void cream_spaghetti(void) {
	system("cls");
	printf("크림 스파게티 만드는 방법\n");
	printf("면이랑 우유랑 치즈랑 섞어 먹는다.\n리조또가 더 맛있다.\n");
	press_any_key();
}
void press_any_key(void) {
	printf("\n\n");
	printf("아무키나 누르면 이전 메뉴로...");
	getch();
}
```

![image](https://github.com/user-attachments/assets/ff4683c1-2d43-402a-8d22-a2252647535b)| ![image](https://github.com/user-attachments/assets/9bd3eb8c-9455-4097-926f-1f40f4d24cdb)
---|---
컴파일을 한 상태 | 3번을 눌러 프로그램을 종료한 상태

![image](https://github.com/user-attachments/assets/2a4103d0-f2e1-4773-a6ca-6808b3624e83) | ![image](https://github.com/user-attachments/assets/1bcfcef0-8b62-4ff8-87b8-c194f034d497) | ![image](https://github.com/user-attachments/assets/4f834596-cf83-4b8a-b990-c0751e7d89ea)
---|---|---
첫 메뉴의 1번을 누른 상태 | 두번째 메뉴의 1번을 누른 상태 | 두번째 메뉴의 2번을 누른 상태

![image](https://github.com/user-attachments/assets/24732214-a22e-47eb-abfe-a1d9abcc8959) | ![image](https://github.com/user-attachments/assets/972ad189-394e-4c35-aa9d-710d45cce812) | ![image](https://github.com/user-attachments/assets/92da64fb-b7b8-4c1e-83ee-0f990ba1ba3b)
---|---|---
첫 메뉴의 2번을 누른 상태 | 두번째 메뉴의 1번을 누른 상태 | 두번째 메뉴의 2번을 누른 상태

---

### 10. 주사위 눈금 난수 생성
- srand()는 난수를 만드는 함수로, 함수의 매개변수에 계속 변하는 시간값을 전달하여 매번 새로운 난수를 생성하는 것이 원리이다.
- time(null)은 현재 시간을 초단위로 구하는 함수이다.
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	int i;
	srand(time(NULL));
	for(i=1;i<=10;i++) printf("%2d:%d\n",i, rand()%6+1);
	
	return 0;
}
```

![image](https://github.com/user-attachments/assets/6d47867e-a918-4d54-a835-c1837501f5ce) | ![image](https://github.com/user-attachments/assets/df8defab-2656-4105-b994-95ac18208ea6)
---|---
