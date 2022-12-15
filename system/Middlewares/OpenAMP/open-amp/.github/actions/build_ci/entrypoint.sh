#!/bin/bash

readonly TARGET="$1"

ZEPHYR_TOOLCHAIN_VARIANT=zephyr
ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk
ZEPHYR_SDK_VERSION=0.13.1
ZEPHYR_SDK_DOWNLOAD_FOLDER=https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v$ZEPHYR_SDK_VERSION
ZEPHYR_SDK_SETUP_BINARY=zephyr-sdk-$ZEPHYR_SDK_VERSION-linux-x86_64-setup.run
ZEPHYR_SDK_DOWNLOAD_URL=$ZEPHYR_SDK_DOWNLOAD_FOLDER/$ZEPHYR_SDK_SETUP_BINARY

FREERTOS_ZIP_URL=https://cfhcable.dl.sourceforge.net/project/freertos/FreeRTOS/V10.0.1/FreeRTOSv10.0.1.zip

pre_build(){
	# fix issue related to tzdata install
	echo 'Etc/UTC' > /etc/timezone || exit 1
	ln -s /usr/share/zoneinfo/Etc/UTC /etc/localtime || exit 1
	apt update || exit 1
	apt-get install -y make || exit 1
	sudo pip3 install cmake || exit 1
}

build_linux(){
	echo  " Build for linux"
	apt-get install -y libsysfs-dev libhugetlbfs-dev gcc || exit 1
	export || exit 1
	pwd || exit 1
	ls -l || exit 1
	cd libmetal || exit 1
	cmake . -Bbuild || exit 1
	cd build || exit 1
	make || exit 1
	export || exit 1
	cd ../.. || exit 1
	cmake . -Bbuild -DWITH_APPS=on -DWITH_PROXY=on -DCMAKE_INCLUDE_PATH="./libmetal/build/lib/include" -DCMAKE_LIBRARY_PATH="./libmetal/build/lib" || exit 1
	cd build || exit 1
	make VERBOSE=1 all || exit 1
	exit 0
}

build_generic(){
	echo  " Build for generic platform "
	apt-get install -y gcc-arm-none-eabi || exit 1
	cd libmetal || exit 1
	cmake . -Bbuild-generic -DCMAKE_TOOLCHAIN_FILE=template-generic || exit 1
	cd build-generic || exit 1
	make VERBOSE=1 || exit 1
	cd ../../ || exit 1
	cmake . -Bbuild-generic -DCMAKE_TRY_COMPILE_TARGET_TYPE="STATIC_LIBRARY" -DCMAKE_C_FLAGS="" -DCMAKE_SYSTEM_PROCESSOR="arm" -DCMAKE_C_COMPILER=arm-none-eabi-gcc -DCMAKE_INCLUDE_PATH="./libmetal/build-generic/lib/include" -DCMAKE_LIBRARY_PATH="./libmetal/build-generic/lib" || exit 1
	cd build-generic || exit 1
	make VERBOSE=1 || exit 1
	exit 0
}

build_freertos(){
	echo  " Build for freertos OS "
	apt-get install -y gcc-arm-none-eabi unzip || exit 1
	wget $FREERTOS_ZIP_URL > /dev/null || exit 1
	unzip FreeRTOSv10.0.1.zip > /dev/null || exit 1
	mkdir -p build-freertos || exit 1
	cd build-freertos || exit 1
	cmake .. -DCMAKE_TOOLCHAIN_FILE=template-freertos -DCMAKE_C_FLAGS="-I$PWD/../FreeRTOSv10.0.1/FreeRTOS/Source/include/ -I$PWD/../FreeRTOSv10.0.1/FreeRTOS/Demo/CORTEX_STM32F107_GCC_Rowley -I$PWD/../FreeRTOSv10.0.1/FreeRTOS/Source/portable/GCC/ARM_CM3" || exit 1
	make VERBOSE=1 || exit 1
	exit 0
}

build_zephyr(){
	echo  " Build for Zephyr OS "
	sudo apt-get install -y git cmake ninja-build gperf || exit 1
	sudo apt-get install -y ccache dfu-util device-tree-compiler wget || exit 1
	sudo apt-get install -y python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file || exit 1
	sudo apt-get install -y make gcc gcc-multilib g++-multilib libsdl2-dev || exit 1
	sudo apt-get install -y libc6-dev-i386 gperf g++ python3-ply python3-yaml device-tree-compiler ncurses-dev uglifyjs -qq || exit 1
	sudo pip3 install pyelftools || exit 1
	pip3 install --user -U west
	echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
	source ~/.bashrc

	wget $ZEPHYR_SDK_DOWNLOAD_URL || exit 1
	chmod +x $ZEPHYR_SDK_SETUP_BINARY || exit 1
	rm -rf $ZEPHYR_SDK_INSTALL_DIR || exit 1
	./$ZEPHYR_SDK_SETUP_BINARY --quiet -- -y -d $ZEPHYR_SDK_INSTALL_DIR 2> /dev/null || exit 1
	west init ./zephyrproject || exit 1
	cd ./zephyrproject || exit 1
	west update || exit 1
	west zephyr-export || exit 1
	pip3 install --user -r ./zephyr/scripts/requirements.txt || exit 1
	echo  "Update zephyr OpenAMP repos"
	#Update zephyr OpenAMP repos
	cp -r ../lib modules/lib/open-amp/open-amp/ || exit 1
	cp ../CMakeLists.txt modules/lib/open-amp/open-amp/ || exit 1
	cp ../VERSION modules/lib/open-amp/open-amp/ || exit 1
	cp -r ../cmake modules/lib/open-amp/open-amp/ || exit 1
	cp -r ../libmetal modules/hal/libmetal/ || exit 1
	cd ./zephyr || exit 1
	source zephyr-env.sh || exit 1
	echo  "build openamp sample"
	west build -b lpcxpresso54114_m4 samples/subsys/ipc/openamp/ || exit 1
	rm -r build
	echo  "build openamp/remote sample"
	west build -b lpcxpresso54114_m0 samples/subsys/ipc/openamp/remote/ || exit 1
	rm -r build
	echo  "build openamp_rsc_table sample"
	west build -b stm32mp157c_dk2 samples/subsys/ipc/openamp_rsc_table || exit 1
	exit 0
}

main(){
	pre_build;

	if [[ "$TARGET" == "linux" ]]; then
		build_linux
	fi
	if [[ "$TARGET" == "generic" ]]; then
		build_generic
	fi
	if [[ "$TARGET" == "freertos" ]]; then
		build_freertos
	fi
	if [[ "$TARGET" == "zephyr" ]]; then
		build_zephyr
	fi
}

main
