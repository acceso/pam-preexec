
preexec
-------

With this pam module you can execute a command before login in.
The command can change your password. 

For example you can use the current minute in the password and even if 
someone sniffs it, it wouldn't work (except if he logs in the same minute).
With creativity you can use things like "one-time passwords", the current
song being played on your favorite radio, the first word of othe latest new 
published in Slashdot or a mix of them.


Instructions:

- Run "make" within pam_preexec dir. If it doesn't compile, you probably need: 
  "apt-get install libpam0g-dev" or whatever...

- cp pam_preexec/pam_preexec.so /lib/security/

- Add: "auth required pam_preexec.so /etc/preexec/change.sh"
  at the top of the file for a given service under /etc/pam.d,
  for ex. /etc/pam.d/login.

- mkdir /etc/preexec/
  if you don't like the location, change it on every step starting
  with the previous one. Then do:
  cp change.sh feeder.sh /etc/preexec/
  Note that change.sh has:
  /etc/preexec/feeder.sh and /etc/preexex/preexec.conf
  hardcoded, so you have to change it on the source too!

- Create /etc/preexec/preexec.conf or $USER/.preexec with a line such as:
  user: /etc/preexec/scripts/user.pl_or_whatever
  the script has to print a string, see sample_scripts directory,
  you can also use shell on the config file:
  user: echo new_password

- I recommend using a "mirrored" user, such as:
  ```
  jose:x:501:501:Jose,,,:/home/jose:/bin/bash
  jose2:x:501:501:Jose,,,:/home/jose:/bin/bash 
  ```
  I usually log in as "jose" but when I'm using an insecure line, 
  I log in as "jose2".

- Enjoy :). 
  This procedure hasn't been tested so I could have left something out, YMMV.




