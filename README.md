getname
======

About
-----
A very simple program to return the name associated with a given user ID.

Compiling
---------
You should compile this against the AOSP. The code compiles successfully against a 4.3 source tree.

	root@build# cd $TOP
	root@build# git clone http://github.com/jakev/android-getname external/getname
	root@build# source build/envsetup.sh
	root@build# lunch yourbuild-eng
	root@build# make getname
