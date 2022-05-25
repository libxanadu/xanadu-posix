#include <xanadu-posix/socket.h>
#include <xanadu-posix/string.h>
#include <xanadu-posix/system.h>
#if defined(XANADU_SYSTEM_WINDOWS)
#include <mstcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif



// posix : gethostbyname
_XPOSIXAPI_ struct hostent* __xcall__ x_socket_get_host_by_name(const char* _Name)
{
	return gethostbyname(_Name);
}

// posix : socket
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_open(int _Family, int _Type, int _Protocol)
{
	return socket(_Family, _Type, _Protocol);
}

// posix : connect
_XPOSIXAPI_ int __xcall__ x_socket_connect(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length)
{
	return connect(_Socket, _Address, _Length);
}

// posix : accept
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_accept(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length)
{
	return accept(_Socket, _Address, _Length);
}

// posix : bind
_XPOSIXAPI_ int __xcall__ x_socket_bind(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length)
{
	return bind(_Socket, _Address, _Length);
}

// posix : close
_XPOSIXAPI_ int __xcall__ x_socket_close(x_socket_t _Socket)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return closesocket(_Socket);
#else
	return close(_Socket);
#endif
}

// posix : getpeername
_XPOSIXAPI_ int __xcall__ x_socket_get_peer_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length)
{
	return getpeername(_Socket, _Address, _Length);
}

// posix : getsockname
_XPOSIXAPI_ int __xcall__ x_socket_get_sock_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length)
{
	return getsockname(_Socket, _Address, _Length);
}

// posix : getsockopt
_XPOSIXAPI_ int __xcall__ x_socket_get_opt(x_socket_t _Socket, int _Level, int _OptName, void* _OptValue, socklen_t* _OptLength)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return getsockopt(_Socket, _Level, _OptName, (char*)_OptValue, _OptLength);
#else
	return getsockopt(_Socket, _Level, _OptName, _OptValue, _OptLength);
#endif
}

// posix : setsockopt
_XPOSIXAPI_ int __xcall__ x_socket_set_opt(x_socket_t _Socket, int _Level, int _OptName, const void* _OptValue, socklen_t _OptLength)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return setsockopt(_Socket, _Level, _OptName, (const char*)_OptValue, _OptLength);
#else
	return setsockopt(_Socket, _Level, _OptName, _OptValue, _OptLength);
#endif
}

// posix : inet_addr
_XPOSIXAPI_ struct in_addr __xcall__ x_socket_inet_addr(const char* _CP)
{
	struct in_addr		vAddress;
	vAddress.s_addr = inet_addr(_CP);
	return vAddress;
}

// posix : inet_ntoa
_XPOSIXAPI_ char* __xcall__ x_socket_inet_ntoa(struct in_addr _IN)
{
	return inet_ntoa(_IN);
}

// posix : listen
_XPOSIXAPI_ int __xcall__ x_socket_listen(x_socket_t _Socket, int _Backlog)
{
	return listen(_Socket, _Backlog);
}

// posix : recv
_XPOSIXAPI_ int __xcall__ x_socket_recv(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return recv(_Socket, (char*)_Buffer, _Length, _Flags);
#else
	return recv(_Socket, _Buffer, _Length, _Flags);
#endif
}

// posix : recvfrom
_XPOSIXAPI_ int __xcall__ x_socket_recvfrom(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags, struct sockaddr* _From, socklen_t* _FromLen)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return recvfrom(_Socket, (char*)_Buffer, _Length, _Flags, _From, _FromLen);
#else
	return recvfrom(_Socket, _Buffer, _Length, _Flags, _From, _FromLen);
#endif
}

// posix : send
_XPOSIXAPI_ int __xcall__ x_socket_send(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return send(_Socket, (const char*)_Buffer, _Length, _Flags);
#else
	return send(_Socket, _Buffer, _Length, _Flags);
#endif
}

// posix : sendto
_XPOSIXAPI_ int __xcall__ x_socket_sendto(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags, const struct sockaddr* _To, socklen_t _ToLen)
{
#if defined(XANADU_SYSTEM_WINDOWS)
	return sendto(_Socket, (const char*)_Buffer, _Length, _Flags, _To, _ToLen);
#else
	return sendto(_Socket, _Buffer, _Length, _Flags, _To, _ToLen);
#endif
}

