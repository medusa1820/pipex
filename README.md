./pipex infile "ls -l" "wc -l" outfile
./pipex infile "kd -l" "wc -l" outfile
main()
1
2
127
126

assign_input()
4
5

./pipex infile "cat" "grep PATH" "grep usr/" "wc -c" outfile


< infile grep PATH | grep usr | wc -c | exit 5 >  outfile    

./pipex infile "grep PATH" "grep usr" "wc -c" "exit 5" outfile



< assets/deepthought.txt | grep Now | exit 5 | outs/test-$num.txt > outs/test-$num-tty.txt 2>&1






/**************/ this command redirects error to file errors:

./pipex infile "grep PATH" "wc -c" "exit 5" outfile > errors 2>&1

< infile grep PATH | wc -c | exit 5 > outfile > errors 2>&1





test 10

./pipex infile1 "grep PATH" "wc -c"  outfile > errors 2>&1
< infile1 grep PATH | wc -c >  outfile > errors 2>&1  






test 29

./pipex infile "grep Now" "$(which cat)" outfile > errors 2>&1

< infile grep Now | /bin/cat > outfile errors 2>&1




PIPEX MEDIC


test(testSubset, testIndex, commandList, envp, inputFileContent);


const t_test basicTests[] = {
        { ARGS("grep Hello", "wc -l"), DEFAULT_ENV, "Hello World!\n" },
        { ARGS("grep Hello", "wc -l"), DEFAULT_ENV, "Hello World!\nHello World!\nHello World!\nHello World!\nHello World!\n" },
        { ARGS("grep Hello", "ls -la src/"), DEFAULT_ENV, "Hello World!\n" },
        { ARGS("ls -la src/", "wc -l"), DEFAULT_ENV, "Hello World!\n" },
        { ARGS("grep Hello", "awk '{count++} END {print count}'"), DEFAULT_ENV, "Hello World!\nHello World!\n" },
        { ARGS("grep Hello", "awk \"{count++} END {print count}\""), DEFAULT_ENV, "Hello World!\nHello World!\n" },
        { ARGS("grep Hello", "awk '\"{count++} END {print count}\"'"), DEFAULT_ENV, "Hello World!\nHello World!\n" },
        { ARGS("grep Hello", "awk \"'{count++} END {print count}'\""), DEFAULT_ENV, "Hello World!\nHello World!\n" }
    };


(1) pipex-tester complete green passed (2) pipexMedic, basic tests: passed [1 - 4]