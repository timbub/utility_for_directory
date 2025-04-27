#!/bin/bash
set -e

echo "Run the test..."

rm -rf test_dir
mkdir test_dir
mkdir -p test_dir/empty_dir
mkdir -p test_dir/dir1
touch test_dir/dir1/empty_file.txt

echo "text test" > test_dir/file1.txt
echo "ABCD 1285" > test_dir/file2.txt
echo "same content" > test_dir/dir1/file3.txt
echo "same content" > test_dir/dir1/file4.txt

./mangen test_dir > actual_manifest.txt

cat > expected_manifest.txt <<EOF
file1.txt : 72731435F2E11194
file2.txt : 726A7C91DA5CD9E9
dir1/empty_file.txt : 1505
dir1/file3.txt : 32760D12580F0A30
dir1/file4.txt : 32760D12580F0A30
EOF

if ! diff expected_manifest.txt actual_manifest.txt; then
    echo "test and the standard are different"
    exit 1
fi
echo "Tests passed"
exit 0