// posix : shutdown
_XPOSIXAPI_ int __xcall__ x_socket_shutdown(x_socket_t _Socket, int _Now)
{
	return shutdown(_Socket, _Now);
}

// posix : select
_XPOSIXAPI_ int __xcall__ x_socket_select(int _Fds, fd_set* _ReadFds, fd_set* _WriteFds, fd_set* _ExceptFds, struct timeval* _Timeout)
{
	return select(_Fds, _ReadFds, _WriteFds, _ExceptFds, _Timeout);
}

// posix : poll
_XPOSIXAPI_ int __xcall__ x_socket_poll(struct pollfd _Fds[], nfds_t _Count, int _Timeout)
{
#if defined(X_CMAKE_HAVE_POLL)
	return poll(_Fds, _Count, _Timeout);
#else
#if defined(XANADU_SYSTEM_WINDOWS)
	return WSAPoll(_Fds, _Count, _Timeout);
#else
	return poll(_Fds, _Count, _Timeout);
#endif
#endif
}

// posix : ppoll
_XPOSIXAPI_ int __xcall__ x_socket_ppoll(struct pollfd* _Fds, nfds_t _Count, const struct timespec* _Timeout, const sigset_t* _SigMask)
{
#if defined(X_CMAKE_HAVE_PPOLL)
	return ppoll(_Fds, _Count, _Timeout, _SigMask);
#else
#if defined(X_CMAKE_HAVE_SIGPROCMASK)
	int		vReady = 0;
	sigset_t	vOrigMask;
	int		vMillisecond = (int)((_Timeout->tv_sec * 1000) + (_Timeout->tv_nsec / 1000000));

	sigprocmask(SIG_SETMASK, _SigMask, &vOrigMask);
	vReady = x_socket_poll(_Fds, _Count, vMillisecond);
	sigprocmask(SIG_SETMASK, &vOrigMask, NULL);

	return vReady;
#else
	XANADU_UNUSED(_SigMask);

	int		vReady = 0;
	int		vMillisecond = (int)((_Timeout->tv_sec * 1000) + (_Timeout->tv_nsec / 1000000));

	vReady = x_socket_poll(_Fds, _Count, vMillisecond);

	return vReady;
#endif
#endif
}



// Check whether the socket is readable, Readable returns 1, unreadable returns 0, and exception returns -1.
_XPOSIXAPI_ int __xcall__ x_socket_is_readable(x_socket_t _Socket, unsigned int _Timeout)
{
	fd_set		vFDS_Read;
	fd_set		vFDS_Except;
	struct timeval	vTimeout;
	vTimeout.tv_sec = (long)(_Timeout / 1000);
	vTimeout.tv_usec = (long) ((_Timeout - (vTimeout.tv_sec * 1000)) * 1000);

	FD_ZERO(&vFDS_Read);
	FD_ZERO(&vFDS_Except);
	FD_SET(_Socket, &vFDS_Read);
	FD_SET(_Socket, &vFDS_Except);

	int		vSelect = select((int)_Socket + 1, &vFDS_Read, NULL, &vFDS_Except, &vTimeout);
	if(vSelect > 0)
	{
		if(FD_ISSET(_Socket, &vFDS_Read))
		{
			return 1;
		}
		else if(FD_ISSET(_Socket, &vFDS_Except))
		{
			return -1;
		}
	}
	return 0;
}

