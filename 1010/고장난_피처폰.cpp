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

