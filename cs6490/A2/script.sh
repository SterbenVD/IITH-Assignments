#!/bin/bash

source ./venv/bin/activate

SCALE_PROGRAM="./venv/lib64/python3.12/site-packages/scalesim/scale.py"

DATA_FOLDER="./data"

# For all folders
for folder in $DATA_FOLDER/*; do
    echo "Running for folder: $folder"
    CONFIG_FOLDER="$folder/configs"
    TOPOLOGY_FOLDER="$folder/cnns"
    OUTPUT_FOLDER="$folder/output"

    # For all config files
    for config_file in $CONFIG_FOLDER/*.cfg; do
        echo "Running for config file: $config_file"
        # For all topology files
        for topology_file in $TOPOLOGY_FOLDER/*.csv; do
            echo "Running for topology file: $topology_file"
            # Create output log directory
            output_log_dir="$OUTPUT_FOLDER/$(basename $topology_file .csv)"
            mkdir -p $output_log_dir
            python3 $SCALE_PROGRAM -c $config_file -t $topology_file -p $output_log_dir
        done
    done
done