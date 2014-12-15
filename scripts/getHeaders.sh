for i in $(find . | egrep '.*\.(h|hpp)$'); do i=${i}; i=${i#./}; echo $i;  done ;
