#ifdef USE_EPOLL
static listensocket_t * listensocket_container_accept__inner_epoll(listensocket_container_t *self, int timeout)
{
    struct epoll_event ufds[self->sock_len];
    listensocket_t *socks[self->sock_len];
    size_t i, found;
    int ok;
    int ret;

    for (i = 0, found = 0; i < self->sock_len; i++) {

        ok = self->sockref[i];
        if (ok && listensocket__epoll_fill(self->sock[i], &(ufds[found])) == -1) {
            //printf("Can not poll on closed socket.");
            ok = 0;
        }

        if (ok) {
            socks[found] = self->sock[i];
            found++;
        }
    }

    if (!found) {
        ICECAST_LOG_ERROR("No sockets found to poll on.");
        return NULL;
    }
    ret=epoll_wait(epollinstance, ufds,found, timeout);

    if (ret == -1) {
        return NULL;
    }
    if (ret == 0) { return NULL; }

    for (i = 0; i < found; i++) {
        if (ufds[i].events & EPOLLIN) {
        return socks[i];
        }


        if ((ufds[i].events & (EPOLLERR) )) {
        //listensocket_unrefsock(socks[i]);
        continue;
        }
     }
    return NULL;

}
