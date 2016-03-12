##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2014, Freescale Semiconductor, Inc.
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#    Looks for *.so symlinks in $1 directory and converts them to hard links.
#
#  USAGE
#    $1 specifies directory to work in (not recursive).
#    If $2 == "d" the original files and intermediate links are deleted.
#
#  AUTHOR
#    Tomas Babinec
#
#  DATE
#    2014-03-16
#
#  LANGUAGE
#    bash script
#
##############################################################################

#﻿!/bin/bash

if [ -d $1 ] ; then
#    echo "About to convert all symbolic links in '$1' . Continue? [y/N]"
#    read confirm
#    if [ $confirm == "y" ]; then
        cd "$1" &&
        FILES="*.so"	#only for *.so libraries
        for file in $FILES
        do
	    # only for links
            if [ -L "$file" ]; then
                target=$(readlink "$file")
                orig=$file
		while [ -L "$target" ]
		do
		  echo "$target is a symbolic link again => going deeper"
		  # reverse link if requested
		  if [ "$2" == "r" ]
		  then
		    ln -s $target $orig
		  fi
		  orig=$target
		  
		  target=$(readlink "$target")
		  
		  # delete link if requested
		  if [ "$2" == "d" ]
		  then
		    rm "$orig"
		  fi
		done
                echo "Converting symbolic link ($file) to hardlink"
                rm "$file" &&
                ln "$target" "$file"
                
		if [ "$2" == "d" ]
		then
		  echo "Removing original file ($file)"
		  rm "$target"
		elif [ "$2" == "r" ]
		then
		  echo "Reversing link"
		  rm "$target" &&
		  ln -s $file $target
		fi
            else
                echo "$file not a symbolic link, skipping"
            fi
        done
        
        # remove any unconnected symbolic links to *.so liblaries 
        if [ "$2" == d ]
        then
	  FILES="*.so*"
	  for file in $FILES
	  do
	      # only for links
	      if [ -L "$file" ]; then
		  target=$(readlink "$file")
		  if [ ! -e "$target" ]
		  then
		    echo " Removing unconnected symbolic link: $file"
		    rm "$file"
		  fi
	      fi
	  done
	fi
#    else
#        echo "Exiting. No changes made."
#    fi

else
    echo "$1 is not a directory, exiting."
fi
exit
