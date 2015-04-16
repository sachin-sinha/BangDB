/*
 * 	basehdr.h
 *
 *  Author: Sachin Sinha
 *  Libbangdb library
 *
 *  Copyright (C) 2015 IQLECT All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BASEHDR_H_
#define BASEHDR_H_

#ifndef _MAC_OS_COMPILE_
//#define _MAC_OS_COMPILE_
#endif

#ifndef _MS_OS_COMPILE_
//#define _MS_OS_COMPILE_
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif
//switch on for 64 bit, and off for 32 bit before compile
#ifndef _PLATFORM_BIT_64_
#define _PLATFORM_BIT_64_
#endif

#ifdef _MS_OS_COMPILE_
#include "pthread-win.h"
#else
/* switch this off for embedded bangdb */
#ifndef _BANGDB_SERVER_HDR_
//#define _BANGDB_SERVER_HDR_
#endif

/*  basically affects the return value in connection for put del update (0 vs lsn) */
#ifndef _RETURN_OFFSET_OPS_
#define _RETURN_OFFSET_OPS_
#endif
//switch on for doing the standalone server test for all bangdb test cases
//basically allows to create db, close db at server, also does not create db by default
#ifndef _BANGDB_ALL_TEST_SERVER_
#define _BANGDB_ALL_TEST_SERVER_
#endif

#ifndef _TEST_WIDE_CONNECTION_
#define _TEST_WIDE_CONNECTION_
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/termios.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>
#include <pthread.h>
#include <poll.h>
#include <sys/poll.h>
#include <grp.h>
#include "atomic.h"

#ifndef _MAC_OS_COMPILE_
#include <sys/sendfile.h>
//#include <stropts.h>
#include <sys/epoll.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <libkern/OSAtomic.h>
typedef long int loff_t;
#define MAP_ANONYMOUS MAP_ANON
typedef OSSpinLock pthread_spinlock_t;
#endif
#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/resource.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
#include <procfs.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <sys/sysinfo.h>
#endif

#else
#error "Cannot define getPeakRSS( ) or getCurrentRSS( ) for an unknown OS."
#endif
#endif

namespace bangdb
{

#ifdef _PLATFORM_BIT_64_
typedef u_int64_t 	ULONG_T;
typedef int64_t		LONG_T;
#else
typedef unsigned long long ULONG_T;
typedef long long LONG_T;
#endif
typedef u_int32_t	UINT_T;
typedef int32_t		INT_T;
typedef int16_t		SHORT_T;

#ifndef _MS_OS_COMPILE_
typedef off_t 		FILEOFF_T;
#else
typedef LONGLONG	FILEOFF_T;
#endif

typedef ULONG_T		LCOUNT_T;
typedef ULONG_T		BUFFER_T;
typedef UINT_T		DATLEN_T;
typedef INT_T		BLOCKNUM_T;
typedef	UINT_T		COUNT_T;

//Default file access permissions for new files.
#define FILE_MODE   		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

//Default permissions for new directories.
#define DIR_MODE    		(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

#define RWRWRW 				(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#define LOCKMODE 			(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)

#ifndef bangdb_max
#define bangdb_min(a,b)     		((a) < (b) ? (a) : (b))
#define bangdb_max(a,b)     		((a) > (b) ? (a) : (b))
#define bangdb_int_min_val			-2147483647
#define bangdb_int_max_val			2147483647
#ifndef _PLATFORM_BIT_64_
#define bangdb_long_min_val			-2147483648
#define bangdb_long_max_val			2147483647
#else
#define bangdb_long_min_val			-9223372036854775808
#define bangdb_long_max_val			9223372036854775807
#endif
#endif

typedef void   Sigfunc(int);   // for signal handlers

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *)-1)
#endif


//sets the file as non blocking
void setnonblocking(int fd);

//sets the file as blocking
void setblocking(int fd);

//clears the flags for the fd supplied
void     clr_fl(int fd, int flags);

//sets the flags for the fd supplied
void     set_fl(int fd, int flags);

//checks the exit status of a process
void     pr_exit(int status);

//checks the signal handler set for the process (current)
void     pr_mask(const char *str);

//sets the seignal handler for signal signo
Sigfunc *signal_intr(int signo, Sigfunc *func);

