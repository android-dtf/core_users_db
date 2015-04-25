mkuserdb
======

About
-----
A simple program to process all user IDs to a Sqlite3 database.

Compiling
---------
You can compile using the Android NDK. The code compiles successfully using NDK r10d.

    # export API=21
    # export CC=arm-linux-androideabi-gcc
    # export LD=arm-linux-androideabi-ld
    # ln -s $NDK_ROOT/platforms/android-${API}/arch-arm/usr/lib/crtend_android.o
    # ln -s $NDK_ROOT/platforms/android-${API}/arch-arm/usr/lib/crtbegin_dynamic.o
    # arm-linux-androideabi-gcc -I$NDK_ROOT/platforms/android-${API}/arch-arm/usr/include -Wl,-rpath-link=$NDK_ROOT/platforms/android-${API}/arch-arm/usr/lib -Wl,-L$NDK_ROOT/platforms/android-${API}/arch-arm/usr/lib -c sqlite3/sqlite3.c
    # arm-linux-androideabi-g++ -I$NDK_ROOT/platforms/android-${API}/arch-arm/usr/include -Wl,-rpath-link=$NDK_ROOT/platforms/android-${API}/arch-arm/usr/lib -Wl,-L$NDK_ROOT/platforms/android-${API}/arch-arm/usr/lib getpwname.c sqlite3/sqlite3.o -pie -o makeuserdb
