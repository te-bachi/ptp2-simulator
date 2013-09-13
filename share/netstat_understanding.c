
https://developer.berlios.de/projects/net-tools/
http://cvs.berlios.de/cgi-bin/viewvc.cgi/net-tools/net-tools/

/****************************************************************************
 * net-tools/lib/pathnames.h
 ***************************************************************************/


#define _PATH_PROCNET_TCP "/proc/net/tcp"
#define _PATH_PROCNET_TCP6 "/proc/net/tcp6"
#define _PATH_PROCNET_UDP "/proc/net/udp"
#define _PATH_PROCNET_UDP6 "/proc/net/udp6"


/****************************************************************************
 * net-tools/netstat.c
 ***************************************************************************/

int main(int argc, char *argv[])
static int tcp_info(void)
static void tcp_do_one(int lnr, const char *line, const char *prot)
static void finish_this_one(int uid, unsigned long inode, const char *timers)
static const char *prg_cache_get(unsigned long inode)


#define INFO_GUTS1(file,name,proc,prot)                 \
  procinfo = proc_fopen((file));                        \
  if (procinfo == NULL) {                               \
    if (errno != ENOENT) {                              \
      perror((file));                                   \
      return -1;                                        \
    }                                                   \
    if (flag_arg || flag_ver)                           \
      ESYSNOT("netstat", (name));                       \
    if (flag_arg)                                       \
      rc = 1;                                           \
  } else {                                              \
    do {                                                \
      if (fgets(buffer, sizeof(buffer), procinfo))      \
        (proc)(lnr++, buffer,prot);                     \
    } while (!feof(procinfo));                          \
    fclose(procinfo);                                   \
  }

/*                 1)   2)    3)   4)   5)    6)   */
#define INFO_GUTS6(file,file6,name,proc,prot4,prot6)    \
 char buffer[8192];                                     \
 int rc = 0;                                            \
 int lnr = 0;                                           \
 if (!flag_arg || flag_inet) {                          \
    INFO_GUTS1(file,name,proc,prot4)                    \
 }                                                      \
 if (!flag_arg || flag_inet6) {                         \
    INFO_GUTS2(file6,proc,prot6)                        \
 }                                                      \
 INFO_GUTS3


static int tcp_info(void) {
    
    [...]
    
    /*         1)                 2)                  3)               4)          5)     6)    */
    INFO_GUTS6(_PATH_PROCNET_TCP, _PATH_PROCNET_TCP6, "AF INET (tcp)", tcp_do_one, "tcp", "tcp6");
    
    [...]
}

/*
  d   local_addr    rem_addr      state                timer_run   retr                  timeout more
               local_port    rem_port txq     rxq         time_len           uid           inode
  20: 84E855A0:D2AF BAE855A0:008B 01 00000000:00000078 00:00000000 00000000  1000        0 21401 1 0000000000000000 20 4 30 10 -1                    
  21: 84E855A0:D29D BAE855A0:008B 01 00000000:000000F4 00:00000000 00000000  1000        0 20538 1 0000000000000000 20 4 30 10 -1                    
  22: 84E855A0:8D77 A6FFB0C3:0050 06 00000000:00000000 03:000012F2 00000000     0        0 0 3 0000000000000000                                      
  23: 84E855A0:D5DB 8FE87D4A:0050 06 00000000:00000000 03:000012F2 00000000     0        0 0 3 0000000000000000
*/

static void tcp_do_one(int lnr, const char *line, const char *prot) {
    
    [...]
    
    num = sscanf(line,
    "%d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X %lX:%lX %X:%lX %lX %d %d %lu %512s\n",
    &d, local_addr, &local_port, rem_addr, &rem_port, &state,
    &txq, &rxq, &timer_run, &time_len, &retr, &uid, &timeout, &inode, more);
    
    [...]
    
