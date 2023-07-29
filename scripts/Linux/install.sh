#!/bin/bash

cd ../..

executable_path='build/bin/linux/64/sandbox'
data_path='data'

all_files_found='true'

CheckForFile ()
{
    if [ -f $1 ]; then
        return 1
    else
        return 0
    fi
}

InstallFilesInDirectory ()
{
    # $1 = path, $2 = executable_directory, $3 = data_files
    if [ ! -d $1 ]; then
        mkdir $1

        if [ ! $? eq 0 ]; then
            echo 'could not make the directory for installation make sure it is not a file system path or run this script with root access.'
            exit
        fi
    fi

    install_directory=$1
    mkdir ${install_directory}

    cp $2 ${install_directory}
    if [ ! $? eq 0 ]; then
        echo 'could not copy executable file into installation directory.'
    fi

    cp -r $3 ${install_directory}
    if [ ! $? eq 0 ]; then
        echo 'could not copy data files into installation directory.'
    fi
}

if [ ! -f ${executable_path} ]; then
    all_files_found="false"
    echo 'executable file is missing, perhaps you did not compile it yet or run clear_build.sh?'
fi

if [ ! -d ${data_path} ]; then
    all_files_found="false"
    echo 'data directory is missing!'

else
    if [ ! -d ${data_path}/fonts ]; then
        all_files_found="false"
        echo 'fonts directory which should be inside data directory is missing!'
    fi

    if [ ! -d ${data_path}/images ]; then
        all_files_found="false"
        echo 'images directory which should be inside data directory is missing!'
    fi

    if [ ! -d ${data_path}/shaders ]; then
        all_files_found="false"
        echo 'shaders directory which should be inside data directory is missing!'
    fi

    if [ ! -d ${data_path}/textures ]; then
        all_files_found="false"
        echo 'textures directory which should be inside data directory is missing!'
    fi
fi

if [ all_files_found = "false" ]; then
    exit
fi

echo 'do you want to install the program into the desktop directory?(y/n)'
read answer
if [ ${answer}=y ] || [ ${answer}=Y ]; then
    InstallFilesInDirectory ${HOME}/Desktop/sandbox ${executable_path} ${data_path}

elif [ ${answer}=n ] || [ ${answer}=N ]; then
    echo 'do you want to install it into system directories or into a custom directory?(y for system install/n for custom install)'
    read answer
    if [ ${answer}=y ] || [ ${answer}=Y ]; then
        InstallFilesInDirectory '/usr/bin' ${executable_path} ${data_path}
    else
        echo 'please specify an installation path.'
        read custom_path
        InstallFilesInDirectory ${custom_path} ${executable_path} ${data_path}    
    fi
fi