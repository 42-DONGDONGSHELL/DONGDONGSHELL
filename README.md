# Minishell

![minishell_record](https://github.com/user-attachments/assets/737f2afc-400e-45fc-83f4-5f9f9af461bf)

## 주요 기능

- 내장 명령어
  - `cd`: 현재 디렉토리 변경
  - `exit`: 쉘 종료
  - `echo`: 메시지를 터미널에 출력
  - `export`: 환경 변수를 설정
  - `unset`: 환경 변수를 제거
  - `env`: 환경 변수 목록을 출력
  - `pwd`: 현재 작업 디렉토리 출력
 
- 외부 명령어
  - 시스템의 `PATH` 환경 변수에 등록된 디렉토리에 있는 명령어들을 실행할 수 있습니다 (예: `ls`, `grep` 등).


## 사용 방법

1. 레포지토리 클론
2. 프로젝트의 root dir로 이동하기
3. 실행 파일 빌드 : 쉘을 컴파일하기 위해 `make`명령어 실행

    ```bash
    $ make
    ```
4. `minishell` 실행

    ```bash
    $ ./minishell
    ```

## 지원 기능
- 신호 처리
  - `Ctrl + C`, `Ctrl + D`, `Ctrl + \` 처리
- 입출력 리다이렉션
  - `>`(덮어쓰기), `>>`(덧붙이기), `<`(파일 입력), `<<`(히어독) 지원
- 파이프 처리
  - `|`
 
