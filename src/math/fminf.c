#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct ff_f t[] = {
#include "sanity/fminf.h"

};

int main(void)
{
	float y;
	float d;
	int e, i, err = 0;
	struct ff_f *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;
		setupfenv(p->r);
		y = fminf(p->x, p->x2);
		e = getexcept();
		if (!checkexcept(e, p->e, p->r)) {
			printf("%s fminf(%a,%a)==%a except: want %s", rstr(p->r), p->x, p->x2, p->y, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		d = ulperrf(y, p->y, p->dy);
		if (!checkulp(d, p->r)) {
			printf("%s fminf(%a,%a) want %a got %a ulperr %.3f = %a + %a\n",
				rstr(p->r), p->x, p->x2, p->y, y, d, d-p->dy, p->dy);
			err++;
		}
	}
	return !!err;
}