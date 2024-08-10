#include "../../include/ft_signal.h"

void	sigint_heredoc_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (1);
}

void	sigint_prompt_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	// 커서가 다음줄로 옮겨간것을 readline에 적용
	// 현재 버퍼를 비워줌
	// readline 메시지를 다시 출력
	// $? 출력 시 1로 나오게 수정.
}
