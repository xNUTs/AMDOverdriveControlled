#!/bin/sh

###############################################################################################
## This file is heavily based on the make_dep.sh script provided by the AMDOverdriveCtrl IDE ##
###############################################################################################

ver=`cat Revision.h | grep VERSION | tr -d " A-Za-z;="`
rev=`cat Revision.h | grep REVISION | tr -d " A-Za-z;="`
build=`cat Revision.h | grep BUILD | tr -d " A-Za-z;="`

arch=`uname -m`

if [ "${arch}" = "i686" ]; then
    arch="i386"
elif [ "${arch}" = "x86_64" ]; then
    arch="amd64"
fi

## Making control and postinst files
generateDebianFiles()
{
    cat > temp/DEBIAN/control <<EOF
Package: AMDOverdriveCtrl
Version: ${ver}.${rev}.${build}
Architecture: ${arch}
Section: utils
Priority: optional
Installed-Size: ${inst_size}
Depends: libwxgtk2.8-0, libgtk2.0-0
Maintainer: Thorsten Gilling [tgilling@web.de]
Description: Control AMD Catalyst Overdrive settings
 This tool let's you control the frequency and fan settings of your AMD/ATI video card.
 It depends on the proprietary AMD/ATI Catalyst display driver and makes use of
 the AMD Display Library (ADL) library.
EOF

    cat > temp/DEBIAN/postinst <<EOF
#!/bin/sh
echo "Running postinst step..."

## Menu updating
if [ "\$1" = "configure" ] && [ -x "\`which update-menus 2>/dev/null\`" ]; then
    update-menus
fi
echo "Done"
EOF

    chmod 0755 temp/DEBIAN/postinst
}

## Making destop file
generateDesktopFile()
{
    rm -fr temp/usr/share/applications/AMDOverdriveCtrl.desktop
    cp -fr create_deb/AMDOverdriveCtrl.desktop temp/usr/share/applications/AMDOverdriveCtrl.desktop
    chmod +x temp/usr/share/applications/AMDOverdriveCtrl.desktop
}

## Making menu entry for WMs
generateMenuFile()
{
    rm -fr temp/usr/share/menu/AMDOverdriveCtrl
    echo "?package(AMDOverdriveCtrl):needs=\"x11\" section=\"Apps/Utils\" \ " >> temp/usr/share/menu/AMDOverdriveCtrl
    echo "        title=\"AMDOverdriveCtrl\" command=\"/usr/bin/AMDOverdriveCtrl\" \ " >> temp/usr/share/menu/AMDOverdriveCtrl
    echo "        icon=\"/usr/share/AMDOverdriveCtrl/images/icon.png\" " >> temp/usr/share/menu/AMDOverdriveCtrl
    echo "" >> temp/usr/share/menu/AMDOverdriveCtrl
}

## clear previous packaged files
rm -fr temp
mkdir -p temp/DEBIAN/
mkdir -p temp/usr/bin/
chmod g-s temp/*

cp ./Release/AMDOverdriveCtrl temp/usr/bin/AMDOverdriveCtrl

mkdir -p temp/usr/share/AMDOverdriveCtrl/images
mkdir -p temp/usr/share/applications/
mkdir -p temp/usr/share/menu/

cp -pr ./create_deb/*.png temp/usr/share/AMDOverdriveCtrl/images/
cp -pr ./create_deb/AUTHORS temp/usr/share/AMDOverdriveCtrl/
cp -pr ./create_deb/LICENSE temp/usr/share/AMDOverdriveCtrl/

## Get installed size
inst_size=`du -s temp/usr/ | awk -F" " '{ print $1 }'`

## Make debain files
generateDebianFiles

## Make desktop file
generateDesktopFile

## Make menu entry
generateMenuFile

chmod +x temp/usr/bin/AMDOverdriveCtrl

fakeroot dpkg -b temp/ .

rm -rf temp

