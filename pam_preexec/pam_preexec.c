
#include <pwd.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>

#define PAM_SM_AUTH
#define PAM_SM_ACCOUNT

#include <security/pam_modules.h>
#include <security/_pam_macros.h>

/* --- authentication management functions (only) --- */

PAM_EXTERN int
pam_sm_authenticate (pam_handle_t * pamh, int flags, int argc, const char **argv)
{
	int retval;
	const char *user;
	int i;
	long s;
	char *args, *j;

	retval = pam_get_user (pamh, &user, NULL);
	if (retval != PAM_SUCCESS) {
		D (("get user returned error: %s", pam_strerror (pamh, retval)));
		return PAM_SERVICE_ERR;
	}

	if (user == NULL || *user == '\0') {
		D (("username not known"));
		return PAM_SERVICE_ERR;
	}

	s = strlen (user) + 1;
	for (i = 0 ; i < argc ; i++)
		s += strlen (argv[i]) + 1;

	args = malloc(s + 1);
	for (i = 0, j = args; i < argc; i++) {
		strcpy (j, argv[i]);
		j += strlen (argv[i]);
		*j++ = ' ';
	}

	strcpy (j, user);

	j += strlen(user);
	*j = '\0';

	system (args);
/*	system ("/home/jose/wordexp/extra/change.sh gemi");
*/
	return PAM_SUCCESS;
}


PAM_EXTERN int
pam_sm_setcred (pam_handle_t * pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}


/* --- account management functions (only) --- */

PAM_EXTERN int
pam_sm_acct_mgmt (pam_handle_t * pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}


/* --- session management --- */

PAM_EXTERN
int pam_sm_open_session (pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN
int pam_sm_close_session (pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}



#ifdef PAM_STATIC

/* static module data */

struct pam_module _pam_permit_modstruct = {
	"pam_preexec",
	pam_sm_authenticate,
	pam_sm_setcred,
	pam_sm_acct_mgmt,
	pam_sm_open_session,
	pam_sm_close_session,
	NULL,
};

#endif /* PAM_STATIC */

/* end of module definition */

