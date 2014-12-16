if [ $# == 0 ]
then
	echo Usage: h - headers, c - cpp files, second argument t - filter tests
else
	filter=$1
	if [ "$filter" == 'h' ]; then
		filter='(h|hpp|hh)'
	else
		filter='(cpp|c|cxx|tpp)'
	fi

	egreparg='.*\.'$filter'$'
	if [ "$2" = 't' ]
	then
	toiter=$(find . | egrep $egreparg | sort -t '\0' | grep -v 'test'); 
	else
	toiter=$(find . | egrep $egreparg | sort -t '\0'); 
	fi

	for i in $toiter; do i=${i}; i=${i#./}; echo $i;  done ;
fi
