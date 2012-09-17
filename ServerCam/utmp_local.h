//
//  utmp_local.h
//  ServerCam
//
//  Created by Dustin Dettmer on 9/16/12.
//  Copyright (c) 2012 Dusty Technologies. All rights reserved.
//

#ifndef ServerCam_utmp_local_h
#define ServerCam_utmp_local_h

#include <stdint.h>

#define FAKE_UTMP_STRUCT 0

#ifndef FAKE_UTMP_STRUCT
#include <utmp.h>
#else

#define UT_LINESIZE	32
#define UT_NAMESIZE	32
#define UT_HOSTSIZE	256


/* The structure describing the status of a terminated process.  This
 type is used in `struct utmp' below.  */
struct exit_status
{
    short int e_termination;	/* Process termination status.  */
    short int e_exit;		/* Process exit status.  */
};


/* The structure describing an entry in the user accounting database.  */
struct utmp
{
    short int ut_type;		/* Type of login.  */
    pid_t ut_pid;			/* Process ID of login process.  */
    char ut_line[UT_LINESIZE];	/* Devicename.  */
    char ut_id[4];		/* Inittab ID.  */
    char ut_user[UT_NAMESIZE];	/* Username.  */
    char ut_host[UT_HOSTSIZE];	/* Hostname for remote login.  */
    struct exit_status ut_exit;	/* Exit status of a process marked
                                 as DEAD_PROCESS.  */
    /* The ut_session and ut_tv fields must be the same size when compiled
     32- and 64-bit.  This allows data files and shared memory to be
     shared between 32- and 64-bit applications.  */
    //#if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
    int32_t ut_session;		/* Session ID, used for windowing.  */
    struct
    {
        int32_t tv_sec;		/* Seconds.  */
        int32_t tv_usec;		/* Microseconds.  */
    } ut_tv;			/* Time entry was made.  */
    //#else
    //    long int ut_session;		/* Session ID, used for windowing.  */
    //    struct timeval ut_tv;		/* Time entry was made.  */
    //#endif
    
    int32_t ut_addr_v6[4];	/* Internet address of remote host.  */
    char unused[20];		/* Reserved for future use.  */
};

#endif // FAKE_UTMP_STRUCT
#endif // ServerCam_utmp_local_h
