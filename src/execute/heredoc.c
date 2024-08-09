#include "../../include/execute.h"

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
	if ((base_path = key_to_value_loc("TMPDIR", token->envp)) == NULL)
		base_path = "/tmp/";
	file_name = ft_strjoin(".heredoc_no", num);
	file_path = ft_strjoin(base_path, file_name);
	free(file_name);
	free(num);
	return (file_path);
}

char	*delete_quotes(char *eof, int *need_convert)
{
	if ((eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\'')
		|| (eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"'))
		*need_convert = 1;
	else
		*need_convert = 0;
	// todo : 동현님 코드에서 '," 제거하는 것 사용
	return (NULL);
}

void	readline_heredoc(char *heredoc_file, char *eof)
{
	int		fd;
	char	*buf;
	int		need_convert;
	char	*real_eof;

	// eof 에 ", ' 있다면 삭제 후 0반환. 없다면 0반환
	real_eof = delete_quotes(eof, &need_convert);
	fd = open(heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, eof, ft_strlen(eof)))
	{
		if (need_convert)
			buf = convert_env_in_str(buf);
		ft_putendl_fd(buf, fd);
		free(buf);
		buf = readline("> ");
	}
	free(buf);
	free(real_eof);
	close(fd);
	// todo : ctrl + c일 경우 return (ERROR);
	return (SUCCESS);
}

/**
 * 히어독 파일 읽기.
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
			if (!heredoc_file)
				free(heredoc_file);
			heredoc_file = create_heredoc_filepath(token);
			readline_heredoc(heredoc_file, files->next->content);
		}
		files = files->next;
	}
	// return : 히어독 있었다면 마지막 히어독 경로, 히어독 없다면 NULL.
	// todo : while 문으로 << 를 체크하여 heredoc 읽기 구현.
	// 3. token->file_list->content->file_path를 히어독 파일 경로로 대체.
	// 히어독 읽는 도중 cmd + d 하면 Tmp 파일 저장되고 이후 명령 수행되어야 함.

	return (NULL);
}