//sleeping for micro sec, for 1 millisec call sleep_us(1000);
void     sleep_us(unsigned long microsec);

//reading n bytes, handles the intterupt and reads unitl it reads n bytes, blocking call
ssize_t  readn(int, void *, size_t);

//read with sock time out
ssize_t readn_timeout(int fd, void *vptr, size_t n, int to_sec);

//writing n bytes, handle interrupt and writes until it writes n bytes, blocking call
ssize_t  writen(int, const void *, size_t);

//writev, handle interrupt and writes until it writes all arrays of bytes, blocking call
ssize_t writevn(int fd, struct iovec *iov, int iovcnt, int towrite);

ssize_t readmessage(int fd, char *buf, size_t minbyte, size_t maxbyte);

//helper function which is like htonl but works for u_int64_t
u_int64_t htonll(u_int64_t v);

//helper function which is like ntohl but works for u_int64_t
u_int64_t ntohll(u_int64_t v);

//prints the cpu time taken by a process for some execution
void 	 pr_cpu_time(void);

#ifndef _MS_OS_COMPILE_
int Epoll_ctl(int _epfd, int _op, int _fd, int _edit_type);

//takes file lock on fd, lock defined by type at a particular offet off_t
int     lock_reg(int fd, int cmd, int type, off_t, int, off_t);
#else
//takes file lock on fd, lock defined by type at a particular offet MS_off_t
int     lock_reg(int fd, int cmd, int type, MS_off_t, int, MS_off_t);
#endif

//following macro uses the lock_reg function for various kinds of locks on the file
#define read_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

#ifndef _MS_OS_COMPILE_
pid_t   lock_test(int, int, off_t, int, off_t);
#else
//tests if a region of a file is locked by a process or not and returns the pid for that process
pid_t   lock_test(int, int, MS_off_t, int, MS_off_t);
#endif
//macro which uses the lock_test for checking read and write lock
#define is_read_lockable(fd, offset, whence, len) \
            (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len) \
            (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

int Write_lock_file(int fd, off_t off, int whence, int len);

int Unlock_file(int fd, off_t off, int whence, int len);

//==for printing error msg to console==

//-------syscall error-----------//

void bangdb_init_log(const char* dbpath, const char* name, int log_mem_size, int log_type);

void bangdb_close_log();

void flush_app_log();

void bangdb_logger(const char *fmt, ...);

//Fatal error related to a system call, dump core, print message and terminate
void    err_dump(const char *, ...);

//Nonfatal error related to a system call, print msg and retrun
void    err_ret(const char *, ...);

void    err_ret_ts(const char *, ...);

//Fatal error related to a system call, print message and terminate
void    err_sys(const char *, ...);

//-------non syscall error-----------//

//Nonfatal error unrelated to a system call, print msg and retrun
void    err_msg(const char *, ...);

//Fatal error non related to a system call, print message and terminate
void    err_quit(const char *, ...);

//Fatal error non related to a system call, error code passed as explicit parameter, print message and terminate
void    err_exit(int, const char *, ...);

//==for syslog, logging msg to the syslog==

//Initializa syslog, if running as daemon
void    log_open(const char *, int, int);

//-------syscall error-----------//

//Nonfatal error related to a system call, log msg and retrun
void    log_ret(const char *, ...);

//Fatal error related to a system call, log message and terminate
void    log_sys(const char *, ...);

//-------non syscall error-----------//

//Nonfatal error unrelated to a system call, log msg and retrun
void    log_msg(const char *, ...);

//Fatal error non related to a system call, log message and terminate//
void    log_quit(const char *, ...);

//==parent/child comminication/notification==

void    TELL_WAIT(void);
void    TELL_PARENT(pid_t);
void    TELL_CHILD(pid_t);
void    WAIT_PARENT(void);
#ifndef _MS_OS_COMPILE_
void    WAIT_CHILD(void);
#endif

//var used in logerror.c
extern int log_to_stderr;

//append str2 to the end of str1 and return it
char* strappend(char *str1, char *str2);

//prints file status flag for given descriptor
void printflstfg(int filedes);

//pr_times is a function which is called for printing various times
void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);

//print local time
void print_local_time();

//current time in micro sec
LONG_T get_current_time_us();

//get the timestamp
LONG_T get_timestamp();

//tells if a file is stream or not, returns 1 if yes and 0 if no
int isastream(int fd);

