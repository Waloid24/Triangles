#/usr/bin/bash

root_dir="../../"
build_dir="${root_dir}build"
test_dir=""
green="\033[42m"
red="\033[41m"
default="\033[0m"

function Mkdir
{
    rm -r $1
    mkdir $1
}

function build_project
{
    cmake ${root_dir} -B ${build_dir} -DCMAKE_BUILD_TYPE=Debug

    cmake --build ${build_dir}

    cmake --install ${build_dir}
}

function run_tests
{
    n_tests=$1
    
    for ((i=0; i<${n_tests}; i++))
    do
        ${build_dir}/test/end_to_end/end_to_end_tests < tests/test_${i}.txt > results/result_${i}.txt
        if diff -Z "answers/answer_${i}.txt" "results/result_${i}.txt" > /dev/null
        then
            echo -e "${green}passed${default}"
        else
            echo -e "${red}failed${default}"
        fi
    done
}

n_tests=$1

if [[ $# -ne 1 ]]
then
    echo "The number of arguments for testing script should be equal to 1"
else
    Mkdir tests
    Mkdir answers
    Mkdir results

    build_project

    python3 generating_tests.py ${n_tests} tests
    python3 check_triangles_intersection.py ${n_tests} tests answers
    
    run_tests ${n_tests}

fi