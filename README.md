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