#ifndef			_XANADU_POSIX_SOCKET_H_
#define			_XANADU_POSIX_SOCKET_H_

#include <xanadu-posix/header.h>
#if !defined(XANADU_SYSTEM_WINDOWS)
#include <netinet/in.h>
#include <poll.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif


// 套接字类型定义
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				SOCKET				x_socket_t;
#else
typedef				int 				x_socket_t;
#endif
#if defined(XANADU_SYSTEM_WINDOWS)
typedef				unsigned long int		nfds_t;
#if !defined(_NSIG_WORDS)
#define				_NSIG_WORDS			2
#endif
typedef struct {
	unsigned long		sig[_NSIG_WORDS];
}sigset_t;
#else
#define INVALID_SOCKET		((x_socket_t)(-1))
#define SOCKET_ERROR		(-1)
#endif
#define XANADU_INVALID_SOCKET	((x_socket_t)(-1))
#define XANADU_SOCKET_ERROR	(-1)


// posix : gethostbyname
_XPOSIXAPI_ struct hostent* __xcall__ x_socket_get_host_by_name(const char* _Name);

// posix : socket
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_open(int _Family, int _Type, int _Protocol);

// posix : connect
_XPOSIXAPI_ int __xcall__ x_socket_connect(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length);

// posix : accept
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_accept(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length);

// posix : bind
_XPOSIXAPI_ int __xcall__ x_socket_bind(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length);

// posix : close
_XPOSIXAPI_ int __xcall__ x_socket_close(x_socket_t _Socket);

// posix : getpeername
_XPOSIXAPI_ int __xcall__ x_socket_get_peer_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length);

// posix : getsockname
_XPOSIXAPI_ int __xcall__ x_socket_get_sock_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length);

// posix : getsockopt
_XPOSIXAPI_ int __xcall__ x_socket_get_opt(x_socket_t _Socket, int _Level, int _OptName, void* _OptValue, socklen_t* _OptLength);

// posix : setsockopt
_XPOSIXAPI_ int __xcall__ x_socket_set_opt(x_socket_t _Socket, int level, int _OptName, const void* _OptValue, socklen_t _OptLength);

// posix : inet_addr
_XPOSIXAPI_ struct in_addr __xcall__ x_socket_inet_addr(const char* _CP);

// posix : inet_ntoa
_XPOSIXAPI_ char* __xcall__ x_socket_inet_ntoa(struct in_addr _IN);

// posix : listen
_XPOSIXAPI_ int __xcall__ x_socket_listen(x_socket_t _Socket, int _Backlog);

// posix : recv
_XPOSIXAPI_ int __xcall__ x_socket_recv(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags);

// posix : recvfrom
_XPOSIXAPI_ int __xcall__ x_socket_recvfrom(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags, struct sockaddr* _From, socklen_t* _FromLen);

// posix : send
_XPOSIXAPI_ int __xcall__ x_socket_send(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags);

// posix : sendto
_XPOSIXAPI_ int __xcall__ x_socket_sendto(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags, const struct sockaddr* _To, socklen_t _ToLen);

// posix : shutdown
_XPOSIXAPI_ int __xcall__ x_socket_shutdown(x_socket_t _Socket, int _Now);

// posix : select
_XPOSIXAPI_ int __xcall__ x_socket_select(int _Fds, fd_set* _ReadFds, fd_set* _WriteFds, fd_set* _ExceptFds, struct timeval* _Timeout);

// posix : poll
_XPOSIXAPI_ int __xcall__ x_socket_poll(struct pollfd _Fds[], nfds_t _Count, int _Timeout);

// posix : ppoll
_XPOSIXAPI_ int __xcall__ x_socket_ppoll(struct pollfd* _Fds, nfds_t _Count, const struct timespec* _Timeout, const sigset_t* _SigMask);



// Check whether the socket is readable, Readable returns 1, unreadable returns 0, and exception returns -1.
_XPOSIXAPI_ int __xcall__ x_socket_is_readable(x_socket_t _Socket, unsigned int _Timeout);

// Check whether the socket is writable, Writable returns 1, unwritable returns 0, and exception returns -1.
_XPOSIXAPI_ int __xcall__ x_socket_is_writable(x_socket_t _Socket, unsigned int _Timeout);

// Check the socket state. At least one value must be passed in for the three states
_XPOSIXAPI_ bool __xcall__ x_socket_select_status(x_socket_t _Socket, bool* _Readable, bool* _Writable, bool* _Except, unsigned int _Timeout);



// socket : 设置套接字心跳属性
_XPOSIXAPI_ int __xcall__ x_socket_set_keepalive(x_socket_t _Socket, bool _KeepAlive, int _KeepIdle, int _KeepInterval, int _KeepCount);



// Translate IP address from fabric
_XPOSIXAPI_ char* __xcall__ x_socket_address_to_string(const struct sockaddr* _Address);


#if defined(__cplusplus)
}
#endif


#endif
