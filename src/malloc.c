#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef malloc
#undef malloc
#undef realloc
#include <errno.h>
#include <stdlib.h>

void *rpl_malloc(size_t n)
{
	void *result;
	if (n == 0)
		n = 1;
	result = malloc(n);
	return result;
}
void *rpl_realloc(void *p, size_t n)
{
	void *result;
	if (n == 0)
		n = 1;
	if (p == NULL)
		result = malloc(n);
	else
		result = realloc(p, n);
	return result;
}
#endif
