void
viewto(const Arg *arg) {
    if (arg->i == +1) {
	if(__builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1
		&& selmon->tagset[selmon->seltags] > 1) {
	    selmon->seltags ^= 1; /* toggle sel tagset */
	    selmon->tagset[selmon->seltags] = selmon->tagset[selmon->seltags ^ 1] >> 1;
	    focus(NULL);
	    arrange(selmon);

	}
	/* else{ */
	/*     Arg *arg */
	/*     view(arg->ui = 1 << 0); */
	/* } */
	return;
    }
    if(__builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1
	    && selmon->tagset[selmon->seltags] & (TAGMASK >> 1)) {
	selmon->seltags ^= 1; /* toggle sel tagset */
	selmon->tagset[selmon->seltags] = selmon->tagset[selmon->seltags ^ 1] << 1;
	focus(NULL);
	arrange(selmon);
    }
}
