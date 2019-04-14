
// 1=x // 2=y 
// +1 would meen move left
// -2 would meen move down
void
mv(const Arg *arg) 
{
	Client *c;
	int axis = arg->i;
	if (!(c = selmon->sel))
		return;
	if (c->isfullscreen || !c->isfloating) /* no support moving fullscreen */
		return;
	if ((axis == 1) || (axis == -1)) {
		int delta = (deltamv * axis);
		XMoveWindow(dpy, c->win, (c->x - delta), c->y);
		c->oldx = c->x;
		c->x = c->oldx - delta;
		XWarpPointer(dpy, None, c->win, 
				0, 0, 0, 0, (c->w/2),(c->h/2));
	}
	else if (axis == 2 || axis == -2){
		int delta = (deltamv * (axis/2));
		XMoveWindow(dpy, c->win, c->x, (c->y - delta));
		c->oldy = c->y;
		c->y = c->oldy - delta;
		XWarpPointer(dpy, None, c->win, 
				0, 0, 0, 0, (c->w/2),(c->h/2));
	}
}

// TODO
// needs to be simplified to one function
// add support for snapping 
