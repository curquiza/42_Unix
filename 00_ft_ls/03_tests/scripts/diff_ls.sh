DIR_FT_LS="/Users/curquiza/Documents/ft_ls"

ft_ls_output1="$DIR_FT_LS/03_tests/outputs/ft_ls_output1.txt"
ls_output1="$DIR_FT_LS/03_tests/outputs/ls_output1.txt"
ft_ls_output2="$DIR_FT_LS/03_tests/outputs/ft_ls_output2.txt"
ls_output2="$DIR_FT_LS/03_tests/outputs/ls_output2.txt"

./ft_ls $@ 1> $ft_ls_output1 2> $ft_ls_output2
ls -1 $@ 1> $ls_output1 2> $ls_output2
echo "\033[1;33mDIFF SORTIE STD\033[0m"
diff $ft_ls_output1 $ls_output1
echo "\033[1;33mDIFF SORTIE ERR\033[0m"
diff $ft_ls_output2 $ls_output2

#./ft_ls $@ 1> 03_tests/outputs/ft_ls_output1.txt 2>03_tests/outputs/ft_ls_output2.txt
#ls -1 $@ 1> 03_tests/outputs/ls_output1.txt 2>03_tests/outputs/ls_output2.txt
#echo "\033[1;33mDIFF SORTIE STD\033[0m"
#diff 03_tests/outputs/ft_ls_output1.txt 03_tests/outputs/ls_output1.txt
#echo "\033[1;33mDIFF SORTIE ERR\033[0m"
#diff 03_tests/outputs/ft_ls_output2.txt 03_tests/outputs/ls_output2.txt
