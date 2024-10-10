#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void play_sound(int num);				// �Ҹ�(�������ġ�) ��� 
void gotoxy(int x, int y);				// ��ġ �̵�
void draw_Screen(int r, int h);			// ��ũ�� �׸��� 
void draw_Keypad(int r, int h);			// Ű�е� �׸��� 
void pad();								// ȭ�鿡 ���� �е� �׸��� 

void control();							// ���� ȭ�� ��Ʈ�� 
void main_mode();						// ���� ȭ�� 
void update_time();						// ���� ȭ�� - ��¥ �� �ð� ���
void call_mode();						// ��ȭ ȭ�� 
void text_mode();						// ���� ȭ��  

#define X 4
#define Y 6

char alpha[][3] = {{' '}, {'a', 'b', 'c'}, {'d', 'e', 'f'}, 
                   {'g', 'h', 'i'}, {'j', 'k', 'l'}, {'m', 'n', 'o'},
                   {'p', 'q', 'r'}, {'w', 't', 'u'}, {'v','w','x'}, 
                   {'y', 'z', '.'}};

int main() {
    SetConsoleTitle("���峭 ��ó��");
    system("color F0");
    
    main_mode();
    control();
}

void main_mode() {
	system("cls");
    pad();
    update_time();  //���� �ð� ��� 
    gotoxy(12, 6);
    printf("��ȭ");
    gotoxy(12, 8);
    printf("����");
    
    gotoxy(9, 6);
}

void call_mode() {
    system("cls");
    pad();
    gotoxy(9, 2);
    printf("��ȭ ���");
    gotoxy(3, 10);
    printf("�� ��������");

    gotoxy(X, Y);
    int num_count = 0;  // �Էµ� ������ ������ �����ϴ� ����
    int x = X;          // Ŀ�� ��ġ�� �����ϴ� ����

    while (1) {
        char num = getch();
        if (num >= '0' && num <= '9' && num_count < 18) {  // ���� �Է� �� 18�� ����
            play_sound(num - '0');
			printf("%c", num);
            num_count++;  // �Էµ� ���� ���� ����
            x++;          // Ŀ�� ��ġ �̵�
        }
        else if (num == 8) {  // Backspace Ű�� ������ ��
            if (num_count > 0) {
                x--;          // Ŀ�� ��ġ�� �������� �̵�
                gotoxy(x, Y); // Ŀ�� �̵�
                printf(" ");  // ���ڸ� ����
                gotoxy(x, Y); // Ŀ���� �ٽ� ���� ��ġ�� �̵�
                num_count--;  // �Էµ� ���� ���� ����
            }
        }
        else if (num == 27) {  // ESC Ű�� ���� ������
            break;
        }
    }
    main_mode();
}

void text_mode() {
    system("cls");
    pad();
    gotoxy(9, 2);
    printf("���� ���");
    gotoxy(3, 10);
    printf("�� ��������");

    gotoxy(X, Y);
    char ch;
    int x = X;  // ���� Ŀ�� ��ġ�� �����ϱ� ���� ����
    int char_count = 0;  // �Էµ� ������ ������ ����

    while (1) {
        ch = getch();
        if (ch == 27) {  // ESC Ű�� ���� ������
            break;
        }
        else if (ch == 8) {  // backspace�� ������ ��
            if (x > 4) {  // ù ��° ��ġ�� ������ ����
                x--;  // Ŀ�� ��ġ �� ĭ �������� �̵�
                gotoxy(x, Y);  // Ŀ�� �̵�
                printf(" ");  // �ش� ��ġ ���� ����
                gotoxy(x, Y);  // Ŀ���� �ٽ� �ش� ��ġ�� �̵�
                char_count--;  // ���� ���� ����
            }
        }
        else if (ch >= '0' && ch <= '9' && char_count < 18) {  // ���� Ű �Է� �� 18���� ����
            char c1 = ch, c2;
            int cnt = 0;
            time_t start, end;
            
            printf("%c", alpha[c1 - '0'][cnt]);  // ���� ���
            x++;  // Ŀ�� ��ġ �̵�
            char_count++;  // �Էµ� ���� ���� ����

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
                    gotoxy(--x, Y);  // Ŀ�� ��ġ���� ���� �����
                    printf("%c", alpha[c1 - '0'][cnt]);  // �� ���� ���
                    x++;  // Ŀ�� ��ġ ������Ʈ
                    start = time(NULL);  // �ð� �ʱ�ȭ
                } else {
                    break;
                }
            } while (1);
        }
    }
    main_mode();
}

