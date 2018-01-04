#!/usr/bin/perl

use POSIX qw(strftime); 

printf ("test%.0d\n", strftime ("%H%M", localtime) / 10);


