#!/bin/bash

# Set the library path
export LD_LIBRARY_PATH=/home/nu/itoshun/Programs/ninjarecon-master/lib/ninja/recon:$LD_LIBRARY_PATH

# Loop through the values from -100 to 100, with an increment of 10
for i in $(seq -100 10 100)
do
  # Set the output file name
  output_file="/home/nu/itoshun/data/ninja/TrackMatch/trackMatch2023-12-4_zshift_$i.root"

  # Check if the file already exists
  if [ -f "$output_file" ]; then
    echo "File $output_file already exists. Skipping..."
  else
    # Execute the command with the current value of $i as the second-to-last argument
    /home/nu/itoshun/Programs/ninjarecon-master/bin/TrackMatch/TrackMatch \
    /home/nu/itoshun/data/ninja/HitConverter/hitConv2023-12-4.root \
    "$output_file" \
    $i 1
  fi
done