#ifndef _MS_OS_COMPILE_
/* Reliable version of signal(), using POSIX sigaction(). */
Sigfunc *signal(int signo, Sigfunc *func);
#else
#endif


//better function to daemonize
int	 daemon_init(const char *pname, int facility);

//daemonize function that can be used if the server is called from inetd, which is a daemon itself
//use this if you want your server to be daemon and called from inetd
void daemon_inetd(const char *, int);

//==socket related functions=

//wrapper over getaddrinfo
struct addrinfo *host_serv(const char *, const char *, int, int);

//helper function used to connect to server
int tcp_connect(const char *host, const char *serv);

//connect with timeout
int tcp_connect_timeout(const char *host, const char *serv, int to_sec);

//sets the socket read time out
int set_socket_r_timeo(int sockfd, int to_sec);

//sets the socket write time out
int set_socket_w_timeo(int sockfd, int to_sec);

//helper function used to bind to server and listen
int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);

int Setsockoptabort(int sockfd);

//checks if daemon is already running
int isdrunning(const char *filepath);

//accepting incoming request for connection - by server
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

//num to presentable format for sockaddr
#ifndef _MS_OS_COMPILE_
char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char **portnum);

int Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *ip, int iplen, char *portnum, int portlen);

int Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *ip, int iplen, int *portnum);

int get_sockaddr(int family, char *ip, char *port, sockaddr_in *sa);

int get_sockaddr(int family, char *ip, int port, sockaddr_in *sa);

int Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);

#else
char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
#endif
/* socket related functions - end */

//returns fd else -1 on error, call this if just want to open file for write
//mode:
int creatw(char *pathname, mode_t mode);

//returns fd else -1 on error, call this if just want to open file for write and read
int creatrw(char *pathname, mode_t mode);

#ifdef _MS_OS_COMPILE_
//for MS
//int lseek(int fd, FILEOFF_T offt, int seekref);

long long atoll(char *str);

#define chdir(A)	_chdir(A)

#define chmod(A,B)	_chmod(A,B)

#define fdopen(A,B)	_fdopen(A,B)
//int chdir(const char* path);

void DisplayError(LPTSTR lpszFunction); 

//int fdatasync(int fd);

//int open(char* fname, int rw, int fmode);

//int close(int fd);

struct iovec
{
	void *iov_base;
	size_t iov_len;
};

int getline(char** line, int* len, FILE* fp);

FILEOFF_T readv(int fd, const struct iovec *iov, int iovcnt);

//int readv(int fd, const struct iovec *iov, int iovcnt, FILEOFF_T offt);

FILEOFF_T writev(int fd, const struct iovec *iov, int iovcnt);

//int writev(int fd, const struct iovec *iov, int iovcnt, FILEOFF_T offt);

//seek current offset in a file
MS_off_t lseek_cur(int fd);
#else
//seek current offset in a file
off_t lseek_cur(int fd);
#endif

//==pthread related helper functions==
/**** mutex ****/
//mutex init
void Pthread_mutex_init(pthread_mutex_t *mptr, const pthread_mutexattr_t *attr);

//init as shared
void Pthread_mutex_init_shared(pthread_mutex_t *mptr);

//init as private
void Pthread_mutex_init_private(pthread_mutex_t *mptr);

//init cond as shared
void Pthread_cond_init_shared(pthread_cond_t *cond);

//init cond as private
void Pthread_cond_init_private(pthread_cond_t *cond);

//attr init
void Pthread_attr_init(pthread_attr_t *attr);

//attr destroy
void Pthread_attr_destroy(pthread_attr_t *attr);

//detach thread
void Pthread_detach (pthread_t th);

//cancel thread
void Pthread_cancel(pthread_t th);

//set thread as detach or attach
void Pthread_attr_setdetachstate (pthread_attr_t *attr, int detachstate);

//cond init
void Pthread_cond_init(pthread_cond_t *cptr, pthread_condattr_t *attr);

//mutex destroy
void Pthread_mutex_destroy(pthread_mutex_t *mptr);

//cond destroy
void Pthread_cond_destroy(pthread_cond_t *cptr);

//lock mutex function
void Pthread_mutex_lock(pthread_mutex_t *mptr);

//try lock mutex function
int Pthread_mutex_trylock(pthread_mutex_t *mptr);

