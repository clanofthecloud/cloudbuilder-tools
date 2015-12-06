export CYGWIN="winsymlinks:native"
export ANDROID_API=android-14
export ANDROID_DEV=c:/cygwin64/opt/android-ndk/platforms/android-14/arch-arm/usr
export PATH=/opt/android-ndk/prebuilt/darwin-x86_64/bin:/opt/android-ndk/toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin:$PATH
export MACHINE=armv7
export SYSTEM=android
export ARCH=arm
export CROSS_COMPILE=arm-linux-androideabi-
cd ..
if [ ! -d "openssl-1.0.1i" ]; then
	tar xzfv openssl-1.0.1i.tar.gz
	cd openssl-1.0.1i
	./config shared -no-hw -no-engines -no-dtls -no-shared --openssldir=Build-Android
	make depend
else
	echo "Source already extracted, will simply rebuild"
	cd openssl-1.0.1i
fi
make build_libs
mkdir -p ../../delivery/openssl/Android/include
mkdir -p ../../delivery/openssl/Android/lib
cp -rL include ../../delivery/openssl/Android
cp libcrypto.a ../../delivery/openssl/Android/lib
cp libssl.a ../../delivery/openssl/Android/lib
