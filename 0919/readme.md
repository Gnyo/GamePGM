# Game Programming 02
## 트럼프 카드 표시

### 트럼프 카드 만들기
- 트럼프 카드는 4개의 모양(♠◆♥♣)으로 나누어져 있으며 각 모양은 13장의 카드로 구성되므로 모두 52장이 사용

<p align="center">
  <img src="https://github.com/user-attachments/assets/3d14c864-7c94-4b75-b640-e525dc4458ed">
</p>

- 숫자(또는 문자)와 모양 즉, 두 가지 데이터로 표시되므로 구조체로 표현
- 순위는 스페이드(♠) 모양을 1순위(order=0), 다이아몬드(◆)는 2순위(order=1), 하트(♥)는 3순위(order=2) 그리고 클로버(♣)는 4순위(order=3)로 가정

```c
struct trump {
    char order;	//카드의 우선순위 
    char shape[3];	//카드 모양(2 byte크기의 완성형 기호)
    char number;	//카드의 숫자(또는 문자)
};
```
<p align="center">
  <img src="https://github.com/user-attachments/assets/29932569-ac15-46c5-8844-32312c65ea71">
</p>


- 카드의 모양(♠◆♥♣)은 2차원 배열에 저장하여 구분
- 반복문에 의해 카드의 순위를 멤버 order에 저장
- 멤버 order의 값에 따라 카드의 모양을 멤버 shpae에 저장하고, 멤버 number에는 카드의 번호를 저장하되 switch-case문으로 1일 경우는 number에 'A'를, 11일 경우는 'J', 12일 경우는 'Q', 13일 경우는 'K'를 저장
```c
void make_card(trump m_card[]) {
    int i, j;
    char shape[4][3] = {"♠","◆", "♥","♣"};

    for (i = 0; i < 4; i++) {

        for (j = i * 13; j < i * 13 + 13; j++) {
            m_card[j].order = i;   
            strcpy(m_card[j].shape, shape[i]);  
            m_card[j].number = j % 13 + 1;  

            switch (m_card[j].number) {
            case 1:
                m_card[j].number = 'A';
                break;
            case 11:
                m_card[j].number = 'J';
                break;
            case 12:
                m_card[j].number = 'Q';
                break;
            case 13:
                m_card[j].number = 'K';
                break;
            }
        }
    }
}
```

---

### 생성된 카드 출력
- number가 10보다 클 경우에는 문자형으로 출력
- 멤버 number는 숫자일 경우 최대 2자리까지 사용되지만, 문자가 저장된 경우에는 하나의 문자이므로 문자일 경우는 형식지정자 "%-2c"(2자리 왼쪽 맞춤)를, 숫자일 경우는 "%-2d "를 사용

```c
void display_card(trump m_card[]) {
    
    int i, count = 0;

    for (i = 0; i < 52; i++) {
        printf("%s", m_card[i].shape);

        if (10 < m_card[i].number)
        	printf("%-2c ", m_card[i].number);
        else
            printf("%-2d ", m_card[i].number);
        count++;

        if (i % 13 + 1 == 13) {
            printf("\n");
            count = 0;
        }
    }
}
```

```c
#include <stdio.h>
#include <string.h>

struct trump {
    char order;		// 우선순위 
    char shape[3];	// 모양 
    char number;	// 숫자 
};

typedef struct trump trump;

void make_card(trump m_card[]);  // 카드 만들기 함수
void display_card(trump m_card[]); // 카드 화면 출력 함수

int main() {
    trump card[52];
    make_card(card);
    display_card(card);
    return 0;
}
```

<p align="center">
  <img src="https://github.com/user-attachments/assets/ca5157ee-366c-46dc-a8d0-9d052aa12d8c">
</p>

---

### 카드 섞기(1)
- 카드를 섞는 것은 카드의 위치를 서로 교환하는 것
> 1단계: 정수 난수 rnd를 발생하여 a[0]과 a[rnd]의 카드를 서로 바꾼다. <br/>
> 2단계: 정수 난수 rnd를 발생하여 a[1]과 a[rnd]의 카드를 서로 바꾼다. <br/>
> 그 후: 단계 반복
```c
void shuffle_card(trump m_card[]){
	int rnd;
	trump temp;
	srand(time(NULL)); //난수의 초기화
	 
	for(int i=0; i<52; i++){
		rnd = rand()%52;
		temp = m_card[rnd];
		m_card[rnd] = m_card[i];
		m_card[i] = temp;
	}
}
```

![image](https://github.com/user-attachments/assets/2dd837fe-6ff0-45ba-9f27-f6944ae9bc32) | ![image](https://github.com/user-attachments/assets/7be11021-3b56-45d6-8704-9db9ac749f6b) |
---| ---|

---

### 카드 섞기(2)
- 카드 섞기(1)방법에서는 발생된 난수(rnd)가 바꿀 카드의 위치 i와 같다면 카드의 위치 교환이 이루어지지 않음
- 발생된 난수 rnd가 i와 같을 경우에는 다시 난수를 발생하도록 하여 위치교환이 이루어지지 않는 경우가 없도록 수정 
```c
void shuffle_card(trump m_card[]){
	int rnd;
	trump temp;
	srand(time(NULL)); //난수의 초기화
	 
	for(int i=0; i<52; i++){
		
		do{
			rnd = rand()%52;
		}while(rnd==i);
		
		temp = m_card[rnd];
		m_card[rnd] = m_card[i];
		m_card[i] = temp;
	}
}
```

---

### 난수 출력
#### rand 함수
- rand 함수를 사용하기 위해서는 stdlib.h 헤더파일을 include 해야 함
- 0부터 RAND_MAX 범위까지의 난수 생성
- int형 반환


