#!/bin/sh

rm -f fba.opk
rm -f fba_ui_only.opk

mksquashfs skin fbasdl.dge skin/fba_icon.png fba_ux.gcw0.desktop fba_explorer.gcw0.desktop aliases.txt fba.opk -all-root -no-xattrs -noappend -no-exports
mksquashfs skin fbasdl.dge skin/fba_icon.png fba_ux.gcw0.desktop fba_ui_only.opk -all-root -no-xattrs -noappend -no-exports
