#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	const char	ch = c;

	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
	{
		subs = malloc(1);
		*subs = 0;
		return (subs);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	subs = malloc(len + 1);
	if (!subs)
		return (NULL);
	ft_strlcpy(subs, &s[start], len + 1);
	return (subs);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	size_dest;

	if (!dest && !size)
		return (ft_strlen(src));
	size_dest = ft_strlen(dest);
	i = size_dest;
	if (size_dest >= size)
		return (ft_strlen(src) + size);
	while (i < size - 1 && src[i - size_dest])
	{
		dest[i] = src[i - size_dest];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src) + size_dest);
}
