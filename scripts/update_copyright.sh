#!/usr/bin/env sh

old_year=${1}
new_year=${2}

find . \
     \( -name "*.cmake" \
     -o -name "*.txt" \
     -o -name "*.?++" \
     -o -name "LICENSE" \) \
     -print | xargs sed -i "s/Copyright © 2017-${old_year} Ruben Van Boxem/Copyright © 2017-${new_year} Ruben Van Boxem/"
