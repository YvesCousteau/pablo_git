# ---------------------------- # INIT
clear
for i in {16..51} {51..16} ; do echo -en "\e[48;5;${i}m \e[0m" ; done ; echo
make clean
make
for i in {16..51} {51..16} ; do echo -en "\e[48;5;${i}m \e[0m" ; done ; echo
error='\e[1;31;48;5;82m <-------Error--------> \e[0m'
success='\e[1;31;48;5;82m <-----Successful-----> \e[0m'
# test="cat main.c"
# test="cat shell.c > test.txt"
# test="cat < test.txt"
#test="ls -1 | sort -r | grep a | grep r"


#test="ls | sort -r"
#test="sleep 30 &"
#test="ls -1 | sort -r | grep a | grep r > out"
#test="grep a < command.c | grep e | wc > out"
#echo -$test
test="sleep 3 | ls"
echo "$test" | ./mishell
# ---------------------------- # TEST 1
# echo -e "\e[1;33mQuestion 1"
# test_1="python hello.py > /dev/null 2>&1"
# output=$(echo -e "$test_1" | ./mishell 1 | sed 's/^.*\(mishell(ಠ_ಠ) %\)//' | sed 's/^.*Selected//')
# echo $test_1
# echo $output
# if [ "$output" = "$test_1" ]; then
#     echo -e $success
# else
#     echo -e $error
# fi
# # ---------------------------- # TEST 2
# echo -e "\e[1;33mQuestion 2"
# test_2="python hello.py > /dev/null 2>&1"
# output=$(echo -e "$test_2" | ./mishell 2 | sed 's/^.*mishell(ಠ_ಠ) %//' | sed 's/^.*Selected//')
# echo $test_2
# echo $output
# if [ "${output}" = "$test_2" ]; then
#     echo -e $success
# else
#     echo -e $error
# fi
# # ---------------------------- # TEST 3
# echo -e "\e[1;33mQuestion 3"
# test_3="python hello.py > /dev/null 2>&1"
# output=$(echo -e "$test_3" | ./mishell 3 | sed 's/^.*mishell(ಠ_ಠ)//' | sed 's/^.*Selected//')
# echo $test_3
# echo $output
# if [ "${output}" = "$test_3" ]; then
#     echo -e $success
# else
#     echo -e $error
# fi
# ---------------------------- # TEST 4
# ---------------------------- # TEST 5
# ---------------------------- # TEST 6
# ---------------------------- # TEST 7
# ---------------------------- # TEST 8

for i in {16..51} {51..16} ; do echo -en "\e[48;5;${i}m \e[0m" ; done ; echo
