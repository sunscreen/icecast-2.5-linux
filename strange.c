   ret=epoll_pwait(epollinstance, ufds,found, timeout, &sigset);
    if (ret == -1) {
        int ep_err = errno;
        if (ep_err == EINTR) {
        printf("interrupted\n");
        }

        printf("epoll error: %d\n",ep_err);
        __call_sockcount_cb(self);

        return NULL;
    }
    if (ret == 0) { return NULL; }

    for (i = 0; i < found; i++) {

        if (ufds[i].events & (EPOLLERR)) {
        __call_sockcount_cb(self);
        return NULL;
        }

        if (ufds[i].events & (EPOLLHUP)) {
        __call_sockcount_cb(self);
        return NULL;
        }

        if (ufds[i].events & EPOLLIN) {
        return socks[i];
        }


     }
    return NULL;
