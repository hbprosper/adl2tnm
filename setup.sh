DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export PYTHONPATH=$DIR:$PYTHONPATH
export PATH=$DIR/bin:$PATH
export ADL2TNM_PATH=$DIR
cd treestream
source setup.sh
cd ..



