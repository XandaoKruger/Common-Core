/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acano-kr <acano-kr@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:12:28 by acano-kr          #+#    #+#             */
/*   Updated: 2026/05/23 19:04:27 by acano-kr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until(int fd, char *buffer, char *remi)
{
	int		rbyt;
	char	*temp;

	if (!remi)
		remi = ft_strdup("");
	if (!remi)
		return (NULL);
	rbyt = 1;
	while (rbyt > 0 && !ft_strchr(remi, '\n'))
	{
		rbyt = read(fd, buffer, BUFFER_SIZE);
		if (rbyt == -1 || (rbyt == 0 && *remi == '\0'))
		{
			free(remi);
			return (NULL);
		}
		buffer[rbyt] = '\0';
		temp = remi;
		remi = ft_strjoin(remi, buffer);
		free(temp);
		if (!remi)
			return (NULL);
	}
	return (remi);
}
//------------------------------------------------------------------------------
// 20. Se for null recebe str vazia
// 22. Se strdup falhar(malloc), retorna null
// 25. Verifica se le um ficheiro (retorno de read), e se nao e \n
// 27. rbyt armazena o retorno de read (num de bytes lido ou -1 se for erro)
//
// 28. Se read der erro (-1) ou EOF com conteúdo vazio, libera e retorna NULL.
//     Caso ainda tiver conteudo, nao retorna null, nao entra no if
//
// 33. inclui o \0 para indicar uma string valida para o strjoin
// 34. temp para poder (36.)limpar o que ja foi usado
// 35. Junta tudo e retorna
//------------------------------------------------------------------------------

char	*extr_line(char *remind)
{
	int	i;

	if (!remind || *remind == '\0')
		return (NULL);
	i = 0;
	while (remind[i] && remind[i] != '\n')
		i++;
	if (remind[i] == '\n')
		i++;
	return (ft_substr(remind, 0, i));
}
//------------------------------------------------------------------------------
// 60. if null retorna null, se for uma str vazia, nao ha nada para extrair
//      retorna null tambem
//
// 63.enquanto nao for fim da str e nem o fim da linha
// 65. se for o final da linha
// 67. substr inicia em 0 para extrair desde o inicio ate i, retorna nova string
//     se nao houver \n retorna o que sobrar, util quando e a ultima linha sem\n
//------------------------------------------------------------------------------

char	*updt_reminder(char *remin)
{
	char	*novo;
	int		a;

	if (!remin)
		return (NULL);
	if (*remin == '\0')
	{
		free(remin);
		return (NULL);
	}
	a = 0;
	while (remin[a] && remin[a] != '\n')
		a++;
	if (!remin[a])
	{
		free(remin);
		return (NULL);
	}
	novo = ft_strdup(remin + a + 1);
	free(remin);
	if (!novo || *novo == '\0')
		return (free(novo), NULL);
	return (novo);
}
// -----------------------------------------------------------------------------
// Atualizar o conteudo depois da extraçao
//  86. protecao contra str vazia; não há conteudo para guardar
//  92. percorre ate encontrar EOF ou \n 
//  94. se for EOF; nao ha mais nada, entao liberta e retorna
//
//  99. novo recebe o conteudo ja utilizado para ser libertado.
// 	 (strdup(avanca ate o char depois do \n) e copia a sobra) [a = posicao \n]
//
//  100. remin ja foi usado, nao ha nada; entao liberta ou mem leak.
// -----------------------------------------------------------------------------

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(reminder), reminder = NULL, NULL);
	reminder = read_until(fd, buffer, reminder);
	free(buffer);
	if (!reminder || *reminder == '\0')
	{
		if (reminder)
			free(reminder);
		reminder = NULL;
		return (NULL);
	}
	line = extr_line(reminder);
	if (!line)
		return (free(reminder), reminder = NULL, NULL);
	reminder = updt_reminder(reminder);
	return (line);
}
// --------------------------------------------------------------------------
// 117. variavel static, permanece entra chamadas, morre apenas quando o 
//		programa morre
//  121. fd invalido/errado, buffer_size invalido, ambos retornam null
//  126. chamada para ver EOF ou \n
//  127. verificaçao se "" ou null, tem que libertar os espacos ou mem leak
//
//  130. Se reminder for string vazia, não há conteúdo útil, liberta e retorna
//		 NULL
//
//  134. extrai a linha e retorna uma nova string com essa linha
//  135. Retorna nova string com o conteúdo restante
//  137. Retorna a linha extraida, pode incluir \n ou não, depende do conteúdo
// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
// <<<<<<<<<<<<<<<<<<<<<<<<  To create test.txt  >>>>>>>>>>>>>>>>>>>>>>>>>>> 
// --------------------------------------------------------------------------
// echo -e "Hello\nNow line 2\nNow line 3\nNo new line at end" > test.txt
// -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c
// --------------------------------------------------------------------------

int main(void)
{
	int		fd;
	char	*line;
	int i = 1;

	fd = open("teste.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Recebi na linha [%d]: %s", i++, line);
		free(line);
	}
	close(fd);
	return (0);
}