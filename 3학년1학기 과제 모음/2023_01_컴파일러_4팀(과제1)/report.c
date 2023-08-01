#include <stdio.h>
#include <stdbool.h>

// DFA의 상태 정의
typedef enum {
    STATE_INITIAL,
    STATE_INTEGER,
    STATE_DECIMAL,
    STATE_INVALID
} State;

// 현재 상태에서 다음 상태로 전이하는 함수
State transition(State current, char input) {
    switch(current) {
        case STATE_INITIAL:
        case STATE_INTEGER:
            if(input >= '0' && input <= '9') return STATE_INTEGER;
            if(input == '.') return STATE_DECIMAL;
            return STATE_INVALID;
        case STATE_DECIMAL:
            if(input >= '0' && input <= '9') return STATE_DECIMAL;
            return STATE_INVALID;
        default:
            return STATE_INVALID;
    }
}

// 입력된 문자열을 판별하는 함수
bool accept(char* str) {
    State current = STATE_INITIAL;
    char c;
    int i = 0;
    while((c = str[i++]) != '\0') {
        current = transition(current, c);
        if(current == STATE_INVALID) {
            printf("Error: Invalid input\n");
            return false;
        }
    }
    if(current == STATE_DECIMAL || current == STATE_INTEGER) {
        printf("Input string: %s\n", str);
        printf("Accepted\n");
        return true;
    } else {
        printf("Input string: %s\n", str);
        printf("Rejected\n");
        return false;
    }
}

int main() {
    FILE *fp = fopen("input.txt", "r"); // 입력 파일 열기
    if(fp == NULL) {
        printf("Error: Cannot open input file\n");
        return 1;
    }
    char str[100];
    while(fscanf(fp, "%s", str) == 1) {
        if(!accept(str)) {
            printf("Rejected\n");
        }
    }
    fclose(fp); // 입력 파일 닫기
    return 0;
}
