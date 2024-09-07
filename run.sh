#!/usr/bin/env bash
DIR="$(realpath $(dirname ${BASH_SOURCE[0]})/)"

files=($(ls -1 ${DIR}/img/*raw 2>/dev/null))
items=()
for file in ${files[@]}; do
	items+=($(echo "$(basename ${file})" | cut -d '_' -f1) \
		"$(echo "${file}" | cut -d'_' -f2)x$(echo "${file}" | cut -d'_' -f3)")
done
if [ ${#items[@]} -eq 0 ]; then
	echo "No file found"
	exit 1
fi
selected="$(realpath ${DIR}/img/$(whiptail --title "Pick a system image" \
	--menu "" 15 60 8 "${items[@]}" 3>&1 1>&2 2>&3))"

if [ "${selected}" == "${DIR}/img" ]; then
	echo "User abort"
	exit 1
fi

for (( i=0; i < ${#items[@]}; i+=3 )); do
	if [ "${items[i]}" == $(basename "${selected}") ]; then
		cols=$(echo "${items[i+1]}" | cut -d'x' -f1)
		rows=$(echo "${items[i+1]}" | cut -d'x' -f2)
		img="${selected}_${cols}_${rows}_raw"
		break
	fi
done

make -C sobel_sw
./sobel_sw/main ${img} ${cols} ${rows}
which octave && octave --eval "show(\"${img}\", ${cols}, ${rows})"
