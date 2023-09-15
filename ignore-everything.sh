for file in $(find soh \( -path soh/assets -prune -or -path soh/soh/Enhancements/randomizer/3drando -prune \) -name "*.cpp" -or -name "*.hpp" -or -name "*.c" -or -name "*.h"); do
  cat format.off $file > $file.modified
  mv $file.modified $file
done