// Check whether the socket is writable, Writable returns 1, unwritable returns 0, and exception returns -1.
_XPOSIXAPI_ int __xcall__ x_socket_is_writable(x_socket_t _Socket, unsigned int _Timeout)
{
	fd_set		vFDS_Write;
	fd_set		vFDS_Except;
	struct timeval	vTimeout;
	vTimeout.tv_sec = (long)(_Timeout / 1000);
	vTimeout.tv_usec = (long) ((_Timeout - (vTimeout.tv_sec * 1000)) * 1000);

	FD_ZERO(&vFDS_Write);
	FD_ZERO(&vFDS_Except);
	FD_SET(_Socket, &vFDS_Write);
	FD_SET(_Socket, &vFDS_Except);

	int		vSelect = select((int)_Socket + 1, NULL, &vFDS_Write, &vFDS_Except, &vTimeout);
	if(vSelect > 0)
	{
		if(FD_ISSET(_Socket, &vFDS_Write))
		{
			return 1;
		}
		else if(FD_ISSET(_Socket, &vFDS_Except))
		{
			return -1;
		}
	}
	return 0;
}

// Check the socket state. At least one value must be passed in for the three states
_XPOSIXAPI_ bool __xcall__ x_socket_select_status(x_socket_t _Socket, bool* _Readable, bool* _Writable, bool* _Except, unsigned int _Timeout)
{
	fd_set		vFDS_Read;
	fd_set		vFDS_Write;
	fd_set		vFDS_Except;
	struct timeval	vTimeout;
	vTimeout.tv_sec = (long)(_Timeout / 1000);
	vTimeout.tv_usec = (long) ((_Timeout - (vTimeout.tv_sec * 1000)) * 1000);

	if(_Readable)
	{
		FD_ZERO(&vFDS_Read);
		FD_SET(_Socket, &vFDS_Read);
	}
	if(_Writable)
	{
		FD_ZERO(&vFDS_Write);
		FD_SET(_Socket, &vFDS_Write);
	}
	if(_Except)
	{
		FD_ZERO(&vFDS_Except);
		FD_SET(_Socket, &vFDS_Except);
	}

	bool		vFound = false;
	int		vSelect = select((int)_Socket + 1, _Readable ? &vFDS_Read : NULL, _Writable ? &vFDS_Write : NULL, _Except ? &vFDS_Except : NULL, &vTimeout);
	if(vSelect > 0)
	{
		if(_Readable)
		{
			*_Readable = FD_ISSET(_Socket, &vFDS_Read);
			vFound = true;
		}
		if(_Writable)
		{
			*_Writable = FD_ISSET(_Socket, &vFDS_Write);
			vFound = true;
		}
		if(_Except)
		{
			*_Except = FD_ISSET(_Socket, &vFDS_Except);
			vFound = true;
		}
		return vFound;
	}
	return false;
}



// socket : Set socket heartbeat
_XPOSIXAPI_ int __xcall__ x_socket_set_keepalive(x_socket_t _Socket, bool _KeepAlive, int _KeepIdle, int _KeepInterval, int _KeepCount)
{
#if defined(XANADU_COMPILER_MSVC)
	XANADU_UNUSED(_KeepCount);

	DWORD				vBytesReturn = 0;
	struct tcp_keepalive		vKA_Settings = {0};
	struct tcp_keepalive		vKA_Returned = {0};
	vKA_Settings.onoff = _KeepAlive ? 1 : 0;		// 是否开启KEEPALIVE
	vKA_Settings.keepalivetime = _KeepIdle;			// 多长毫秒时间触发Keepalive报文的发送
	vKA_Settings.keepaliveinterval = _KeepInterval;		// 多长毫秒时间没有回应触发下一次发送
	return WSAIoctl(_Socket, SIO_KEEPALIVE_VALS, &vKA_Settings, sizeof(struct tcp_keepalive), &vKA_Returned, sizeof(struct tcp_keepalive), &vBytesReturn, NULL, NULL);
#elif defined(XANADU_COMPILER_LINUX)
	int		keepalive = _KeepAlive ? 1 : 0;		// 是否开启keepalive属性
	int		keepidle = _KeepIdle / 1000;		// 如该连接在 N 秒内没有任何数据往来,则进行探测
	int		keepinterval = _KeepInterval / 1000;	// 探测时发包的时间间隔为 N 秒
	int		keepcount = _KeepCount;			// 探测尝试的次数。如果第1次探测包就收到响应了,则后 N - 1 次的不再发。
	x_socket_set_opt(_Socket, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));
	x_socket_set_opt(_Socket, SOL_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle));
	x_socket_set_opt(_Socket, SOL_TCP, TCP_KEEPINTVL, &keepinterval, sizeof(keepinterval));
	x_socket_set_opt(_Socket, SOL_TCP, TCP_KEEPCNT, &keepcount, sizeof(keepcount));
	return 0;
