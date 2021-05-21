# Ancient Versions of slib

Here I keep the older versions of slib (which I wrote really really long ago).
It's normal to see many typos in those files, since I was in primary school
back then. If there are encoding issues, try to open with GB2312 or GBK. Also,
all CRLF line endings were replaced to LF by git.

Semantic versioning started at v2.2.0, the versioning scheme before that
is unknown, that is, for the first few revisions, I did't name any release,
then sometimes I used "12" to prefix some versions.
(I really cannot understand myself!)

The versions and corresponding sources are:
 - 12v1.1: Email. 2016-01-01T11:36:11+08:00 (`administration.txt`),
                  2016-01-01T11:59:50+08:00 (`administration.c`).
 - Unversioned/01admin.c: Email. 2016-01-03T14:30:32+08:00.
 - admin_v1.3.6: Email, originally named as `admin.txt`. 2016-01-27T20:07:11+08:00.
 - 12v2_3.6: Email. 2016-10-07T08:44:32+08:00
 - admin_v2.3.12: Email. 2017-01-15T11:36:07+08:00.
 - v0.7: Found in Baidu Netdisk.
 - v0.9: Found in Baidu Netdisk.

The ones inside `Uncompilable` are not correct C sources.
 - administration.c: 2016-01-01T20:09:47+08:00.
 - cerror.txt: 2016-01-02T19:44:29+08:00.
 - administration_2.c: 2016-01-01T18:08:36+08:00.

For a while, I really wanted to have a calculator function, and tried hard to
incorporate what I'd found online into my codebase. Of course it hardly worked:
I didn't know that there cannot be a function inside other functions. But this
progress indeed helped me to understand how functions work. Those copied
portions are not a part of today's codebase for sure.

Those days I didn't know about git, so I "develop"ed with notepad++,
CFree (an IDE, can still be found on [their website](https://programarts.com)),
and iEditor (an editor for iOS), and transmitted the files with email and net
disk.

For the history of this project, see README.md at the root directory.
