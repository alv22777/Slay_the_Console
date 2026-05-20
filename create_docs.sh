#!/bin/bash

echo "========================================"
echo "Generating repository documentation..."
echo "========================================"

# Clear old outputs first
rm -f All_code.txt
rm -f Commit_tree.txt
rm -f File_structure.txt




# ----------------------------------------
# 1. ALL CODE DUMP
# ----------------------------------------

echo "[1/4] Generating All_code.txt..."


find . -type f -name "*.cpp" |
while read file; do

    echo "========================================" >> ./Documentation/Code/All_code.txt
    echo "FILE: $file" >> ./Documentation/Code/All_code.txt
    echo "========================================" >> ./Documentation/Code/All_code.txt

    cat "$file" >> ./Documentation/Code/All_code.txt

    echo -e "\n\n" >> ./Documentation/Code/All_code.txt

done

# ----------------------------------------
# 2. COMMIT TREE
# ----------------------------------------

echo "[2/4] Generating Commit_tree.txt..."

git log --graph --oneline --decorate --all > ./Documentation/Code/Commit_tree.txt

# ----------------------------------------
# 3. FILE STRUCTURE
# ----------------------------------------

echo "[3/4] Generating File_structure.txt..."

find ./src ./include \
| awk -F/ '
{
    indent = ""
    for(i = 1; i<NF;i++){
        indent = indent "   "
    }
    print indent $NF
}
' > ./Documentation/Code/File_structure.txt

# ----------------------------------------
# 3. FULL COMMIT HISTORY
# ----------------------------------------

echo "[4/4] Generating history.txt..."

git log --stat -p > ./documentation/Code/history.txt
echo "========================================"
echo "Done!"
echo "========================================"