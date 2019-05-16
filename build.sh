#!/bin/bash
#Building script for DnD generator app!
#This is configured to work on my machine. -Adam

echo "Starting script..."

# Projucer absolute path for my machine.
projucer=/Applications/JUCE/Projucer\(Applications\).app/Contents/MacOS/Projucer
projectName="DnD"


undoSettingsAndExit(){
    # Switch back to XCode 9
    sudo xcode-select --switch /Applications/xCode.app
    exit 1
}

# resave jucer project to make sure everything is updated (eg BinaryData & JUCE Code)
$projucer --resave "$projectName.jucer"
handleError

echo "Project resaved."

# Switch to XCode 10
sudo xcode-select --switch /Applications/xCode10/Xcode10.app

# # build mac app
pushd Builds/MacOSX
xcodebuild clean -configuration Release
handleError
buildLog="xcodebuild.log"
xcodebuild -target "$projectName - App" -configuration Release 2> "$buildLog"
handleError

if [ -s "$buildLog" ]
then
echo "build failed due to following errors:"
cat "$buildLog"
undoSettingsAndExit
fi
popd


# build IOS app
# pushd Builds/iOS
# xcodebuild clean -configuration Release
# handleError
# buildLog="xcodebuild.log"
# xcodebuild -target "$projectName - App" -configuration Release 2> "$buildLog" PROVISIONING_PROFILE="${PROVISION_PROFILE}"
# #xcodebuild -workspace ../DnD.xcworkspace -scheme "$PRODUCT_NAME" -sdk iphoneos -configuration "${CONFIGURATION}" archive -archivePath "${TARGET_BUILD_DIR}/${PRODUCT_NAME}.xcarchive" PROVISIONING_PROFILE="${PROVISION_PROFILE}"
# #xcodebuild -target "$projectName - App" -configuration Release 2> "$buildLog" archive -archivePath "${TARGET_BUILD_DIR}/${PRODUCT_NAME}.xcarchive" PROVISIONING_PROFILE="${PROVISION_PROFILE}"

# handleError

# if [ -s "$buildLog" ]
# then
# echo "build failed due to following errors:"
# cat "$buildLog"
# undoSettingsAndExit
# fi
# popd


#build Android app
pushd Builds/Android
./gradlew

undoSettingsAndExit()



