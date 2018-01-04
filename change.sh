#!/bin/sh

command=""

find_user ()
{
	local user_str=`grep -E "^${USER}\s*:" $1 2> /dev/null`
	if [ "$user_str" != "" ]; then
		# some magic and we're done!!
		command=`echo $user_str | cut -d':' -f2-`
	fi
}

gethome ()
{
	local _USER=$1
	_HOME=""

	if [ -z "${_USER}" ]; then
		return 1
	fi

# FIXME: I guess this won't work for a nis like system
	# it has to be done to avoid expansion
	local F='$6'
	_HOME=`cat /etc/passwd | awk -F ':' "/${_USER}/ { printf $F; }"`

	return 0
}


USER=$1

if [ "$USER" == "" ]; then
	exit
fi


conf="global"
file="/etc/preexec/preexec.conf"
if [ -r $file ]; then
	find_user $file
fi

if [ "$command" == "" ]; then
	gethome $USER
	file="${_HOME}/.preexec"
	if [ -r $file ]; then
		find_user $file
	fi
	conf="local"
fi

if [ "$command" == "" ]; then
	exit
fi

# global options get euid == root, TODO: add a configurable switch for this?
if [ "$conf" == "global" ]; then
	NEWPASS=`$command`
else
	# of course this is needed, otherwise the user whould have root privileges
	NEWPASS=`su -c "$command" $USER`
fi


if [ "$NEWPASS" == "" ]; then
	exit
fi

/etc/preexec/feeder.sh $NEWPASS | /usr/bin/passwd $USER 2>/dev/null

