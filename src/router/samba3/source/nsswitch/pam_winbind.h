/* pam_winbind header file 
   (Solaris needs some macros from Linux for common PAM code)

   Shirish Kalele 2000
*/

#include "lib/replace/replace.h"
#include "system/syslog.h"
#include "system/time.h"
#include <talloc.h>
#include "libwbclient/wbclient.h"
#include "localedir.h"

#define MODULE_NAME "pam_winbind"
#define PAM_SM_AUTH
#define PAM_SM_ACCOUNT
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

#ifndef PAM_WINBIND_CONFIG_FILE
#define PAM_WINBIND_CONFIG_FILE "/etc/security/pam_winbind.conf"
#endif

#include <iniparser.h>

#ifdef HAVE_LIBINTL_H
#include <libintl.h>
#endif

#if defined(LINUX)

/* newer versions of PAM have this in _pam_compat.h */
#ifndef PAM_AUTHTOK_RECOVERY_ERR
#define PAM_AUTHTOK_RECOVERY_ERR PAM_AUTHTOK_RECOVER_ERR
#endif

#else /* !LINUX */

/* Solaris always uses dynamic pam modules */
#define PAM_EXTERN extern
#if defined(HAVE_SECURITY_PAM_APPL_H)
#include <security/pam_appl.h> 
#elif defined(HAVE_PAM_PAM_APPL_H)
#include <pam/pam_appl.h>
#endif

#ifndef PAM_AUTHTOK_RECOVER_ERR
#define PAM_AUTHTOK_RECOVER_ERR PAM_AUTHTOK_RECOVERY_ERR
#endif

#endif /* defined(SUNOS5) || defined(SUNOS4) || defined(HPUX) || defined(FREEBSD) || defined(AIX) */

#if defined(HAVE_SECURITY_PAM_MODULES_H)
#include <security/pam_modules.h>
#elif defined(HAVE_PAM_PAM_MODULES_H)
#include <pam/pam_modules.h>
#endif

#if defined(HAVE_SECURITY__PAM_MACROS_H)
#include <security/_pam_macros.h>
#elif defined(HAVE_PAM__PAM_MACROS_H)
#include <pam/_pam_macros.h>
#else
/* Define required macros from (Linux PAM 0.68) security/_pam_macros.h */
#define _pam_drop_reply(/* struct pam_response * */ reply, /* int */ replies) \
do {                                              \
    int reply_i;                                  \
                                                  \
    for (reply_i=0; reply_i<replies; ++reply_i) { \
        if (reply[reply_i].resp) {                \
            _pam_overwrite(reply[reply_i].resp);  \
            free(reply[reply_i].resp);            \
        }                                         \
    }                                             \
    if (reply)                                    \
        free(reply);                              \
} while (0)

#define _pam_overwrite(x)        \
do {                             \
     register char *__xx__;      \
     if ((__xx__=(x)))           \
          while (*__xx__)        \
               *__xx__++ = '\0'; \
} while (0)

/*
 * Don't just free it, forget it too.
 */

#define _pam_drop(X) SAFE_FREE(X)

#define  x_strdup(s)  ( (s) ? strdup(s):NULL )     
#endif /* HAVE_SECURITY__PAM_MACROS_H */

#ifdef HAVE_SECURITY_PAM_EXT_H
#include <security/pam_ext.h>
#endif

#define WINBIND_DEBUG_ARG		0x00000001
#define WINBIND_USE_AUTHTOK_ARG		0x00000002
#define WINBIND_UNKNOWN_OK_ARG		0x00000004
#define WINBIND_TRY_FIRST_PASS_ARG	0x00000008
#define WINBIND_USE_FIRST_PASS_ARG	0x00000010
#define WINBIND__OLD_PASSWORD		0x00000020
#define WINBIND_REQUIRED_MEMBERSHIP	0x00000040
#define WINBIND_KRB5_AUTH		0x00000080
#define WINBIND_KRB5_CCACHE_TYPE	0x00000100
#define WINBIND_CACHED_LOGIN		0x00000200
#define WINBIND_CONFIG_FILE		0x00000400
#define WINBIND_SILENT			0x00000800
#define WINBIND_DEBUG_STATE		0x00001000
#define WINBIND_WARN_PWD_EXPIRE		0x00002000
#define WINBIND_MKHOMEDIR		0x00004000

#if defined(HAVE_GETTEXT) && !defined(__LCLINT__)
#define _(string) dgettext(MODULE_NAME, string)
#else
#define _(string) string
#endif

#define N_(string) string

/*
 * here is the string to inform the user that the new passwords they
 * typed were not the same.
 */

#define MISTYPED_PASS _("Sorry, passwords do not match")

#define on(x, y) (x & y)
#define off(x, y) (!(x & y))

#define PAM_WINBIND_NEW_AUTHTOK_REQD "PAM_WINBIND_NEW_AUTHTOK_REQD"
#define PAM_WINBIND_NEW_AUTHTOK_REQD_DURING_AUTH "PAM_WINBIND_NEW_AUTHTOK_REQD_DURING_AUTH"
#define PAM_WINBIND_HOMEDIR "PAM_WINBIND_HOMEDIR"
#define PAM_WINBIND_LOGONSCRIPT "PAM_WINBIND_LOGONSCRIPT"
#define PAM_WINBIND_LOGONSERVER "PAM_WINBIND_LOGONSERVER"
#define PAM_WINBIND_PROFILEPATH "PAM_WINBIND_PROFILEPATH"
#define PAM_WINBIND_PWD_LAST_SET "PAM_WINBIND_PWD_LAST_SET"

#define SECONDS_PER_DAY 86400

#define DEFAULT_DAYS_TO_WARN_BEFORE_PWD_EXPIRES 14

#include "winbind_client.h"

#define PAM_WB_REMARK_DIRECT(c,x)\
{\
	const char *error_string = NULL; \
	error_string = _get_ntstatus_error_string(x);\
	if (error_string != NULL) {\
		_make_remark(c, PAM_ERROR_MSG, error_string);\
	} else {\
		_make_remark(c, PAM_ERROR_MSG, x);\
	};\
};

#define LOGON_KRB5_FAIL_CLOCK_SKEW	0x02000000

#define PAM_WB_CACHED_LOGON(x) (x & WBC_AUTH_USER_INFO_CACHED_ACCOUNT)
#define PAM_WB_KRB5_CLOCK_SKEW(x) (x & LOGON_KRB5_FAIL_CLOCK_SKEW)
#define PAM_WB_GRACE_LOGON(x)  ((WBC_AUTH_USER_INFO_CACHED_ACCOUNT|WBC_AUTH_USER_INFO_GRACE_LOGON) == ( x & (WBC_AUTH_USER_INFO_CACHED_ACCOUNT|WBC_AUTH_USER_INFO_GRACE_LOGON)))

struct pwb_context {
	pam_handle_t *pamh;
	int flags;
	int argc;
	const char **argv;
	dictionary *dict;
	uint32_t ctrl;
};

#define TALLOC_FREE(ctx) do { if ((ctx) != NULL) {talloc_free(ctx); ctx=NULL;} } while(0)
#define TALLOC_ZERO_P(ctx, type) (type *)_talloc_zero(ctx, sizeof(type), #type)
#define TALLOC_P(ctx, type) (type *)talloc_named_const(ctx, sizeof(type), #type)

