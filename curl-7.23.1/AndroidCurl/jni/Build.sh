architectures="armeabi armeabi-v7a arm64-v8a x86 x86_64"

ndk-build

for cpu in $architectures; do
	echo "Installing binary for $cpu to delivery"
	mkdir ../../../delivery/curl/Android/$cpu
	cp ../obj/local/$cpu/libcurl.a ../../../delivery/curl/Android/$cpu
done
