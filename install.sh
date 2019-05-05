echo "installing..."
echo "STEP 1  rm -rf treestream"
rm -rf treestream
echo "        git clone https://github.com/hbprosper/treestream"
echo ""
git clone https://github.com/hbprosper/treestream

if [ -d "treestream" ]; then
    echo ""
    echo "STEP 2  cd treestream"
    cd treestream
    echo "        make"
    make
    
    if [ -f "lib/libtreestream.so" ] || [ -f "lib/libtreestream.dylib" ]; then
	echo ""
	echo "   installation SUCCESSFUL"
	echo ""
	cd -
    else
	echo
	echo "** oops! installation FAILED ** "
	echo
    fi
else
    echo
    echo "** oops! treestream download FAILED **"
    echo
fi




