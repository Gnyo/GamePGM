# Game Programming 04

## 게임 업그레이드

### 원본 코드
```c
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void display_phone_pad(void);
void control_phone_pad(void);
void draw_check02(int c, int r);
void gotoxy(int x, int y);

char alpha[][3]={{' '}, {'.', 'q', 'z'}, {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'},
                {'j','k','l'}, {'m', 'n', 'o'}, {'p', 'r', 's'}, {'t', 'u', 'v'}, {'w', 'x', 'y'}};

int main(void) {
	display_phone_pad();
	control_phone_pad();	
    	return 0;
}

void display_phone_pad(void) {
	int y, x, z, cnt=0;
  draw_check02(3, 4);

	for(y=2;y<=8;y+=3) {
		for(x=3;x<=15;x+=6) {
			gotoxy(x, y);
			printf("%d", ++cnt);
			gotoxy(x+1, y+1);
			for(z=0;z<=2;z+=1)
				printf("%c", alpha[cnt][z]);
		}
	}
	gotoxy(9, 11);
	printf("0");
	gotoxy(10, 12);
	printf("SP");
	gotoxy(1, 15);
}

void control_phone_pad(void) {
  char c1, c2, cnt;
  time_t start, end;

	printf("숫자키 입력>");
	c1=getch();

	start=time(NULL);
	do {
		cnt=0;
		if (c1==' ') printf("\b");
		else printf("%c", alpha[c1-'0'][cnt]);
		do {
			c2=getch();
			end=time(NULL);
			if ((c1==c2) && ((end-start)<=2)) {
				if (cnt>1) cnt=0;
				else cnt++;

				c1=c2;
				printf("\b%c", alpha[c1-'0'][cnt]);
				start=time(NULL);
			}
			else break;
		}while(1);
		start=time(NULL);
		c1=c2;
	}while(1); 
}

void draw_check02(int c, int r) {
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(i=1;i<12;i++) b[i]=0xa0+i;

    printf("%c%c",a, b[3]);
    for(i=0;i<c-1;i++) {
  		printf("%c%c%c%c", a, b[1], a, b[1]);
  		printf("%c%c", a, b[8]);
    }
    printf("%c%c%c%c", a, b[1], a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");

    for(i=0;i<r-1;i++) {
  		printf("%c%c", a, b[2]);
  		for(j=0;j<c;j++) {
  			printf("    ");
  			printf("%c%c",a, b[2]);
  		}
  		printf("\n");
  		//
  		printf("%c%c", a, b[2]);
  		for(j=0;j<c;j++) {
  			printf("    ");
  			printf("%c%c",a, b[2]);
  		}
  		printf("\n");
  		//
  		printf("%c%c", a, b[7]);
  		for(j=0;j<c-1;j++) {
  			printf("%c%c%c%c", a, b[1], a, b[1]);
  			printf("%c%c", a, b[11]);
  		}
      printf("%c%c%c%c", a, b[1], a, b[1]);
      printf("%c%c",a, b[9]);
      printf("\n");
    }
    printf("%c%c", a, b[2]);
    for(j=0;j<c;j++) {
  		printf("    ");
  		printf("%c%c",a, b[2]);
    }
    printf("\n");
	  //
	  printf("%c%c", a, b[2]);
	  for(j=0;j<c;j++) {
		  printf("    ");
		  printf("%c%c",a, b[2]);
    }
	  printf("\n");
	  //
    printf("%c%c", a, b[6]);
    for(i=0;i<c-1;i++) {
  		printf("%c%c%c%c", a, b[1], a, b[1], a, b[1]);
  		printf("%c%c", a, b[10]);
    }
	  printf("%c%c%c%c", a, b[1], a, b[1], a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

void gotoxy(int x, int y) {
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

### 소스 분석

![image](https://github.com/user-attachments/assets/d697a54f-09c5-4659-9495-52e48195868d) | ![슬라이드4](https://github.com/user-attachments/assets/dcf8543f-1452-49f7-9225-5430686c742f)
:---:|:---:
실행 파일 | main()

![슬라이드5](https://github.com/user-attachments/assets/8d444be0-6b42-4e91-a3be-0df889d9feca) | ![슬라이드6](https://github.com/user-attachments/assets/e99fa754-1dc9-4879-8007-7fb51807eddc) |
:---:|:---:
전역 배열 alpha | display_phone_pad()

![슬라이드7](https://github.com/user-attachments/assets/d3f30bc0-1f9b-4e64-85b5-efdcb1dfe428) |
:---: |
화면 그리기에서 사용할 기호 소개

![슬라이드8](https://github.com/user-attachments/assets/434fb66a-9239-4a7d-854f-b60772f3c0e0) | ![슬라이드9](https://github.com/user-attachments/assets/3777f469-da78-4d7e-8d83-4fea85ef975c) | ![슬라이드10](https://github.com/user-attachments/assets/233bef96-9df7-45da-98b8-68ea6a2636ef)
:---:|:---:|:---:

![슬라이드11](https://github.com/user-attachments/assets/d835a024-373d-4ca5-b7ef-1c92b7223450) | ![슬라이드12](https://github.com/user-attachments/assets/10ee2615-c119-464f-b92c-0789dbfbb054)
:---:|:---:
숫자 키 입력 시 문자 처리 | 숫자 키 두 번 이상 입력 시 문자 처리 

![슬라이드13](https://github.com/user-attachments/assets/74e0c798-b03c-439d-8ec7-8937752da84d) |
:---: |
커서를 지정한 (x, y) 좌표로 이동


### 원본 소스 코드의 문제점
- 화면 그림이 맞지 않음, 화면이 무너짐
- 백스페이스가 작동이 되지 않음

---

### 기능 추가를 위한 컨셉 선정
- 원본 코드를 분석하며 '피처폰'을 연상시켜 컨셉을 '피처폰(Feature Phone)'으로 택함

![슬라이드15](https://github.com/user-attachments/assets/02b06c10-aee5-4322-9cc8-c02322de46de) |
---|

### 고장난 피처폰 코드(원본 코드에서 기능 수정 및 추가)
```c
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void play_sound(int num);				// 소리(도레미파…) 출력 
void gotoxy(int x, int y);				// 위치 이동
void draw_Screen(int r, int h);			// 스크린 그리기 
void draw_Keypad(int r, int h);			// 키패드 그리기 
void pad();								// 화면에 나올 패드 그리기 

