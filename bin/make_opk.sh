#!/bin/sh

rm -f fba.opk
rm -f fba_ui_only.opk

mksquashfs skin fbasdl_gcw0.dge fbasdl_lepus.dge skin/fba_icon.png fba_ux.gcw0.desktop fba_ux.lepus.desktop fba_explorer.gcw0.desktop fba_explorer.lepus.desktop aliases.txt fba.opk -all-root -no-xattrs -noappend -no-exports
mksquashfs skin fbasdl_gcw0.dge fbasdl_lepus.dge skin/fba_icon.png fba_ux.gcw0.desktop fba_ux.lepus.desktop fba_ui_only.opk -all-root -no-xattrs -noappend -no-exports
