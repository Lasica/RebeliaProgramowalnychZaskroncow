#PATH="$PATH:/sunflower/codes/scripts/"
alias wow="git status"
alias such="git"
alias very="git"
alias much="git"
alias suchastyle="git ls-files | egrep '.*\.(cpp|h|c)$' | xargs ~/prog/RPZ/repo/RebeliaProgramowalnychZaskroncow/scripts/astyle.sh"
alias commituj="suchastyle | git commit"
alias rebuild="make clean all"

# enable core dumps
ulimit -c unlimited
