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





=========================================================================================
==========================				pipex-tester						
=========================================================================================





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






=========================================================================================
==========================				PIPEX MEDIC							
=========================================================================================



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

infile1: "Hello World!\nHello World!\n"
< infile1 grep Hello | awk '{count++} END {print count}' > outfile1




const t_test errorTests[] = {
	{ ARGS("grep Hello", "wc -l"), DEFAULT_ENV, NULL },
	{ ARGS("grep Hello", "wc -l"), NULL_ENV, "Hello World!\n" },
	{ ARGS("fizzBuzz", "ls -la src/"), DEFAULT_ENV, "Hello World!\n" },
	{ ARGS("ls -la src/", "buzzFizz"), DEFAULT_ENV, "Hello World!\n" },
	{ ARGS("fizzBuzz", "wc -l"), NULL_ENV, "Hello World!\n" },
	{ ARGS("grep Hello", "buzzFizz"), NULL_ENV, "Hello World!\n" }
};


infile1: NULL
< infile1 grep Hello | wc -l > outfile1
./pipex infile1 "grep Hello" "wc -l" outfile1






const t_test multiple_commandTests[] = {
	{ ARGS("ls -la src/", "grep .c", "wc -l"), DEFAULT_ENV, "Hello World!\n" },
	{ ARGS("tr -d !", "grep -v !", "sed 's/Hello/Salut/g'"), DEFAULT_ENV, "Hello World!\nHello World!\nHello World!\nHello World!\nHello World!\n" },
	{ ARGS("tr -d !", "grep -v !", "sed 's/Hello/Salut/g'", "grep Salut", "wc -l"), DEFAULT_ENV, "Hello World!\nHello World!\nHello World!\nHello World!\nHello World!\n" }
};




infile1: Hello World!\n
< infile1 ls -la src/ | grep .c | wc -l > outfile1
./pipex infile1 "ls -la src/" "grep .c" "wc -l" outfile1



infile1: Hello World!\nHello World!\nHello World!\nHello World!\nHello World!\n
< infile1 tr -d ! | grep -v ! | sed 's/Hello/Salut/g' > outfile1
./pipex infile1 "tr -d !" "grep -v" "sed 's/Hello/Salut/g'" outfile1






=========================================================================================
===========================				fsoares								
=========================================================================================




TestCase(3, ['infile.txt', 'sed    "s/And/But/"', 'grep But', 'outfile.txt'],
		             'Normal parameters, commands with arguments, everything should go ok'),


< infile.txt sed "s/And/But/" | grep But > outfile.txt

./pipex infile.txt "sed "s/And/But/"" "grep But" outfile.txt









 TestCase(35, ['here_doc', '"EOF"', 'cat', 'cat -e', 'no_file.txt'],
					 "heredoc where output file does not exist",
					 input="teste\nsome_str\nEOF\n"),




./pipex here_doc EOF cat "cat -e" no_file

cat << EOF | cat -e >> no_file





./pipex here_doc EOF cat "grep PATH" "grep /usr" no_file

cat << EOF | grep PATH | grep /usr >> no_file






TestCase(36, ['here_doc', '""', 'cat', 'cat -e', 'outfile.txt'],
		             "heredoc with empty string, but multiple lines",
		             input="teste\nsome_str\n\n"),



./pipex here_doc "" cat "cat -e" outfile3

cat << "" | cat -e >> outfile3