//unlock mutex
void Pthread_mutex_unlock(pthread_mutex_t *mptr);

//wait on cond
void Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);

//signal on cond
void Pthread_cond_signal(pthread_cond_t *cptr);

//broadcast obn cond
void Pthread_cond_broadcast(pthread_cond_t *cptr);

//init mutex attr
void Pthread_mutexattr_init(pthread_mutexattr_t *mattr);

//init cond attr
void Pthread_condattr_init(pthread_condattr_t *cattr);

//destroy mutexattr
void Pthread_mutexattr_destroy(pthread_mutexattr_t *mattr);

//destroy condattr
void Pthread_condattr_destroy(pthread_condattr_t *cattr);

//set the mutexattr shared
void Pthread_mutexattr_setpshared(pthread_mutexattr_t *mattr, int value);

//set the condattr share
void Pthread_condattr_setpshared(pthread_condattr_t *cattr, int value);

/**** pthread ****/
//pthread create
void Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*func)(void*), void *arg);

//pthread join
void Pthread_join(pthread_t tid, void **status);

//to store key, value on a thread data - following three examples
//to deal with thread specific data, called everytime thred specific data is used, onceptr ensures that init is called only once
void Pthread_once(pthread_once_t *onceptr, void (*init)(void));

//to deal with thread specific data, to create key, called only once for a given key
void Pthread_key_create(pthread_key_t *keyptr, void (*destructor)(void *value));

//to deal with thread specific data, set the value associated with the key
void Pthread_setspecific(pthread_key_t key, const void *value);

/**** rwlock ****/
//init rwlock
void Pthread_rwlock_init(pthread_rwlock_t *rwptr, const pthread_rwlockattr_t *rwattr);

//init rdlock as shared
void Pthread_rwlock_init_shared(pthread_rwlock_t *rwptr);

//init rdlock as private
void Pthread_rwlock_init_private(pthread_rwlock_t *rwptr);

//set the rwattr set shared
void Pthread_rwlockattr_setpshared(pthread_rwlockattr_t *mattr, int value);

//init attr
void Pthread_rwlockattr_init(pthread_rwlockattr_t *rwattr);

//destrroy rwlock
void Pthread_rwlock_destroy(pthread_rwlock_t *rwptr);

//destroy rwlockattr
void Pthread_rwlockattr_destroy(pthread_rwlockattr_t *rwattr);

//for read lock
void Pthread_rwlock_rdlock(pthread_rwlock_t *rwptr);

//for write lock
void Pthread_rwlock_wrlock(pthread_rwlock_t *rwptr);

//try read lock
int Pthread_rwlock_tryrdlock(pthread_rwlock_t *rwptr);

//try wr lock
int Pthread_rwlock_trywrlock(pthread_rwlock_t *rwptr);

//unlock rwlock
void Pthread_rwlock_unlock(pthread_rwlock_t *rwptr);

/**** for spinlock ****/
//init spinlock
void Pthread_spin_init(pthread_spinlock_t *lock, int pshared);

//destroy spinlock
void Pthread_spin_destroy(pthread_spinlock_t *lock);

//spinlock lock
void Pthread_spin_lock(pthread_spinlock_t *lock);

//spinlock unlock
void Pthread_spin_unlock(pthread_spinlock_t *lock);

//==some wrapper function for stdio=

//close the file
void Fclose(FILE *fp);

//open the file with fd and returns FILE*
FILE *Fdopen(int fd, const char *type);

//gets char* from stream
char * Fgets(char *ptr, int n, FILE *stream);

//opens a file filename and returns FILE*
FILE * Fopen(const char *filename, const char *mode);

//puts char* on stream
void Fputs(const char *ptr, FILE *stream);

#ifndef _MS_OS_COMPILE_
ssize_t Sendfile(int out_fd, int in_fd, off_t offset, size_t count);
#else
//send file, works only for send data from file to socket, not otherwise
ssize_t Sendfile(int out_fd, int in_fd, MS_off_t offset, size_t count);
#endif
//the system call which avoids extra copy of buffer from user space to kernel space
size_t Splice(int fdin, loff_t offtin, int fdout, loff_t offtout, size_t len);

//=====some more helper functions=====

//strncpy where it allocates memory as well, caller has responsibilty of deleting the memory
char* Strncpy(char *dest, char *src);

