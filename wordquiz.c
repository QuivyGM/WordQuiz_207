#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


typedef 
	enum {	//기능: 단어장 목록보기, 단어장 내용보기, 단어장 테스트, 종료
		C_ZERO,
		C_LIST,
		C_SHOW,
		C_TEST,
		C_EXIT,
	}
	command_t ;

char * read_a_line (FILE * fp){	//파일에서 한 줄씩 읽어오는 함수
	static char buf[BUFSIZ] ;	//버퍼
	static int buf_n = 0 ;		//버퍼의 크기
	static int curr = 0 ;		//현재 위치

	if (feof(fp) && curr == buf_n - 1)	//파일의 끝에 도달하면
		return 0x0 ;

	char * s = 0x0 ;	//문자열
	size_t s_len = 0 ;	//문자열의 길이

	do {	//버퍼에 있는 문자열을 한 줄씩 읽어옴 - (while: 버퍼의 크기가 0보다 클 때)

		int end = curr ;	//현재 위치
		while (!(end >= buf_n || !iscntrl(buf[end]))) {	//문자열이 끝나거나 제어문자가 아닐 때까지
			end++ ;
		}

		if (curr < end && s != 0x0) {					//현재 위치가 끝보다 작고 문자열이 비어있지 않을 때
			curr = end ;
			break ;
		}

		curr = end ;	//현재 위치를 끝으로 설정

		while (!(end >= buf_n || iscntrl(buf[end]))) {	//문자열이 끝나거나 제어문자일 때까지
			end++ ;
		}
		if (curr < end) {	//현재 위치가 끝보다 작을 때
			if (s == 0x0) {	//문자열이 비어있을 때
				s = malloc(end - curr + 1);									//replaced strndup
				memcpy(s, buf + curr, end - curr);
				s[end - curr] = '\0';
				s_len = end - curr ;
			}
			else {			//문자열이 비어있지 않을 때
				s = realloc(s, s_len + end - curr + 1) ;
				s = strncat(s, buf + curr, end - curr) ;
				s_len = s_len + end - curr ;
			}
		}
		if (end < buf_n) {	//끝이 버퍼의 크기보다 작을 때
			curr = end + 1 ;
			break ;
		}

		buf_n = fread(buf, 1, sizeof(buf), fp) ;	//버퍼에 파일을 읽어옴
		curr = 0 ;									//현재 위치를 0으로 설정
	} while (buf_n > 0) ;//버퍼의 크기가 0보다 클 때
	return s ;	//문자열 반환
}



void print_menu() {	//메뉴 출력

	printf("1. List all wordbooks\n") ;
	printf("2. Show the words in a wordbook\n") ;
	printf("3. Test with a wordbook\n") ;
	printf("4. Exit\n") ;
}

int get_command() {	//명령어 입력
	int cmd ;

	printf(">") ;
	scanf("%d", &cmd) ;
	return cmd ;
}

void list_wordbooks (){	//단어장 목록 출력

	DIR * d = opendir("wordbooks") ;	//wordbooks 디렉토리 열기
	
	printf("\n  ----\n") ;

	struct dirent * wb ;				//단어장
	while ((wb = readdir(d)) != NULL) {	//단어장이 NULL이 아닐 때까지
		if (strcmp(wb->d_name, ".") != 0 && strcmp(wb->d_name, "..") !=0) {	//단어장이 .이나 ..이 아닐 때
			printf("  %s\n", wb->d_name) ;	//단어장 출력
		}
	}
	closedir(d) ;	//디렉토리 닫기

	printf("  ----\n") ;
}

void show_words (){	//단어장 내용 출력
	char wordbook[128] ;	//단어장
	char filepath[256] ;	//파일 경로

	list_wordbooks() ;		//단어장 목록 출력

	printf("Type in the name of the wordbook?\n") ;
	printf(">") ;
	scanf("%s", wordbook) ;	//단어장 입력

	sprintf(filepath, "wordbooks/%s", wordbook);	//파일 경로 설정

	FILE * fp = fopen(filepath, "r") ;				//파일 열기

	printf("\n  -----\n") ;

	char * line ;									//문자열
	while (line = read_a_line(fp)) {				//문자열이 NULL이 아닐 때까지
		char * word = strtok(line, "\"") ;				//word는 문자열 (strtok: 문자열을 나눔)
		strtok(NULL, "\"") ;							//문자열 나눔
		char * meaning = strtok(NULL, "\"") ;			//meaning은 문자열 (strtok: 문자열을 나눔)

		printf("  %s : %s\n", word, meaning) ;			//단어와 뜻 출력

		free(line) ;									//문자열 해제
	}
	printf("  -----\n\n") ;

	fclose(fp) ;										//파일 닫기
}


void run_test (){
	char wordbook[128] ;	//단어장
	char filepath[256] ;	//파일 경로

	printf("Type in the name of the wordbook?\n") ;
	printf(">") ;
	scanf("%s", wordbook) ;

	sprintf(filepath, "wordbooks/%s", wordbook) ;	//파일 경로 설정

	FILE * fp = fopen(filepath, "r") ;				//파일 열기

	printf("\n-----\n") ;

	int n_questions = 0 ;	//질문 수
	int n_correct = 0 ; 	//정답 수

	char * line ;			//문자열 (*한 이유는 문자열을 나누기 위해)
	while (line = read_a_line(fp)) {		//문자열이 NULL이 아닐 때까지
		char * word = strtok(line, "\"") ;		//word는 문자열 (strtok: 문자열을 나눔)
		strtok(NULL, "\"") ;					//문자열 나눔
		char * meaning = strtok(NULL, "\"") ;	//meaning은 문자열 (strtok: 문자열을 나눔)

		printf("Q. %s\n", meaning) ;		//문제 출력
		printf("?  ") ;						//입력	

		char answer[128] ;				//답	
		scanf("%s", answer) ;			//답 입력

		if (strcmp(answer, word) == 0) {	//답이 맞을 때
			printf("- correct\n") ;
			n_correct++ ;					//정답 수 증가
		}
		else {								//답이 틀릴 때
			printf("- wrong: %s\n", word) ;
		}

		n_questions++ ;						//질문 수 증가
		free(line) ;						//문자열 해제
	}

	printf("(%d/%d)\n", n_correct, n_questions) ;	//정답 수와 질문 수 출력

	printf("-----\n\n") ;	

	fclose(fp) ;	//파일 닫기							
}


int main (){
	
	printf(" *** Word Quiz *** \n\n") ;

	int cmd ;
	do {
		print_menu() ;					//메뉴 출력

		cmd = get_command() ;			//명령어 입력
		switch (cmd) {	
			case C_LIST : {				//단어장 목록 출력
				list_wordbooks() ;
				break ;
			}

			case C_SHOW: {				//단어장 내용 출력
				show_words() ;
				break ;
			}

			case C_TEST: {				//단어장 테스트
				run_test() ;
				break ;
			}

			case C_EXIT: {				//종료
				return EXIT_SUCCESS ;
			}
		}
	}
	while (cmd != C_EXIT) ;				//명령어가 종료가 아닐 때


	return EXIT_SUCCESS ;
}
