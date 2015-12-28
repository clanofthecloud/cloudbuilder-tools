# CloudBuilder-tools
Tools for the native C++ SDK of Clan of the Cloud

# Compiling

This project contains external tools used building the CloudBuilder SDK. You need to read information about the main project by refering to the [main page](https://github.com/clanofthecloud/unity-sdk) first. Then read further if you want to recompile the tools by yourselves, which is **not required in order to use the SDK** since we provide precompiled binaries.

As described previously, check out the `cloudbuilder-tools` repository next to this (`cloudbuilder`) repository. Do not rename the folders, as they may refer themselves during some steps of the compilation process.

The tools currently contain three projects:

	- pthreads (Windows only)
	- openssl
	- curl

These libraries are used by the main SDK and are expected to be placed in the `cloudbuilder/delivery` folder (`cloudbuilder/delivery/curl`, etc.). The Facebook and Google folders under `cloudbuilder/delivery` there need to be taken from the precompiled distribution, but you may replace them with a newer version of these SDK (though we do not recommend that).

We suggest that you follow this order when compiling.

## Compiling pthreads for Windows

This step is only required on Windows, since pthreads is a standard library shipped with most UNIX-like distributions. Open `pthreads-w32-2.9.1\pthreads.2\pthread.sln`. Same as with curl, you need to compile it four times by selecting an alternate concfiguration from the Configuration Manager each time. Use the following configurations:

	- LIB_Debug_VS2012 with platform Win32 and x64
	- LIB_Release_VS2012 with platform Win32 and x64

Which means 4 configurations, therefore running the compilation 4 times. After that, the `cloudbuilder\delivery\pthread` directory should look as follows:

	- Headers: containing a few header files
	- Windows
		- Debug_VS2012
			- x86
				- libpthread.lib
				- vc110.pdb
			- x64
				- Same as in x86
		- Release_VS2012
			- Same structure as in Debug_VS2012

## Compiling OpenSSL

This one is tricky. It requires an official version of the OpenSSL library as indicated in the `REQUIRED.txt` file under the `openssl`. Fetch the required archive and put it there. The various scripts refer the corresponding version directly. You may change it by modifying them. Note that compiling OpenSSL is always a pretty lengthy and tedious process (in the order of magnitude of half an hour, depending on your machine).

**On Windows**: you need to install [Active Perl](http://www.activestate.com/activeperl) first. Then open the `openssl\Windows` folder and copy the folder path using the address bar. Then you will run the process twice, once for building a 64-bit (x64) version and one for the 32-bit (x86) version. In the following steps, just replace x86 by x64 when doing it the second time.

Look for VS2012 x86 Native Tools Command Prompt from your start menu (replace with the appropriate version of Visual Studio). Right click the entry and choose "Run as administrator". This step is required because the compilation scripts use symbolic links which require administrative privileges on Windows.

From the console, type cd `the path` that you copied earlier, then Enter. Then type Run using Visual Studio x86 command line tools.bat and press Enter.

If something goes wrong you can try again, but sometimes it may be better to delete the openssl-1.0.1i folder (resulting of the extracted archive) in order to start over the process clean. Else the resulting files should be copied properly to the `cloudbuilder\delivery\openssl` folder. In case of issue, the output should be more than verbose.

When you start the process over for the 64-bit version, we recommend deleting the the openssl-1.0.1i folder (resulting of the extracted archive) manually.

**On Mac and iOS**: nothing special is required here, except that the Command Line Tools are available on your system, since no xcode project is provided. The system itself will prompt you to download the tools when running the script for the first time. In case you haven't accepted the license and this process fails to be prompted by the system automatically, run `sudo xcodebuild -license` from the terminal.

Then simply open a Terminal, move to the folder (`openssl/Mac+iOS`) and run `./openssl-maker.sh`.

**On Android**: even trickier to compile, please read the instructions in the file `HowTo.txt` placed under `openssl/Android` directory.

## Compiling CURL

**On Windows**: open `curl-7.23.1\vc6curl.sln`. We currently use Visual Studio 2012. An upgrade may be suggested with later versions. By modifying the target SDK, you may compile it on Visual Studio 2010 too, but it has not been tested on previous versions.

You can play with the Configuration Manager and compile it for your needs. Use the following configurations:

	- LIB_Debug_VS2012 with platform Win32 and x64
	- LIB_Release_VS2012 with platform Win32 and x64

Which means 4 configurations, therefore running the compilation 4 times.

**On Mac**: open `curl-7.23.1\MacosXCurl\MacosXCurl.xcodeproj` with Xcode (you need Mac OS X). Here, just like on Windows, you should run all the 4 possible configurations one by one: MacosXCurl-Debug and MacosXCurl-Release, on both My Mac (32-bit) and My Mac (64-bit). Note that you need OpenSSL to be compiled successfully prior to this step, else you'll get errors about missing .h files.

**On iOS**: open `curl-7.23.1\iOSCurl\iOSCurl.xcodeproj` with Xcode (you need Mac OS X). Here, just like on Mac OS X, you should run all the 4 possible configurations one by one:

	* For iOSCurl-Debug and iOSCurl-Release,
	* Once with With any iPhone Simulator (e.g. iPhone 6S) and once with *Generic iOS Device*.

Note that you need OpenSSL to be compiled successfully prior to this step, else you'll get errors about missing .h files.

**On Android**: open a console in the directory `curl-7.23.1\AndroidCurl\jni`. On Windows, you need a cygwin console (unless you replicate what the `Build.sh` script does by hand). Run the `Build.sh` script, which will compile the library successively for all CPU architectures (known to be running Android to date). If you get errors like this:

```$ ./Build.sh
./Build.sh: line 2: $'\r': command not found
./Build.sh: line 3: $'ndk-build\r': command not found```

It may be that the line endings from the git repository do not match what is expected by the shell. You may just open the `Build.sh` file and re-save it with Unix Line Endings. Any powerful text editor for programmers is able to do that (on SublimeText, open the file, click on View, Line Endings, Unix and save the file).

If you get an error regarding `ndk-build` being not found, you need to check that your Android SDK installation is [configured properly for command line invocation](http://developer.android.com/ndk/guides/ndk-build.html).