void control(void) {
    int cursor_pos = 6;  // ���� ���õ� �޴��� ��ġ (6: ��ȭ, 8: ����)
    int prev_cursor_pos = 6;  // ���� ���õ� �޴��� ��ġ
    char c;
	
	gotoxy(9, cursor_pos);
    printf("��");
	
    do {
        if (prev_cursor_pos != cursor_pos) { // ���õ� �޴��� ����Ǿ��� ���� ȭ�� ������Ʈ 
            gotoxy(9, prev_cursor_pos);
            printf("  ");  // ���� ���� ǥ�� �����

            gotoxy(9, cursor_pos);
            printf("��");  // ���� ���� ǥ��

            prev_cursor_pos = cursor_pos;  // ���� ��ġ�� ���� ��ġ�� ������Ʈ
        }

        if (_kbhit()) {  // Ű �Է��� �ִ��� Ȯ��
            c = getch();

            if (c == '8') {  // ��Ű 
                if (cursor_pos < 8) {
                    cursor_pos += 2;
                }
            }
            else if (c == '2') {  // ��Ű 
                if (cursor_pos > 7) {
                    cursor_pos -= 2;
                }
            }
            else if (c == '5') {  // Enter Ű
                if (cursor_pos == 6) {
                    call_mode();
                } else if (cursor_pos == 8) {
                    text_mode();
                }
            }
        }
    } while (1);
}

void update_time() {	// ���� ��¥ �� �ð� ��� 
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
    if (0 <= num && num <= 9) {	// 1=��, 2=��, ��, 9=���� ��, 0=���� �� 
        Beep(frequencies[num], 150);
    }
}

void pad() {
    int y, x, z, cnt = 0;
    
    draw_Screen(4, 3);
    draw_Keypad(4, 3);
    
    for (y = 13; y <= 22; y += 4) {
        for (x = 5; x <= 21; x += 8) {
            gotoxy(x, y);	// ���� ��� 
            printf("%d", ++cnt);
            
            if(cnt%2==0) {	//ȭ��ǥ ��� 
            	gotoxy(x, y+1);
            	if (cnt == 2) printf("��");
	            else if (cnt == 4) printf("��");
	            else if (cnt == 8) printf("��");
	            else if (cnt == 6) printf("��");
			} 
			else if(cnt==5) {
				gotoxy(x, y+1);
				printf("��");
			} 
            
            gotoxy(x-1, y+2);	// ���� ��� 
            for (z = 0; z <= 2; z += 1)
                printf("%c", alpha[cnt][z]);
        }
    }
    gotoxy(4, 25);
    printf("ESC");
    gotoxy(5, 27);
    printf("��");
    
    gotoxy(13, 25);
    printf("0");
    gotoxy(13, 27);
    printf("_");
    
    gotoxy(20, 25);
    printf("BSP");
    gotoxy(21, 27);
    printf("��");
}

// Phone Screen
void draw_Screen(int r, int h) {
    int i, j, l;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(int i=1;i<12;i++) b[i]=0xa0+i;
    
	printf("%c%c",a, b[3]); 						// ��
	for(i=0;i<r*6-1;i++) printf("%c%c", a, b[1]);	// �� 
    printf("%c%c", a, b[4]);						// ��
	
	printf("\n");
	
	for(l=0; l<h; l++){
		for(i=0; i<r-1; i++){
			printf("%c%c",a, b[2]);				// ��
			for(j=0;j<r*6-1;j++) printf(" ");
			printf("%c%c",a, b[2]);				// ��
			printf("\n");
		}
    }
	
	printf("%c%c", a, b[6]); 					// �� 
	for(i=0;i<r*6-1;i++) printf("%c%c", a, b[1]);	// �� 
    printf("%c%c", a, b[5]);					// �� 
    printf("\n");
}

// Phone Keypad
void draw_Keypad(int r, int h) {
    int i, j, k, l;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(int i=1;i<12;i++) b[i]=0xa0+i;
    
    printf("%c%c",a, b[3]); 						// ��
    for(j=0; j<r-2; j++){
        for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// �� 
        printf("%c%c", a, b[8]);					// �� 
    }
    for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ��
    printf("%c%c", a, b[4]);						// ��
    
    printf("\n");
    
    for(l=0; l<h; l++){
        for(i=0; i<r-1; i++){
            for(j=0;j<r;j++) {
                printf("%c%c",a, b[2]);				// �� 
                for(k=0;k<r*2-1;k++) printf(" ");
            }
            printf("\n");
        }
        for(i=0;i<r-1;i++) {
            printf("%c%c", a, b[7]); 						// �� 
            for(j=0; j<r-2; j++){
                for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// �� 
                printf("%c%c", a, b[11]);					// �� 
            }
            for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ��
            printf("%c%c",a, b[9]); 						// �� 
            printf("\n");
        }
    }
    for(i=0; i<r-1; i++){
        for(j=0;j<r;j++) {
            printf("%c%c",a, b[2]);				// �� 
            for(k=0;k<r*2-1;k++) printf(" ");
        }
        printf("\n");
    }
    
    printf("%c%c", a, b[6]); 					// �� 
    for(j=0; j<r-2; j++){
        for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ��
        printf("%c%c", a, b[10]);					// �� 
    }
    for(i=0;i<r*2-1;i++) printf("%c%c", a, b[1]);	// ��
    printf("%c%c", a, b[5]);					// �� 
    printf("\n");
}

