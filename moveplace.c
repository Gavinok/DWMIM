/* From: Christopher Drelich <cd@cdrakka.com> */
/* Date: Thu, 24 May 2018 21:12:22 -0400 */
/* Subject: [PATCH] Makes win floating,  */
/* 		 and moves it into one of 9 screen positions. */
enum { WIN_NW, WIN_N, WIN_NE, WIN_W, WIN_C, WIN_E, WIN_SW, WIN_S, WIN_SE }; /* coordinates for moveplace */

void
moveplace(const Arg *arg)
{
	Client *c;
	int nh, nw, nx, ny;
	c = selmon->sel;
	if (!c || (arg->ui >= 9))
		 return;
	if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
		togglefloating(NULL);
	nh = (selmon->wh / 3) - (c->bw * 2);
	nw = (selmon->ww / 3) - (c->bw * 2);
	nx = (arg->ui % 3) -1;
	ny = (arg->ui / 3) -1;
	if (nx < 0)
		nx = selmon->wx;
	else if(nx > 0)
		nx = selmon->wx + selmon->ww - nw - c->bw*2;
	else
		nx = selmon->wx + selmon->ww/2 - nw/2 - c->bw;
	if (ny <0)
		ny = selmon->wy;
	else if(ny > 0)
		ny = selmon->wy + selmon->wh - nh - c->bw*2;
	else
		ny = selmon->wy + selmon->wh/2 - nh/2 - c->bw;
	resize(c, nx, ny, nw, nh, True);
	XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, nw/2, nh/2);
}