void control();							// 메인 화면 컨트롤 
void main_mode();						// 메인 화면 
void update_time();						// 메인 화면 - 날짜 및 시간 출력
void call_mode();						// 전화 화면 
void text_mode();						// 문자 화면  

#define X 4
#define Y 6

char alpha[][3] = {{' '}, {'a', 'b', 'c'}, {'d', 'e', 'f'}, 
                   {'g', 'h', 'i'}, {'j', 'k', 'l'}, {'m', 'n', 'o'},
                   {'p', 'q', 'r'}, {'w', 't', 'u'}, {'v','w','x'}, 
                   {'y', 'z', '.'}};

int main() {
    SetConsoleTitle("고장난 피처폰");
    system("color F0");
    
    main_mode();
    control();
}

void main_mode() {
	system("cls");
    pad();
    update_time();  //현재 시간 출력 
    gotoxy(12, 6);
    printf("전화");
    gotoxy(12, 8);
    printf("문자");
    
    gotoxy(9, 6);
}

void call_mode() {
    system("cls");
    pad();
    gotoxy(9, 2);
    printf("전화 모드");
    gotoxy(3, 10);
    printf("☜ 메인으로");

    gotoxy(X, Y);
    int num_count = 0;  // 입력된 숫자의 개수를 추적하는 변수
    int x = X;          // 커서 위치를 추적하는 변수

    while (1) {
        char num = getch();
        if (num >= '0' && num <= '9' && num_count < 18) {  // 숫자 입력 시 18개 제한
            play_sound(num - '0');
			printf("%c", num);
            num_count++;  // 입력된 숫자 개수 증가
            x++;          // 커서 위치 이동
        }
        else if (num == 8) {  // Backspace 키가 눌렸을 때
            if (num_count > 0) {
                x--;          // 커서 위치를 왼쪽으로 이동
                gotoxy(x, Y); // 커서 이동
                printf(" ");  // 문자를 지움
                gotoxy(x, Y); // 커서를 다시 왼쪽 위치로 이동
                num_count--;  // 입력된 숫자 개수 감소
            }
        }
        else if (num == 27) {  // ESC 키를 눌러 나가기
            break;
        }
    }
    main_mode();
}