#else
	XANADU_UNUSED(_Socket);
	XANADU_UNUSED(_KeepAlive);
	XANADU_UNUSED(_KeepIdle);
	XANADU_UNUSED(_KeepInterval);
	XANADU_UNUSED(_KeepCount);
	return 0;
#endif
}



// Translate IP address from fabric
_XPOSIXAPI_ char* __xcall__ x_socket_address_to_string(const struct sockaddr* _Address)
{
	if(_Address->sa_family == AF_INET)
	{
		const struct sockaddr_in*	vIPv4 = (const struct sockaddr_in*)_Address;
#if defined(XANADU_SYSTEM_WINDOWS)
		const char*			vAddress = inet_ntoa(vIPv4->sin_addr);
#else
		char				vAddress[1024] = {0};
		inet_ntop(AF_INET, vIPv4, vAddress, 1024);
#endif
		return x_posix_strdup(vAddress);
	}
	return x_posix_strdup("");
}



// Transfer data between two sockets
_XPOSIXAPI_ int __xcall__ x_socket_transfer(x_socket_t _Socket1, x_socket_t _Socket2)
{
	if(_Socket1 == INVALID_SOCKET || _Socket2 == INVALID_SOCKET)
	{
		return EINVAL;
	}

	int		vError = 0;
	char 		vBuffer[XANADU_SIZE_KB] = {0};
	int		vSocketMax = (int)(_Socket1 > _Socket2 ? _Socket1 : _Socket2);
	fd_set		vReadFds;
	fd_set 		vExceptFds;
	struct timeval	vTimeout;
	while(true)
	{
		FD_ZERO(&vReadFds);
		FD_SET(_Socket1, &vReadFds);
		FD_SET(_Socket2, &vReadFds);

		FD_ZERO(&vExceptFds);
		FD_SET(_Socket1, &vExceptFds);
		FD_SET(_Socket2, &vExceptFds);

		vTimeout.tv_sec = 1;
		vTimeout.tv_usec = 0;

		int		vSelect = x_socket_select(vSocketMax + 1, &vReadFds, NULL, &vExceptFds, &vTimeout);
		if(vSelect < 0)
		{
			// an error occurred
			vError = x_posix_errno();
			break;
		}
		else if(vSelect == 0)
		{
			// Socket query timed out
			continue;
		}
		else
		{
			// There are sockets to read
			if (FD_ISSET(_Socket1, &vReadFds))
			{
				int		vReadBytes = recv(_Socket1, vBuffer, XANADU_SIZE_KB, 0);
				if(vReadBytes < 0)
				{
					// Failed to receive
					vError = x_posix_errno();
					break;
				}
				else if(vReadBytes == 0)
				{
					// The peer socket is closed
					break;
				}
				int		vSent = 0;
				while (vSent < vReadBytes)
				{
					int		vSendBytes = send(_Socket2, vBuffer + vSent, vSent - vSent, 0);
					if (vSendBytes <= 0)
					{
						// Failed to send
						vError = x_posix_errno();
						break;
					}
					vSent += vSendBytes;
				}
			}
			if (FD_ISSET(_Socket2, &vReadFds))
			{
				int		vReadBytes = recv(_Socket2, vBuffer, XANADU_SIZE_KB, 0);
				if(vReadBytes < 0)
				{
					// Failed to receive
					vError = x_posix_errno();
					break;
				}
				else if(vReadBytes == 0)
				{
					// The peer socket is closed
					break;
				}
				int		vSent = 0;
				while (vSent < vReadBytes)
				{
					int		vSendBytes = send(_Socket1, vBuffer + vSent, vSent - vSent, 0);
					if (vSendBytes <= 0)
					{
						// Failed to send
						vError = x_posix_errno();
						break;
					}
					vSent += vSendBytes;
				}
			}
		}
	}

	return vError;
}
