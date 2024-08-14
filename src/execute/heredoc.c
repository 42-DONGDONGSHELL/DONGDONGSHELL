#include "../../include/ms_execute.h"
#include "../../include/ms_signal.h"
/**
 * 히어독 파일 경로 생성
 */
char	*create_heredoc_filepath(t_token *token)
{
	static int	i = 0;
	char		*num;
	char		*base_path;
	char		*file_name;
	char		*file_path;

	num = ft_itoa(i++);
	if ((base_path = key_to_value_loc("TMPDIR", *(token->envp))) == NULL)
		base_path = "/tmp/";
	file_name = ft_strjoin(".heredoc_no", num);
	file_path = ft_strjoin(base_path, file_name);
	free(file_name);
	free(num);
	return (file_path);
}

/**
 * EOF가 "나 '로 감싸여 있는지 확인 후 need_convert에 정보 저장, 만약 감싸여 있다면 벗기기.
 * return 순수한 EOF 반환.
 */
char	*delete_quotes_and_check(char *eof, int *need_convert)
{
	if ((eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\'')
		|| (eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"'))
		*need_convert = 0;
	else
		*need_convert = 1;
	return (strip_quotes(eof));
}

/**
 * 히어독 파일 경로를 받아 열고, readline으로 히어독의 입력을 받아 파일에 write.
 * todo : 히어독 읽는 도중 cmd + d 하면 Tmp 파일 저장되고 이후 명령 수행되어야 함.
 * todo : cmd + c 에 대한 처리
 */
void	readline_heredoc(t_token *token, char *heredoc_file, char *eof)
{
	int		fd;
	char	*buf;
	int		need_convert;
	char	*real_eof;
	t_envp	*envp_dict;

	real_eof = delete_quotes_and_check(eof, &need_convert);
	envp_dict = create_envp_dict(*(token->envp));
	fd = open(heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, eof, ft_strlen(eof) + 1) != 0)
	{
		if (need_convert)
			buf = envsubst_heredoc(buf, envp_dict);
		ft_putendl_fd(buf, fd);
		free(buf);
		buf = readline("> ");
	}
	free(buf);
	free(real_eof);
	free_envp_dict(envp_dict);
	close(fd);
}

/**
 * 히어독 파일 읽기.
 * return : 히어독 있었다면 마지막 히어독 경로, 히어독 없다면 NULL.
 */
char	*read_heredoc(t_token *token)
{
	char	*heredoc_file;
	t_node	*files;

	files = token->file_list->head;
	heredoc_file = NULL;
	while (files)
	{
		if (files->type == 5)
		{
			ft_signal_heredoc();
			if (heredoc_file)
				free(heredoc_file);
			heredoc_file = create_heredoc_filepath(token);
			readline_heredoc(token, heredoc_file, files->next->content);
			ft_signal_prompt();
		}
		files = files->next;
	}
	return (heredoc_file);
}
