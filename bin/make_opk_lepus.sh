#!/bin/sh

rm -f fba_lepus.opk
rm -f fba_ui_only_lepus.opk

mksquashfs skin fbasdl_lepus.dge skin/fba_icon.png fba_ux.lepus.desktop fba_explorer.lepus.desktop aliases.txt fba_lepus.opk -all-root -no-xattrs -noappend -no-exports
mksquashfs skin fbasdl_lepus.dge skin/fba_icon.png fba_ux.lepus.desktop fba_ui_only_lepus.opk -all-root -no-xattrs -noappend -no-exports
