/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongclee <dongclee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:20:38 by dongclee          #+#    #+#             */
/*   Updated: 2024/08/16 17:11:14 by dongclee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms_execute.h"
#include "../../include/ms_signal.h"
#include "../../include/ms_error.h"
#include "../../include/ms_wait.h"
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
	base_path = key_to_value_loc("TMPDIR", *(token->envp));
	if (base_path == NULL)
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
	int	i;

	i = 0;
	*need_convert = 1;
	while (eof[i])
	{
		if (eof[i] == '\'' || eof[i] == '\"')
		{
			*need_convert = 0;
			break ;
		}
		i++;
	}
	return (strip_quotes(eof));
}

/**
 * 히어독 파일 경로를 받아 열고, readline으로 히어독의 입력을 받아 파일에 write.
 */
void	readline_heredoc(char **envp, char *heredoc_file, char *eof)
{
	int		fd;
	char	*buf;
	int		need_convert;
	char	*real_eof;
	t_envp	*envp_dict;

	real_eof = delete_quotes_and_check(eof, &need_convert);
	envp_dict = create_envp_dict(envp, 0);
	fd = open(heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, real_eof, ft_strlen(real_eof) + 1) != 0)
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
	exit(0);
}

char	*process_heredoc_file(t_token *token, t_node *files)
{
	char	*h_file;
	int		pid;
	int		status;

	h_file = create_heredoc_filepath(token);
	pid = fork();
	if (pid < 0)
		perror_cmd("fork");
	if (pid == 0)
	{
		ft_signal_heredoc();
		readline_heredoc(*(token->envp), h_file, files->next->content);
		free_token_list(token->list_info);
	}
	else
	{
		ft_signal_ignore();
		waitpid(pid, &status, 0);
		status_to_exit_code(status);
	}
	return (h_file);
}

/**
 * 히어독 파일 읽기.
 * return : 히어독 있었다면 마지막 히어독 경로, 히어독 없다면 NULL.
 */
char	*read_heredoc(t_token *token)
{
	char	*h_file;
	t_node	*files;

	files = token->file_list->head;
	h_file = NULL;
	while (files)
	{
		if (files->type == 5)
		{
			if (h_file)
				free(h_file);
			h_file = process_heredoc_file(token, files);
		}
		files = files->next;
	}
	return (h_file);
}