char* Strncpy(char *dest, char *src, int srclen);

char* Strncpy(char* src);

char* Strncpy(char* src, int srclen);

int Strncpy(char* dest, int destlen, char* src);

//strcat where it allocates memory as well, caller has responsibilty of deleting the memory
char* Strncat(char *dest, char *src);

char* Strncat(char* dest, int dlen, char* src, int slen);

//returns full path, filedir is true for file else false for dir
char *get_full_path(char *base, char *name, bool filedir);

char** get_index_file_names(char *tabledir, char *tablename, char **basenames = NULL);

//create the db dir
int create_db_dir(char *dirname);

//simple string reverse
char* Reverse(char s[], int n);

//itoa where it allocates memory as well, caller has responsibilty of deleting the memory
char* Itoa(int i);

int Itoa(int i, char *str, int len);

//ltoa for long int
char* Ltoa(LONG_T i);

//int isnumeric (const char * s);

//strchr variation for any byte array
char* Strchr(char* str, char c, size_t len);

//list files in a dir
void listdir(char *dname);

//list of file matching list of ext names
int list_of_files_for_ext(const char *dname, const char *extnames[], int next, char ***file_names);

//returns num of dir in the folder
int num_dirs(const char* path);

//returns the list of the names of the dir as well
int num_list_dirs(const char* path, char **list, int n);

//to check if dir exists or not
bool direxists(char *path);

//returns the size of the file. opens and closes a file if fd < 0 and fname != NULL
FILEOFF_T size_of_file(int fd, char *fname);

//total num of files in a dir
int num_files_dir(char *dbname);

//given extname in a dir, return num of files
int num_files_dir(char *dbname, char *extname);

//recursively print all the files in the dir and subdir
void recurlistdir(char *dname);

//remove all files from a dir, note delete only files and not ., .., or dir
void removefile(char *parent, DIR *dp);

int rmfile2(char *basedir, char *fname, char *ext);

int rmfile(char *path);

//implementation of rm -r, deletes dir and all it's contents including dir and files, leaving only . and ..
void rrmdir(char *dname);

//read lines from file into buf[] of dimension bufdim
int readlinesfromfile(int fd, char *buf[], int bufdim);

//checks if file exists, returns 0 for no, 1 for yes and -1 for error
int fileexists(char *fname);

//copis the content of bu to file from begining
int _copy_tofile(char *filename, char *buf, off_t offset, int len);

//mkdir
int Mkdir(const char *path, mode_t mode);

//chown
int Chown(const char *path, uid_t owner, gid_t group);

//chmod
int Chmod(const char *path, mode_t mode);

//chdir
int Chdir(const char *path);

#ifndef _MS_OS_COMPILE_
int Fstat(int fd, struct stat *buf);
#else
//fstat
int Fstat(int fd, struct _stat64 *buf);
#endif

//fchown
int Fchown(int fd, uid_t owner, gid_t group);

//rename
int Rename(const char *oldpath, const char *newpath);

#ifndef _MS_OS_COMPILE_
LONG_T mulmod(LONG_T a, LONG_T b, LONG_T c);

bool Miller(LONG_T p, int iteration);

#else
int modulo(int a, int b, int c);

long long mulmod(long long a, long long b, long long c);

bool Miller(long long p, int iteration);
#endif

//creates shared mmap
int mmap_private(FILEOFF_T bufsize, char **bufptr);

//creates shared mmap
void* mmap_shared(FILEOFF_T bufsize, char **bufptr, int fd=0);

int Munmap(char *pbuf, void* hMapFil, FILEOFF_T bufsize);

UINT_T hash_string_32(char* str, int len);

ULONG_T hash_string_64(char* str, int len);

UINT_T MurmurHash32(const void * key, int len, unsigned int seed);

uint64_t MurmurHash64AEndInd (const void * key, int len, unsigned int seed);

ULONG_T hash_long(ULONG_T key);

UINT_T hash_int(UINT_T blocknum);

size_t getPeakRSS();

void getRamStat(unsigned long *totalRam, unsigned long *freeRam);

size_t getCurrentRSS();

void getTotalSystemMemory(unsigned long *totalmem, unsigned long *freemem, unsigned long *freevirtmem);

}
#endif /* BASEHDR_H_ */
