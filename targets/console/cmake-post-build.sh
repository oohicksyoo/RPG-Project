#!/bin/bash

echo "Adding Frameworks @rpath to binary ..."
install_name_tool -add_rpath @loader_path/../Frameworks out/rpg-engine-console

pushd out
	# See if there is an `assets` folder already.
	if [ ! -d "assets" ]; then
		# If there isn't create a new symlink named `assets`.
		echo "Linking 'assets' path to '../../../assets'"
		ln -s ../../../assets assets
	fi

	# See if there is a `vulkan` folder already.
	if [ ! -d "vulkan" ]; then
		# If there isn't create a new symlink named `vulkan`.
		echo "Linking 'vulkan' path to '../vulkan'"
		ln -s ../vulkan vulkan
	fi
popd