architectures="armeabi armeabi-v7a arm64-v8a x86 x86_64"

/opt/android-ndk/ndk-build

for cpu in $architectures; do
	echo "Installing binary for $cpu to delivery"
	mkdir -p ../../../../cloudbuilder/delivery/curl/Android/$cpu
	cp ../obj/local/$cpu/libcurl.a ../../../../cloudbuilder/delivery/curl/Android/$cpu
done