void text_mode() {
    system("cls");
    pad();
    gotoxy(9, 2);
    printf("문자 모드");
    gotoxy(3, 10);
    printf("☜ 메인으로");

    gotoxy(X, Y);
    char ch;
    int x = X;  // 현재 커서 위치를 추적하기 위한 변수
    int char_count = 0;  // 입력된 문자의 개수를 추적

    while (1) {
        ch = getch();
        if (ch == 27) {  // ESC 키를 눌러 나가기
            break;
        }
        else if (ch == 8) {  // backspace가 눌렸을 때
            if (x > 4) {  // 첫 번째 위치는 지우지 않음
                x--;  // 커서 위치 한 칸 왼쪽으로 이동
                gotoxy(x, Y);  // 커서 이동
                printf(" ");  // 해당 위치 문자 삭제
                gotoxy(x, Y);  // 커서를 다시 해당 위치로 이동
                char_count--;  // 문자 개수 감소
            }
        }
        else if (ch >= '0' && ch <= '9' && char_count < 18) {  // 숫자 키 입력 시 18글자 제한
            char c1 = ch, c2;
            int cnt = 0;
            time_t start, end;
            
            printf("%c", alpha[c1 - '0'][cnt]);  // 문자 출력
            x++;  // 커서 위치 이동
            char_count++;  // 입력된 문자 개수 증가

            start = time(NULL);

            do {
                c2 = getch();
                end = time(NULL);

                if ((c1 == c2) && ((end - start) <= 2)) {
                    if (cnt >= 2)
                        cnt = 0;
                    else
                        cnt++;
                    c1 = c2;
                    gotoxy(--x, Y);  // 커서 위치에서 문자 지우기
                    printf("%c", alpha[c1 - '0'][cnt]);  // 새 문자 출력
                    x++;  // 커서 위치 업데이트
                    start = time(NULL);  // 시간 초기화
                } else {
                    break;
                }
            } while (1);
        }
    }
    main_mode();
}

void control(void) {
    int cursor_pos = 6;  // 현재 선택된 메뉴의 위치 (6: 전화, 8: 문자)
    int prev_cursor_pos = 6;  // 이전 선택된 메뉴의 위치
    char c;
	
	gotoxy(9, cursor_pos);
    printf("▶");
	
    do {
        if (prev_cursor_pos != cursor_pos) { // 선택된 메뉴가 변경되었을 때만 화면 업데이트 
            gotoxy(9, prev_cursor_pos);
            printf("  ");  // 이전 선택 표시 지우기

            gotoxy(9, cursor_pos);
            printf("▶");  // 현재 선택 표시

            prev_cursor_pos = cursor_pos;  // 현재 위치를 이전 위치로 업데이트
        }

        if (_kbhit()) {  // 키 입력이 있는지 확인
            c = getch();

            if (c == '8') {  // ↓키 
                if (cursor_pos < 8) {
                    cursor_pos += 2;
                }
            }
            else if (c == '2') {  // ↑키 
                if (cursor_pos > 7) {
                    cursor_pos -= 2;
                }
            }
            else if (c == '5') {  // Enter 키
                if (cursor_pos == 6) {
                    call_mode();
                } else if (cursor_pos == 8) {
                    text_mode();
                }
            }
        }
    } while (1);
}

