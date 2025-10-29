#include <linux/input.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*ft_connect(void *arg)
{
	struct sockaddr_in		servtarg;
	int						sockfd;

	memset(&servtarg, 0, sizeof(servtarg));
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	servtarg.sin_family = AF_INET;
	servtarg.sin_port = htons(8523);
	inet_pton(AF_INET, "127.0.0.1", &servtarg.sin_addr);
	if (connect(sockfd, (struct sockaddr *)&servtarg, sizeof(servtarg)) < 0)
		perror("conexação recusada");
	while (true);
	close(sockfd);
	exit(EXIT_SUCCESS);
	return (arg);
}

int	main(void)
{
	struct input_event	key;
	int					fd;
	pthread_t			payload;

	fd = open("/dev/input/event0", O_RDONLY);
	if (fd < 0)
	{
		perror("Erro: leitura invalidad da interface input");
		exit(EXIT_FAILURE);
	}
	while (read(fd, &key, sizeof(key)))
	{
		if (key.type == EV_KEY && key.value == 1)
		{
			if (key.code == KEY_A || key.code == KEY_E || key.code == KEY_I ||
				key.code == KEY_O || key.code == KEY_U)
				pthread_create(&payload, NULL, &ft_connect, NULL);
		}
	}
	return (0);
}
