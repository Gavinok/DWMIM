void
forcekill(const Arg *arg)
{
	Client *c;
	if (!(c = selmon->sel))
		return;
        c->nokill = False;
        killclient(0);
}
void
nokill(const Arg *arg)
{
	Client *c;
	if (!(c = selmon->sel))
		return;
	if (c->nokill){
		c->nokill = False;
	}
	else{
		c->nokill = True;		
	}
}
