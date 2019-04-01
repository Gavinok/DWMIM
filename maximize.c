void
max(const Arg *arg)
{
	if (!selmon->sel)
		return;
	if (!selmon->sel->isfullscreen){
		if(selmon->showbar){
			setfullscreen(selmon->sel, 2);
		}else
			setfullscreen(selmon->sel, 1);
	}
	else
		setfullscreen(selmon->sel, 0);
}
