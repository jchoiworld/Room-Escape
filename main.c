#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct
{
    int firstDigit;   
    int secondDigit;  
    int thirdDigit;
    int fourthDigit;
    int diff;        
    int answer;
    int solved;
	int key;
    int restkey;
} Status;

void RandomNum(Status* s);
void printEast(Status* s);
void printWest(Status* s);
void printNorth(Status* s);
void printSouth(Status* s);

void printRoom(Status s)
{
    printf("\n=== [ Room Escape ] ===\n");
    printf("방 한가운데 서 있습니다. 사방을 둘러보며 힌트를 연결해 탈출하세요.\n");
    printf("명령어: [동], [서], [남], [북], [종료]\n\n");
    printf("현재 상태 - 열쇠: %s\n", s.key ==1 ? "보유" : "없음");
};

int main(void) 
{
    Status state = { 0 }; 
    char input[100];

    RandomNum(&state);

    while (!state.solved)
    {
        printRoom(state);
        printf("명령 입력: ");

        if (scanf("%s", input) != 1)
        {
            break;
        }

        if (strcmp(input, "동") == 0)
        {
            printEast(&state);
        }
        else if (strcmp(input, "서") == 0)
        {
            printWest(&state);
        }
        else if (strcmp(input, "남") == 0)
        {
            printSouth(&state);
        }
        else if (strcmp(input, "북") == 0)
        {
            printNorth(&state);
        }
        else if (strcmp(input, "종료") == 0)
        {
            printf("게임을 종료합니다.\n");
            return 0;
        }
        else
        {
            printf("알 수 없는 명령입니다.\n");
        }
    }

    printf("\n축하합니다! 단서들을 연결해 탈출에 성공했습니다!\n");
    return 0;
}

void RandomNum(Status* s) 
{
    srand((unsigned int)time(NULL));

    s->firstDigit = rand() % 8 + 1;
    s->secondDigit = rand() % 8 + 1;
    s->thirdDigit = rand() % 8 + 1;
    s->fourthDigit = rand() % 8 + 1;
    s->diff = s->secondDigit - s->firstDigit;
    s->answer = s->firstDigit * 1000 + s->secondDigit * 100 + s->thirdDigit * 10 + s->fourthDigit ;
    s->solved = 0;
    s->key = 0;
}

void printEast(Status *s) 
{
    char inspect[50];

    while (1)
    {
        printf("\n========================================\n");
        printf("=                                      =\n");
        printf("=        [시계], [책상], [서랍]        =\n");
        printf("=                                      =\n");
        printf("========================================\n");
        printf("무엇을 살펴볼까요? (시계, 책상, 서랍, 그만보기): ");
        
        if (scanf("%s", inspect) != 1) 
        {
            break;
        }

        if (strcmp(inspect, "시계") == 0)
        {
            printf("시침이 %d를 가리키고 있다.\n", s->firstDigit);
        }
        else if (strcmp(inspect, "책상") == 0)
        {
            printf("아무것도 없다.\n");
        }
        else if (strcmp(inspect, "서랍") == 0)
        {
            printf("[쪽지]: 암호의 첫번째 자리는 시침.\n");
        }
        else if (strcmp(inspect, "그만보기") == 0)
        {
            printf("동쪽을 살피는 것을 멈춥니다.\n");
            break;
        }
        else
        {
            printf("그런 물체는 보이지 않습니다.\n");
        }
    }
}

void printWest(Status* s)
{
    char inspect[50];

    while (1)
    {
        printf("\n========================================\n");
        printf("=                                      =\n");
        printf("=        [거울], [박스], [화장실]      =\n");
        printf("=                                      =\n");
        printf("========================================\n");
        printf("무엇을 살펴볼까요? (거울, 박스, 화장실, 그만보기): ");

        if (scanf("%s", inspect) != 1)
        {
            break;
        }

        if (strcmp(inspect, "거울") == 0)
        {
            printf("거울에 %d가 희미하게 보인다.\n", s->thirdDigit);
        }
        else if (strcmp(inspect, "박스") == 0)
        {
            printf("[쪽지]: 암호의 네번째 자리는 화장실에서 찾을 수 있다.\n");
        }
        else if (strcmp(inspect, "화장실") == 0)
        {
            if (s->restkey == 1)
            {
                printf("화장실에 %d개의 수건이 있다.\n", s->fourthDigit);
            }
            else printf("문이 잠겨있다.\n");
        }
        else if (strcmp(inspect, "그만보기") == 0)
        {
            printf("서쪽을 살피는 것을 멈춥니다.\n");
            break;
        }
        else
        {
            printf("그런 물체는 보이지 않습니다.\n");
        }
    }
}

void printNorth(Status* s)
{
    char inspect[50];

    while (1)
    {
        printf("\n========================================\n");
        printf("=                                      =\n");
        printf("=        [상자], [금고], [컴퓨터]      =\n");
        printf("=                                      =\n");
        printf("========================================\n");
        printf("무엇을 살펴볼까요? (상자, 금고, 컴퓨터, 그만보기): ");

        if (scanf("%s", inspect) != 1)
        {
            break;
        }

        if (strcmp(inspect, "상자") == 0)
        {
            if (s->restkey == 1)
            {
                printf("상자가 비어있다.\n");
            }
            else
            {
                printf("키를 찾았다.\n");
                s->restkey = 1;
            }            
        }
        else if (strcmp(inspect, "금고") == 0)
        {
            int password = 0;
            
            if (s->key == 1)
            {
                printf("금고가 비어있다.\n");
            }
            else
            {
                printf("비밀번호 4자리를 입력하시오: ");
                if (scanf("%d", &password) != 1)
                {
                    break;
                }

                if (password == s->answer)
                {
                    s->key = 1;
                    printf("비밀번호가 맞았습니다. [열쇠]를 획득했습니다!\n");
                }
                else
                {
                    printf("비밀번호가 틀렸습니다.\n");
                }
            }
        }
        else if (strcmp(inspect, "컴퓨터") == 0)
        {
            if (s->diff >= 0) 
            {
                printf("두번째 자리는 첫째 자리보다 %d 크다.\n", s->diff);
            }
            else {
                printf("두번째 자리는 첫째 자리보다 %d 작다.\n", -(s->diff));
            }
        }
        else if (strcmp(inspect, "그만보기") == 0)
        {
            printf("북쪽을 살피는 것을 멈춥니다.\n");
            break;
        }
        else
        {
            printf("그런 물체는 보이지 않습니다.\n");
        }
    }
}

void printSouth(Status* s)
{
    char inspect[50];

    while (1)
    {
        printf("\n========================================\n");
        printf("=                                      =\n");
        printf("=               [탈출구]               =\n");
        printf("=                                      =\n");
        printf("========================================\n");
        printf("무엇을 살펴볼까요? (탈출구, 그만보기): ");

        if (scanf("%s", inspect) != 1)
        {
            break;
        }

        if (strcmp(inspect, "탈출구") == 0)
        {
            if (s->key == 1)
            {
                s->solved = 1;
                printf("탈출하였습니다!!\n");
                break;
            }
            else
            {
                printf("열쇠가 필요합니다.\n");                
            }
        }
        else if (strcmp(inspect, "그만보기") == 0)
        {
            printf("남쪽을 살피는 것을 멈춥니다.\n");
            break;
        }
        else
        {
            printf("그런 물체는 보이지 않습니다.\n");
        }
    }
}

