
#include <libft.h>

static	void	ft_free_join(char **s1, char **s2, int tofree)
{
	if (tofree == 0)
		free(*s1);
	else if (tofree == 1)
		free(*s2);
	else if (tofree == 2)
	{
		free(*s1);
		free(*s2);
	}
}

char			*ft_strjoin(char *s1, char *s2, int tofree)
{
	char		*frch;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	frch = (char*)malloc(sizeof(char*) * (strlen(s1) + strlen(s2) + 1));
	if (!(frch))
		return (NULL);
	while (s1[i] != '\0')
	{
		frch[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		frch[i] = s2[j];
		i++;
		j++;
	}
	frch[i] = '\0';
	ft_free_join(&s1, &s2, tofree);
	return (frch);
}
