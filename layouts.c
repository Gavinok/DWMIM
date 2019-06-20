#ifdef ENABLEUSLESSGAPS

//for compatibility
#define OGWIDTH(X)                ((X)->w + 2 * (X)->bw)
#define OGHEIGHT(X)               ((X)->h + 2 * (X)->bw)

void
vanillaresizeclient(Client *c, int x, int y, int w, int h)
{
	XWindowChanges wc;

	c->oldx = c->x; c->x = wc.x = x;
	c->oldy = c->y; c->y = wc.y = y;
	c->oldw = c->w; c->w = wc.width = w;
	c->oldh = c->h; c->h = wc.height = h;
	wc.border_width = c->bw;
	XConfigureWindow(dpy, c->win, CWX|CWY|CWWidth|CWHeight|CWBorderWidth, &wc);
	configure(c);
	XSync(dpy, False);
}

void
vanillaresize(Client *c, int x, int y, int w, int h, int interact)
{
	if (applysizehints(c, &x, &y, &w, &h, interact))
		vanillaresizeclient(c, x, y, w, h);
}

void
bstack(Monitor *m)
{
	unsigned int i, n, w, mh, mx, tx;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if(n == 1){
		c = nexttiled(m->clients);
		vanillaresize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	if (n > m->nmaster)
		mh = m->nmaster ? m->wh * m->mfact : gappx;
	else
		mh = m->wh;
	for (i = 0, mx = tx = gappx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i) - gappx;
			vanillaresize(c, m->wx + mx, m->wy + gappx, w - (2*c->bw), mh - 2*(c->bw + gappx), 0);
			mx += OGWIDTH(c) + gappx;
		} else {
			w = (m->ww - tx) / (n - i) - gappx;
			vanillaresize(c, m->wx + tx, m->wy + mh, w - (2*c->bw), m->wh - mh - 2*(c->bw) - gappx, 0);
			tx += OGWIDTH(c) + gappx;
		}
}
#else /* ENABLEUSLESSGAPS */
/* customized for better horizontal gaps*/
static void
bstack(Monitor *m) {
	int w, h, mh, mx, tx, ty, tw;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if (n > m->nmaster) {
		mh = m->nmaster ? m->mfact * m->wh : 0;
		tw = m->ww / (n - m->nmaster);
		ty = m->wy + mh;
	} else {
		mh = m->wh;
		tw = m->ww;
		ty = m->wy;
	}
	for (i = mx = 0, tx = m->wx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - (2 * c->bw), mh - (2 * c->bw), 0);
			mx += WIDTH(c);
		} else {
			h = m->wh - mh;
			resize(c, tx, ty, tw - (2 * c->bw), h - (2 * c->bw), 0);
			if (tw != m->ww)
				tx += WIDTH(c);
		}
	}
}
#endif /* ifdef ENABLEUSLESSGAPS */

void
centeredmaster(Monitor *m)
{
	unsigned int i, n, h, mw, mx, my, oty, ety, tw;
	Client *c;

	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	/* initialize areas */
	mw = m->ww;
	mx = 0;
	my = 0;
	tw = mw;

	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		mw = m->nmaster ? m->ww * m->mfact : 0;
		tw = m->ww - mw;

		if (n - m->nmaster > 1) {
			/* only one client */
			mx = (m->ww - mw) / 2;
			tw = (m->ww - mw) / 2;
		}
	}

	oty = 0;
	ety = 0;
	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked vertically, in the center
		 * of the screen */
		h = (m->wh - my) / (MIN(n, m->nmaster) - i);
		resize(c, m->wx + mx, m->wy + my, mw - (2*c->bw),
		       h - (2*c->bw), 0);
		my += HEIGHT(c);
	} else {
		/* stack clients are stacked vertically */
		if ((i - m->nmaster) % 2 ) {
			h = (m->wh - ety) / ( (1 + n - i) / 2);
			resize(c, m->wx, m->wy + ety, tw - (2*c->bw),
			       h - (2*c->bw), 0);
			ety += HEIGHT(c);
		} else {
			h = (m->wh - oty) / ((1 + n - i) / 2);
			resize(c, m->wx + mx + mw, m->wy + oty,
			       tw - (2*c->bw), h - (2*c->bw), 0);
			oty += HEIGHT(c);
		}
	}
}

void
vanitytile(Monitor *m)
{

	static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
	unsigned int i, n, h, r, oe = 1, mw, my, ty;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	if (smartgaps == n) {
		oe = 0; // outer gaps disabled
	}

	if (n > m->nmaster)
		mw = m->nmaster ? (m->ww + gappxi) * m->mfact : 0;
	else
		mw = m->ww - 2*gappxo*oe + gappxi;
	for (i = 0, my = ty = gappxo*oe, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			r = MIN(n, m->nmaster) - i;
			h = (m->wh - my - gappxo*oe - gappxi * (r - 1)) / r;
			vanillaresize(c, m->wx + gappxo*oe, m->wy + my, mw - (2*c->bw) - gappxi, h - (2*c->bw), 0);
			/* my += HEIGHT(c) + gappx; */
			my += OGHEIGHT(c) + gappxi;
		} else {
			r = n - i;
			h = (m->wh - ty - gappxo*oe - gappxi * (r - 1)) / r;
			vanillaresize(c, m->wx + mw + gappxo*oe, m->wy + ty, m->ww - mw - (2*c->bw) - 2*gappxo*oe, h - (2*c->bw), 0);
			ty += OGHEIGHT(c) + gappxi;
		}
}

