/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketClient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:16:30 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 20:02:02 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <game.h>

void	write_server(int sock, const char *buffer);

int read_server(int sock, char *buffer);

int read_msg(int fd, char *buffer);

void	socketManager(t_game *g);

void	reset(t_game *g) {
	g->is_ready = 0;
	g->is_selecting = S_NONE;
	g->frame = FRAME_START;
	displayFrame(g);
	initScore(g);
	closesocket(&g->sock);
	initNetworking(g);
}

int	getAdv(int slct, int rslt) {
	if (rslt == R_WIN){
		if (slct == S_ROCK)
			return (S_SCISSORS);
		else if (slct == S_PAPER)
			return (S_ROCK);
		else
			return (S_PAPER);
	}
	else if (rslt == R_LOSE) {
		if (slct == S_ROCK)
			return (S_PAPER);
		else if (slct == S_PAPER)
			return (S_SCISSORS);
		else
			return (S_ROCK);
	}
	return (slct);
}

void	*socketThread(t_game *g) {
	char buffer[BUF_SIZE];
	fd_set rdfs;
	int nfds = MAX(g->fd[LECTURE], g->sock);
	while (1) {
		FD_ZERO(&rdfs);
		FD_SET(g->fd[LECTURE], &rdfs);
		FD_SET(g->sock, &rdfs);
		if(select(nfds + 1, &rdfs, NULL, NULL, NULL) == -1)
			perror("select(), socketThread");
		if (FD_ISSET(g->fd[LECTURE], &rdfs))
		{
			int n = read_msg(g->fd[LECTURE], buffer);
			/* to exit */
			if (n == 0) {
				printf("Pipe closed !\n");
				break;
			}
			if (!strcmp(buffer, "exit")) {
				printf("exit socket thread...\n");
				close(g->fd[LECTURE]);
				break ;
			}
			else if (!strcmp(buffer, "bot"))
				write_server(g->sock, "bot");
			else if (!strcmp(buffer, "paper"))
				write_server(g->sock, "paper");
			else if (!strcmp(buffer, "rock"))
				write_server(g->sock, "rock");
			else if (!strcmp(buffer, "scissors"))
				write_server(g->sock, "scissors");
		}
		if (FD_ISSET(g->sock, &rdfs)) {
			int n = read_server(g->sock, buffer);
			/* server down */
			if (n == 0) {
				printf("Server disconnected !\n");
				closeGame(g);
			}
			if (!strcmp(buffer, "waiting"))
				printf(" => En attente d'un adversaire... ");
			else if (!strcmp(buffer, "find")) {
				g->is_ready = 1;
				printf(" OK \n");
			}
			else if (!strcmp(buffer, "discon")) {
				printf("L'adversaire quitte le match !\n");
				fflush(stdout);
				reset(g);
				break ;
			}
			else if (!strcmp(buffer, "nul"))
				displayResult(g, R_EQ, getAdv(g->is_selecting, R_EQ));
			else if (!strcmp(buffer, "gagne") && (g->my_score += 1))
				displayResult(g, R_WIN, getAdv(g->is_selecting, R_WIN));
			else if (!strcmp(buffer, "perdu") && (g->adv_score += 1))
				displayResult(g, R_LOSE, getAdv(g->is_selecting, R_LOSE));
			fflush(stdout);
		}
	}
	pthread_exit(NULL);
}
void	write_server(int sock, const char *buffer)
{
	if (send(sock, buffer, strlen(buffer), 0) < 0)
		perror("send()");
}
int read_server(int sock, char *buffer)
{
	int n = 0;

	if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
		perror("recv()");

	buffer[n] = 0;
	return n;
}

int read_msg(int fd, char *buffer) {
	int n = 0;
	if ((n = read(fd, buffer, BUF_SIZE)) < 0)
		perror("recv()");
	buffer[n] = 0;
	return n;
}

void	socketManager(t_game *g) {
	pthread_t	tid;
	pthread_create(&tid, NULL, (void*)socketThread, g);
}
