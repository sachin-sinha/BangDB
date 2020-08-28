ln -sf $PWD/lib/libdlib.so.19.20.0 /usr/local/lib/libdlib.so
ln -sf $PWD/lib/libmitie.so /usr/local/lib/libmitie.so
cp -r bangdb_udf /usr/local/include/
apt-get install liblapack-dev libblas-dev build-essential

	#
	# Setting up the core-pattern
	#
<< 'COMMENT'
	def_path_to_cores="/mnt/bangdb_core_mnt/cores/"
	if [ -d ${def_path_to_cores} ]
	then
		# core.<executable_name>.<pid>.<hostname>.<time_of_dump>
		echo "Updating the core-pattern file.. "
		echo "${def_path_to_cores}/core.%e.%p.%h.%t" | sudo tee /proc/sys/kernel/core_pattern &> /dev/null
	else
		# Using the current directory as the path for core
		def_path_to_cores=${PWD}
		# core.<executable_name>.<pid>.<hostname>.<time_of_dump>
		echo "Updating the core-pattern file.. "
		echo "${def_path_to_cores}/core.%e.%p.%h.%t" | sudo tee /proc/sys/kernel/core_pattern &> /dev/null
	fi
COMMENT
