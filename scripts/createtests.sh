 for i in $(find . -maxdepth 5 | egrep '.*\.(cpp|h)$'); do i=${i%.*}; i=${i##*/}; echo $i; cp ./test/TestTemplate.h ./tmp/$i.cpp; done 

