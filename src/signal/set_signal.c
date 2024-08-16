#include "../../include/ms_signal.h"

/**
 * heredoc 처리 중 사용.
 */
void	ft_signal_heredoc(void)
{
	set_terminal_print_off();
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * 기본
 * - 프롬프트 띄우기 전 init 할 때
 * - heredoc이 끝났다면 다시 이 함수를 통해 설정.
 * - 명령어 실행이 모두 끝났다면 설정
 */
void	ft_signal_prompt(void)
{
	set_terminal_print_off();
	signal(SIGINT, sigint_prompt_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * 부모 프로세스에서 자식 프로세스 기다리며 사용
 */
void	ft_signal_ignore(void)
{
	set_terminal_print_off();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * 자식 프로세스에서 bin 명령어 실행 전 사용
 */
void	ft_signal_default(void)
{
	set_terminal_print_on();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
