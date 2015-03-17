# ~/.bashrc --
# $Id: .bashrc,v 1.2 1999/02/12 13:32:54 ray Exp ray $
# The individual per-interactive-shell startup file for bash
#[ -e /etc/config.d/D ] && echo "~$USER/.bashrc: \$-='$-'" 1>&2

# load maintained system-defaults...  (NB: $HOME/.profile, i.e.
# /etc/config.d/shells/profile) depend on this one!!!)
[ -r /etc/config.d/shells/bashrc ] && . /etc/config.d/shells/bashrc

# Network-wide defaults
[ -r /netdisk/skel/bashrc-main ] && . /netdisk/skel/bashrc-main

# load user-defaults
[ -r $HOME/.bashrc-private ] && . $HOME/.bashrc-private

# personal additions should preferrably be placed in the above file,
# $HOME/.bashrc-private but may nevertheless be appendend below...

alias mytars='ls -Fal ~/MAIN/tars | more'
create_tar(){
	cd ; tar czf ~/MAIN/tars/Martinez_Joe${1}.tar.z CSC60
}