void update_time() {	// 현재 날짜 및 시간 출력 
    time_t t;
    struct tm *current_time;
    
    t = time(NULL);
    current_time = localtime(&t);
	
    gotoxy(5, 2);
    printf("%04d-%02d-%02d %02d:%02d", 
           current_time->tm_year + 1900,
           current_time->tm_mon + 1,
           current_time->tm_mday, 
           current_time->tm_hour, 
           current_time->tm_min);      
}

void gotoxy(int x, int y) {
   COORD Pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void play_sound(int num) {
    int frequencies[] = {659, 261, 293, 329, 349, 392, 440, 493, 523, 587}; 
    if (0 <= num && num <= 9) {	// 1=도, 2=레, …, 9=높은 레, 0=높은 미 
        Beep(frequencies[num], 150);
    }
}

void pad() {
    int y, x, z, cnt = 0;
    
    draw_Screen(4, 3);
    draw_Keypad(4, 3);
    
    for (y = 13; y <= 22; y += 4) {
        for (x = 5; x <= 21; x += 8) {
            gotoxy(x, y);	// 숫자 출력 
            printf("%d", ++cnt);
            
            if(cnt%2==0) {	//화살표 출력 
            	gotoxy(x, y+1);
            	if (cnt == 2) printf("↑");
	            else if (cnt == 4) printf("←");
	            else if (cnt == 8) printf("↓");
	            else if (cnt == 6) printf("→");
			} 
			else if(cnt==5) {
				gotoxy(x, y+1);
				printf("▶");
			} 
            
            gotoxy(x-1, y+2);	// 문자 출력 
            for (z = 0; z <= 2; z += 1)
                printf("%c", alpha[cnt][z]);
        }
    }
    gotoxy(4, 25);
    printf("ESC");
    gotoxy(5, 27);
    printf("☜");
    
    gotoxy(13, 25);
    printf("0");
    gotoxy(13, 27);
    printf("_");
    
    gotoxy(20, 25);
    printf("BSP");
    gotoxy(21, 27);
    printf("◀");
}

// Phone Screen
void draw_Screen(int r, int h) {
    int i, j, l;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(int i=1;i<12;i++) b[i]=0xa0+i;
    
	printf("%c%c",a, b[3]); 						// ┌
	for(i=0;i<r*6-1;i++) printf("%c%c", a, b[1]);	// ━ 
    printf("%c%c", a, b[4]);						// ┐
	
	printf("\n");
	
	for(l=0; l<h; l++){
		for(i=0; i<r-1; i++){
			printf("%c%c",a, b[2]);				// │
			for(j=0;j<r*6-1;j++) printf(" ");
			printf("%c%c",a, b[2]);				// │
			printf("\n");
		}
    }
	
	printf("%c%c", a, b[6]); 					// └ 
	for(i=0;i<r*6-1;i++) printf("%c%c", a, b[1]);	// ━ 
    printf("%c%c", a, b[5]);					// ┘ 
    printf("\n");
}

// Phone Keypad
void draw_Keypad(int r, int h) {
    int i, j, k, l;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(int i=1;i<12;i++) b[i]=0xa0+i;
    
    printf("%c%c",a, b[3]); 						// ┌
    for(j=0; j<r-2; j++){
        for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━ 
        printf("%c%c", a, b[8]);					// ┯ 
    }
    for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
    printf("%c%c", a, b[4]);						// ┐
    
    printf("\n");
    
    for(l=0; l<h; l++){
        for(i=0; i<r-1; i++){
            for(j=0;j<r;j++) {
                printf("%c%c",a, b[2]);				// │ 
                for(k=0;k<r*2-1;k++) printf(" ");
            }
            printf("\n");
        }
        for(i=0;i<r-1;i++) {
            printf("%c%c", a, b[7]); 						// ┣ 
            for(j=0; j<r-2; j++){
                for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━ 
                printf("%c%c", a, b[11]);					// ┿ 
            }
            for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
            printf("%c%c",a, b[9]); 						// ┤ 
            printf("\n");
        }
    }
    for(i=0; i<r-1; i++){
        for(j=0;j<r;j++) {
            printf("%c%c",a, b[2]);				// │ 
            for(k=0;k<r*2-1;k++) printf(" ");
        }
        printf("\n");
    }
    
    printf("%c%c", a, b[6]); 					// └ 
    for(j=0; j<r-2; j++){
        for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
        printf("%c%c", a, b[10]);					// ┴ 
    }
    for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
    printf("%c%c", a, b[5]);					// ┘ 
    printf("\n");
}
```

### 수정 및 추가한 기능 소개

① 콘솔 창 제목 추가 
![슬라이드17](https://github.com/user-attachments/assets/63343f3b-67a3-42a0-a4db-72f7dd414b50) | ![슬라이드18](https://github.com/user-attachments/assets/59b4e9f0-db33-4122-ad49-5cfb222665b0)
---|---

② 콘솔 창 색상, 글자 색상 변경
![슬라이드19](https://github.com/user-attachments/assets/a19844b7-8aab-47ea-8548-e54ab9d8471f) | ![슬라이드20](https://github.com/user-attachments/assets/ccff40a4-7953-4b50-8388-0bdd6eae77e1)
---|---

③ 문자(알파벳) 배치 순서 변경
![슬라이드21](https://github.com/user-attachments/assets/225017d7-905c-4835-85be-4ff42976072e) | ![슬라이드22](https://github.com/user-attachments/assets/761c3dcd-950b-42f6-bcd9-1c8bef5be649)
---|---

④ 키패드 디자인 변경
![슬라이드23](https://github.com/user-attachments/assets/78c1a3bc-083c-4e35-b570-8398775af2b7) | ![슬라이드24](https://github.com/user-attachments/assets/68ec85f3-5fff-404a-b82f-937f100e149b) | ![슬라이드25](https://github.com/user-attachments/assets/c8b252cd-6029-4784-8bb6-6ffd1a9d07c6)
---|---|---
![슬라이드26](https://github.com/user-attachments/assets/1ead73d8-c816-4409-b69a-6378c0ca876c) | ![슬라이드27](https://github.com/user-attachments/assets/000b7856-c4de-48f4-91d1-612b448d9d15) | ![슬라이드28](https://github.com/user-attachments/assets/ea21abe0-2334-4865-b15d-15813c14b911)

⑤ 스크린 추가
![슬라이드29](https://github.com/user-attachments/assets/8dccea4f-39c7-481d-8538-f149aef96d4f) | ![슬라이드30](https://github.com/user-attachments/assets/1302559c-7f60-4a5d-8560-87c8b980c55e) | ![슬라이드31](https://github.com/user-attachments/assets/ea8c75a7-ffef-4409-8b0a-0af97e33b0c6)
---|---|---

⑥ 현재 날짜 및 시간 출력 추가
![슬라이드32](https://github.com/user-attachments/assets/daf88a71-34fd-453b-a371-4d3c7ae78707) | ![슬라이드33](https://github.com/user-attachments/assets/9d2cbad7-7c5c-4117-8978-3b8c8a992722)
---|---

⑦ 메인 화면 기능 추가
![슬라이드34](https://github.com/user-attachments/assets/f40bfb6d-faa6-4a2c-b9a5-90a4b9635f0b) | ![슬라이드35](https://github.com/user-attachments/assets/dc7dd64d-a92d-4647-b141-7c4dae510d03) | ![슬라이드36](https://github.com/user-attachments/assets/e6851036-f0c2-4ebc-ac8a-6f44f5bfde72)
---|---|---

⑧ 소리 기능 추가
![슬라이드37](https://github.com/user-attachments/assets/c4c7470b-a32c-4da7-812c-bd6c022c3d47) | ![슬라이드38](https://github.com/user-attachments/assets/c91ba83c-d37d-44d1-95c1-a9a9d2fa30c1)
---|---|

⑨ 전화 기능, 숫자 입력이 가능한 화면
![슬라이드39](https://github.com/user-attachments/assets/d7aa1d9c-6f46-4346-a684-9a0aaf107002) | ![슬라이드40](https://github.com/user-attachments/assets/6a35dd8e-349b-4dc0-ad1c-1a07ef078846) | ![슬라이드41](https://github.com/user-attachments/assets/d258ffa3-6315-483d-87c5-74a97bea2ac0)
---|---|---

⑩ 문자 기능, 텍스트 입력이 가능한 화면
![슬라이드42](https://github.com/user-attachments/assets/d00ed3d3-b74e-4842-965d-2c37fbf2bf71) | ![슬라이드43](https://github.com/user-attachments/assets/39691941-4fba-4d36-a489-dc4bc7c7fd2f) |
---|---|
![슬라이드44](https://github.com/user-attachments/assets/23cde334-3a98-46e4-a627-37805f0101f8) | ![슬라이드45](https://github.com/user-attachments/assets/36def3f3-6e5e-4c4b-9fe3-58784cbc53bd)

---

### 고장난 피처폰 수정 코드
```c
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void play_sound(int num);				// 소리(도레미파…) 출력 
void gotoxy(int x, int y);				// 위치 이동
void draw_Screen(int r, int h);			// 스크린 그리기 
void draw_Keypad(int r, int h);			// 키패드 그리기 
void pad();								// 화면에 나올 패드 그리기 

void control();							// 메인 화면 컨트롤 
void main_mode();						// 메인 화면 
void update_time();						// 메인 화면 - 날짜 및 시간 출력
void call_mode();						// 전화 화면 
void text_mode();						// 문자 화면  

#define X 4
#define Y 6

char alpha[][3] = {{' '}, {'a', 'b', 'c'}, {'d', 'e', 'f'}, 
                   {'g', 'h', 'i'}, {'j', 'k', 'l'}, {'m', 'n', 'o'},
                   {'p', 'q', 'r'}, {'w', 't', 'u'}, {'v','w','x'}, 
                   {'y', 'z', '.'}};

int main() {
    SetConsoleTitle("고장난 피처폰");
    
    main_mode();
    control();
}

void main_mode() {
	system("cls");
	system("color F0"); // 색상 변화 
    pad();
    update_time();  //현재 시간 출력 

    gotoxy(12, 6);
    printf("전화");
    gotoxy(12, 8);
    printf("문자");
    
    gotoxy(9, 6);
}

void call_mode() {
    system("cls");
    system("color E0"); // 색상 변화 
    pad();
    gotoxy(9, 2);
    printf("전화 모드");
    gotoxy(3, 10);
    printf("☜ 메인으로");

    gotoxy(X, Y);
    int num_count = 0;  // 입력된 숫자의 개수를 추적하는 변수
    int x = X;          // 커서 위치를 추적하는 변수

    while (1) {
        char num = getch();
        if (num >= '0' && num <= '9' && num_count < 18) {  // 숫자 입력 시 18개 제한
            play_sound(num - '0');
			printf("%c", num);
            num_count++;  // 입력된 숫자 개수 증가
            x++;          // 커서 위치 이동
        }
        else if (num == 8) {  // Backspace 키가 눌렸을 때
            if (num_count > 0) {
                x--;          // 커서 위치를 왼쪽으로 이동
                gotoxy(x, Y); // 커서 이동
                printf(" ");  // 문자를 지움
                gotoxy(x, Y); // 커서를 다시 왼쪽 위치로 이동
                num_count--;  // 입력된 숫자 개수 감소
            }
        }
        else if (num == 27) {  // ESC 키를 눌러 나가기
            break;
        }
    }
    main_mode();
}

void text_mode() {
    system("cls");
    system("color E0"); // 색상 변화 
    pad();
    gotoxy(9, 2);
    printf("문자 모드");
    gotoxy(3, 10);
    printf("☜ 메인으로");

    gotoxy(X, Y);
    char ch;
    int x = X;  // 현재 커서 위치를 추적하기 위한 변수
    int char_count = 0;  // 입력된 문자의 개수를 추적

    while (1) {
        ch = getch();
        if (ch == 27) {  // ESC 키를 눌러 나가기
            break;
        }
        else if (ch == 8) {  // backspace가 눌렸을 때
            if (x > 4) {  // 첫 번째 위치는 지우지 않음
                x--;  // 커서 위치 한 칸 왼쪽으로 이동
                gotoxy(x, Y);  // 커서 이동
                printf(" ");  // 해당 위치 문자 삭제
                gotoxy(x, Y);  // 커서를 다시 해당 위치로 이동
                char_count--;  // 문자 개수 감소
            }
        }
        else if (ch >= '0' && ch <= '9' && char_count < 18) {  // 숫자 키 입력 시 18글자 제한
            char c1 = ch, c2;
            int cnt = 0;
            time_t start, end;
            
            printf("%c", alpha[c1 - '0'][cnt]);  // 문자 출력
            x++;  // 커서 위치 이동
            char_count++;  // 입력된 문자 개수 증가

            start = time(NULL);

            do {
                c2 = getch();
                end = time(NULL);

                if ((c1 == c2) && ((end - start) <= 2)) {
                    if (cnt >= 2)
                        cnt = 0;
                    else
                        cnt++;
                    c1 = c2;
                    gotoxy(--x, Y);  // 커서 위치에서 문자 지우기
                    printf("%c", alpha[c1 - '0'][cnt]);  // 새 문자 출력
                    x++;  // 커서 위치 업데이트
                    start = time(NULL);  // 시간 초기화
                } else {
                    break;
                }
            } while (1);
        }
    }
    main_mode();
}

void control(void) {
    int cursor_pos = 6;  // 현재 선택된 메뉴의 위치 (6: 전화, 8: 문자)
    int prev_cursor_pos = 6;  // 이전 선택된 메뉴의 위치
    char c;
	
	gotoxy(9, cursor_pos);
    printf("▶");
	
    do {
        if (prev_cursor_pos != cursor_pos) { // 선택된 메뉴가 변경되었을 때만 화면 업데이트 
            gotoxy(9, prev_cursor_pos);
            printf("  ");  // 이전 선택 표시 지우기

            gotoxy(9, cursor_pos);
            printf("▶");  // 현재 선택 표시

            prev_cursor_pos = cursor_pos;  // 현재 위치를 이전 위치로 업데이트
        }

        if (_kbhit()) {  // 키 입력이 있는지 확인
            c = getch();

            if (c == '8') {  // ↓키 
                if (cursor_pos < 8) {
                    cursor_pos += 2;
                }
            }
            else if (c == '2') {  // ↑키 
                if (cursor_pos > 7) {
                    cursor_pos -= 2;
                }
            }
            else if (c == '5') {  // Enter 키
                if (cursor_pos == 6) {
                    call_mode();
                } else if (cursor_pos == 8) {
                    text_mode();
                }
            }
        }
    } while (1);
}

void update_time() {	// 현재 날짜 및 시간 출력 
    time_t t;
    struct tm *current_time;
    
    t = time(NULL);
    current_time = localtime(&t);
	
    gotoxy(5, 2);
    printf("%04d-%02d-%02d %02d:%02d", 
           current_time->tm_year + 1900,
           current_time->tm_mon + 1,
           current_time->tm_mday, 
           current_time->tm_hour, 
           current_time->tm_min);      
}

void gotoxy(int x, int y) {
   COORD Pos = {(SHORT)(x - 1), (SHORT)(y - 1)};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void play_sound(int num) {
    int frequencies[] = {659, 261, 293, 329, 349, 392, 440, 493, 523, 587}; 
    if (0 <= num && num <= 9) {	// 1=도, 2=레, …, 9=높은 레, 0=높은 미 
        Beep(frequencies[num], 150);
    }
}

void pad() {
    int y, x, z, cnt = 0;
    
    draw_Screen(4, 3);
    draw_Keypad(4, 3);
    
    for (y = 13; y <= 22; y += 4) {
        for (x = 5; x <= 21; x += 8) {
            gotoxy(x, y);	// 숫자 출력 
            printf("%d", ++cnt);
            
            if(cnt%2==0) {	//화살표 출력 
            	gotoxy(x, y+1);
            	if (cnt == 2) printf("↑");
	            else if (cnt == 4) printf("←");
	            else if (cnt == 8) printf("↓");
	            else if (cnt == 6) printf("→");
			} 
			else if(cnt==5) {
				gotoxy(x, y+1);
				printf("▶");
			} 
            
            gotoxy(x-1, y+2);	// 문자 출력 
            for (z = 0; z <= 2; z += 1)
                printf("%c", alpha[cnt][z]);
        }
    }
    gotoxy(4, 25);
    printf("ESC");
    gotoxy(5, 27);
    printf("☜");
    
    gotoxy(13, 25);
    printf("0");
    gotoxy(13, 27);
    printf("_");
    
    gotoxy(20, 25);
    printf("BSP");
    gotoxy(21, 27);
    printf("◀");
}

// Phone Screen
void draw_Screen(int r, int h) {
    int i, j, l;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(int i=1;i<12;i++) b[i]=0xa0+i;
    
	printf("%c%c",a, b[3]); 						// ┌
	for(i=0;i<r*6-1;i++) printf("%c%c", a, b[1]);	// ━ 
    printf("%c%c", a, b[4]);						// ┐
	
	printf("\n");
	
	for(l=0; l<h; l++){
		for(i=0; i<r-1; i++){
			printf("%c%c",a, b[2]);				// │
			for(j=0;j<r*6-1;j++) printf(" ");
			printf("%c%c",a, b[2]);				// │
			printf("\n");
		}
    }
	
	printf("%c%c", a, b[6]); 					// └ 
	for(i=0;i<r*6-1;i++) printf("%c%c", a, b[1]);	// ━ 
    printf("%c%c", a, b[5]);					// ┘ 
    printf("\n");
}

// Phone Keypad
void draw_Keypad(int r, int h) {
    int i, j, k, l;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(int i=1;i<12;i++) b[i]=0xa0+i;
    
    printf("%c%c",a, b[3]); 						// ┌
    for(j=0; j<r-2; j++){
        for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━ 
        printf("%c%c", a, b[8]);					// ┯ 
    }
    for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
    printf("%c%c", a, b[4]);						// ┐
    
    printf("\n");
    
    for(l=0; l<h; l++){
        for(i=0; i<r-1; i++){
            for(j=0;j<r;j++) {
                printf("%c%c",a, b[2]);				// │ 
                for(k=0;k<r*2-1;k++) printf(" ");
            }
            printf("\n");
        }
        for(i=0;i<r-1;i++) {
            printf("%c%c", a, b[7]); 						// ┣ 
            for(j=0; j<r-2; j++){
                for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━ 
                printf("%c%c", a, b[11]);					// ┿ 
            }
            for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
            printf("%c%c",a, b[9]); 						// ┤ 
            printf("\n");
        }
    }
    for(i=0; i<r-1; i++){
        for(j=0;j<r;j++) {
            printf("%c%c",a, b[2]);				// │ 
            for(k=0;k<r*2-1;k++) printf(" ");
        }
        printf("\n");
    }
    
    printf("%c%c", a, b[6]); 					// └ 
    for(j=0; j<r-2; j++){
        for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
        printf("%c%c", a, b[10]);					// ┴ 
    }
    for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ━
    printf("%c%c", a, b[5]);					// ┘ 
    printf("\n");
}

```

### 고장난 피처폰 수정 사항 소개
- 전화 모드 또는 문자 모드에 들어가면 배경 색이 바뀜
- 다시 돌아오면 색이 원래대로 돌아옴

![image](https://github.com/user-attachments/assets/60eb9004-ecdd-4fc5-acee-e64fcc247b06) | ![image](https://github.com/user-attachments/assets/3458279f-ed0f-479c-a6d5-1414ff125026) | ![image](https://github.com/user-attachments/assets/5363b177-362f-4d0b-9bd5-b925cc0431cb)
:---: | :---: | :---:
메인 화면 | 전화 모드 화면 | 문자 모드 화면


