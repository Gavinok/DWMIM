// needs to be simplified to one function
// add support for snapping 
// later implemet using .v int[] instead of .i
void
mvx(const Arg *arg) 
{
	Client *c;
	int axis = 1;
	int delta = arg->i;
	// Monitor *m;
	if (!(c = selmon->sel))
		return;
	if (c->isfullscreen) /* no support moving fullscreen */
		return;
	if(!c->isfloating)
		togglefloating(0);

	// 0=x // 1=y 
	if (axis) {
		// resize(c, (c->x), (c->y * c->bw), c->w, c->h, 0);
		XMoveWindow(dpy, c->win, (c->x - delta), c->y);
		c->oldx = c->x;
		c->x = c->oldx - delta;
		XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, (c->w/2),(c->h/2));
	}
	else{
		// resize(c, (c->x), (c->y * c->bw), c->w, c->h, 0);
		XMoveWindow(dpy, c->win, c->x, (c->y - delta));
		c->oldy = c->y;
		c->y = c->oldy - delta;
		XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, (c->w/2),(c->h/2));
	}
}

void
mvy(const Arg *arg) 
{
	Client *c;
	int axis = 0;
	int delta = arg->i;
	// Monitor *m;
	if (!(c = selmon->sel))
		return;
	if (c->isfullscreen) /* no support moving fullscreen */
		return;
	if(!c->isfloating)
		togglefloating(0);

	// 0=x // 1=y 
	if (axis) {
		// resize(c, (c->x), (c->y * c->bw), c->w, c->h, 0);
		XMoveWindow(dpy, c->win, (c->x - delta), c->y);
		c->oldx = c->x;
		c->x = c->oldx - delta;
		XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, (c->w/2),(c->h/2));
	}
	else{
		// resize(c, (c->x), (c->y * c->bw), c->w, c->h, 0);
		XMoveWindow(dpy, c->win, c->x, (c->y - delta));
		c->oldy = c->y;
		c->y = c->oldy - delta;
		XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, (c->w/2),(c->h/2));
	}
}
// movekeyx(const Arg *arg) 
// {
// 	movekey(c, 0, arg->i);
// }
// movekeyy(const Arg *arg) 
// {
// 	movekey(c, 1, arg->i);
// }
