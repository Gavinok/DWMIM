void
max(const Arg *arg)
{
	if (!selmon->sel)
	return;

	if (!selmon->sel->isfullscreen)
	{
		setfullscreen(selmon->sel, 2);
	}
	else if (selmon->sel->isfullscreen)
		setfullscreen(selmon->sel, 0);
}
